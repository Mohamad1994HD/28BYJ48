#ifndef MT
#define MT

#include "Arduino.h"

enum rotation_status {CCW, CW, STOP};
typedef  long (*calc_function) (long);

class BaseMotor{
protected:
  uint8_t pin1,pin2,pin3,pin4;
  int time_between_pulses;
  const int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
  rotation_status status;

  calc_function conv_function;

  void out(int);
public:
  BaseMotor(uint8_t, uint8_t, uint8_t, uint8_t);
  virtual void init();

  void set_time_between_pulses(int);
  virtual void set_rotation_status(rotation_status);
  void set_conversion_function(calc_function);

  const int steps_per_rev = 512; // 4096 steps / 8 pulses
};


class BlockingMotor:public BaseMotor{
private:
  void step(int);

public:
  BlockingMotor(uint8_t, uint8_t, uint8_t, uint8_t);
  void rotate_by(long val);
};

// class Motor{
// private:
//   uint8_t pin1,pin2,pin3,pin4;
//   int time_between_pulses;
//   int steps;
//   int to_steps;
//   int degrees;
//   int to_angle;
//   bool goal_set;
//   long t;
//
//   const int steps_per_rev = 512; // 4096 steps / 8 pulses
//   const int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
//   rotation_status status;
//   void out(int digit);
// public:
//   Motor(uint8_t p1, uint8_t p2,
//         uint8_t p3, uint8_t p4); // Blue, Pink, Yellow, Orange
//   void init();
//
//   void set_time_between_pulses(int);
//
//   void step(int);
//   void rotate_by_steps(int);
//
//
//   void set_rotation_status(rotation_status);
//   // non blocking
//   void rotate_by(int);
//   void commit();
//   // blocking
//   void rotate(int);
// };

#endif
