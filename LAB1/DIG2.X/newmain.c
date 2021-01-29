/*
 * File:   newmain.c
 * Author: Gary
 *
 * Created on 22 de enero de 2021, 08:24 AM
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
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 8000000

void setup(void) {
    PORTA = 0;
    PORTB = 0;
    PORTC = 1; //0b00000001 para tener el semaforo en rojo inicialmente.
    PORTD = 0;
    ANSEL = 0; //Desactivamos las entradas analogicas del lado izquierdo.
    ANSELH = 0; //Desactivamos las entradas analogicas del lado derecho.
    TRISA = 7; //Activamos las entradas del puerto A (pines 0:2) 0b00000111.
    TRISB = 0; //Establecemos los puertos B, C y D como salidas.
    TRISC = 0;
    TRISD = 0;
    return;
}

void main(void) {
    setup();
    while (1) {
        while (PORTCbits.RC0 == 1) {
            if (PORTAbits.RA0 == 1) {
                __delay_ms(500);
                PORTC = 2; //0b00000010 enciende c1.
                __delay_ms(500);
                PORTC = 4; //0b00000100 enciende c2.
            }
        }
        if (PORTCbits.RC4 == 0) {
            if (PORTCbits.RC5 == 0) {
                if (PORTAbits.RA1 == 1) {
                    if (PORTB == 0) {
                        PORTB = 1;
                        __delay_ms(500);
                    } else {
                        if(PORTB == 0b10000000){
                            PORTC = 0b00010001;
                        }
                        PORTB = PORTB + PORTB;
                        __delay_ms(500);
                    }
                }
                if (PORTAbits.RA2 == 1) {
                    if (PORTD == 0) {
                        PORTD = 1;
                        __delay_ms(500);
                    } else {
                        if(PORTD == 0b10000000){
                            PORTC = 0b00100001;
                        }
                        PORTD = PORTD + PORTD;
                        __delay_ms(500);
                    }
                }
            }
        }
    }
}
