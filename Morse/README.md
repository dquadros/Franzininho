# Projeto #3 - Treinador de C�digo Morse
Apresenta em um display LCD caracteres digitados em c�digo Morse.

Uma tecla � usada para entrada do c�digo. A press�o da tecla � acompanhada do
acionamento de um buzzer.

O LCD usado � um display alfanum�rico de 2 linhas de 8 caracteres. Um integrado
PCF8574A � usado para expandir as sa�das digitais do Franzininho.

Ao ligar o circuito estamos no modo "Treino". Neste modo o software "aprende" 
a velocidade do operador; ele fica neste modo at� voc� ficar 3 segundos sem 
apertar o teclado. Ao sair deste modo, a m�dia dos tr�s �ltimos apertos � 
considerada o tempo para o "ponto" do c�digo Morse.

O tempo para um tra�o deve ser tr�s vezes o tempo do ponto. O tempo entre os 
pontos e tra�os de um caracter deve ser igual ao tempo de um ponto. Ao final 
de uma letra deve ser dado o tempo de um tra�o e ao final de uma palavra deve
ser dado o tempo de sete pontos.

Os pontos e tra�os v�o sendo mostrados na linha inferior do display, at� ser 
detectado o tempo entre caracteres. Os caracteres v�o sendo mostrados na linha 
de cima do display.

