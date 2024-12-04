#ifndef _XRPMOTOR_H_
#define _XRPMOTOR_H_

#include "Arduino.h"

#include <stdint.h>

class XRPMotor {
 public:
  XRPMotor(uint8_t dir_pin, uint8_t speed_pin, bool inverted = false);
  void config();
  void set_effort(double effort);
  
 private:
  uint8_t dir_pin;
  uint8_t speed_pin;
  bool inverted;
  // MotorDirection direction = kForward;
  void set_direction(uint8_t direction);
};

// enum MotorDirection {
//   kBackward = LOW,
//   kForward = HIGH
// };

#endif