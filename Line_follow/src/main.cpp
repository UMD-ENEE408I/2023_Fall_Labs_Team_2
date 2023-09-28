#include <Arduino.h>
#include <Encoder.h>
#include <Adafruit_MCP3008.h>

Adafruit_MCP3008 adc1;
Adafruit_MCP3008 adc2;

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

int velocity1 = 0; //velocity 1
int velocity2 = 0; //velocity 2
int deltaTime = 0;

long enc1_value_old;
long enc2_value_old;

bool taskA = false;
bool taskB = false;
int task = 0;
int line_avg = 0;

const unsigned int ADC_1_CS = 2;
const unsigned int ADC_2_CS = 17;

int adc1_buf[8];
int adc2_buf[8];
float avgVal = 0;
int trueVal = 0;

int threshold = 700; // threshold value for light and dark

void readADC() {
  avgVal = 0;
  trueVal = 0;
  for (int i = 0; i < 8; i++) {

    //adc1_buf[i] = adc1.readADC(i);
    //adc2_buf[i] = adc2.readADC(i);
    /*
    if (i<7) {
      if (adc1_buf[i] > threshold) {
      } else {
        avgVal += (i*2) + 1;
        trueVal += 1;
      }
    }

    if (i<6) {
      if (adc2_buf[i] > threshold) {
      } else {
        avgVal += (i*2) + 2;
        trueVal += 1;
      }
    }
  }
  /*if (trueVal > 0) {
    avgVal = avgVal / (float)trueVal;
  }
  Serial.print(avgVal);*/
  }
}

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
  delay(2000);
  // Create the encoder objects after the motor has
  // stopped, else some sort exception is triggered
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);
  readADC();

  while(true) {
    //long enc1_value = -enc1.read();
    //long enc2_value = enc2.read();

    switch (task) {
    case 0:
      //readADC();
      break;
      //follow line
      //readADC();
      //straight
      /*
      if (avgVal >= 4.5 && avgVal <= 8.5) {
          forwardM1(500);
          forwardM2(500);
      }
      //right
      if (avgVal < 4.5) {
          forwardM1(600);
          forwardM2(400);
      }
      //left
      if (avgVal > 8.5) {
          forwardM1(400);
          forwardM2(600);
      }
      break;
    case 1:
      brakeM1();
      brakeM2();
    }


    if (enc1_value != enc1_value_old) {
      enc1_value_old = enc1_value;
    }
    if (enc2_value != enc2_value_old) {
      enc2_value_old = enc2_value;
    }*/
  }
  }
}
