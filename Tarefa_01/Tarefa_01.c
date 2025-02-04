#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

// ---------------- Defines - Início ----------------

// Definição dos pinos dos LEDs do semáforo
#define red_pin 11
#define yellow_pin 12
#define green_pin 13

// ---------------- Defines - Fim ----------------



// ---------------- Variáveis - Início ----------------

// Variável de controle para gerenciar o estado do semáforo
static volatile uint ctrl = 0;

// ---------------- Variáveis - Fim ----------------



// ---------------- Semáforo - Início ----------------

// Inicializa os pinos do semáforo e define o estado inicial (vermelho ligado)
void init_semaforo() {
  gpio_init(red_pin);
  gpio_init(yellow_pin);
  gpio_init(green_pin);

  gpio_set_dir(red_pin,GPIO_OUT);
  gpio_set_dir(yellow_pin,GPIO_OUT);
  gpio_set_dir(green_pin,GPIO_OUT);

  gpio_put(red_pin, 1);    // Vermelho ligado
  gpio_put(yellow_pin, 0); // Amarelo desligado
  gpio_put(green_pin, 0);  // Verde desligado

  ctrl = 1; // Define o estado inicial do semáforo
}

// ---------------- Semáforo - Fim ----------------



// Callback para a troca dos estados do semáforo em intervalos de tempo
bool repeating_timer_callback(struct repeating_timer *t) {
    switch(ctrl) {
        case 0:
            gpio_put(green_pin, 0);  // Desliga verde
            gpio_put(red_pin, 1);    // Liga vermelho
            ctrl++;
            break;
        case 1:
            gpio_put(red_pin, 0);    // Desliga vermelho
            gpio_put(yellow_pin, 1); // Liga amarelo
            ctrl++;
            break;
        case 2:
            gpio_put(yellow_pin, 0); // Desliga amarelo
            gpio_put(green_pin, 1);  // Liga verde
            ctrl = 0;
            break;
        default:
            // Estado inválido: Reinicia o controle
            gpio_put(red_pin, 1);
            gpio_put(yellow_pin, 0);
            gpio_put(green_pin, 0);
            ctrl = 1;
    }
    return true;
}

int main()
{
    uint contador = 0; // Para contar os segundos passados da execução

    stdio_init_all();

    init_semaforo(); // Configura o semáforo
    
    // Configura um timer para chamar a função de troca de estados a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Superloop: Imprime um contador de segundos continuamente
    while (true) {
        printf("Contador de segundos: %d s\n",contador);
        
        sleep_ms(1000); // Espera 1 segundo (1000 ms)

        // Incrementa o contador e verifica se é múltiplo de 3
        if( ( (++contador) % 3) == 0 ) {
            printf("TEMPO! "); // Indica quando deve acontecer uma troca no semáforo
        } 
    }
    return 0;
}