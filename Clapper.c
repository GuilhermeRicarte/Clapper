#include "pico/stdlib.h"
#include "hardware/adc.h"

// Defina o pino do microfone e dos LEDs
#define MIC_PIN 26  // Exemplo de pino para o microfone 
#define LED_PIN 15  // Exemplo de pino para o LED 

// Limiar para detectar aplauso 
#define SOUND_THRESHOLD 2000  

// Função para inicializar o microfone (ADC)
void init_microphone() {
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(0);  // Assume que o microfone está no canal ADC0 
}

// Função para ler o valor do microfone
uint16_t read_microphone() {
    return adc_read();
}

// Função para acionar o LED
void set_led_state(bool state) {
    gpio_put(LED_PIN, state);
}

int main() {
    // Inicializar os pinos e o microfone
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    init_microphone();

    while (true) {
        // Ler o valor do microfone
        uint16_t mic_value = read_microphone();

        // Verificar se o som detectado está acima do limiar 
        if (mic_value > SOUND_THRESHOLD) {
            // Acender o LED se houver aplauso
            set_led_state(true);
            sleep_ms(500);  // LED aceso por 500ms
            set_led_state(false);  // Apagar o LED
        }

        sleep_ms(50);  // Atraso para não sobrecarregar o processador
    }

    return 0;
}
