#include <Arduino.h>

#include "tank_core.h"

// WiFi / Bluetooth through the serial control.
TankCommand ReadCommandFromBt(TankState* state) {
  auto cmd = state->bt_serial.readStringUntil('\n');
  if (cmd.length() > 0) {
    Serial.print("Bt cmd: ");
    Serial.println(cmd);
  }
  if (cmd == "up") {
    return TankCommand::kGoForward;
  } else if (cmd == "down") {
    return TankCommand::kGoBack;
  } else if (cmd == "left") {
    return TankCommand::kGoLeft;
  } else if (cmd == "right") {
    return TankCommand::kGoRight;
  } else if (cmd == "lon") {
    return TankCommand::kSwitchOnLight;
  } else if (cmd == "loff") {
    return TankCommand::kSwitchOffLight;
  } else if (cmd == "horn") {
    return TankCommand::kBlowHorn;
  } else if (cmd == "servo") {
    return TankCommand::kMoveServo;
  } else if (cmd == "auto") {
    return TankCommand::kAutoAvoidance;
  }
  return TankCommand::kNone;
}