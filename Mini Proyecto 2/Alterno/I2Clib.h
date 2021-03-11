//I2C Functions developed by electrosome

void I2C_Master_Init(const unsigned long c)
{
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*c))-1;
    SSPSTAT = 0x80;
    TRISC3 = 1;
    TRISC4 = 1;
}

void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_Master_Write(unsigned d)
{
    I2C_Master_Wait();
    SSPBUF = d;
    while(!PIR1bits.SSPIF);
}

unsigned short I2C_Master_Read(unsigned short a)
{
    unsigned short temp;
    I2C_Master_Wait();
    RCEN = 1;
    I2C_Master_Wait();
    while(!SSPIF);
    temp = SSPBUF;
    I2C_Master_Wait();
    ACKDT = (a)?1:0;
    ACKEN = 1;
    return temp;
}

void I2C_ConfigM(void){
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x6B);
    I2C_Master_Write(0x01);
    I2C_Master_Stop();
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x19);
    I2C_Master_Write(0x07);
    I2C_Master_Write(0x00);
    I2C_Master_Write(0x00);
    I2C_Master_Write(0x00);
    I2C_Master_Stop();
}

void I2C_WWW(float *dato){
    char d[6];
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x3B);
    I2C_Master_RepeatedStart();
    I2C_Master_Write(0xD1);
    for(int i = 0;i<5;i++)d[i]=I2C_Master_Read(0);
    d[5]=I2C_Master_Read(1);
    I2C_Master_Stop();
    int e[3];
    for(int i = 0; i<3 ; i++) e[i]=((int) d[2*i]<<8)|((int)d[2*i+1]);
    dato[0] = ((float)e[0])*0.000598;
    dato[1] = ((float)e[1])*0.000598;
    dato[2] = ((float)e[2])*0.000598;
}