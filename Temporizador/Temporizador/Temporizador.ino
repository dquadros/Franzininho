/*
 * Temporizador
 * DQ - 18/02/18
 */

 // Pinos utilizados
const int pinTecla = 3;
const int pinRele = 0;
const int pinPot = A1;

void setup() {
  // Iniciação do relê
  // Nível alto no pino = relê desligado
  pinMode (pinRele, OUTPUT);
  digitalWrite(pinRele, HIGH);

  // Iniciação do botão
  pinMode (pinTecla, INPUT_PULLUP);

  // Iniciação do potenciômetro
  analogReference(DEFAULT);
}

void loop() {

  // Espera apertar o botão
  while (digitalRead(pinTecla) == HIGH) {
    delay(10);
  }

  // Lê o potenciômetro
  int pot = analogRead(pinPot);

  // Espera soltar o botão
  while (digitalRead(pinTecla) == LOW) {
    delay(10);
  }

  // Aciona o relê por um tempo proporcional à leitura
  long tempo = 10L*60L*pot + 1000L; 
  digitalWrite(pinRele, LOW);
  delay (tempo);  
  digitalWrite(pinRele, HIGH);
}
