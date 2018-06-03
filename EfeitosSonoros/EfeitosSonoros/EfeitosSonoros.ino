/*
 * Efeitos Sonoros - Toca arquivo MP3 conforme botão apertado
 * 
 * Daniel Quadros - 02/06/18
 * https://dqsoft.blogspot.com
 */

#include "EfeitosSonoros.h"

MiniSerial serial(pinTxMp3);
static TecAnalogico teclado(pinTeclas);
static MP3 mp3(pinBusyMp3);

// iniciacao
void setup() {
  delay(2000);
  mp3.init();
}

// laco principal
void loop() {
  uint8_t tecla;

  tecla = teclado.LeTecla();
  if (tecla != SEM_TECLA)
  {
    mp3.toca(tecla);
    mp3.espera();
    while (teclado.LeTecla() != SEM_TECLA)
    {
      delay(10);
    }
  }
}

