void I2C_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Init()
{
  SSPCON = 0x28;
  SSPCON2 = 0x00;
  SSPSTAT = 0x00;
  SSPADD = ((_XTAL_FREQ/4)/I2C_BaudRate) - 1;
  TRISC3 = 1;
  TRISC4 = 1;
}

void I2C_Start()
{
  //---[ Initiate I2C Start Condition Sequence ]---
  I2C_Wait();
  SEN = 1;
}

void I2C_Stop()
{
  //---[ Initiate I2C Stop Condition Sequence ]---
  I2C_Wait();
  PEN = 1;
}

void I2C_Restart()
{
  //---[ Initiate I2C Restart Condition Sequence ]---
  I2C_Wait();
  RSEN = 1;
}

void I2C_ACK(void)
{
  //---[ Send ACK - For Master Receiver Mode ]---
  I2C_Wait();
  ACKDT = 0; // 0 -> ACK, 1 -> NACK
  ACKEN = 1; // Send ACK Signal!
}

void I2C_NACK(void)
{
  //---[ Send NACK - For Master Receiver Mode ]---
  I2C_Wait();
  ACKDT = 1; // 1 -> NACK, 0 -> ACK
  ACKEN = 1; // Send NACK Signal!
}

unsigned char I2C_Write(unsigned char Data)
{
  //---[ Send Byte, Return The ACK/NACK ]---
  I2C_Wait();
  SSPBUF = Data;
  I2C_Wait();
  return ACKSTAT;
}

unsigned char I2C_Read_Byte(void)
{
  //---[ Receive & Return A Byte ]---
  RCEN = 1;        // Enable & Start Reception
  while(!SSPIF);   // Wait Until Completion
  SSPIF = 0;       // Clear The Interrupt Flag Bit
  return SSPBUF;   // Return The Received Byte
}