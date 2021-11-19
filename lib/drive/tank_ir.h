#ifndef LIB_DRIVE_TANK_IR_H_
#define LIB_DRIVE_TANK_IR_H_

#include<IRremoteInt.h> // https://githubmemory.com/repo/Arduino-IRremote/Arduino-IRremote/issues/805

TankCommand ReadCommandFromIr(IRrecv* ir, TankState* state);

#endif //LIB_DRIVE_TANK_IR_H_
