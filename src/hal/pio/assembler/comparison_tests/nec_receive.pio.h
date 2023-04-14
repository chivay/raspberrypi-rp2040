// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ----------- //
// nec_receive //
// ----------- //

#define nec_receive_wrap_target 0
#define nec_receive_wrap 8

static const uint16_t nec_receive_program_instructions[] = {
            //     .wrap_target
    0xe03e, //  0: set    x, 30                      
    0x2020, //  1: wait   0 pin, 0                   
    0x00c7, //  2: jmp    pin, 7                     
    0x0042, //  3: jmp    x--, 2                     
    0xa0c3, //  4: mov    isr, null                  
    0x20a0, //  5: wait   1 pin, 0                   
    0x0000, //  6: jmp    0                          
    0xae42, //  7: nop                           [14]
    0x4001, //  8: in     pins, 1                    
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program nec_receive_program = {
    .instructions = nec_receive_program_instructions,
    .length = 9,
    .origin = -1,
};

static inline pio_sm_config nec_receive_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + nec_receive_wrap_target, offset + nec_receive_wrap);
    return c;
}

static inline void nec_receive_program_init (PIO pio, uint sm, uint offset, uint pin) {
    // Set the GPIO function of the pin (connect the PIO to the pad)
    //
    pio_gpio_init(pio, pin);
    // Set the pin direction to `input` at the PIO
    //
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);
    // Create a new state machine configuration
    //
    pio_sm_config c = nec_receive_program_get_default_config (offset);
    // configure the Input Shift Register
    //
    sm_config_set_in_shift (&c,
                            true,       // shift right
                            true,       // enable autopush
                            32);        // autopush after 32 bits
    // join the FIFOs to make a single large receive FIFO
    //
    sm_config_set_fifo_join (&c, PIO_FIFO_JOIN_RX);
    // Map the IN pin group to one pin, namely the `pin`
    // parameter to this function.
    //
    sm_config_set_in_pins (&c, pin);
    // Map the JMP pin to the `pin` parameter of this function.
    //
    sm_config_set_jmp_pin (&c, pin);
    // Set the clock divider to 10 ticks per 562.5us burst period
    //
    float div = clock_get_hz (clk_sys) / (10.0 / 562.5e-6);
    sm_config_set_clkdiv (&c, div);
    // Apply the configuration to the state machine
    //
    pio_sm_init (pio, sm, offset, &c);
    // Set the state machine running
    //
    pio_sm_set_enabled (pio, sm, true);
}

#endif
