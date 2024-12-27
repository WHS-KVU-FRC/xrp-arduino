/*
 * Copyright (C) 2023 Giovanni di Dio Bruno
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __PIO_ENCODER_H__
#define __PIO_ENCODER_H__

#include "Arduino.h"
#include "rp2040-encoder-library/quadrature.pio.h"

#define COUNT_1X 2
#define COUNT_2X 1
#define COUNT_4X 0

/**
 * \class PioEncoder
 * \author Giovanni di Dio Bruno
 * \version 0.2.0
 * \brief Quadrature Encoder library for RP2040/RP2350 
 * 
 * This library can be used with any RP240/RP2350 board,
 * such as Arduino Nano RP2040 Connect, RPI Pico and
 * RPI Pico 2.
 */
class PioEncoder {
 public:
  static uint offset;
  static bool not_first_instance;
  
  /**
   * Constructor for a quadrature encoder PioEncoder object.
   * The pins for Channels A and B must be consecutive, and
   * the pin for Channel A must be the smaller of the two pin
   * values.
   * 
   * \param pin The pin for Channel A of the encoder.
   * \param resolution  (Optional) The resolution of the encoder (i.e.,
   *                    the number of encoder counts per one revolution).
   *                    The default value is 1 count per revolution.
   * \param flip  (Optional) Whether to flip the encoder or not.  The
   *              default value is `false`.
   * \param zero_offset (Optional) The initial amount of offset the
   *                    encoder counts by.  Defaulted to 0.
   * \param count_mode (Optional) The counting mode for the encoder.  Must be one
   *                   of `COUNT_1X`, `COUNT_2X`, or `COUNT_4X`.
   * \param pio (Optional) Internal #define in the `pio.h` file.  Defaulted
   *            to pio0.
   * \param sm  (Optional) Default value of -1.  Probably don't want to mess
   *            with this.
   * \param max_step_rate (Optional) The maximum stepping rate.  Defaulted to 0.
   */
  PioEncoder(const uint8_t pin, const uint16_t resolution = 1, const bool flip = false, const int zero_offset = 0, const uint8_t count_mode = COUNT_4X,
            PIO pio = pio0, const uint sm = -1, const int max_step_rate = 0);

  /**
   * Sets up the hardware for your encoder.  Call this method
   * within `setup()`.
   */
  void begin();

  /**
   * Resets the encoder to the given value.
   * 
   * \param reset_value (Optional) The value to reset to.  Defaulted to 0.
   */
  void reset(const int reset_value = 0);

  /**
   * Sets the flipped state of the encoder.  A flipped state
   * of `true` means that the encoder is flipped.
   * 
   * \param x The flipped state.  Defaulted to `true` when
   *          this method is called.
   */
  void flip(const bool x=true);

  /**
   * Gets the total encoder counts read by the encoder.
   * 
   * \return  The total count read by the encoder.
   */
  int getCount();

  /**
   * Sets the counting mode of the encoder.  The default
   * value is `COUNT_4X`
   * 
   * \param mode  The counting mode for the encoder.  Must be one
   *              of `COUNT_1X`, `COUNT_2X`, or `COUNT_4X`.
   */
  void setMode(const uint8_t mode = COUNT_4X);

  /**
   * Sets the conversion factor to multiply the encouder position by.
   * 
   * \param conversionFactor  The factor to multiply the encouder position.
   */
  void setConversionFactor(double conversionFactor) {
    _conversionFactor = conversionFactor;
  }

  /**
   * Sets the resolution of the encoder.  This should be in units of
   * encoder ticks per revolution/rotation of the wheel (or shaft the
   * encoder is mounted on).
   * 
   * \param resolution  The resolution of the encoder in encoder counts
   *                    per revolution.
   */
  void setResolution(uint16_t resolution) {
    _resolution = resolution;
  }

  /**
   * Returns the position of the encoder.  The default unit is revolutions
   * or rotations (of the wheel).  The units returned can be changed by the
   * conversion factor.
   * \see setConversionFactor
   * 
   * \return  The position of the encoder in units given by the
   *          conversion factor.
   */
  double getPosition() {
    return getCount() * _conversionFactor / _resolution;
  }
  
 private:
  uint16_t _resolution = 1;
  double _conversionFactor = 1.0;

  uint8_t pin;
  uint sm;
  PIO pio;
  int max_step_rate;
  int flip_it;
  int zero_offset;
  uint8_t count_mode;
};


#endif