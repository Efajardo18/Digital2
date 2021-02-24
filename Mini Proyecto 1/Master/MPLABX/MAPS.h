#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

uint8_t ascii(uint8_t datos) {
    switch (datos) {
        case 0x00:
            return (0x30);//(0b00110000); //0
            //break;
        case 0x01:
            return (0x31);//(0b00110001);
            //break;
        case 0x02:
            return (0x32);//(0b00110010);
            //break;
        case 0x03:
            return (0x33);//(0b00110011);
            //break;
        case 0x04:
            return (0x34);//(0b00110100);
            //break;
        case 0x05:
            return (0x35);//(0b00110101);
           // break;
        case 0x06:
            return (0x36);//(0b00110110);
           // break;
        case 0x07:
            return (0x37);//(0b00110111);
           // break;
        case 0x08:
            return (0x38);//(0b00111000);
           // break;
        case 0x09:
            return (0x39);//(0b00111001);
           // break;
    }
}
//void ascii2(uint8_t datos) {
//    switch (datos) {
//        case 0:
//            uwu2= 0b00110000; //0
//            break;
//        case 1:
//            uwu2= 0b00110001;
//            break;
//        case 2:
//            uwu2= 0b00110010;
//            break;
//        case 3:
//            uwu2= 0b00110011;
//            break;
//        case 4:
//            uwu2= 0b00110100;
//            break;
//        case 5:
//            uwu2= 0b00110101;
//            break;
//        case 6:
//            uwu2= 0b00110110;
//            break;
//        case 7:
//            uwu2= 0b00110111;
//            break;
//        case 8:
//            uwu2= 0b00111000;
//            break;
//        case 9:
//            uwu2= 0b00111001;
//            break;
//    }
//}

