#include <TinyWireM.h>
#include "LCD0208.h"

void LCD0208::setRS(byte valor) {
  if (valor == LOW) {
    valorAtual &= ~bitRS;
  } else {
    valorAtual |= bitRS;
  }
  TinyWireM.beginTransmission(addr);
  TinyWireM.send(valorAtual);
  TinyWireM.endTransmission();
}

void LCD0208::setRW(byte valor) {
  if (valor == LOW) {
    valorAtual &= ~bitRW;
  } else {
    valorAtual |= bitRW;
  }
  TinyWireM.beginTransmission(addr);
  TinyWireM.send(valorAtual);
  TinyWireM.endTransmission();
}

void LCD0208::setE(byte valor) {
  if (valor == LOW) {
    valorAtual &= ~bitE;
  } else {
    valorAtual |= bitE;
  }
  TinyWireM.beginTransmission(addr);
  TinyWireM.send(valorAtual);
  TinyWireM.endTransmission();
}

void LCD0208::setBL(byte valor) {
  if (valor == LOW) {
    valorAtual &= ~bitBL;
  } else {
    valorAtual |= bitBL;
  }
  TinyWireM.beginTransmission(addr);
  TinyWireM.send(valorAtual);
  TinyWireM.endTransmission();
}

void LCD0208::setDado(byte nib) {
  valorAtual = (valorAtual & ~mskData) | (nib << shtData);
  TinyWireM.beginTransmission(addr);
  TinyWireM.send(valorAtual);
  TinyWireM.endTransmission();
}

void LCD0208::writeByte(byte rs, byte dado) {
  setRS(rs);
  setE(HIGH);
  setDado(dado >> 4);
  setE(LOW);
  setE(HIGH);
  setDado(dado & 0x0F);
  setE(LOW);
}

void LCD0208::writeCmd(byte cmd) {
  writeByte (CMD, cmd);
}

void LCD0208::writeChar(byte chr) {
  writeByte (DADO, chr);
}

LCD0208::LCD0208(byte address) {
  
  TinyWireM.begin();
  addr = address;
  TinyWireM.beginTransmission(addr);
  TinyWireM.send(valorAtual);
  TinyWireM.endTransmission();

  delay (100);
  setRW(LOW);
  writeCmd (0x03);
  delay(5);    
  writeCmd (0x03);
  delay(1);    
  writeCmd (0x03);
  delay(1);    
  writeCmd (0x02);
  delay(1);    
  writeCmd(CMD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);
  delay(1);    
  writeCmd (CMD_CLS);
  delay(2);    
  writeCmd (CMD_DISPON);
  delay(1);    
}

void LCD0208::backlightOn() {
  setBL(HIGH);
}

void LCD0208::backlightOff() {
  setBL(LOW);
}

void LCD0208::displayWrite(byte lin, byte col, char *texto) {
  byte ender = col;
  if (lin == 1) {
    ender += 0x40;
  }
  writeCmd(CMD_POSCUR | ender);
  while (*texto) {
    writeChar(*texto++);
  }
}

void LCD0208::clear() {
  writeCmd (CMD_CLS);
  delay(2);    
}

