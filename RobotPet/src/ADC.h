#include <Arduino.h>
#include <Adafruit_MCP3008.h>

Adafruit_MCP3008 adc1;
Adafruit_MCP3008 adc2;

const unsigned int ADC_1_CS = 2;
const unsigned int ADC_2_CS = 17;

//global variables
int adc1_buf[8];
int adc2_buf[8];
float avgVal = 0;
int trueVal = 0;
int threshold = 700; // threshold value for light and dark

void initADC() {
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  delay(100);
  adc1.begin(ADC_1_CS);  
  adc2.begin(ADC_2_CS);
}

void readADC() {
  avgVal = 0;
  trueVal = 0;
  for (int i = 0; i < 8; i++) {
    adc1_buf[i] = adc1.readADC(i);
    adc2_buf[i] = adc2.readADC(i);

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
  if (trueVal > 0) {
    avgVal = float(avgVal / (float)trueVal);
  }
  Serial.println(avgVal);
}