#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void setup_io();
void setup_isr();

/**
 * ISR performs tap handling and controls the onboard LED.
 */
ISR(PCINT2_vect) {
    if (PIND & _BV(PIND2)) {
        // Turn on LED if touch sensor is being tapped
        PORTB |= _BV(PORTB5);
    } else {
        // Turn off LED if touch sensor is not being tapped
        PORTB &= ~_BV(PORTB5);
    }
}

int main() {
    setup_io();
    setup_isr();

    while (1) {
        // Loop. Handling performed in ISR.
    }

    return 0;
}

/**
 * Helper method to configure correct pins as either inputs or outputs.
 */
void setup_io() {
    // Set PD2 (pin 2) as input
    DDRD &= ~_BV(DDD2);
    // Enable pull-up resistor for PD2
    PORTD |= _BV(PORTD2);

    // Set PB5 (pin 13) as output
    DDRB |= _BV(DDB5);
}

/**
 * Helper method to configure ISR for pin 2.
 */
void setup_isr() {
    // Enable pin change interrupt for PCINT18 (pin 2)
    PCMSK2 |= _BV(PCINT18);
    PCICR  |= _BV(PCIE2);

    // Enable interrupts
    sei();
}
