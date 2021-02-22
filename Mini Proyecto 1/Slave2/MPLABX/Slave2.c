/*
 * File:   Slave2.c
 * Author: Gary
 *
 * Created on 22 de febrero de 2021, 11:03 AM
 */
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdio.h>
#include <stdint.h>

void setup(void);

void main(void) {
    setup();
    while(1){
        __delay_ms(10);
    }
    return;
}

void setup(void) {
    TRISA   = 0b00000000;
    TRISB   = 0b00000011;
    TRISC   = 0b00000000;
    TRISD   = 0b00000000;
    ANSEL   = 0b00000000;
    ANSELH  = 0b00000000;
    PORTA   = 0b00000000;
    PORTC   = 0b00000000;
    PORTD   = 0b00000000;
    INTCON  = 0b10001000;
    PIE1    = 0b00000000;
    IOCB    = 0b00000011;
}

void __interrupt() ISR (void){
    if(INTCONbits.RBIF==1){
        INTCONbits.RBIF=0;
        if(PORTBbits.RB0==1){
            PORTD++;
        }
        if(PORTBbits.RB1==1){
            PORTD--;
        }
    }
}