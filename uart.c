#include <stdint.h>

#define FOSC 16000000UL
#define BAUD 9600
#define MYUBRR ((FOSC/(16UL*BAUD))-1)
#define TXEN 3
#define RXEN 4
#define UCSZ00 1
#define UCSZ01 2
#define UDRE0 5

volatile uint8_t *ubrr0h = (uint8_t*)(0xc5);
volatile uint8_t *ubrr0l = (uint8_t*)(0xc4);
volatile uint8_t *ucsr0a = (uint8_t*)(0xc0);
volatile uint8_t *ucsr0b = (uint8_t*)(0xc1);
volatile uint8_t *ucsr0c = (uint8_t*)(0xc2);
volatile uint8_t *udr0 = (uint8_t*)(0xc6);

void usart_init(uint16_t ubrr) {
    *ubrr0h = (uint8_t)(ubrr >> 8);
    *ubrr0l = (uint8_t)(ubrr);
    *ucsr0b = (uint8_t)((1 << RXEN) | (1 << TXEN));
    *ucsr0c = (uint8_t)((1 << UCSZ01) | (1 << UCSZ00));
}

void usart_transmit(uint8_t data) {
    while (!(*ucsr0a & (1 << UDRE0))) {}
    *udr0 = data;
}

int main() {
    usart_init(MYUBRR);
    usart_transmit((uint8_t)'Z');
    while (1) {}
}
