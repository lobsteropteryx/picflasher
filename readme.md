#Basic Guide to Microcontroller funtionality using a PIC 16F688

The code and schematics here are a demonstration of some of the built-in peripherals on Pic microcontrollers.  The circuit reads a analog value from a temperature sensor, and sends the converted temperature value out over the USART.  In addition, a pushbutton is attached, which will send a message over the USART when pressed.  The following functions are demonstrated:

- Interrupt on Change (pushbutton)
- Hardware USART
- A/D Converter
- And of course, flashing an LED

#Bill of Materials
- Microchip [PIC16F688](http://ww1.microchip.com/downloads/en/DeviceDoc/41203D.pdf)
- [TMP36](http://cdn.sparkfun.com/datasheets/Sensors/Temp/TMP35_36_37.pdf)
- [HC-06](http://abc-rc.pl/templates/images/files/995/1425483439-hc-06-datasheet.pdf)
- 330 ohm resistor
- LED

#Schematic
![schematic](https://github.com/lobsteropteryx/picflasher/blob/master/picflasher.schematic.svg)

#ToDo:
- Refactor code into separate modules

