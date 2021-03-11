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
#define I2C_BaudRate 100000

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "I2Clib.h"

float   I2gato[3];
uint8_t ledsu;

void setup(void);
void UARTSendChar(const char c);
void UARTSendString(const char* str, const uint8_t max_length);


void main(void) {
    __delay_ms(1000);
    setup();
    I2C_Master_Init(100000);    //INICIAMOS LA COMUNICACIÓN I2C
    I2C_ConfigM();
    while(1)
    {
        switch(ledsu){              //ANALIZAR EL DATO PROVENIENTE DE SP32
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
        I2C_WWW(I2gato);
        char *regs;
        int  status;
        regs=ftoa(I2gato[0],&status);
        UARTSendString(regs,6);
        UARTSendChar(' ');
        regs=ftoa(I2gato[1],&status);
        UARTSendString(regs,6);
        UARTSendChar(' ');
        regs=ftoa(I2gato[2],&status);
        UARTSendString(regs,6);
        UARTSendChar(' ');
        UARTSendChar('\n');
        __delay_ms(5);
    }
    return;
}

void setup(void) {
    TRISA   = 0b00000000;
    TRISB   = 0b00000000;
    TRISC   = 0b11011000; //    [7:6] UART, [4:3]I2C
    TRISD   = 0b00000000;
    TRISE   = 0b00000000;
    ANSEL   = 0b00000000;
    ANSELH  = 0b00000000;
    PORTA   = 0b00000000;
    PORTB   = 0b00000000;
    PORTD   = 0b00000000;
    ledsu   = 0;
    INTCON  = 0b11000000; //    GIE, PEIE ACTIVOS
    PIE1    = 0b00100000; //    RCIE ACTIVO 
    TXSTA   = 0b00100100; //    TXEN Y BRGH ACTIVO 
    RCSTA   = 0b10010000; //    SPEN, CREN ACTIVOS
    SPBRG   = 0b00011001; //    25
}

void __interrupt() ISR(void) {
    if (PIR1bits.RCIF == 1) {
        ledsu=RCREG;
        PIR1bits.RCIF = 0;    
    }
}
//*https://github.com/asct20/PIC_UART_lib
void UARTSendChar(const char c) {
    while (TXSTAbits.TRMT == 0);    // Wait for buffer to be empty
    TXREG = c;
}

/**
 * Send a string, until '\0' is read, up to max_length characters
 * @param str
 * @param max_length
 */
void UARTSendString(const char* str, const uint8_t max_length) {
    int i = 0;
    for (i=0 ; i<max_length && str[i]!='\0' ; i++) {
        UARTSendChar(str[i]);
    }
}