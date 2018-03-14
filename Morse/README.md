# Projeto #3 - Treinador de Código Morse
Apresenta em um display LCD caracteres digitados em código Morse.

Uma tecla é usada para entrada do código. A pressão da tecla é acompanhada do
acionamento de um buzzer.

O LCD usado é um display alfanumérico de 2 linhas de 8 caracteres. Um integrado
PCF8574A é usado para expandir as saídas digitais do Franzininho.

Ao ligar o circuito estamos no modo "Treino". Neste modo o software "aprende" 
a velocidade do operador; ele fica neste modo até você ficar 3 segundos sem 
apertar o teclado. Ao sair deste modo, a média dos três últimos apertos é 
considerada o tempo para o "ponto" do código Morse.

O tempo para um traço deve ser três vezes o tempo do ponto. O tempo entre os 
pontos e traços de um caracter deve ser igual ao tempo de um ponto. Ao final 
de uma letra deve ser dado o tempo de um traço e ao final de uma palavra deve
ser dado o tempo de sete pontos.

Os pontos e traços vão sendo mostrados na linha inferior do display, até ser 
detectado o tempo entre caracteres. Os caracteres vão sendo mostrados na linha 
de cima do display.

