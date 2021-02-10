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

#define _XTAL_FREQ 8000000
#define RS RE1
#define EN RE2
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "lcdlib.h"



uint8_t lmao;
uint8_t t1;
uint8_t t2;

void setup(void){
    t1      = 0;
    t2      = 0;
    TRISA   = 255;
    TRISC   = 0b00000000;
    TRISD   = 0b00000000;
    TRISE   = 0b00000000;
    ANSEL   = 0b00000011;
    ANSELH  = 0b00000000;
    PORTD   = 0b00000000;
    INTCON  = 0b11000000; //GIE, PEIE ACTIVOS
    PIE1    = 0b01000010; //ADIE, TMR2IE ACTIVOS
    ADCON0  = 0b00000001; 
    ADCON1  = 0b00000000;
    PR2     = 255;
    T2CON   = 0b00010110;
    return;   
}

void main(void) {
    setup();
    Lcd_Init();
    char s[16];
    while(1){
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("V1  V2  CONT");
        Lcd_Set_Cursor(2,1);
        sprintf(s," %3i   %3i",t1, t2);
        Lcd_Write_String(s);
        __delay_ms(10);
        if(ADCON0bits.GO==0){
            ADCON0bits.GO=1;
        }
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