#ifndef LIB_DRIVE_TANK_DRIVE_H_
#define LIB_DRIVE_TANK_DRIVE_H_

void CloseLed(int led_num);

void SetMotorSpeed(int lspeed, int rspeed);

void GoAhead(int t);
void GoBack(int t);
void StopMotor();
void TurnLeft(int t);
void TurnRight(int t);

void Beep();

void RunTankCommand(const TankCommand& command, TankState* state);
void StopMotorOnTimeout(TankState* state);

#endif //LIB_DRIVE_TANK_DRIVE_H_
