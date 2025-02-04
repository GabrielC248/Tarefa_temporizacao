#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

// ---------------- Defines - Início ----------------

// Definição dos pinos para os LEDs e o botão
#define blue_pin 11
#define red_pin 12
#define green_pin 13
#define button_pin 5

// ---------------- Defines - Fim ----------------



// ---------------- Variáveis - Início ----------------

static volatile bool button_ctrl = false; // Variável para controlar o acionamento do botão
static volatile uint counter = 0;         // Variável para contar o número de execuções do alarme

// ---------------- Variáveis - Fim ----------------



// ---------------- Setup - Início ----------------

// Função para inicializar os pinos
void init_pins() {
  gpio_init(blue_pin);
  gpio_init(red_pin);
  gpio_init(green_pin);
  gpio_init(button_pin);

  // Define os LEDs como saída e o botão como entrada
  gpio_set_dir(blue_pin,GPIO_OUT);
  gpio_set_dir(red_pin,GPIO_OUT);
  gpio_set_dir(green_pin,GPIO_OUT);
  gpio_set_dir(button_pin, GPIO_IN);

  // Garante que os LEDs estejam desligados no início
  gpio_put(blue_pin, 0);
  gpio_put(red_pin, 0);
  gpio_put(green_pin, 0);

  // Habilita o pull-up interno no botão (ativo em nível baixo)
  gpio_pull_up(button_pin);
}

// ---------------- Setup - Fim ----------------

// Função callback chamada pelo alarme quando o tempo programado expira
int64_t alarm_callback(alarm_id_t id, __unused void *user_data) {

    // Visualizar no terminal o tempo em ms do acionamento do alarme
    printf("Tempo no %dº alarme: %d ms\n",counter+1,(int)to_ms_since_boot(get_absolute_time()));

    // Controle da sequência de desligamento dos LEDs
    if(counter == 0) { // Primeiro alarme
        counter++;
        add_alarm_in_ms(3000, alarm_callback, NULL, false);
        gpio_put(blue_pin, 0);
    }else
    if(counter == 1) { // Segundo alarme
        counter++;
        add_alarm_in_ms(3000, alarm_callback, NULL, false);
        gpio_put(red_pin, 0);
    }else
    if(counter == 2) { // Terceiro alarme
        counter = 0;
        button_ctrl = false;
        gpio_put(green_pin, 0);
    }
    return 0;
}

int main() {

    stdio_init_all();

    init_pins(); // Configura os pinos

    while(true) {
        sleep_ms(20); // Pequeno atraso para o wokwi e para servir como um pequeno debounce também

        // Verifica se o botão foi pressionado e se ainda não está bloqueado
        if( (gpio_get(button_pin) == 0) && (button_ctrl == false) ) {

            button_ctrl = true; // Bloqueia novas ativações até o ciclo terminar

            // Liga todos os LEDs
            gpio_put(blue_pin, 1);
            gpio_put(red_pin, 1);
            gpio_put(green_pin, 1);

            // Visualizar no terminal o tempo em ms do acionamento do botão
            printf("Tempo no acionamento do botão: %d ms\n",(int)to_ms_since_boot(get_absolute_time()));

            // Configura o primeiro alarme para desligamento dos LEDs após 3s
            add_alarm_in_ms(3000, alarm_callback, NULL, false);
        }
    }
}