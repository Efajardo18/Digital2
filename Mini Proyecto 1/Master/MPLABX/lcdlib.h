#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded. 

//LCD Functions Developed by electroSome


void Lcd_Port(char a) {
    if (a & 1)
        D0 = 1;
    else
        D0 = 0;

    if (a & 2)
        D1 = 1;
    else
        D1 = 0;

    if (a & 4)
        D2 = 1;
    else
        D2 = 0;

    if (a & 8)
        D3 = 1;
    else
        D3 = 0;
    if (a & 16)
        D4 = 1;
    else
        D4 = 0;
    if (a & 32)
        D5 = 1;
    else
        D5 = 0;
    if (a & 64)
        D6 = 1;
    else
        D6 = 0;
    if (a & 128)
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear() {
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        Lcd_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd(temp);
    }
}

void Lcd_Init() {
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x38); //0b00111000
    Lcd_Cmd(0x0C); //0b00001000
    Lcd_Cmd(0x06); //0b00000110
}

void Lcd_Write_Char(char a) {
    RS = 1; // => RS = 1
    Lcd_Port(a); //Data transfer
    EN = 1;
    __delay_ms(4);
    EN = 0;

}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}

void ARRANQUE() {
    unsigned int a;
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("LCD Library for");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("MPLAB XC8");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Developed By");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("electroSome");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("www.electroSome.com");

    for (a = 0; a < 15; a++) {
        __delay_ms(300);
        Lcd_Shift_Left();
    }

    for (a = 0; a < 15; a++) {
        __delay_ms(300);
        Lcd_Shift_Right();
    }

    Lcd_Clear();
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_Char('e');
    Lcd_Write_Char('S');
    __delay_ms(2000);
}