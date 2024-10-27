#include "Arduino.h"
#include "XRPMotor.h"

xrp::XRPMotor::XRPMotor(int dir_pin, int speed_pin, bool inverted) {
  this->dir_pin = dir_pin;
  this->speed_pin = speed_pin;
  this->inverted = inverted;
}