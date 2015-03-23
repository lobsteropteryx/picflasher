/* 
 * File:   main.c
 * Author: Ian Firkin
 *
 * Created on March 19, 2015, 7:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

/* Set Configuration bits */
#pragma config FOSC = INTOSCIO /* Use high speed internal oscillator */
#pragma config WDTE = OFF /* Disable Watchdog timer */
#pragma config MCLRE = OFF /* Disable Master Clear */

/* Define oscillator frequency for delays */
#define _XTAL_FREQ 8000000

volatile int keyPressed = 0;

/* This is triggered by the interrupt on change for PORTA, pin 5.
 When the interrupt is fired, the chip will wake from sleep. */
void __interrupt handleButtonPress(void) {
    int portA;
    if (INTCONbits.RAIF == 1) { // Interrupt bit set
        portA = PORTA; // Read PORTA to reset the pin check
        INTCONbits.RAIF = 0; // Clear it
        keyPressed = 1; // Set our flag and get out of here
    }
}

void flashLED(void) {
    int i;
    for (i = 0; i < 3; i++) {
        RC2 = 1;
        __delay_ms(100);
        RC2 = 0;
        __delay_ms(100);
    }
}

void initialize(void) {
    CMCON0 = 0b00000100; /* Disable the comparator */
    ANSEL = 0b00000000; /* Disable A/D converter functions */

    OPTION_REG = 0b00000000; /* Enable PORTA pullups */
    TRISA = 0b11111111; /* Set I/O for PORTA */
    WPUA5 = 1; /* Enable internal pullup for A5 */
    IOCA5 = 1; /* Enable interrupt on change for A5 */

    /* Set port RC2 to output */
    TRISC = 0b11111011;

    /* Enable Interrupts*/
    INTCONbits.GIE = 1;  /* Global interrupt */
    INTCONbits.RAIE = 1; /* Interrupt on change for PORTA */

    /* Turn LED off */
    RC2 = 0;
}

int main(int argc, char** argv) {
    initialize();
    while (1) {
        SLEEP();
        if (keyPressed) {
            keyPressed = 0;
            flashLED();
        }
    }
    return (EXIT_SUCCESS);
}


