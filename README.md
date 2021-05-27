# stroke-rehabilitation
====================

This project uses analog input from sound sensors to detect beats on microcontrollers in real-time. 
In addition to using the overall audio signal amplitudes (time domain), it transforms the data using the [Fast Hartley Transform](http://wiki.openmusiclabs.com/wiki/ArduinoFHT) (frequency domain).
It then extracts some features from specific frequency bands and calculates a beat probability for each sample period.

For the electical circuit set up, the analog output of the microphone module MAX9814 needs to be connected to pin  `A0`. This pin will be configured to allow faster sampling from analog input. Refer to [this](http://yaab-arduino.blogspot.com/2015/02/fast-sampling-from-analog-input.htm) to learn more.

Deploy the `.ino` file onto ARDUINO MKR Wifi 1010 and connect the LEDs to pin `D9` to see the beat detection output. To get an idea of what the beat detection is thinking, connect to the serial port with a baut rate of `115200`.

Credit to https://blog.yavilevich.com/2016/08/arduino-sound-level-meter-and-spectrum-analyzer/ for the theory

