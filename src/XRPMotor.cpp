#include "Arduino.h"
#include "XRPMotor.h"

#include <stdint.h>
#include <math.h>

XRPMotor::XRPMotor(uint8_t dir_pin, uint8_t speed_pin, bool inverted) {
  _dir_pin = dir_pin;
  _speed_pin = speed_pin;
  _inverted = inverted;
}

void XRPMotor::config() {
  pinMode(_dir_pin, OUTPUT);
  pinMode(_speed_pin, OUTPUT);
  digitalWrite(_dir_pin, _inverted);
}

void XRPMotor::set_effort(double speed) {
  if (speed >= 0) {
    _set_direction(LOW);
  } else {
    _set_direction(HIGH);
  }

  // point-slope form to map [0,1] to [0,255]
  // note that we only need to map [0,1] since
  // we are keeping all speeds positive and
  // merely switching direction
  double analog_effort = 255.0 * abs(speed);
  analogWrite(_speed_pin, analog_effort);
}

void XRPMotor::set_inverted(bool inverted) {
  _inverted = inverted;
}

bool XRPMotor::get_inverted() const {
  return _inverted;
}


void XRPMotor::_set_direction(uint8_t direction) {
  if (_inverted) {
    direction = !direction;
  }
  digitalWrite(_dir_pin, direction);
}

