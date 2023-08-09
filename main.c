#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define data_bus_direction      DDRD
#define control_bus_direction   DDRC

#define data_bus                PORTD
#define control_bus             PORTC

#define RS                      PC5
#define RW                      PC4
#define ENABLE                  PC3

void display_set(uint8_t num) {
    data_bus = num;
    control_bus &= ~(1 << RS);
    control_bus &= ~(1 << RW);
    control_bus |= (1 << ENABLE);
    _delay_us(1);
    control_bus &= ~(1 << ENABLE);
    _delay_ms(1);
}

void display_write_letter(char letter) {
    _delay_ms(1);
    data_bus = letter;
    control_bus |= (1 << RS);
    control_bus &= ~(1 << RW);
    control_bus |= (1 << ENABLE);
    _delay_us(1);
    control_bus &= ~(1 << ENABLE);
    control_bus &= ~(1 << RS);
    _delay_ms(1);
}

void display_write_string(char *sentence) {
    for(; *sentence; sentence++) {
        display_write_letter(*sentence);
    }
}

void display_initialize() {
    _delay_ms(50);

    // 8 bit mode, 1 line 
    display_set(0b00110000);

    // Display on, no cursor
    display_set(0b00001100);

    // Clean display
    display_set(0b00000001);

    // Return home
    display_set(0b00000010);
}

int main() {
    // Set buses to OUTPUT 
    data_bus_direction = 0xff;
    control_bus_direction |= (1 << RS) | (1 << RW) | (1 << ENABLE);
    
    // Initialize lcd display
    display_initialize();

    // Write L
    display_write_string("Hello World.");
    return 0;
} 
