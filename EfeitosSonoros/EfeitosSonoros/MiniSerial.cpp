/*
 * MiniSerial - versão simplificada de Digispark SoftSerial
 * https://github.com/digistump/DigistumpArduino/blob/master/digistump-avr/libraries/DigisparkSoftSerial/SoftSerial.cpp
 * 
 * Somente transmissão a 9600
 * 
 * Daniel Quadros - 02/06/18
 * https://dqsoft.blogspot.com
 */

#include <arduino.h>
#include "EfeitosSonoros.h"


// Assume clock de 8MHz, 9600bps
static const unsigned short TX_DELAY =  112;
static const int XMIT_START_ADJUSTMENT = 4;

//
// Métodos privados
//

// Rotina de delay
inline void MiniSerial::tunedDelay(uint16_t delay) { 
  uint8_t tmp=0;

  asm volatile("sbiw    %0, 0x01 \n\t"
    "ldi %1, 0xFF \n\t"
    "cpi %A0, 0xFF \n\t"
    "cpc %B0, %1 \n\t"
    "brne .-10 \n\t"
    : "+r" (delay), "+a" (tmp)
    : "0" (delay)
    );
}

// Define o pino de transmissão
void MiniSerial::setTX(uint8_t tx)
{
  pinMode(tx, OUTPUT);
  _transmitBitMask = digitalPinToBitMask(tx);
  uint8_t port = digitalPinToPort(tx);
  _transmitPortRegister = portOutputRegister(port);
  tx_pin_write(HIGH);  
}

// Controla o pino de transmissão
inline void MiniSerial::tx_pin_write(uint8_t pin_state)
{
  if (pin_state == LOW)
    *_transmitPortRegister &= ~_transmitBitMask;
  else
    *_transmitPortRegister |= _transmitBitMask;
}


//
// Construtor
//
MiniSerial::MiniSerial(uint8_t transmitPin)
{
  setTX(transmitPin);
}


//
// Métodos Públicos
//

// Transmite um byte
void MiniSerial::write(uint8_t b)
{
  uint8_t oldSREG = SREG;
  cli();  // turn off interrupts for a clean txmit

  // Write the start bit
  tx_pin_write(LOW);
  tunedDelay(TX_DELAY + XMIT_START_ADJUSTMENT);

  // Write each of the 8 bits
  for (byte mask = 0x01; mask; mask <<= 1)
  {
    if (b & mask) // choose bit
      tx_pin_write(HIGH); // send 1
    else
      tx_pin_write(LOW); // send 0
  
    tunedDelay(TX_DELAY);
  }

  tx_pin_write(HIGH); // restore pin to natural state
  tunedDelay(TX_DELAY);

  SREG = oldSREG; // turn interrupts back on
}

