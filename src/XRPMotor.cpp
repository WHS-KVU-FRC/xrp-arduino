#include "Arduino.h"
#include "XRPMotor.h"

#include <stdint.h>
#include <math.h>

// Change #2 for teaching

XRPMotor::XRPMotor(uint8_t dir_pin, uint8_t speed_pin, bool inverted) {
  _dir_pin = dir_pin;
  _speed_pin = speed_pin;
  _inverted = inverted;
}

void XRPMotor::config() {
  pinMode(_dir_pin, OUTPUT);
  pinMode(_speed_pin, OUTPUT);
  
  // assuming that LOW means fowards, and HIGH means reverse
  // TODO: test on actual robot what direction LOW and HIGH are
  // if inverted is true, then dir_pin is set to HIGH, which is backwards motion
  digitalWrite(_dir_pin, _inverted);
}

/** Sets the effort of the motor.  It handles backwards motion by switching the direction
 * of the motor; i.e., to go backwards is to switch the direction and keep the speed positive
 * @param effort  The speed to set the motor at.  Value must be between [-1, 1], where positive
 *                values indicate forwards movement.
 */
void XRPMotor::set_effort(double effort) {
  if (effort >= 0) {
    _set_direction(LOW);
  } else {
    _set_direction(HIGH);
  }

  // point-slope form to map [0,1] to [0,255]
  // note that we only need to map [0,1] since
  // we are keeping all speeds positive and
  // merely switching direction
  double analog_effort = 255.0 * abs(effort);
  analogWrite(_speed_pin, analog_effort);
}

void XRPMotor::_set_direction(uint8_t direction) {
  if (_inverted) {
    direction = !direction;
  }
  digitalWrite(_dir_pin, direction);
}