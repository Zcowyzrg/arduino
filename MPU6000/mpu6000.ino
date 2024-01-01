// Uses MPU6x00 library from https://github.com/simondlevy/MPU6x00
// Uses Robogaia shield with MPU6000 in SPI mode
// Shield layout, connected to Arduino Micro:
// [. upper 8]         [upper 6 .]
// [.]                         [.]
// [.]                         [.]
// [CS]    -- PIN7    GND -- [GND]
// [SDA/SDI] -- MO             [.]
// [AD0/SDO] -- MI    3V3 -- [3V3]
// [SCLK]   -- SCK             [.]
// [.]
// [.]

#include "mpu6x00.h"

#define CS_PIN 7
static char led_state = 0;
static Mpu6000 imu = Mpu6000(CS_PIN);
static bool imu_ok = false;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  imu_ok = imu.begin();
}

void loop()
{
  float gyro_x = 0, gyro_y = 0, gyro_z = 0;
  float accel_x = 0, accel_y = 0, accel_z = 0;
  digitalWrite(LED_BUILTIN, led_state ? HIGH : LOW);

  if (imu_ok) {
    imu.readSensor();
    imu.getGyro(gyro_x, gyro_y, gyro_z);
    imu.getAccel(accel_x, accel_y, accel_z);
  }

  if (Serial && Serial.availableForWrite() > 0) {
    if (!imu_ok) {
      Serial.println("IMU error");
      delay(1000);
    } else {
      //Serial.print(gyro_x);
      //Serial.print(' ');
      //Serial.print(gyro_y);
      //Serial.print(' ');
      //Serial.print(gyro_z);
      Serial.print(accel_x);
      Serial.print(' ');
      Serial.print(accel_y);
      Serial.print(' ');
      Serial.print(accel_z);
      Serial.println();
    }
  }
  led_state ^= 1;
  delay(50);
}
