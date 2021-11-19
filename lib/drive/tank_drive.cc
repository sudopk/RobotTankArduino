#include <Arduino.h>

#include "tank_core.h"
#include "tank_servo.h"

/*motor control*/
void GoAhead(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(t);
}

void GoBack(int t) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(t);
}

void StopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void TurnLeft(int t) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(t);
}

void TurnRight(int t) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(t);
}

/*set motor speed */
void SetMotorSpeed(int lspeed, int rspeed) {
  analogWrite(ENA, lspeed);
  analogWrite(ENB, rspeed);
}
/*******control led*******/
void open_led(int led_num) {
  if (led_num == 1) digitalWrite(LED1, LOW);
  else digitalWrite(LED2, LOW);
}

void CloseLed(int led_num) {
  if (led_num == 1) digitalWrite(LED1, HIGH);
  else digitalWrite(LED2, HIGH);
}

/*******control buzzer*******/
void Beep() {
  digitalWrite(BUZZER, LOW);
  delay(100);
  digitalWrite(BUZZER, HIGH);
}

void LogCurrentAndLastCommand(const TankCommand& command, TankState* state) {
  Serial.print("Current command: ");
  Serial.print(static_cast<int>(command));
  Serial.print(", last value: ");
  Serial.println(static_cast<int>(state->last_ir_command));
}

void RunTankCommand(const TankCommand& command, TankState* state) {
  switch (command) {
    case TankCommand::kGoForward: {
      GoAhead(10);
      state->command_start_time = millis();
      break;
    }
    case TankCommand::kGoBack: {
      GoBack(10);
      state->command_start_time = millis();
      break;
    }
    case TankCommand::kGoLeft: {
      TurnLeft(10);
      state->command_start_time = millis();
      break;
    }
    case TankCommand::kGoRight: {
      TurnRight(10);
      state->command_start_time = millis();
      break;
    }
    case TankCommand::kMoveServo: {
      AdjustServo(&state->servo);
      state->command_start_time = millis();
      break;
    }
    case TankCommand::kSwitchOnLight: {
      open_led(1);
      open_led(2);
      break;
    }
    case TankCommand::kSwitchOffLight: {
      CloseLed(1);
      CloseLed(2);
      break;
    }
    case TankCommand::kBlowHorn: {
      Beep();
      break;
    }
    default: break;
  }
}

void StopMotorOnTimeout(TankState* state) {
  // Keep current moving mode for some time.
  if (millis() - state->command_start_time >= 200) {
    state->command_start_time = millis();
    StopMotor();
  }
}
