/*
 * TimerTv - Desliga a TV após um certo tempo
 * Daniel Quadros 30/06/18
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
const int pinBotao = 9;
const int pinLED = 13;
#else
const int pinBotao = 2;
const int pinLED = 1;
#endif

// Tempos (em segundos)
const unsigned long tempoEspera = 30L*60L;
const unsigned long tempoAviso = 30;

// Envio do comando
static IRsend irsend;

// Comando salvo na EEPROM
static decode_results results;

// Iniciação
void setup() {
  pinMode (pinLED, OUTPUT);
  digitalWrite (pinLED, LOW);
  pinMode (pinBotao, INPUT_PULLUP);
  #ifdef UNO
  Serial.begin(9600);
  #endif
  leCmd ();
}

// Programa Principal
void loop() {
  unsigned long final = millis() + 1000*tempoEspera;
  unsigned long aviso = final - 1000*tempoAviso;
  
  while (millis() < final) {
    // Testa o botão
    if (digitalRead(pinBotao) == LOW) {
      // espera soltar o botão
      delay(100);
      while (digitalRead(pinBotao) == LOW)
        ;
      #ifdef UNO
      Serial.println ("Reinicia contagem");
      #endif
      return; //reiniciar a contagem
    }
    // Testa horário do aviso
    if (millis() > aviso) {
      #ifdef UNO
      Serial.println ("Aviso");
      #endif
      aviso += 2000;
      digitalWrite (pinLED, HIGH);
      delay (300);
      digitalWrite (pinLED, LOW);
    }
  }

  // Estourou o tempo, desligar a TV
  #ifdef UNO
  Serial.println ("Desliga");
  #endif
  enviaCmd();
  for (;;)
    ;
}

// Recupera da EEProm o comando que foi aprendido
void leCmd() {
  results.decode_type = EEPROM.read(0);
  results.bits = EEPROM.read(1);
  results.value = ((unsigned long) EEPROM.read(4)) << 24;
  results.value += ((unsigned long) EEPROM.read(5)) << 16;
  results.value += ((unsigned long) EEPROM.read(6)) << 8;
  results.value += (unsigned long) EEPROM.read(7);

  #ifdef UNO
  results.address = (EEPROM.read(2) << 8) + EEPROM.read(3);

  Serial.print (results.decode_type);
  Serial.print (' ');
  Serial.print (results.bits);
  Serial.print (' ');
  Serial.print (results.address, HEX);
  Serial.print (' ');
  Serial.println (results.value, HEX);
  #endif
}

// Envia o comando para desligar a TV
void enviaCmd() {
  switch (results.decode_type) {
    case RC5:
      irsend.sendRC5(results.value, results.bits);
      break;
    case RC6:
      irsend.sendRC6(results.value, results.bits);
      break;
    case SONY:
      irsend.sendSony(results.value, results.bits);
      break;
    case LG:
      irsend.sendLG(results.value, results.bits);
      break;  
    case NEC:
      irsend.sendNEC(results.value, results.bits);
      break;
    #ifdef UNO
    case PANASONIC:
      irsend.sendPanasonic(results.address, results.value);
      break;
    case SAMSUNG:
      irsend.sendSAMSUNG(results.value, results.bits);
      break;
    #endif
  }
}

