#Synopsis
A quick and dirty wrapper around the MPU6050 library.

# Example
```c++

#include "EasyMPU.h"

#define INTERRUPT_PIN D6
#define MPU6050_ACCEL_FS_2 0x00

EasyMPU mpu(INTERRUPT_PIN, MPU6050_ACCEL_FS_2);

void dmpDataReady() {
    mpu.interrupt = true;
}

void setup() {
  mpu.setup();
  Serial.begin(230400);
  mpu.setInterrupt(dmpDataReady);
}

void loop() {
  if (mpu.handle()){
    Point<float> p = mpu.acceleration();
    Serial.printf("%5.3f %5.3f %5.3f\n", p.x, p.y, p.z);
  }
}
```