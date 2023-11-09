#include <Arduino.h>
#include <PID_v1.h>
#include "ADC.h"
#include "motorController.h"
#include "IMU.h"
#include "WiFiServer.h"

char task = 0;
//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
double Kp=15, Ki=7, Kd=2;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup() {
  Serial.begin(115200);
  initADC();
  initMotorController();
  initIMU();
  initWIFI();
  Input = 0;
  Setpoint = 6.5;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-150,150);
  myPID.SetTunings(Kp,Ki,Kd);
  delay(1000);
}

void loop() {
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B); 

  //Check for input from client
  readWIFI();

  //Main switch case/state machine
  Serial.printf("Received command: %s\n", incomingPacket);
  task = incomingPacket[0];
  switch(task) {
    //Default
    default:
      idle();
      break;
  
    //Find audio cue
    case 'A':
      Serial.printf("Audio cue\n");
      break;
    //Look for human
    case 'H':
      Serial.printf("Look for human\n");
      break;
    //Chase after ball
    case 'C':
      Serial.printf("Chase after ball\n");
      break;
    
    //Actions
    //Roam
    case 'R':
      Serial.printf("Roam\n");
      break;
    //Sleep, do nothing until it reaceives next action
    case 'S':
      Serial.printf("Sleep\n");
      idle();
      break;
    //Eat
    case 'E':
      Serial.printf("Eat\n");
      break;
    //Dance
    case 'D':
      Serial.printf("Dance\n");
      break;
    
    //Movement Commands
    //Move Forwards
    case '^':
      Serial.printf("Forwards\n");
      forwardM1(300);
      forwardM2(300);
      delay(1000);
      brakeM1();
      brakeM2();
      break;
    //Move Backwards
    case '_':
      Serial.printf("Backwards\n");
      backwardsM1(300);
      backwardsM2(300);
      delay(1000);
      brakeM1();
      brakeM2();
      break;
    //Turn left
    case '<':
      Serial.printf("Turn left\n");
      imuTurnN90();
      break;
    //Turn Right
    case '>':
      Serial.printf("Turn right\n");
      imuTurn90();
      break;
  }
}