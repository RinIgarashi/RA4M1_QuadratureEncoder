#include "RA4M1_QuadratureEncoder.h"

// Type information of the GPT registers
using GPT_Type = typeof(*R_GPT0);

// Mapping of channel numbers (0-7) to hardware pointers
static GPT_Type* const GPT_PTRS[8] = {
    (GPT_Type*)R_GPT0,
    (GPT_Type*)R_GPT1,
    (GPT_Type*)R_GPT2,
    (GPT_Type*)R_GPT3,
    (GPT_Type*)R_GPT4,
    (GPT_Type*)R_GPT5,
    (GPT_Type*)R_GPT6,
    (GPT_Type*)R_GPT7
};

QuadratureEncoder::QuadratureEncoder(uint8_t timer_ch, uint16_t pinA, uint16_t pinB) {
    // Limit channel to 0-7
    _timer_ch = (timer_ch > 7) ? 7 : timer_ch;
    _timer_ptr = GPT_PTRS[_timer_ch];

    // GPT0-1: 32bit, GPT2-7: 16bit
    _is_16bit = (_timer_ch >= 2);

    // Decoding port and pin from the format (e.g., 301 -> Port 3, Pin 1)
    _port_a = pinA / 100;
    _pin_a = pinA % 100;
    _port_b = pinB / 100;
    _pin_b = pinB % 100;
}

void QuadratureEncoder::begin() {
    GPT_Type* timer = (GPT_Type*)_timer_ptr;

    // Module stop control register D (MSTPCRD) 
    if (_is_16bit) {
        R_MSTP->MSTPCRD_b.MSTPD6 = 0;  // GPT 167-162 module stop setting: 0 (Disabled)
    } else {
        R_MSTP->MSTPCRD_b.MSTPD5 = 0;  // GPT 321-320 module stop setting: 0 (Disabled)
    }
    // Module stop control register C (MSTPCRC)
    R_MSTP->MSTPCRC_b.MSTPC14 = 0;     // Event link controller module stop setting: 0 (Disabled)

    // GPT control register (GTCR)
    timer->GTCR_b.CST = 0; // Count start: 0 (Stop)

    // Port mn pin function selection register (PmnPFS)
    configurePin(_port_a, _pin_a);
    configurePin(_port_b, _pin_b);

    timer->GTUPSR = 0x6900; // GPT up-count factor selection register (GTUPSR)
    timer->GTDNSR = 0x9600; // GPT down-count factor selection register (GTDNSR)

    // GPT period setting register (GTPR)
    timer->GTPR = _is_16bit ? 0xFFFF : 0xFFFFFFFF; // Set to maximum value for 16bit/32bit

    // Reset the counter to 0
    // timer->GTCNT = 0;

    // GPT control register (GTCR)
    timer->GTCR_b.CST = 1; // Count start: 1 (Start)
}

int32_t QuadratureEncoder::read() {
    GPT_Type* timer = (GPT_Type*)_timer_ptr;
    
    if (_is_16bit) {
        // Important: For 16-bit timers, cast to int16_t first, then to int32_t.
        return (int32_t)(int16_t)timer->GTCNT;
    } else {
        return (int32_t)timer->GTCNT;
    }
}

void QuadratureEncoder::write(int32_t value) {
    GPT_Type* timer = (GPT_Type*)_timer_ptr;

    // GPT control register (GTCR)
    timer->GTCR_b.CST = 0; // Count start: 0 (Stop)

    // Overwrite the counter value directly
    timer->GTCNT = (uint32_t)value;

    // GPT control register (GTCR)
    timer->GTCR_b.CST = 1; // Count start: 1 (Start)
}

void QuadratureEncoder::configurePin(uint16_t port, uint16_t pin) {
   // Port mn pin function selection register (PmnPFS)
    R_PFS->PORT[port].PIN[pin].PmnPFS_b.PDR = 0;         // Port Direction: 0 (Input)
    R_PFS->PORT[port].PIN[pin].PmnPFS_b.PCR = 1;         // Pull-up Control: 1 (Pull-up enabled)
    R_PFS->PORT[port].PIN[pin].PmnPFS_b.PMR = 1;         // Port Mode Control: 1 (Peripheral function I/O port)
    R_PFS->PORT[port].PIN[pin].PmnPFS_b.PSEL = 0b00011;  // Peripheral Select: GTIOCxA/B (0b00011)
}