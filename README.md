# Zaluzio Geret
Automated smart blinds retrofit device with WiFi , MQTT and light measurement capability.

## Bill of material
* [Wemos D1 mini](http://s.click.aliexpress.com/e/b7xoMFF6) 
* [180 degree servo](http://s.click.aliexpress.com/e/cCIS5ETW)
* [LDR 5516 photoresistor](http://s.click.aliexpress.com/e/sKHeBEs)
* [NPN Transistor](http://s.click.aliexpress.com/e/bSLbOB7K)
* [Tactile push buttons](http://s.click.aliexpress.com/e/0rbMNuk)
* [10k Resistors](http://s.click.aliexpress.com/e/boawi0Ak)
* Some spring, hard to specify dimensions and power
* Some basic soldering equipment and skills

## Settings
You can redefine some default settings through Settings.h file. It is pretty self-explanatory I think.

## Usage
There is WiFi Manager on board so after burning the firmware, device is in AP mode, default password for connecting to AP is: configure.

After connecting to WiFi, there is UI configuration interface, you can find device IP address through serial terminal or through in your router, or through scanning the network. Device hostname is ZaluzioGeret-MAC_END.

There are settings for specifiing MIN and MAX angle of rotation, and reverse direction of inner logic.

There are 2 buttons connected, UP and DOWN, each short press control the servo with 5° in respective direction. Short pressing of both buttons resets the servo in middle position. 
Long press of each button moves the servo to the MIN or MAX position defined. Long pressing of both buttons starts the LightFinder procedure. LightFinder procedure moves the servo to MIN position, and then continually measure light after each move. Then it move to the position in which highest light was measured. 

## Wiring scheme
TO BE DONE

## Physical installation
Device is mounted to window frame by self adhesive tape by 3M.