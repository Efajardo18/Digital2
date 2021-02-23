/*
 * File:   Slave2.c
 * Author: Gary
 *
 * Created on 22 de febrero de 2021, 11:03 AM
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "spi.h"

uint8_t putu;
uint8_t tempi;

void setup(void);

void main(void) {
    setup();
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while(1){
        PORTD=tempi;
    }
    return;
}

void setup(void) {
    TRISA   = 0b00100000;
    TRISB   = 0b00000011;   //RB0 Y RB1 ESTABLECIDAS COMO ENTRADAS
    TRISC   = 0b00000000;
    TRISD   = 0b00000000;
    ANSEL   = 0b00000000;
    ANSELH  = 0b00000000;
    PORTA   = 0b00000000;
    PORTC   = 0b00000000;
    PORTD   = 0b00000000;
    INTCON  = 0b11001000;   //GIE, PEIE Y RBIE ACTIVOS
    PIE1    = 0b00001000;   //SSPIE ACTIVO
    IOCB    = 0b00000011;   //HABILITADAS INTERRUPCIONES EN B PARA RB0 Y RB1
    tempi   = 0;
}

void __interrupt() ISR (void){
    if(INTCONbits.RBIF==1){
        if(PORTBbits.RB0==1){
            tempi++;
            INTCONbits.RBIF=0;
        }
        if(PORTBbits.RB1==1){
            tempi--;
            INTCONbits.RBIF=0;
        }
    }
    if(SSPIF == 1){
        SSPIF = 0;
        putu=spiRead();
        spiWrite(PORTD);
    }
}