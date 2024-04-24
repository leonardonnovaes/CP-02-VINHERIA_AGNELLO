# CP-02-VINHERIA_AGNELLO

No projeto, enfrentamos o desafio de desenvolver um sistema integrado de sensores de luz, umidade e temperatura, conectados a um display, para garantir a conservação ideal dos vinhos em uma vinícola.

# Descrição

O projeto consiste em um sistema baseado em Arduino UNO R3 com uma board, que integra sensores de LDR para medição de luz, DHT11 para medição de umidade e temperatura, além de um display para exibir as informações coletadas. Quando a temperatura, umidade ou luz ultrapassam os níveis ideais, um buzzer é acionado e um LED vermelho é ligado como alerta. Quando os valores estão em níveis intermediários, um LED amarelo é acionado e o buzzer emite um aviso. Quando todas as condições estão dentro dos parâmetros desejados, um LED verde indica que está tudo certo. Esse sistema visa garantir a conservação ideal dos vinhos em uma vinícola.

# Componentes

- 1xArduino UNO R3
- 1xSensor LDR
- 1XLed verde
- 1xLed vermelho
- 1xLed amarelo
- 1xSensor DHT11
- 1xDisplay LCD
- 4xResistores 220Ω
- 1xBUZZER
- 23xCabos Jumper
- 1xProtoboard

# Montagem
1. Para dar vida ao projeto, inicie posicionando os componentes na protoboard. A montagem é livre mas caso queira seguir nossa configuração aqui está:
![Captura de tela 2024-04-24 193128](https://github.com/leonardonnovaes/CP-02-VINHERIA_AGNELLO/assets/148134209/c6d8b1d1-bdb9-4965-b180-4031e47ddb04)

2. Certifique-se de que o DHT está na porta 13, os leds nas portas 9, 8, 7, o buzzer na porta 6, o ldr na porta A5 e o lcd nas portas 12, 11, 10, 5, 4, 3, 2.

3. 
