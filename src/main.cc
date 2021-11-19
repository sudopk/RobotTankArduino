#include <IRremote.h>

#include "tank_bt.h"
#include "tank_core.h"
#include "tank_drive.h"
#include "tank_ir.h"
#include "tank_servo.h"

TankState state{};
IRrecv IR(IRPIN);  //   IRrecv object  IR get code from IR remoter

void setup() {
  state.bt_serial.begin(9600);
  state.bt_serial.setTimeout(50);
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  state.servo.attach(SERVO);
  CloseLed(1), CloseLed(2); //close led
  digitalWrite(BUZZER, HIGH);//close buzzer
  pinMode(IRPIN, INPUT);
  digitalWrite(IRPIN, HIGH);
  IR.enableIRIn();
  SetMotorSpeed(255, 215); // 0 is min speed, 255 is max speed.
  StopMotor();
}

void loop() {
  auto command = ReadCommandFromBt(&state);
  if (command == TankCommand::kNone) {
    command = ReadCommandFromIr(&IR, &state);
  }
  if (command == TankCommand::kAutoAvoidance) {
    state.auto_avoidance_mode = !state.auto_avoidance_mode;
  }
  if (state.auto_avoidance_mode) {
    AutoAvoidance(&state);
  } else {
    RunTankCommand(command, &state);
    StopMotorOnTimeout(&state);
  }
}
