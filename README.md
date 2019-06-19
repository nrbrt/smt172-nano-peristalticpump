This project is to control a persitalticpump through the serial-USB port of an Arduino Nano, while also measuring the temperature with an smt172 in combination with a Raspberry Pi.
The command that can be sent is the following:

rot:x:y:z

where x is the speed, y is the maxspeed and z is the acceleration

For example,

rot:500:1000:100

would be a valid command to send.

The install script is meant to be run on a raspberry pi like this:
wget -O - https://raw.githubusercontent.com/nrbrt/smt172-nano-peristalticpump/master/install.sh | sh

This will program the nano, that needs to be connected at that moment, without any user interaction and is meant for novice users
and easy installation.

The smt172 sensor needs to be connected to pin 8 and needs some electronics to connect it to the Arduino as shown in the connection diagram.
The drv8825 driver that I use to connect the steppermotor of the peristalticpump is connected to 12(DIR) and pin 11(STEP).
This sketch uses the great smt172 library and smt172 connection diagram picture by Edwin Croissant.