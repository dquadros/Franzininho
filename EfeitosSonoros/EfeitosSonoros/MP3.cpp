/*
 * Tratamento simplificado do módulo DFPlayer
 * 
 * Daniel Quadros - 02/06/18
 * https://dqsoft.blogspot.com
 */

#include <arduino.h>
#include "EfeitosSonoros.h"

// Parâmetros de configuração
static const uint16_t volume = 30;      // 0 a 48
static const uint16_t equalizacao = 1;  // 0=normal, 1=pop, 2=rock, 3=jazz
                                        // 4=classic, 5=bass

// Construtor
MP3::MP3(uint8_t pin)
{
  // prepara o buffer de envio de comand com os valores fixos
  bufCmd[0] = 0x7E;  // marca do inicio
  bufCmd[1] = 0xFF;  // versão do protocolo
  bufCmd[2] = 6;     // tamanho dos dados
  bufCmd[4] = 0;     // não queremos resposta
  bufCmd[9] = 0xEF;  // marca do fim
  // pino para detectar fim da musica
  pinBusy = pin;
  pinMode(pinBusy, INPUT);
} 

// Iniciação
void MP3::init()
{
  // configura o módulo
  enviaCmd(0x06, volume);
  delay(30);
  enviaCmd(0x07, equalizacao);
  delay(30);
}

// Inicia uma faixa
void MP3::toca(int faixa)
{
  // envia o comando
  enviaCmd(0x12, faixa);
    
  // aguarda começar a tocar
  long timeout = millis()+2000; // 2 segundos de timeout
  while ((digitalRead(pinBusy) == HIGH) && (millis() < timeout))
  {
    delay(10);
  }
}

// Espera acabar de tocar
void MP3::espera()
{
  while (digitalRead(pinBusy) == LOW)
  {
     delay(10);
  }
}

// Envia comando ao módulo
void MP3::enviaCmd(uint8_t cmd, uint16_t param)
{
  // coloca comando e parametro no buffer
  bufCmd[3] = cmd;
  bufCmd[5] = param >> 8;
  bufCmd[6] = param & 0xFF;

  // calcula o checksum e coloca no buffer
  uint16_t check = 0;
  for (int i = 1; i < 7; i++)
  {
    check += bufCmd[i];
  }
  check = -check;
  bufCmd[7] = check >> 8;
  bufCmd[8] = check & 0xFF;

  // transmite o buffer
  for (int i = 0; i < 10; i++)
  {
    serial.write(bufCmd[i]);
  }
}

