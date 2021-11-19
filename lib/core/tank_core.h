#ifndef LIB_CORE_CORE_H_
#define LIB_CORE_CORE_H_

#include<Servo.h>
#include <SoftwareSerial.h>

/******************Define L298N Dual H-Bridge Motor Controller Pins******************/
#define IN1  8    //K1、K2 motor direction
#define IN2  9    //K1、K2 motor direction
#define IN3  10    //K3、K4 motor direction
#define IN4  12   //K3、K4 motor direction
#define ENA  5    // Needs to be a PWM pin to be able to control motor speed ENA
#define ENB  6    // Needs to be a PWM pin to be able to control motor speed ENB

#define SERVO 11  //servo(SG90) connect to D11
#define SONIC_TRIG    A2  // Ultrasonic Trig pin
#define SONIC_ECHO    A3 // Ultrasonic Echo pin

#define LED1 2  //lefe led connect to D2
#define LED2 3  //right led connect to D3

#define IRPIN  13 //IR receiver Signal pin connect to Arduino pin 13

#define BUZZER  16

#define IR_ADVANCE       0x00FF18E7       //code from IR controller "▲" button
#define IR_BACK          0x00FF4AB5       //code from IR controller "▼" button
#define IR_RIGHT         0x00FF5AA5       //code from IR controller ">" button
#define IR_LEFT          0x00FF10EF       //code from IR controller "<" button
#define IR_SERVO         0x00FF38C7       //code from IR controller "OK" button
#define IR_OPENLED       0x00FFB04F       //code from IR controller "#" button
#define IR_CLOSELED      0x00FF6897       //code from IR controller "*" button
#define IR_BEEP          0x00FF9867       //code from IR controller "0" button

enum class TankCommand {
  kNone,
  kGoForward,
  kGoBack,
  kGoLeft,
  kGoRight,
  kMoveServo,
  kSwitchOnLight,
  kSwitchOffLight,
  kBlowHorn,
  kAutoAvoidance,
};

struct TankState {
  Servo servo{};
  bool auto_avoidance_mode = false;
  // Only RX pins is used. TX is some arbitrary value.
  SoftwareSerial bt_serial = SoftwareSerial(4, 7); // RX, TX
  TankCommand last_ir_command = TankCommand::kNone;
  unsigned long command_start_time = 0; // Arduino millis();
};

#endif // LIB_CORE_CORE_H_
