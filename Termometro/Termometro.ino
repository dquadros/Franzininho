/*
 * Termômetro
 * DQ - 01/03/18
 */

// Conexões do display ao Franzininho
#define PIN_SCE   0
#define PIN_DC    4
#define PIN_SDIN  1
#define PIN_SCLK  3

// Conexão do sensor (LM35)
#define PIN_SENSOR A1

// Seleção de dado ou comando
#define LCD_CMD   LOW
#define LCD_DAT   HIGH

// Tamanho da tela
#define LCD_DX    84
#define LCD_DY    48

// Envia um byte para o controlador do display
// dc:   LCD_CMD ou LCD_DAT
// data: byte a enviar
void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

// Iniciação do display
void LcdInitialise(void)
{
  // define a direção dos pinos de E/S
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  
  // envia os comandos de iniciação
  LcdWrite( LCD_CMD, 0x21 ); // LCD Extended Commands.
  LcdWrite( LCD_CMD, 0xB0 ); // Set LCD Vop (Contraste)
  LcdWrite( LCD_CMD, 0x04 ); // Set Temp coefficent
  LcdWrite( LCD_CMD, 0x14 ); // LCD bias mode 1:48
  LcdWrite( LCD_CMD, 0x20 ); // LCD Basic Commands.
  LcdWrite( LCD_CMD, 0x0c ); // LCD no modo normal  
}

// Limpa a tela
void LcdClear(void)
{
  // posiciona ponteiro no inicio da memória
  LcdWrite( LCD_CMD, 0x40);  
  LcdWrite( LCD_CMD, 0x80);
  
  // preenche a memória com zeros
  for (int index = 0; index < LCD_DX * LCD_DY / 8; index++)
  {
    LcdWrite(LCD_DAT, 0x00);
  }
}

// Posiciona em uma determina linha e coluna alfanuméricas
void LcdPos(int lin, int col)
{
  LcdWrite( LCD_CMD, 0x40 + lin);  
  LcdWrite( LCD_CMD, 0x80 + col*7);  
}

// Tabelas para desenhar os caracteres

static const int offset_dig[] = {0, 14, 28, 36, 50, 58 };
static const int larg_dig[] = {14, 14, 8, 14, 8, 14 };
static const byte gc_dig[][30] =
{
  { 0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00 }, // 0
  { 0x00, 0x00, 0x0C, 0x06, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 }, // 1
  { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 }, // 2
  { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00 }, // 3
  { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03 }, // 4
  { 0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00 }, // 5
  { 0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00 }, // 6
  { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03 }, //7
  { 0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00 }, // 8
  { 0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFC,
    0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00 }, // 9
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x60, 0x1F, 
    0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // virgula
  { 0x1E, 0x21, 0x21, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // grau
  { 0xFC, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 }  // C
};

// Escreve um dígito na tela
// dig: 0 a 9, 10 (virgula), 11 (grau), 12 (C)
// pos: 0 a 5
void LcdWriteDig(int dig, int pos)
{
  byte *gc = gc_dig[dig];
  int larg = larg_dig[pos] - 4;

  for (byte bloco = 1; bloco <= 3; bloco++)
  {
    LcdWrite(LCD_CMD, 0x40 + bloco);  
    LcdWrite(LCD_CMD, 0x80 + offset_dig[pos]);  
    LcdWrite(LCD_DAT, 0x00);
    LcdWrite(LCD_DAT, 0x00);
    for (int index = 0; index < larg; index++)
    {
      LcdWrite(LCD_DAT, *gc++);
    }
    LcdWrite(LCD_DAT, 0x00);
    LcdWrite(LCD_DAT, 0x00);
  }
}

//=====================================
// Pontos de entrada padrão do Arduino
//=====================================

void setup(void)
{
  LcdInitialise();
  LcdClear();
  LcdWriteDig (0, 0);
  LcdWriteDig (0, 1);
  LcdWriteDig (10, 2);
  LcdWriteDig (0, 3);
  LcdWriteDig (11, 4);
  LcdWriteDig (12, 5);

  analogReference(INTERNAL);
  analogRead(PIN_SENSOR);
}

void loop(void)
{
  // Faz 16 leituras para maior precisão
  int vSensor = 0;
  for (int i = 0; i < 16; i++)
  {
    vSensor += analogRead(PIN_SENSOR);
  }
  vSensor = vSensor >> 2;

  // 0,01V = 1 grau Celsius
  // Referência interna pode variar entre 1.0 e 1.2 V
  // Valor abaixo baseado em medida feita com multímetro
  long temp = (vSensor*1016L)/(4096L);

  // Mostra a temperatura
  LcdWriteDig ((int)(temp/100), 0);
  LcdWriteDig ((int)((temp/10)%10), 1);
  LcdWriteDig ((int)(temp%10), 3);

  // Tempo entre atualizações
  delay(1000);
}


