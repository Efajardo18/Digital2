/*
 * File:   newmain.c
 * Author: Gary
 *
 * Created on 4 de febrero de 2021, 09:47 AM
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
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
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
int xd;

void main(void) {
    setup;
    while(1){
        
    }
    return;
}

void setup(void) {
    TRISA   = 0b00000000;
    TRISB   = 0b00001011;
    TRISC   = 0b00000000;
    TRISD   = 0b00000000;
    ANSEL   = 0b00000000;
    ANSELH  = 0b00000010;
    PORTA   = 0;
    PORTB   = 0;
    PORTC   = 0;
    PORTD   = 0;
    INTCON	= 0b11001000;	//GIE, PEIE, RBIE activos
    PIE1	= 0b01000000;	//ADIE  activo
    IOCB    = 0b00000011;
    ADCON0  = 0b00100111;   //ACTIVAMOS el canal 9 y el bit GO
    ADCON1  = 0b10000000;
    return;
}

void __interrupt ISR(void){
    if  (PIR1bits.ADIF==1){
        xd=ADRESH;
        PIR1bits.ADIF=0;
        ADCON0 =0b00100111; //ni idea cual de la lista es el GO/~DONE
    }
    else if (INTCONbits.RBIF==1){
        if(PORTBbits.RB0==1){
            
        }
    }
}