/*
 * TimerTvLearn - Aprende uma tecla do controle remoto
 *                e salva na EEProm
 * Daniel Quadros 25/06/18
 * https://dqsoft.blogspot.com
 */

#include <EEPROM.h>

// Descomentar o define abaixo para testar no Arduino UNO
//#define UNO

#ifdef UNO
#include <IRremote.h>
#else
#include <tiny_IRremote.h>
#endif


// Pinos utilizados
#ifdef UNO
const int pinRecv = 11;
const int pinLED = 13;
#else
const int pinRecv = 0;
const int pinLED = 1;
#endif

// Recepção do comando
static IRrecv irrecv(pinRecv);

// Para confirmar o código
static decode_results resultsAnt;

// Iniciação
void setup() {
  pinMode (pinLED, OUTPUT);
  digitalWrite (pinLED, LOW);
  irrecv.enableIRIn();
  #ifdef UNO
  Serial.begin(9600);
  #endif
  resultsAnt.decode_type = UNKNOWN;
  resultsAnt.value = 0;
}

// Programa Principal
void loop() {
  decode_results results;

  // Aguarda reconhecer um comando
  if (irrecv.decode(&results)) {
    // Trata alguns casos especiais
    if ((results.decode_type == NEC) && (results.bits == 0)) {
      // Ignora REPEAT do NEC
      results.decode_type = UNKNOWN;
    } else if ((results.decode_type == RC5) || (results.decode_type == RC6)) {
      // Zera o toogle bit
      results.value &= ~(1L << (results.bits - 1)); 
    }
    // Tentar de novo se código nao identificado
    if (results.decode_type == UNKNOWN) {
      irrecv.resume();
    } else if ((results.decode_type != resultsAnt.decode_type) ||
               (results.value != resultsAnt.value))
    {
      // Não bateu com o anterior, insistir
      resultsAnt.decode_type = results.decode_type;
      resultsAnt.value = results.value;
      irrecv.resume();
    } else {
      // Salva o comando na EEPROM
      EEPROM.write(0, (uint8_t) results.decode_type);
      EEPROM.write(1, (uint8_t) results.bits);
      #ifdef UNO
      EEPROM.write(2, (results.address >> 8) & 0xFF);
      EEPROM.write(3, results.address & 0xFF);
      #endif
      EEPROM.write(4, (results.value >> 24) & 0xFF);
      EEPROM.write(5, (results.value >> 16) & 0xFF);
      EEPROM.write(6, (results.value >> 8) & 0xFF);
      EEPROM.write(7, results.value & 0xFF);
      
      // Acende o LED
      digitalWrite (pinLED, HIGH);
      
      #ifdef UNO
      Serial.print (results.decode_type);
      Serial.print (' ');
      Serial.print (results.bits);
      Serial.print (' ');
      Serial.print (results.address, HEX);
      Serial.print (' ');
      Serial.println (results.value, HEX);
      #endif
      
      // Faz mais nada
      for (;;)
        ;
    }
  }
}

