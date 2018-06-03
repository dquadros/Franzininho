/*
 * TecAnalogico - Tratamento de teclas ligadas a entrada analogica
 * 
 * Tecla    tensão
 * T1       4,55 - 4,68
 * T2       3,84 - 4,13
 * T3       2,50 - 2,98
 * T4       1,24 - 1,62
 * T5       0,65
 * T6       0V
 * nenhuma  5V
 * 
 * Daniel Quadros - 02/06/18
 * https://dqsoft.blogspot.com
 */

#include <arduino.h>
#include "EfeitosSonoros.h"

// Converte tensão em leitura do ADC
#define valorADC(v)  ((1024u*v)/50u)

// Tempo em que o valor deve permanecer constante
const int tempoDebounce = 100;  // milisegundos

// Construtor
TecAnalogico::TecAnalogico(int pin)
{
  pinTec = pin;
  ultimaTecla = SEM_TECLA;
  leitura[0] = leitura[1] = leitura[2] = leitura[3] = 1023;
  pos = 0;
  ultimaLeitura = 1023;
}

// Testa se tem tecla apertada
uint8_t TecAnalogico::LeTecla()
{
  // Le a tensão e faz a média
  leitura[pos] = analogRead(pinTec);
  pos = (pos + 1) & 3;
  unsigned valor = (leitura[0] + leitura[1] + leitura[2] + leitura[3])/4;

  // Ignora pequenas oscilações
  unsigned dif;
  if (valor > ultimaLeitura)
    dif = valor - ultimaLeitura;
  else
    dif = ultimaLeitura - valor;
  if (dif >= 5)
  {
    // mudou leitura, aguardar tempo de debounce
    ultimaLeitura = valor;
    tempoLeitura = millis();
  }
  if ((tempoLeitura + tempoDebounce) < millis())
  {
    // passou tempo de debounce, determinar a tecla
    if (valor < valorADC(4))
      ultimaTecla = 6;
    else if (valor < valorADC(10))
      ultimaTecla = 5;
    else if (valor < valorADC(20))
      ultimaTecla = 4;
    else if (valor < valorADC(30))
      ultimaTecla = 3;
    else if (valor < valorADC(40))
      ultimaTecla = 2;
    else if (valor < valorADC(47))
      ultimaTecla = 1;
    else
      ultimaTecla = SEM_TECLA;
  } 
  return ultimaTecla;
}


