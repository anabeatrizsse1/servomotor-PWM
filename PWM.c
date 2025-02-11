#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>


#define PINO_CTRL_SERVO 22 // Pino utilizado para o controle do servomotor

// Definições para os ângulos do servomotor (0, 90 e 180 graus)
int angulos_servo[] = {0, 90, 180};  // Posições: 0°, 90° e 180°
uint16_t ciclo_ativo; // Para armazenar o ciclo de trabalho do PWM
uint num_slice_pwm; // Para armazenar o número do slice do PWM
int angulos[] = {0, 90, 180};

// Função que realiza a movimentação suave entre 0° e 180° 
void realizar_movimentacao_suave() {
    ciclo_ativo = 500;  // Inicializa com o ciclo de trabalho de 0 graus (500μs)
    
    // Movimentação do servomotor entre 0 e 180 graus
    int estado = 0;  // 0 para aumento, 1 para diminuição
    while (true) {
        if (estado == 0) {
            ciclo_ativo += 5; // Aumenta o ciclo de trabalho em 5μs
            if (ciclo_ativo >= 2400) {
                estado = 1; // Se o ciclo chegar a 2400μs, começa a diminuir
            }
        } else {
            ciclo_ativo -= 5; // Diminui o ciclo de trabalho em 5μs
            if (ciclo_ativo <= 500) {
                estado = 0; // Se o ciclo chegar a 500μs, começa a aumentar
            }
        }

        pwm_set_chan_level(num_slice_pwm, PWM_CHAN_A, ciclo_ativo); // Aplica o ciclo de trabalho no PWM
        sleep_ms(10); // Pausa de 10ms para transições suaves
    }
}

// Função para configurar o PWM do servomotor
void configurar_pwm() {
    gpio_set_function(PINO_CTRL_SERVO, GPIO_FUNC_PWM); // Define o pino como PWM
    num_slice_pwm = pwm_gpio_to_slice_num(PINO_CTRL_SERVO); // Obtém o número do slice PWM

    // Define a frequência do PWM como 50Hz (20ms)
    pwm_set_clkdiv(num_slice_pwm, 125.0f); // Calcula para 50Hz
    pwm_set_wrap(num_slice_pwm, 20000);    // Período de 20ms (equivalente a 50Hz)
    pwm_set_enabled(num_slice_pwm, true);  // Habilita o PWM para o pino
}

// Função para mover o servomotor para diferentes ângulos
void mover_servo_para_angulo(uint16_t angulo) {
    // Usa o switch para alternar entre os ângulos de 0, 90 e 180 graus
    switch (angulo) {
        case 0:
            ciclo_ativo = 500;  // Para 0 graus, ciclo de 500μs
            printf("Movendo o servo para 0 graus\n");
            break;
        case 90:
            ciclo_ativo = 1470; // Para 90 graus, ciclo de 1470μs
            printf("Movendo o servo para 90 graus\n");
            break;
        case 180:
            ciclo_ativo = 2400; // Para 180 graus, ciclo de 2400μs
            printf("Movendo o servo para 180 graus\n");
            break;
        default:
            ciclo_ativo = 500;  // Padrão para 0 graus caso o valor seja inválido
            break;
    }
    pwm_set_chan_level(num_slice_pwm, PWM_CHAN_A, ciclo_ativo); // Aplica o ciclo de trabalho
}

// Função principal
int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    configurar_pwm();  // Configura o PWM para o controle do servomotor

    for (int i = 0; i < 3; i++) {  // Usando um loop for para iterar sobre os ângulos
        mover_servo_para_angulo(angulos[i]);
        sleep_ms(5000);  // Aguarda 5 segundos em cada posição
    }
    // Inicia a movimentação suave do servomotor entre 0 e 180 graus
    realizar_movimentacao_suave();

    return 0;
}