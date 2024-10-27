#include "Arduino.h"
#include "XRPMotor.h"

#include <cmath>

xrp::XRPMotor::XRPMotor(int dir_pin, int speed_pin, bool inverted) {
  this->dir_pin = dir_pin;
  this->speed_pin = speed_pin;
  this->inverted = inverted;
}

xrp::XRPMotor::config() {
  pinMode(dir_pin, OUTPUT);
  pinMode(speed_pin, OUTPUT);
  
  // assuming that LOW means fowards, and HIGH means reverse
  // TODO: test on actual robot what direction LOW and HIGH are
  // if inverted is true, then dir_pin is set to HIGH, which is backwards motion
  digitalWrite(dir_pin, inverted);
}

/** Sets the effort of the motor.  It handles backwards motion by switching the direction
 * of the motor; i.e., to go backwards is to switch the direction and keep the speed positive
 * @param effort  The speed to set the motor at.  Value must be between [-1, 1], where positive
 *                values indicate forwards movement.
 */
xrp::XRPMotor::set_effort(double effort) {
  if (effort >= 0) {
    set_direction(LOW);
  } else {
    set_direction(HIGH);
  }

  // point-slope form to map [0,1] to [0,255]
  // note that we only need to map [0,1] since
  // we are keeping all speeds positive and
  // merely switching direction
  double analog_effort = 255.0 * abs(effort);
  analogWrite(speed_pin, analog_effort);
}

xrp::XRPMotor::set_direction(short direction) {
  if (inverted) {
    direction = !direction;
  }
  digitalWrite(dir_pin, direction);
}