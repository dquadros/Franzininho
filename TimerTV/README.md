# Projeto #5 - Timer para TV
Desliga a TV ap�s um certo tempo.

TimerTVLearn descobre qual o comando para desligar a TV e o salva na
EEPRom. Um detector de IR precisa ser ligado ao pino P0 do Franzininho.
Pressione o bot�o de desligar do controle remoto at� o LED do Franzininho
acender, indicando que o comando foi reconhecido e salvo.

TimetTV � a aplica��o principal. Ap�s o tempo (fixo no software) � o comando
de desligar a TV � enviado atrav�s de um LED IR ligado ao pino P4 no Arduino.
A press�o de um bot�o ligando ao pino P2 do Franzininho reinicia o contador. 
Quando estiver faltando pouco para o tempo expirar o LED do Franzininho � 
aceso (um buzzer pode ser ligado a P1 para chamar mais a aten��o).



