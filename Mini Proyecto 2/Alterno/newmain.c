/*
 * File:   newmain.c
 * Author: Gary
 *
 * Created on 6 de marzo de 2021, 07:00 PM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "I2Clib.h"

uint8_t I2DATO;
uint8_t ledsu;

void setup(void);

void main(void) {
    setup();
    //I2C_Master_Init(100000);    //INICIAMOS LA COMUNICACIÓN I2C
    while(1)
    {
        //I2C_Master_Start();
        //I2C_Master_Write(0x29);
        //I2DATO = I2C_Master_Read(0);
        //I2C_Master_Stop();
        //__delay_ms(200);
        switch(ledsu){
            case 0:
                PORTB=0;
                break;
            case 1:
                PORTB=1;
                break;
            case 2:
                PORTB=2;
                break;
            case 3:
                PORTB=3;
                break;
        }
        TXREG = I2DATO;
        __delay_ms(5);
    }
    return;
}

void setup(void) {
    TRISA   = 0b00000000;
    TRISB   = 0b00000000;
    TRISC   = 0b11011000;
    TRISD   = 0b00000000;
    TRISE   = 0b00000000;
    ANSEL   = 0b00000000;
    ANSELH  = 0b00000000;
    PORTA   = 0b00000000;
    PORTB   = 0b00000000;
    PORTD   = 0b00000000;
    I2DATO  = 0;
    ledsu   = 0;
    INTCON  = 0b11000000;
    PIE1    = 0b00100000;
    TXSTA   = 0b00100100;
    RCSTA   = 0b10010000;
    SPBRG   = 0b00011001;
}

void __interrupt() ISR(void) {
    if (PIR1bits.RCIF == 1) {
        ledsu=RCREG;
        PIR1bits.RCIF = 0;    
    }
}