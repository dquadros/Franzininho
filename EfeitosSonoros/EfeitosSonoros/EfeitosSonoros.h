/*
 * Efeitos Sonoros - Toca arquivo MP3 conforme botão apertado
 * 
 * Daniel Quadros - 02/06/18
 * https://dqsoft.blogspot.com
 */

// Conexões
const int pinTxMp3 = 1;
const int pinBusyMp3 = 0; 
const int pinTeclas = A1;

// Módulo MP3
class MP3
{
  private:
    uint8_t pinBusy;
    uint8_t bufCmd[10];
    void enviaCmd(uint8_t cmd, uint16_t param);

  public:
    MP3(uint8_t pin);
    void init(void);
    void toca(int faixa);
    void espera(void);
};

// Teclado
const uint8_t SEM_TECLA = 0;
class TecAnalogico
{
  private:
    int pinTec;
    uint8_t ultimaTecla;
    int leitura[4];
    int pos;
    int ultimaLeitura;
    unsigned long tempoLeitura;

  public:
    TecAnalogico(int pin);
    uint8_t LeTecla();
};


// Mini Serial
class MiniSerial
{
  private:
    uint8_t _transmitBitMask;
    volatile uint8_t *_transmitPortRegister;
    void inline tx_pin_write(uint8_t pin_state);
    void setTX(uint8_t transmitPin);
    static inline void tunedDelay(uint16_t delay);

  public:
    MiniSerial(uint8_t transmitPin);
    void write(uint8_t byte);
};
extern MiniSerial serial;


