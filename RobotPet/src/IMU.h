// Basic demo for accelerometer readings from Adafruit MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
float angle;

void initIMU() {
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
}

void imuTurnCounterClkWise(float targetAngle) {
  brakeM1();
  brakeM2();
  //Target angle in degrees
  targetAngle = targetAngle*100*PI/180;
  bool turnComplete = false;
  angle = 0;
  sensors_event_t a, g, temp;
  while(!turnComplete) {
    /* Get new sensor events with the readings */
    mpu.getEvent(&a, &g, &temp);
    angle = angle + (g.gyro.z)*2.1;
    Serial.println(angle);
    if (angle < targetAngle) {
      forwardM2(600);
    } else {
      brakeM1();
      brakeM2();
      Serial.println("Complete");
      turnComplete = true;
    }
    delay(21);
  }
}

void imuTurnClkWise(float targetAngle) {
  brakeM1();
  brakeM2();
  //Target angle in degrees to radians
  targetAngle = -targetAngle*100*PI/180;
  bool turnComplete = false;
  angle = 0;
  sensors_event_t a, g, temp;
  while(!turnComplete) {
    /* Get new sensor events with the readings */
    mpu.getEvent(&a, &g, &temp);
    angle = angle + (g.gyro.z)*2.1;
    Serial.println(angle);
    if (angle > targetAngle) {
      forwardM1(600);
    } else {
      brakeM1();
      brakeM2();
      Serial.println("Complete");
      turnComplete = true;
    }
    delay(21);
  }
}