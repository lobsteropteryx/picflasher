# Basic Guide to Microcontroller funtionality using a PIC 16F688

The code and schematics here are a demonstration of some of the built-in peripherals on Microchip PIC microcontrollers.  The circuit reads a analog value from a temperature sensor, and sends the converted temperature value out over the USART.  In addition, a pushbutton is attached, which will send a message over the USART when pressed.  The following functions are demonstrated:

- Interrupt on Change (pushbutton)
- Hardware USART
- A/D Converter
- And of course, flashing an LED!

This program is written in C, compiled using [MPLABX](http://www.microchip.com/pagehandler/en-us/family/mplabx/) and the [xc8](http://www.microchip.com/pagehandler/en_us/devtools/mplabxc/) compiler.

For now, everything is in [main.c](https://github.com/lobsteropteryx/picflasher/blob/master/picflasher.X/main.c)

# Bill of Materials
- [PIC16F688](http://ww1.microchip.com/downloads/en/DeviceDoc/41203D.pdf)
- [TMP36](http://cdn.sparkfun.com/datasheets/Sensors/Temp/TMP35_36_37.pdf)
- [HC-06](http://abc-rc.pl/templates/images/files/995/1425483439-hc-06-datasheet.pdf)
- 330 ohm resistor
- LED
- Momentary pushbutton
- Microchip [PICkit2](http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=PG164130) programmer

When using the PICkit, the circuit can be powered from the programmer itself; once the chip has been programmed, the programmer can be replaced by a standard 5v power supply.  Note that the schematic does not include the isolation circuit for the programmer, so disconnect any external power before flashing the chip.

# Schematic
![schematic](https://github.com/lobsteropteryx/picflasher/blob/master/picflasher.schematic.svg)

#ToDo:
- Refactor code into separate modules

