/*
 * Caixa de Música
 * DQ - 07/02/18
 */

// Pinos utilizados
const int pinLED = 1;
const int pinLDR = A1;
const int pinSOM = 0;

// Variaveis globais
int refLDR; // valor correspondente a caixa aberta

// Musica a ser tocada
#define MI5   659
#define RE5s  622
#define DO5   523
#define SI4   494
#define LA4   440
#define SOL4s 415
#define MI4   330
#define DO4   262

#define PAUSA 20000
#define D(x) (10000+x)
#define TEMPO 250

int musica[] = {
  MI5, RE5s, MI5, RE5s, MI5, SI4, RE5s, DO5, D(LA4), PAUSA,
  DO4, MI4, LA4, D(SI4), PAUSA,
  MI4, SOL4s, SI4, DO5, PAUSA,
  MI4, MI5, RE5s, MI5, RE5s, MI5, SI4, RE5s, DO5, D(LA4), PAUSA,
  DO4, MI4, LA4, D(SI4), PAUSA,
  MI4, DO5, SI4, D(LA4),
  0
};

void setup() {

  // Iniciação do LED
  pinMode (pinLED, OUTPUT);
  digitalWrite (pinLED, HIGH);  // acende

  // Iniciação do SOM
  pinMode (pinSOM, OUTPUT);
  digitalWrite (pinSOM, LOW);

  // Iniciação do LDR
  // Assume que caixa está aberta
  analogReference (DEFAULT);
  refLDR = 0;
  for (int i = 0; i < 10; i++) {
    refLDR += analogRead(pinLDR);
    delay (50);
  }
}

void loop() {
  int leituraLDR;
  
  // Espera a caixa ser fechada
  do {
    leituraLDR = 0;
    for (int i = 0; i < 10; i++) {
      leituraLDR += analogRead(pinLDR);
      delay (50);
    }
  } while (leituraLDR/10 > refLDR/12);
  digitalWrite (pinLED, LOW);  // apaga

  // Espera a caixa ser fechada
  do {
    leituraLDR = 0;
    for (int i = 0; i < 10; i++) {
      leituraLDR += analogRead(pinLDR);
      delay (50);
    }
  } while (leituraLDR/10 < refLDR/11);
  digitalWrite (pinLED, HIGH);  // acende

  tocaMusica();
}

// Toca as notas da música
void tocaMusica() {
  int i = 0;
  int f, d;
  while (musica[i] != 0) {
    f = musica[i];
    d = TEMPO;
    if (f == PAUSA) {
      delay (TEMPO);
    } else {
      if (f > 10000) {
        f -= 10000;
        d = 2*TEMPO;
      }
      beep (pinSOM, f, d);
    }
    delay(10);
    i++;
  }
}

// Rotina para gerar tons "na raça"
// Fonte: https://learn.adafruit.com/trinket-gemma-mini-theramin-music-maker/arduino-code
//        http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ 
  int  x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
  }
}

