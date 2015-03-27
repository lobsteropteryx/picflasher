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
volatile int adcResult = 0;

void handleButtonPress(void) {
    int portA;
    portA = PORTA; // Read PORTA to reset the pin check
    RAIF = 0; // Clear it
    keyPressed = 1; // Set our flag and get out of here
}

void handleTempReading(void) {
    ADIF = 0;
    adcResult = 1;
}

void __interrupt handleInterrupt(void) {
    if (RAIF == 1) { // Pushbutton
        handleButtonPress();
    }
    if (ADIF == 1) { // Temperature
        handleTempReading();
    }
}

unsigned long getADCResult(void) {
    unsigned long value;
    value = (ADRESH << 8) | ADRESL;
    return value;
}

float adcResultToVoltage(unsigned long adcResult) {
    return (4723.0 / 1023.0 * adcResult);
}

float voltageToDegreesC(float mv) {
    return (mv - 500.0) / 10.0;
}

void putch(char data) {
    while(!TXIF) {
        continue; // Wait for buffer to empty
    }
    TXREG = data;
}

void printADCResult(void) {
    unsigned long adcResult;
    char adcString[4];
    adcResult = getADCResult();
    ultoa(adcString, adcResult, 10);
    printf("ADC: %s\r\n", adcString);
}

printVoltage(void) {
    unsigned long adcResult;
    float voltage;
    char * voltageString;
    int status;
    adcResult = getADCResult();
    voltage = adcResultToVoltage(adcResult);
    voltageString = ftoa(voltage, &status);
    printf("Voltage: %s mv\r\n", voltageString);
}

printTemperature(void) {
    unsigned long adcResult;
    float voltage, temp;
    char * tempString;
    int status;
    adcResult = getADCResult();
    voltage = adcResultToVoltage(adcResult);
    temp = voltageToDegreesC(voltage);
    tempString = ftoa(temp, &status);
    printf("Temp: %s C\r\n", tempString);
}

void startADC(void) {
    __delay_us(5); // Acquisition time
    ADCON0bits.GO_DONE = 1; // restart ADC
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

void initialize_usart(void) {
    SPBRG = 51; // ~9600 baud @ 8MHz
    TXEN = 1; // Enable transmit
    BRGH = 1; // high speed transmit
    BRG16 = 0; // 8-bit speed
    SYNC = 0; // Set mode to async
    SPEN = 1; // Enable serial port
    //TXIE = 1; // Enable interrupt
}

void initialize_temp_sensor(void) {
    TRISCbits.TRISC3 = 1; // output
    ANSELbits.ANS7 = 1; // analog
    ADCON0bits.CHS0 = 1; // Select AN7
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.ADFM = 1; // Right justified
    ADCON0bits.VCFG = 0; // VDD
    ADCON0bits.ADON = 1; // Enable
    ADCON1 = 0; // Set adc clock to FOSC / 2
    ADIF = 0; // Clear interrupt flag
    ADIE = 1; // Enable interrupt
}

void initialize_led(void) {
    TRISCbits.TRISC2 = 0; // Output
    RC2 = 0; // Turn LED off
}

void initialize_pushbutton(void) {
    TRISCbits.TRISC5 = 0; // Input
    WPUA5 = 1; /* Enable internal pullup for A5 */
    IOCA5 = 1; /* Enable interrupt on change for A5 */
    RAIE = 1; /* Interrupt on change for PORTA */
}

void initialize(void) {
    OSCCON = 0b11111111; /* Initialize oscillator settings */
    CMCON0 = 0b00000100; /* Disable the comparator */
    ANSEL = 0b00000000; /* Disable A/D converter functions */
    OPTION_REG = 0b00000000; /* Enable PORTA pullups */
    TRISA = 0b11111111; /* Set I/O for PORTA */
    TRISC = 0b11111111;

    initialize_led();
    initialize_pushbutton();
    initialize_usart();
    initialize_temp_sensor();

    /* Enable Interrupts*/
    PEIE = 1; /* Peripheral interrupts */
    GIE = 1;  /* Global interrupt */
}

int main(int argc, char** argv) {
    initialize();
    startADC();
    while (1) {
        //SLEEP();
        if (keyPressed) {
            keyPressed = 0;
            flashLED();
            printf("button press\n");
        }
        if (adcResult) {
            adcResult = 0;
            flashLED();
            printTemperature();
            startADC();
        }
    }
    return (EXIT_SUCCESS);
}


