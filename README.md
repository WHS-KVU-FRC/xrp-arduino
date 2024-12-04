# XRP-Arduino
An Arduino-based library for the XRP robot.

# Adding the Raspberry Pi Pico to the Boards Manager
You can follow the instructions [here](https://randomnerdtutorials.com/programming-raspberry-pi-pico-w-arduino-ide/).

1. In the Arduino IDE, go to File > Preferences.
2. Enter the following URL into the “Additional Boards Manager URLs” field, and click OK.
```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```
3. Open the Boards Manager. Go to Tools > Board > Boards Manager
4. Search for “pico” and install the Raspberry Pi Pico/RP2040 boards.
5. Now, if you go to Tools > Board, there should be a selection of Raspberry Pi Pico boards.

# Additional Dependencies
To use the XRP encoder, you must either write your own library, or use a library that someone else wrote.  A nice one to use is the [rp2040-encoder-library](https://github.com/gbr1/rp2040-encoder-library) by Giovanni di Dio Bruno.