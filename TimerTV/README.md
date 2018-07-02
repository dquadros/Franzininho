# Projeto #5 - Timer para TV
Desliga a TV após um certo tempo.

TimerTVLearn descobre qual o comando para desligar a TV e o salva na
EEPRom. Um detector de IR precisa ser ligado ao pino P0 do Franzininho.
Pressione o botão de desligar do controle remoto até o LED do Franzininho
acender, indicando que o comando foi reconhecido e salvo.

TimetTV é a aplicação principal. Após o tempo (fixo no software) é o comando
de desligar a TV é enviado através de um LED IR ligado ao pino P4 no Arduino.
A pressão de um botão ligando ao pino P2 do Franzininho reinicia o contador. 
Quando estiver faltando pouco para o tempo expirar o LED do Franzininho é 
aceso (um buzzer pode ser ligado a P1 para chamar mais a atenção).



