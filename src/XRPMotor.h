#ifndef _XRPMOTOR_H_
#define _XRPMOTOR_H_

#include "Arduino.h"

namespace xrp {
class XRPMotor {
 public:
  XRPMotor(int dir_pin, int speed_pin, bool inverted = false);
 private:
  int dir_pin;
  int speed_pin;
  bool inverted;
};
}  // namespace xrp

#endif