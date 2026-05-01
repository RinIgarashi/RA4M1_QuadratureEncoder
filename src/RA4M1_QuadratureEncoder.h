#ifndef RA4M1_QUADRATUREENCODER_H
#define RA4M1_QUADRATUREENCODER_H

#include <Arduino.h>

// Pin-specified macro (e.g., PORT_PIN(3, 2) -> 302)
#define PORT_PIN(port, pin) (((port) * 100) + (pin))

class QuadratureEncoder {
public:
    // Constructor: Specify timer channel and pins
    // timer_ch: 0-7 (GPT0-1: 32bit, GPT2-7: 16bit)
    // pinA, pinB: Renesas RA4M1 port/pin format (e.g., P302 -> 302, P101 -> 101)
    QuadratureEncoder(uint8_t timer_ch, uint16_t pinA, uint16_t pinB);

    void begin();               // Initialization and start counting
    int32_t read();             // Read the count value (signed)
    void write(int32_t value);  // Set the count value (used for reset, etc.)

private:
    void* _timer_ptr;
    uint8_t _timer_ch;
    uint16_t _port_a, _pin_a;
    uint16_t _port_b, _pin_b;
    bool _is_16bit;

    void configurePin(uint16_t port, uint16_t pin);
};

#endif // RA4M1_QUADRATUREENCODER_H