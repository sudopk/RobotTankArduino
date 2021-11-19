#include <Arduino.h>
#include <Servo.h>

#include "tank_core.h"
#include "tank_drive.h"

namespace {
constexpr int kMinObstacleDistanceCm = 40; // Distance limit from obstacles.
constexpr int kServoAdjustDelayMs = 100; // Distance limit from obstacles.
}

void AdjustServo(Servo* servo) {
  for (int i = 0; i < 180; i++) {
    servo->write(i);
    delay(5);
  }
  for (int i = 180; i >= 0; i--) {
    servo->write(i);
    delay(5);
  }
  servo->write(90);
}

void LogDistance(TankState* state, long distance, const String& context) {
  Serial.print(context);
  Serial.print(" (cm): ");
  Serial.println(distance);
  state->bt_serial.print(context);
  state->bt_serial.print(" (cm): ");
  state->bt_serial.println(distance);
}

/******detection of ultrasonic distance******/
long CalculateDistanceInCm(TankState* state) {
  long distance;
  digitalWrite(SONIC_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(SONIC_TRIG, HIGH);
  delayMicroseconds(15);
  digitalWrite(SONIC_TRIG, LOW);
  distance = pulseIn(SONIC_ECHO, HIGH);
  distance = round(distance * 0.01657); // How far away is the object in cm.
  return distance;
}

/******auto avoid obstacles******/
void AutoAvoidance2(TankState* state) {
  auto servo = state->servo;
  servo.write(90);
  delay(kServoAdjustDelayMs);
  long distance = CalculateDistanceInCm(state);
  if (distance >= kMinObstacleDistanceCm) {
    GoAhead(50);
    return;
  }

  StopMotor();
  Beep();

  // Left
  servo.write(180);
  delay(kServoAdjustDelayMs);
  distance = CalculateDistanceInCm(state);

  if (distance >= kMinObstacleDistanceCm) {
    GoBack(50);
    TurnLeft(500);
    return;
  }

  // Right
  servo.write(0);
  delay(50);
  distance = CalculateDistanceInCm(state);

  if (distance >= kMinObstacleDistanceCm) {
    GoBack(50);
    TurnRight(500);
    return;
  }
}

/******auto avoid obstacles******/
void AutoAvoidance(TankState* state) {
  auto servo = state->servo;
  servo.write(90);
  delay(kServoAdjustDelayMs);
  long centerscanval = CalculateDistanceInCm(state);
  LogDistance(state, centerscanval, "Center");
    servo.write(120);
  delay(kServoAdjustDelayMs);
  long ldiagonalscanval = CalculateDistanceInCm(state);

    LogDistance(state, ldiagonalscanval, "Left 45");

  servo.write(60);
  delay(kServoAdjustDelayMs);
  long rdiagonalscanval = CalculateDistanceInCm(state);

    LogDistance(state, rdiagonalscanval, "Right 45");
  if (centerscanval >= kMinObstacleDistanceCm && ldiagonalscanval >= kMinObstacleDistanceCm && rdiagonalscanval >= kMinObstacleDistanceCm) {
    GoAhead(0);
    return;
  }
  StopMotor();
  Beep();

  servo.write(180);
  delay(kServoAdjustDelayMs);
  long leftscanval = CalculateDistanceInCm(state);
  LogDistance(state, leftscanval, "Left");
  if (leftscanval >= kMinObstacleDistanceCm) {
    GoBack(200);
    TurnLeft(1000);
    return;
  }

  servo.write(0);
  delay(kServoAdjustDelayMs);
  long rightscanval = CalculateDistanceInCm(state);
  LogDistance(state, rightscanval, "Right");
  if (rightscanval >= kMinObstacleDistanceCm) {
    GoBack(200);
    TurnRight(1000);
    return;
  }
  GoBack(1000);
}