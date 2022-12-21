#include <stdint.h>

#define LOOP_NUM 100000

volatile uint8_t *portb = (uint8_t*)(0x25);
volatile uint8_t *ddrb = (uint8_t*)(0x24);

void delay(uint32_t num) {
    uint32_t i;
    for (i = 0; i < num; i++) {
        asm volatile("nop");
    }
}

int main() {
    *ddrb = 0xff;
    while(1) {
        *portb = (1<<7);
        delay(LOOP_NUM);
        *portb = 0;
        delay(LOOP_NUM);
    }
}
