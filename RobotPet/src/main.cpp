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
//PID values for searching movement
double Kp=1, Ki=0.04, Kd=0.10;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// State machine, states that lock in
bool roaming = false;
bool searching = false;
bool sleeping = false;
int targetX = 0;
int targetSize = 0;
int targetXCenter = 128;

void setup() {
  Serial.begin(115200);
  initADC();
  initMotorController();
  initIMU();
  initWIFI();
  initBuzzer();
  jingleDance(100);
  Input = targetXCenter;
  Setpoint = targetXCenter;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-200,200);
  myPID.SetTunings(Kp,Ki,Kd);
  delay(1000);
}

// Size is the size to approach
int approach(int goalSize, int goalXMargin) {
  //PID input
  Input = targetX;
  if (searching == false) {
    Serial.printf("initialize search\n");
    jingleSearch(100);
    searching = true;
  }
  Serial.printf("TargetX: %d TargetSize: %d\n", targetX, targetSize);
  if (targetX >= targetXCenter-goalXMargin && targetX <= targetXCenter+goalXMargin) {
    if(targetSize <= goalSize) {
      forwardM1((500)*1.2);
      forwardM2((500));
    } else {
      // Found Target
      return(1);
    }
    myPID.Compute();
    return 0;
  }
  if (targetX <= 0) {
    Input = targetXCenter;
    idle();
  }
  if (Output >= -15 && Output <= 15) {
    idle();     
  }
  //hard right
  if (Output < 0) {
    Serial.printf("Turning right towards target!\n");
    forwardM1((250-Output)*1.2);
    backwardsM2(250-Output);
  }
  //hard left
  if (Output > 0) {
    Serial.printf("Turning left towards target!\n");
    backwardsM1((250+Output)*1.2);
    forwardM2(250+Output);
  }
  //Approach
  myPID.Compute();
  Serial.printf("Output: %d\n", Output); 
  return 0;
}

void loop() {
  //Encoder enc1(M1_ENC_A, M1_ENC_B);
  //Encoder enc2(M2_ENC_A, M2_ENC_B); 

  //Check for input from client
  //Main switch case/state machine
  if (readWIFI() > 0) {
    Serial.printf("Received command: %c\n", incomingPacket[0]) + Serial.printf("Received X: %d\n", incomingPacket[1]) + Serial.printf("Received command: %d\n", incomingPacket[2]);
    task = incomingPacket[0];
    targetX = incomingPacket[1];
    targetSize = incomingPacket[2];
  } else if (task == 'R' || 'C' || 'H' || 'A') {
    roaming = true;
    searching = true;
  } else {
    roaming = false;
    searching = false;
    task = 0;
  }
  // For testing set state
  // task = 'H';
  switch(task) {
    //Default
    default:
      idle();
      break;
  
    //Find audio cue
    case 'A':
      Serial.printf("Audio cue\n");
      //jingleHeardSound(100);
      break;
    //Look for human
    case 'H':
      if (approach(200, 60) == true) {
        idle();
        jingleFoundHuman(100);
      }
      break;
    //Chase after ball
    case 'C':
      if (approach(180, 70) == true) {
        forwardM1(500);
        forwardM2(500);
        delay(500);
        jingleFoundHuman(100);
      }
      break;
    
    //Actions
    //Roam
    case 'R':
      Serial.printf("Roaming: ");
      if (roaming == false) {
        Serial.printf("initialize roam\n");
        jingleRoam(150);
        roaming = true;
      }
      //Check for obstacles
      //follow line
      readADC();
      if (trueVal > 1) {
        // Turn around
        if (avgVal >= 5.5 && avgVal <= 7.5) {
          Serial.printf("Turn Around\n");
          backwardsM1(350*1.2);
          backwardsM2(350);
          delay(1000);
          imuTurnClkWise(45);
        }
        //hard right
        if (avgVal < 5.5) {
          Serial.printf("Right\n");
          brakeM1();
          forwardM2(300);
        }
        //hard left
        if (avgVal > 7.5) {
          Serial.printf("Left\n");
          forwardM1(300*1.2);
          brakeM2();
        }
      } else{
        Serial.printf("Forward\n");
        forwardM1(350*1.2);
        forwardM2(350);
      }
      break;

    //Sleep, do nothing until it reaceives next action
    case 'S':
      if (sleeping == false) {
        Serial.printf("Sleeping\n");
        idle();
        jingleSleep(200);
        sleeping = true;
      }
      idle();
      break;
    //Eat
    case 'E':
      Serial.printf("Eat\n");
      // Sounds super cool for some reason at delay of 10
      myChirp(1);
      forwardM1(400*1.2);
      forwardM2(400);
      myChirp(1);
      backwardsM1(400*1.2);
      backwardsM2(400);
      myChirp(1);
      brakeM1();
      brakeM2();
      myChirp(8);
      break;
    //Dance
    case 'D':
      Serial.printf("Dance\n");
      forwardM1(300*1.2);
      backwardsM2(400);
      jingleDance(200);
      idle();
      backwardsM1(400*1.2);
      forwardM2(400);
      jingleDance(200);
      idle();
      forwardM1(400*1.2);
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
      forwardM1(600);
      forwardM2(600);
      delay(1000);
      brakeM1();
      brakeM2();
      break;
    //Move Backwards
    case '2':
      Serial.printf("Backwards\n");
      jingleMove(100);
      delay(100);
      backwardsM1(600);
      backwardsM2(600);
      delay(1000);
      brakeM1();
      brakeM2();
      break;
    //Turn left
    case '6':
      Serial.printf("Turn left\n");
      jingleMove(100);
      delay(100);
      imuTurnCounterClkWise(45);
      break;
    //Turn Right
    case '4':
      Serial.printf("Turn right\n");
      jingleMove(100);
      delay(100);
      imuTurnClkWise(45);
      break;
  }
}