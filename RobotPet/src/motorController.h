#include <Arduino.h>
#include <Encoder.h>
const unsigned int M1_ENC_A = 39;
const unsigned int M1_ENC_B = 38;
const unsigned int M2_ENC_A = 37;
const unsigned int M2_ENC_B = 36;

const unsigned int M1_IN_1 = 13;
const unsigned int M1_IN_2 = 12;
const unsigned int M2_IN_1 = 25;
const unsigned int M2_IN_2 = 14;

const unsigned int M1_IN_1_CHANNEL = 0;
const unsigned int M1_IN_2_CHANNEL = 1;
const unsigned int M2_IN_1_CHANNEL = 2;
const unsigned int M2_IN_2_CHANNEL = 3;

const unsigned int M1_I_SENSE = 35;
const unsigned int M2_I_SENSE = 34;

const unsigned int PWM_VALUE = 512; // Do not give max PWM. Robot will move fast

const int freq = 5000;
const int resolution = 10;

bool taskA = false;
bool taskB = false;

void initMotorController() {
  ledcSetup(M1_IN_1_CHANNEL, freq, resolution);
  ledcSetup(M1_IN_2_CHANNEL, freq, resolution);
  ledcSetup(M2_IN_1_CHANNEL, freq, resolution);
  ledcSetup(M2_IN_2_CHANNEL, freq, resolution);

  ledcAttachPin(M1_IN_1, M1_IN_1_CHANNEL);
  ledcAttachPin(M1_IN_2, M1_IN_2_CHANNEL);
  ledcAttachPin(M2_IN_1, M2_IN_1_CHANNEL);
  ledcAttachPin(M2_IN_2, M2_IN_2_CHANNEL);

  pinMode(M1_I_SENSE, INPUT);
  pinMode(M2_I_SENSE, INPUT);
}

void forwardM1(int speed) {
  ledcWrite(M1_IN_1_CHANNEL, speed);
  ledcWrite(M1_IN_2_CHANNEL, 0);
}

void forwardM2(int speed) {
  ledcWrite(M2_IN_1_CHANNEL, speed);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void backwardsM1(int speed) {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, speed);
}

void backwardsM2(int speed) {
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, speed);
}

void brakeM1() {
  ledcWrite(M1_IN_1_CHANNEL, PWM_VALUE);
  ledcWrite(M1_IN_2_CHANNEL, PWM_VALUE);
}

void brakeM2() {
  ledcWrite(M2_IN_1_CHANNEL, PWM_VALUE);
  ledcWrite(M2_IN_2_CHANNEL, PWM_VALUE);
}

void idle() {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, 0);
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void turnRight90(Encoder E1, Encoder E2) {
  long enc1_value = 0;
  long enc2_value = 0;
  while(!taskA) {
    enc1_value = -E1.read();
    enc2_value = E2.read();
    if (enc2_value >= -359) {
      backwardsM2(200);
    } else if(taskA == false) {
      brakeM2();
      taskA = true;
    }
    Serial.print(enc1_value); Serial.print(" "); Serial.print(enc2_value);
    Serial.println();
  } 
  taskA = false;
}

void turnLeft90(Encoder E1, Encoder E2) {
  long enc1_value = 0;
  long enc2_value = 0;
  while(!taskA) {
    enc1_value = -E1.read();
    enc2_value = E2.read();
    if (enc1_value >= -359) {
      backwardsM1(200);
    } else if(taskA == false) {
      brakeM1();
      taskA = true;
    }
    Serial.print(enc1_value); Serial.print(" "); Serial.print(enc2_value);
    Serial.println();
  }
  taskA = false;
}