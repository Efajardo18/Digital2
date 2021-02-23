/*
 * File:   Slave3.c
 * Author: Gary
 *
 * Created on 22 de febrero de 2021, 07:14 PM
 */
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
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
#include <stdint.h>
#include <stdio.h>
#include "ADClib.h"

uint8_t VADC;

void setup(void);

void main(void) {
    setup();
    while(1){
        __delay_ms(10);
        GOCHK();
        if(VADC>=33){
            PORTD=0b00000100;
        }
        else if(VADC>=16){
            PORTD=0b00000010;
        }
        else{
            PORTD=0b00000001;
        }
    }
    return;
}

void setup(void){
    TRISA   = 0b00001001;
    TRISB   = 0b00000000;
    TRISC   = 0b00000000;
    TRISD   = 0b00000000;
    ANSEL   = 0b00000001;
    ANSELH  = 0b00000000;
    INTCON  = 0b11000000;
    PIE1    = 0b01000000;
    ADCON0  = 0b01000001;
    ADCON1  = 0b00010000;
    PORTA   = 0;
    PORTB   = 0;
    PORTC   = 0;
    PORTD   = 0;
    return;
}

void __interrupt() ISR (void){
    if(PIR1bits.ADIF==1){
            PIR1bits.ADIF=0;
            VADC=ADRESH;
    }
}
