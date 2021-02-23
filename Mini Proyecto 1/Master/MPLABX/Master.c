/*
 * File:   Master.c
 * Author: Gary
 *
 * Created on 22 de febrero de 2021, 11:34 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
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
#include "spi.h"
#include "lcdlib.h"

uint8_t SLAVE1;
uint8_t SLAVE2;
uint8_t SLAVE3;
uint8_t DATAS;

void setup(void);

void main(void) {
    setup();
    Lcd_Init();
    char s[16];
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    while (1) {
        PORTBbits.RB0=0;
        spiWrite(0);
        SLAVE1=spiRead();
        PORTBbits.RB0=1;
        
        PORTBbits.RB1=0;
        spiWrite(255);
        SLAVE2=spiRead();
        PORTBbits.RB1=1;
        
        PORTBbits.RB2=0;
        spiWrite(100);
        SLAVE3=spiRead();
        PORTBbits.RB2=1;
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("ADC CONT  TEMP");
        Lcd_Set_Cursor(2,1);
        sprintf(s," %3i   %3i   %3i",SLAVE1, SLAVE2, SLAVE3);
        Lcd_Write_String(s);
    }
    return;
}

void setup(void) {
    TRISA   = 0b00000000;
    TRISB   = 0b00000000;
    TRISD   = 0b00000000;
    TRISE   = 0b00000000;
    ANSEL   = 0b00000000;
    ANSELH  = 0b00000000;
    INTCON  = 0b11000000; //SE ACTIVA EL GIE Y PEIE 
    PORTA   = 0;
    PORTB   = 0x0F;
    PORTD   = 0;
    return;
}

void __interrupt() ISR(void) {
    if (SSPIF == 1) {
        SSPIF=0;
    }
//        if (PORTBbits.RB0 == 0) {
//            SLAVE1 = spiRead();
//            SSPIF = 0;
//            PORTBbits.RB0 = 1;
//            PORTBbits.RB1 = 0;
//        }
//        else if (PORTBbits.RB1 == 0){
//            SLAVE2 = spiRead();
//            SSPIF = 0;
//            PORTBbits.RB1 = 1;
//            PORTBbits.RB2 = 0;
//        }
//        else{
//            SLAVE3 = spiRead();
//            SSPIF = 0;
//            PORTBbits.RB2 = 1;
//            PORTBbits.RB0 = 0;
//        }
//    }
}

