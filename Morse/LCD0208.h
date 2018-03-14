class LCD0208 {

private:
  const byte bitRS = 0x01;
  const byte bitRW = 0x02;
  const byte bitE = 0x04;
  const byte bitBL = 0x08;
  const byte mskData = 0xF0;
  const byte shtData = 4;

  const byte CMD = LOW;
  const byte DADO = HIGH;
  
  const byte CMD_CLS = 0x01;
  const byte CMD_DISPON = 0x0C;
  const byte CMD_POSCUR = 0x80;
  const byte CMD_FUNCTIONSET = 0x20;
  const byte LCD_4BITMODE = 0x00;
  const byte LCD_2LINE = 0x08;
  const byte LCD_5x8DOTS = 0x00;

  byte addr = 0x20;
  byte valorAtual = 0;

  void setRS(byte valor);
  void setRW(byte valor);
  void setE(byte valor);
  void setBL(byte valor);
  void setDado(byte nib);
  void writeByte(byte rs, byte dado);
  void writeCmd(byte cmd);
  void writeChar(byte chr);

public:
  LCD0208(byte address);
  void backlightOn(void);
  void backlightOff(void);
  void displayWrite(byte lin, byte col, char *texto);
  void clear(void);
};

