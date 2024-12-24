/*
  Servo.h - Interrupt driven Servo library for Arduino using 16 bit timers - Version 2
  Copyright (c) 2009 Michael Margolis. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
  A servo is activated by creating an instance of the Servo class passing
  the desired pin to the attach() method.
  The servos are pulsed in the background using the value most recently
  written using the write() method.

  Note that analogWrite of PWM on pins associated with the timer are
  disabled when the first servo is attached.
  Timers are seized as needed in groups of 12 servos - 24 servos use two
  timers, 48 servos will use four.
  The sequence used to seize timers is defined in timers.h
 */

#ifndef Servo_h
#define Servo_h

#include <inttypes.h>

/*
 * Defines for 16 bit timers used with Servo library
 *
 * If _useTimerX is defined then TimerX is a 16 bit timer on the current board
 * timer16_Sequence_t enumerates the sequence that the timers should be allocated
 * _Nbr_16timers indicates how many 16 bit timers are available.
 */

// Architecture specific include
#if defined(ARDUINO_ARCH_AVR)
#include "avr/ServoTimers.h"
#elif defined(ARDUINO_ARCH_SAM)
#include "sam/ServoTimers.h"
#elif defined(ARDUINO_ARCH_SAMD)
#include "samd/ServoTimers.h"
#elif defined(ARDUINO_ARCH_STM32F4)
#include "stm32f4/ServoTimers.h"
#elif defined(ARDUINO_ARCH_NRF52)
#include "nrf52/ServoTimers.h"
#elif defined(ARDUINO_ARCH_MEGAAVR)
#include "megaavr/ServoTimers.h"
#elif defined(ARDUINO_ARCH_MBED)
#include "mbed/ServoTimers.h"
#elif defined(ARDUINO_ARCH_RENESAS)
#include "renesas/ServoTimers.h"
#elif defined(ARDUINO_ARCH_XMC)
#include "xmc/ServoTimers.h"
#else
#error "This library only supports boards with an AVR, SAM, SAMD, NRF52, STM32F4, Renesas or XMC processor."
#endif

#define Servo_VERSION           2     // software version of this library

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minimum time to refresh servos in microseconds

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index

#if !defined(ARDUINO_ARCH_STM32F4) && !defined(ARDUINO_ARCH_XMC)

typedef struct  {
  uint8_t nbr        :6 ;             // a pin number from 0 to 63
  uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false
} ServoPin_t   ;

typedef struct {
  ServoPin_t Pin;
  volatile unsigned int ticks;
} servo_t;


/**
 * \class Servo
 * \author  Michael Margolis, Arduino
 * \version 1.2.2
 * \brief Allows Arduino boards to control a variety of servo motors.
 * 
 * This library can control a great number of servos.
 * <br />
 * It makes careful use of timers: the library can control 12 servos 
 * using only 1 timer.
 * <br />
 * On the Arduino Due you can control up to 60 servos.
 * 
 * *NOTE:* For FRC purposes, the stm32f4 and xmc directories from the
 * original Github repository have been removed.
 */
class Servo
{
public:
  /**
   * Constructor for a Servo object.  Make sure you call `attach()` within
   * `setup()` as well.
   */
  Servo();

  /**
   * Attach the given pin to the next free channel, and sets `pinMode`.
   * 
   * \param pin The pin the Servo is wired to
   * \return  Channel number or `INVALID_SERVO` if failure
   */
  uint8_t attach(int pin);

  /**
   * Attach the given pin to the next free channel, and sets `pinMode`.
   * Also sets min and max values (in microseconds) for writes.  The
   * default minimum is 544, and the default maximum is 2400.
   * 
   * \param pin The pin the Servo is wired to
   * \param min The minimum value in microseconds we can write to the Servo
   * \param max The maximum value in microseconds we can write to the Servo
   * \return  Channel number or `INVALID_SERVO` if failure
   */
  uint8_t attach(int pin, int min, int max);

  /**
   * Stops an attached Servo from pulsing its I/O pin
   */
  void detach();

  /**
   * Sets the servo angle in degrees.
   * 
   * \param value The angle in degrees.  Inputs greater than or equal to 200
   *              are treated as being in units of microseconds instead of
   *              in degrees.
   */
  void write(int value);

  /**
   * Sets the servo pulse width in microseconds
   */
  void writeMicroseconds(int value);

  /**
   * Gets the last written servo pulse width.
   * 
   * \return  An angle between 0 and 180
   */
  int read();

  /**
   * Gets the last written servo pulse width in microseconds.
   * 
   * \return Last written servo pulse width in microseconds
   */
  int readMicroseconds();

  /**
   * Checks if the Servo is attached
   * 
   * \return  `true` if the Servo is attached, and `false` otherwise
   */
  bool attached();
private:
   uint8_t servoIndex; // index into the channel data for this servo
   int8_t min;         // minimum is this value times 4 added to MIN_PULSE_WIDTH
   int8_t max;         // maximum is this value times 4 added to MAX_PULSE_WIDTH
};

#endif
#endif
