/*
 * Treinador Morse
 * DQ - 07/03/18
 */

#include "LCD0208.h"

// Pinos usados
const int pinBuzzer = 1;
const int pinTecla = 4;

// Endereço I2C do display
const byte LCD_ADDR = 0x38;

// Acesso ao display
LCD0208 *lcd;

// Temporizações
int tDot;

// Iniciação
void setup() {
  // Inicia perifericos
  pinMode (pinBuzzer, OUTPUT);
  digitalWrite (pinBuzzer, LOW);
  pinMode (pinTecla, INPUT_PULLUP);
  lcd = new LCD0208(LCD_ADDR);
  
  // Aprende tempo do ponto
  treino();
}

// Loop principal
void loop() {
  static unsigned char carac = 0;   
  static int nbits = 0;
  
  // Espera apertar a tecla
  unsigned long inicio = millis();
  while (digitalRead(pinTecla) == HIGH) {
    delay(50);
  }
  unsigned long pausa = millis() - inicio;
  inicio = millis();
  digitalWrite (pinBuzzer, HIGH);

  // Identifica a pausa
  if (pausa < (tDot << 1)) {
    // pausa entre bits, nada a fazer
  } else if (pausa < (tDot << 2)) {
    // pausa entre caracteres
    mostra (decod (carac, nbits));
    carac = 0;
    nbits = 0;
    lcd->displayWrite(1, 0, "     ");
  } else {
    // pausa entre palavras
    mostra (decod (carac, nbits));
    carac = 0;
    nbits = 0;
    mostra (' ');
    lcd->displayWrite(1, 0, "     ");
    carac = 0;
    nbits = 0;
  }
    
  // Espera soltar a tecla
  while (digitalRead(pinTecla) == LOW) {
    delay(50);
  }
  digitalWrite (pinBuzzer, LOW);
  unsigned long duracao = millis() - inicio;
  delay(50);

  // Classifica e acrescenta ao caracter atual
  if (nbits < 5) {
    carac = carac << 1;
    if (duracao < (tDot << 1)) {
      // ponto
      lcd->displayWrite(1, nbits, "*");
    } else {
      // traco
      carac |= 1;      
      lcd->displayWrite(1, nbits, "-");
    }
    nbits++;
  }
}

// Decodifica um caracter
char decod (unsigned char cod, int nbits) {
  switch (nbits) {
    case 1: return "ET"[cod];
    case 2: return "IANM"[cod];
    case 3: return "SURWDKGO"[cod];
    case 4: return "HVF?L?PJBXCYZQ??"[cod];
    case 5: return "54?3???2???????16???????7???8?90"[cod];
  }
  return '?';
}

// Mostra caracter na primeira linha
void mostra (char carac) {
  static char texto[9] = "        ";
  static int poscar = 0;
  
  if (poscar > 7) {
    // rola o texto para a esquerda
    for (int i = 0; i < 7; i++) {
      texto[i] = texto[i+1];
    }
    poscar = 7;
  }
  texto[poscar++] = carac;
  lcd->displayWrite(0, 0, texto);
}

// Treinamento
// Aprende o tempo de um ponto (média dos três últimos)
// Encerrado se não apertar o botão por mais de três segundos
void treino() {
  int tempo[3];
  int iTempo = 0;
  int nTempo = 0;
  
  lcd->displayWrite(0, 0, "Treino");
  for (;;) {
    // Espera apertar a tecla
    unsigned long inicio = millis();
    while (digitalRead(pinTecla) == HIGH) {
      delay(50);
      if ((millis() - inicio) > 3000) {
        break;
      }
    }
    if ((millis() - inicio) > 3000) {
      break;
    }
    digitalWrite (pinBuzzer, HIGH);
    inicio = millis();
    // Espera soltar a tecla
    while (digitalRead(pinTecla) == LOW) {
      delay(50);
    }
    digitalWrite (pinBuzzer, LOW);
    // Calcula a duração
    unsigned long duracao = millis() - inicio;
    // Guarda o tempo
    tempo[iTempo++] = (int) duracao;
    if (iTempo > 2) {
      iTempo = 0;
    }
    if (nTempo < 3) {
      nTempo++;
    }
  }
  if (nTempo == 0) {
    tDot = 200; // tempo padrão = 200ms
  } else {
    tDot = 0;
    for (int i = 0; i < nTempo; i++) {
      tDot += tempo[i];
    }
    tDot = tDot / nTempo;
  }
  lcd->clear();
}

