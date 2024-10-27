#ifndef _XRPMOTOR_H_
#define _XRPMOTOR_H_

#include "Arduino.h"

namespace xrp {
class XRPMotor {
 public:
  XRPMotor(int dir_pin, int speed_pin, bool inverted = false);
  config();
  set_effort(double effort);
 private:
  int dir_pin;
  int speed_pin;
  bool inverted;
  // MotorDirection direction = kForward;
  void set_direction(short direction);
};

// enum MotorDirection {
//   kBackward = LOW,
//   kForward = HIGH
// };
}  // namespace xrp

#endif