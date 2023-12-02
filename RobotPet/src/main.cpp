#include <Arduino.h>
#include <PID_v1.h>
#include "ADC.h"
#include "motorController.h"
#include "IMU.h"
#include "WiFiServer.h"
#include "buzzer.h"

char task = 0;
//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
double Kp=15, Ki=7, Kd=2;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// STate machine
bool roaming = false;


void setup() {
  Serial.begin(115200);
  initADC();
  initMotorController();
  initIMU();
  initWIFI();
  initBuzzer();
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
  //Main switch case/state machine
  if (readWIFI() > 0) {
    Serial.printf("Received command: %s\n", incomingPacket);
    task = incomingPacket[0];
  } else if (task == 'R') {
    roaming = true;
  } else {
    roaming = false;
    task = 0;
  }
  switch(task) {
    //Default
    default:
      idle();
      break;
  
    //Find audio cue
    case 'A':
      Serial.printf("Audio cue\n");
      jingleHeardSound(100);
      break;
    //Look for human
    case 'H':
      Serial.printf("Look for human\n");
      jingleSearch(100);
      break;
    //Chase after ball
    case 'C':
      Serial.printf("Chase after ball\n");
      jingleSearch(100);
      break;
    
    //Actions
    //Roam
    case 'R':
      if (roaming == false) {
        Serial.printf("Roam\n");
        jingleRoam(150);
        roaming = true;
      }
      // Check for obstacles
      readADC();
      forwardM1(400);
      forwardM2(400);
      //Turn around
      if (avgVal >= 4.5 && avgVal <= 8.5) {
          backwardsM1(500);
          backwardsM2(500);
          delay(200);
          forwardM1(400);
          backwardsM2(400);
      }
      //steer right
      if (avgVal < 4.5) {
          forwardM1(400);
          backwardsM2(400);
      }
      //steer left
      if (avgVal > 8.5) {
          backwardsM2(400);
          forwardM2(400);
      }
      break;

    //Sleep, do nothing until it reaceives next action
    case 'S':
      Serial.printf("Sleep\n");
      jingleSleep(200);
      idle();
      break;
    //Eat
    case 'E':
      Serial.printf("Eat\n");
      // Sounds super cool for some reason at delay of 10
      myChirp(1);
      backwardsM1(400);
      backwardsM2(400);
      myChirp(2);
      forwardM1(400);
      forwardM2(400);
      myChirp(1);
      brakeM1();
      brakeM2();
      myChirp(8);
      break;
    //Dance
    case 'D':
      Serial.printf("Dance\n");
      forwardM1(400);
      backwardsM2(400);
      jingleDance(200);
      idle();
      backwardsM1(400);
      forwardM2(200);
      jingleDance(200);
      idle();
      forwardM1(400);
      backwardsM2(400);
      jingleDance(200);
      brakeM1();
      brakeM2();
      break;
    //Stop
    case 'X':
      Serial.printf("Stop\n");
      jingleStop();
      break;
    
    //Movement Commands
    //Move Forwards
    case '8':
      Serial.printf("Forwards\n");
      jingleMove(100);
      delay(100);
      forwardM1(400);
      forwardM2(400);
      delay(1000);
      brakeM1();
      brakeM2();
      break;
    //Move Backwards
    case '2':
      Serial.printf("Backwards\n");
      jingleMove(100);
      delay(100);
      backwardsM1(400);
      backwardsM2(400);
      delay(1000);
      brakeM1();
      brakeM2();
      break;
    //Turn left
    case '6':
      Serial.printf("Turn left\n");
      jingleMove(100);
      delay(100);
      imuTurnN90();
      break;
    //Turn Right
    case '4':
      Serial.printf("Turn right\n");
      jingleMove(100);
      delay(100);
      imuTurn90();
      break;
  }
}