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

const unsigned int M1_IN_1_CHANNEL = 8;
const unsigned int M1_IN_2_CHANNEL = 9;
const unsigned int M2_IN_1_CHANNEL = 10;
const unsigned int M2_IN_2_CHANNEL = 11;

const unsigned int M1_I_SENSE = 35;
const unsigned int M2_I_SENSE = 34;

const unsigned int PWM_VALUE = 1024; // Max PWM given 8 bit resolution

const int freq = 5000;
const int resolution = 10;

unsigned long myTime = 1; //time in milliseconds
unsigned long oldTime = 0;

int velocity1 = 0; //velocity 1
int velocity2 = 0; //velocity 2
int deltaTime = 0;

long enc1_value_old;
long enc2_value_old;

bool taskA = false;
bool taskB = false;
int task = 0;

void forwardM1(int speed) {
  ledcWrite(M1_IN_1_CHANNEL, speed);
  ledcWrite(M1_IN_2_CHANNEL, 0);
}

void forwardM2(int speed) {
  ledcWrite(M2_IN_1_CHANNEL, speed);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void brakeM1() {
  ledcWrite(M1_IN_1_CHANNEL, PWM_VALUE);
  ledcWrite(M1_IN_2_CHANNEL, PWM_VALUE);
}

void brakeM2() {
  ledcWrite(M2_IN_1_CHANNEL, PWM_VALUE);
  ledcWrite(M2_IN_2_CHANNEL, PWM_VALUE);
}

void backwardsM1(int speed) {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, speed);
}

void backwardsM2(int speed) {
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, speed);
}

void idle() {
  ledcWrite(M1_IN_1_CHANNEL, 0);
  ledcWrite(M1_IN_2_CHANNEL, 0);
  ledcWrite(M2_IN_1_CHANNEL, 0);
  ledcWrite(M2_IN_2_CHANNEL, 0);
}

void setup() {
  // Stop the right motor by setting pin 14 low
  // this pin floats high or is pulled
  // high during the bootloader phase for some reason
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  delay(100);

  Serial.begin(115200);
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

void loop() {
  delay(1000);
  // Create the encoder objects after the motor has
  // stopped, else some sort exception is triggered
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);  

  while(true) {
    long enc1_value = -enc1.read();
    long enc2_value = enc2.read();
    deltaTime = 200;
    velocity1 = enc1_value / deltaTime;
    velocity2 = enc2_value / deltaTime;


    switch (task) {
    case 0:
      //forward/
      Serial.print(enc1_value); Serial.print(" "); Serial.print(enc2_value);
      Serial.println();
      if (enc1_value <= 359) {
        forwardM1(500);
      } else if(taskA == false) {
        brakeM1();
        taskA = true;
      }

      if (enc2_value <= 359) {
        forwardM2(450);
      } else if(taskB == false) {
        brakeM2();
        taskB = true;
      }

      if (taskA && taskB) {
        task = 1;
      }
      break;
    case 1:
      Serial.println("Start pause");
      brakeM1();
      brakeM2();
      delay(5000);
      taskA = false;
      taskB = false;
      Serial.println("End pause");
      task = 2;
      break;
    case 2:
      //backwards
      Serial.print(enc1_value); Serial.print(" "); Serial.print(enc2_value);
      Serial.println();
      if (enc1_value > 1) {
        backwardsM1(500);
      } else if(taskA == false) {
        brakeM1();
        taskA = true;
      }
      if (enc2_value > 1) {
        backwardsM2(450);
      } else if(taskB == false) {
        brakeM2();
        taskB = true;
      }
      if (taskA && taskB) {
        Serial.println("Finished");
        task = 4;
      }
      break;
    case 4:
      brakeM1();
      brakeM2();
      break;
    }


    if (enc1_value != enc1_value_old) {
      enc1_value_old = enc1_value;
    }
    if (enc2_value != enc2_value_old) {
      enc2_value_old = enc2_value;
    }

  }
}
