/*
 * File:   newmain.c
 * Author: Gary
 *
 * Created on 7 de febrero de 2021, 09:13 PM
 */
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000

uint8_t lmao;
uint8_t t1;
uint8_t t2;

void setup(void){
    lmao    = 0x00;
    TRISA   = 255;
    TRISB   = 0b00000000;
    TRISC   = 0b00000000;
    TRISD   = 0b00000000;
    ANSEL   = 0b00000011;
    ANSELH  = 0b00000000;
    PORTD   = 0b00000000;
    INTCON  = 0b11000000;
    PIE1    = 0b01000010;
    ADCON0  = 0b00000001;
    ADCON1  = 0b00000000;
    PR2     = 255;
    T2CON   = 0b00010110;
    return;   
}

void main(void) {
    setup();
    while(1){
        __delay_ms(10);
        if(ADCON0bits.GO==0){
            ADCON0bits.GO=1;
        }
        PORTB=t1;
        PORTC=t2;
    }
    return;
}

void __interrupt() ISR (void){
    if(PIR1bits.ADIF==1){
        if(ADCON0==0b00000001){
            t1=ADRESH;
            PIR1bits.ADIF=0;
        }
        else{
            t2=ADRESH;
            PIR1bits.ADIF=0;
        }
    }
    if(PIR1bits.TMR2IF==1){
        if(ADCON0==0b00000001){
            ADCON0=0b00000101;
            PIR1bits.TMR2IF=0;
            TMR2=0;
        }
        else{
            ADCON0=0b00000001;
            PIR1bits.TMR2IF=0;
            TMR2=0;
        }
    }
    
}