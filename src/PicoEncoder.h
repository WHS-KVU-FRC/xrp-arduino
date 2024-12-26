/*
  PicoEncoder - High resolution quadrature encoder using the PIO on the RP2040
  Created by Paulo Marques, Pedro Pereira, Paulo Costa, 2022
  Distributed under the BSD 2-clause license. For full terms, please refer to the LICENSE file.
*/
#ifndef PicoEncoder_h
#define PicoEncoder_h

#include "Arduino.h"

#ifdef ARDUINO_ARCH_RP2040

#include "hardware/pio.h"

/**
 * \class PicoEncoder
 * \author Paulo Marques
 * \version 1.0.9
 * \brief High resolution quadrature encoder using the PIO on the RP2040
 * 
 * The two phases (channels A and B) of the encoder must be connected to
 * consecutive pins.  Note that the pins must be consecutive in the RP2040
 * and may not correspond to consecutive numbers in the Arduino mapping.
 * For instance, on the Arduino Nano RP2040 board, pins D2 and D3 are 
 * GPIO25 and GPIO15, so they can not be used for this purpose. However,
 * pin D4 is GPIO16, which means pins D3 and D4 could be used to connect
 * the encoder
 */
class PicoEncoder
{
  public:
    /**
     * PicoEncoder constructor.
     */
    PicoEncoder();

    /**
     * The method also sets the pins as inputs and will turn on the 
     * pull-ups on the pins if "pullUp" is true. Many encoders have
     * open-collector outputs and require pull-ups. If unsure, leave
     * the default value of `true`.
     * 
     * \param firstPin  The pin for Channel A of the encoder.  It
     *                  must be the smaller of two consectuve pins.
     * \param resolution  The resolution of the encoder (i.e., the number
     *                    of encoder counts per one revolution).  The
     *                    default value is 1 tick per revolution.
     * \param pullUp  (Optional) Whether or not to use the internal pullup
     *                resistor of the board.  Defaulted to `true`.
     * \return  Returns 0 on success, -1 if there is no PIO available,
     *          -2 if there are too many encoder instances
     */
    int begin(int firstPin, uint resolution = 1, bool pullUp = true);

    /**
     * This method must be called within `loop` to properly updated the
     * encoder readings.
     */
    void update(void);

    /**
     * Measure the relative phase sizes of the encoder. On success returns a
     * positive number that represents the sizes (and can be passed later to
     * setPhases to calibrate the phase sizes). On failure returns a negative
     * number:
     * <ul>
     * <li>-1 : speed too slow (less than 20 raw steps per second)</li>
     * <li>-2 : speed too high (while measuring the current step jumped
     * by more than one, so either the encoder is rotating to fast or
     * some interrupt routine is interrupting the code long enough to
     * lose steps)</li>
     * </ul>
     * 
     * \return  The relative phase (positive number), -1, or -2.
     */

    int measurePhases(void);

    /**
     * Set the phase sizes of the encoder.  You can determine the appropriate
     * phase size using `measurePhases`.
     * 
     * \param phases  The relative phase size of the encoder.
     */
    void setPhases(int phases);

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
    void setResolution(int resolution) {
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
    double getPosition() const {
      return step / _resolution * _conversionFactor;
    }

    /**
     * Returns the speed of the encoder.  The default units are in rotations
     * per minute (RPM), but can be modified by the conversion factor.
     * \see setConversionFactor
     * 
     * \return  The speed of the encoder.
     */
    double getSpeed() const {
      return speed / 64.0 / _resolution * _conversionFactor * 60.0;
    }


  private:
    // current encoder speed in "substeps per second"
    int speed;

    // current encoder position in substeps
    int position; // 1 substep is 1/64 of a step

    // current position in raw quadrature steps
    uint step;
    int _resolution = 1;
    double _conversionFactor = 1.0;
    // configuration data:
    uint calibration_data[4]; // relative phase sizes
    uint clocks_per_us;       // save the clk_sys frequency in clocks per us

    // PIO resources being used by this encoder
    PIO pio;
    uint sm;

    // internal fields to keep track of the previous state:
    uint prev_trans_pos, prev_trans_us;
    uint prev_step_us;
    uint prev_low, prev_high;
    uint idle_stop_sample_count;
    int speed_2_20;
    int stopped;

    // internal helper methods
    void read_pio_data(uint *step, uint *step_us, uint *transition_us, int *forward);
    uint get_step_start_transition_pos(uint step);
};

#else // ARCH
#error PicoEncoder library requires a PIO peripheral and only works on the RP2040 architecture
#endif  // #ifdef ARDUINO_ARCH_RP2040

#endif  // #ifndef PicoEncoder_h