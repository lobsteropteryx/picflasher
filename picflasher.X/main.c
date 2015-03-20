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
#pragma config FOSC = INTOSCIO
#pragma config WDTE = OFF
#pragma config MCLRE = OFF

/* Define oscillator frequency for delays */
#define _XTAL_FREQ 8000000

int main(int argc, char** argv) {

    /* Set Analog pins to digital i/o */
    CMCON0 = 0b00000100;
    ANSEL = 0b00000000;

    /* Set port RC2 to output */
    TRISC = 0b11111011;

    while (1) {
        RC2 = 1;
        __delay_ms(500);
        RC2 = 0;
        __delay_ms(500);
    }

    return (EXIT_SUCCESS);
}

