#ifndef _XRPMOTOR_H_
#define _XRPMOTOR_H_

#include "Arduino.h"
#include <stdint.h>

/**
 * \class XRPMotor
 * \brief A class to work with a motor plugged into the XRP
 */
class XRPMotor {
 public:
  /**
   * Constructor for an XRP Motor plugged into the microcontroller (brain).
   * 
   * \param dir_pin The pin used to control the direction of the motor.  This
   *                is also called the "phase" pin, and is labeled as PH on
   *                the board.
   * \param speed_pin The pin used to control the speed of the motor.  This
   *                is also called the "enable" pin, and is labeled as EN on
   *                the board.
   * \param inverted  (Optional) Whether or not the motor should be inverted.
   *                  By default, the value of `inverted` is set to `false`.
   */
  XRPMotor(uint8_t dir_pin, uint8_t speed_pin, bool inverted = false);

  /**
   * Configures the hardware for your motor and sets up the pin modes.
   * You *MUST* call this method at least once (preferably in `setup`).
   */
  void config();

  /**
   * Sets the speed of the motor.  A positive speed causes the motor to spin
   * in the forwards direction, and vice versa for negative speeds.
   * 
   * \param speed  The speed to set the motor to, between -1.0 and 1.0
   */
  void set_effort(double speed);

  /**
   * Sets the inversion state of the motor.
   * 
   * \param inverted  Whether or not the motor should be inverted.  A value
   *                  of `true` causes the motor to be inverted.
   */
  void set_inverted(bool inverted);

  /**
   * Gets the inversion state of the motor.
   * 
   * \return  The current inversion state of the motor.  A value of `true`
   *          means that the motor is inverted.
   */
  bool get_inverted() const;
  
 private:
  uint8_t _dir_pin;
  uint8_t _speed_pin;
  bool _inverted;
  void _set_direction(uint8_t direction);
};

#endif  // #ifndef _XRPMOTOR_H_