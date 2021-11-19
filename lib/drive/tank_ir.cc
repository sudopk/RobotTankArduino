#include <Arduino.h>
#include <IRremoteInt.h>

#include "tank_core.h"


/**************detect IR code***************/
TankCommand ReadCommandFromIr(IRrecv* ir, TankState* state) {
  decode_results results{};
  if (!ir->decode(&results)) {
    return TankCommand::kNone;
  }

  TankCommand command = TankCommand::kNone;
  Serial.print("IR code: ");
  Serial.println(results.value, HEX);
  if (results.value == IR_ADVANCE) {
    command = TankCommand::kGoForward;
  } else if (results.value == IR_RIGHT) {
    command = TankCommand::kGoRight;
  } else if (results.value == IR_LEFT) {
    command = TankCommand::kGoRight;
  } else if (results.value == IR_BACK) {
    command = TankCommand::kGoBack;
  } else if (results.value == IR_SERVO) {
    command = TankCommand::kMoveServo;
  } else if (results.value == IR_OPENLED) {
    command = TankCommand::kSwitchOnLight;
  } else if (results.value == IR_CLOSELED) {
    command = TankCommand::kSwitchOffLight;
  } else if (results.value == IR_BEEP) {
    command = TankCommand::kBlowHorn;
  } else if (results.value == 0xFFFFFFFF) {
    Serial.print("Last drive number: ");
    Serial.println(static_cast<int>(state->last_ir_command));
    command = state->last_ir_command;
  }
  state->last_ir_command = command;
  results.value = 0;
  ir->resume();

  return command;
}
