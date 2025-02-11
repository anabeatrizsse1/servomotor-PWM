# servomotor-PWM

# Link do Video
https://youtu.be/m3l2yfEme7g

# Controle de Servomotor com Raspberry Pi Pico

Este projeto utiliza a placa Raspberry Pi Pico para controlar um servomotor com um sinal PWM, movendo-o suavemente entre as posições de 0°, 90° e 180°.

## Descrição

O código configura um pino da Raspberry Pi Pico (GPIO 22) para enviar sinais PWM, controlando o ângulo do servomotor. Ele realiza movimentos suaves do servomotor entre os ângulos de 0°, 90° e 180° e também implementa uma movimentação periódica entre esses ângulos.

O programa realiza as seguintes etapas:

1. Configura o PWM para a frequência de 50Hz (20ms).
2. Move o servomotor para as posições de 0°, 90° e 180°.
3. Realiza uma movimentação suave entre 0° e 180° com um incremento de 5µs no ciclo de trabalho (ciclo ativo).
4. Usa o delay de 5 segundos entre os movimentos para que o servomotor permaneça em cada posição.

## Requisitos

- Raspberry Pi Pico.
- Servomotor compatível com PWM.
- Biblioteca `pico-sdk` instalada e configurada para o Raspberry Pi Pico.

## Conexões de Hardware

- **GPIO 22**: Pino de controle do servomotor (pino PWM).
- **GND**: Terra (GND).
- **VCC**: Alimentação do servomotor (normalmente 5V ou 3.3V dependendo do modelo do servomotor).

## Passos para Compilar e Carregar o Código

1. Clone o repositório ou faça o download do código fonte para o seu computador.
2. Instale o `pico-sdk` no seu ambiente de desenvolvimento. Se necessário, siga a [documentação oficial do pico-sdk](https://github.com/raspberrypi/pico-sdk) para configurar o SDK.
3. Compile o código com as ferramentas fornecidas pelo `pico-sdk`:
    - Abra o terminal na pasta do projeto.
    - Compile o código usando o comando `make`.
    - O arquivo `.uf2` gerado será o binário do firmware que pode ser carregado na Raspberry Pi Pico.
4. Conecte a Raspberry Pi Pico ao seu computador enquanto mantém o botão "BOOTSEL" pressionado para entrar no modo de armazenamento.
5. Copie o arquivo `.uf2` gerado para a Raspberry Pi Pico (ela irá reiniciar automaticamente após o carregamento).

## Funcionamento do Código

1. O código inicializa o pino GPIO 22 para usar PWM, com a frequência configurada em 50Hz (20ms).
2. O servomotor é movido para as posições de 0°, 90° e 180° com ciclos de 500µs, 1470µs e 2400µs, respectivamente.
3. Depois de mover para essas posições, o código executa um movimento suave do servomotor entre 0° e 180°, ajustando o ciclo de trabalho em 5µs a cada iteração.
4. O servomotor se moverá continuamente entre 0° e 180°, passando por todas as posições intermediárias com um intervalo de 10ms para transições suaves.
