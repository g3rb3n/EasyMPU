#ifndef _EASYMPU_H_
#define _EASYMPU_H_

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h"
//#include "helper_3dmath.h"
template <typename T>
struct Point {
  T x;
  T y;
  T z;
};

class EasyMPU {
public:
  uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
  volatile bool interrupt;
private:
  void (*fp)();
  int interruptPin;
  int range;
  
  MPU6050 mpu;
  bool dmpReady = false;  // set true if DMP init was successful
  uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
  uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
  uint16_t fifoCount;     // count of all bytes currently in FIFO
  uint8_t fifoBuffer[64]; // FIFO storage buffer

  // orientation/motion vars
  Quaternion q;           // [w, x, y, z]         quaternion container
  VectorInt16 aa;         // [x, y, z]            accel sensor measurements
  VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
  VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
  VectorFloat gravity;    // [x, y, z]            gravity vector
  float euler[3];         // [psi, theta, phi]    Euler angle container
  float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
  
public:
  EasyMPU(int interruptPin, int range);
  ~EasyMPU();
  bool setup();
  bool handle();
  void setInterrupt(void (*fp)());
  Point<float> acceleration();

private:  
  float dmpToG(int dmp);
};

#endif