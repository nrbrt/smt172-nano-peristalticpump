This project controls a peristaltic pump through the serial-USB port of an Arduino Nano, while also measuring the temperature with an smt172 in combination with a Raspberry Pi.
The commands that can be sent are the following:

`rot:x`

where x is the speed in steps per second. This command will only work if the next two are already set.
a postive x will rotate the motor CW a negative value for x will rotate the motor CCW

`acc:z`

where z is the acceleration in steps per second per second. With this setting you can ramp up and down. Useful at higher speeds and microstepping

`pos:x:y`

where x is like before the speed and y a relative position to the current one. This way you can calibrate a certain amount to be pumped at a certain speed.

The install script is meant to be run on a raspberry pi like this:

`wget -O - https://raw.githubusercontent.com/nrbrt/smt172-nano-peristalticpump/master/install.sh | sh`

This will program the nano, that needs to be connected at that moment, without any user interaction and is meant for novice users
and easy installation.

The smt172 sensor needs to be connected to pin 8 and needs some electronics to connect it to the Arduino as shown in the connection diagram.
The drv8825 driver that I use to connect the steppermotor of the peristalticpump is connected to 12(DIR) and pin 11(STEP).
This sketch uses the great smt172 library and smt172 connection diagram picture by Edwin Croissant.
