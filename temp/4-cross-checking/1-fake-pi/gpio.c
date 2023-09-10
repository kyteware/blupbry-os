/*
 * Implement the following routines to set GPIO pins to input or output,
 * and to read (input) and write (output) them.
 *
 * DO NOT USE loads and stores directly: only use GET32 and PUT32
 * to read and write memory.  Use the minimal number of such calls.
 *
 * See rpi.h in this directory for the definitions.
 */
#include "rpi.h"

// see broadcomm documents for magic addresses.
enum {
    GPIO_BASE = 0x20200000,
    gpio_sel0  = (GPIO_BASE), // function select 9-0
    gpio_set0  = (GPIO_BASE + 0x1C),
    gpio_clr0  = (GPIO_BASE + 0x28),
    gpio_lev0  = (GPIO_BASE + 0x34)
};

//
// Part 1 implement gpio_set_on, gpio_set_off, gpio_set_output
//

// set <pin> to be an output pin.
//
// note: fsel0, fsel1, fsel2 are contiguous in memory, so you
// can (and should) use array calculations!
void gpio_set_output(unsigned pin) {
    if(pin >= 32)
        return;

    uint32_t addr_offset = pin/10;
    uint32_t bit_offset = pin%10 * 3;

    uint32_t old = GET32(gpio_sel0 + addr_offset * 4);

    uint32_t mask = 0xffffffff ^ (0x7 << bit_offset);

    uint32_t msg = (old & mask) | (1 << bit_offset);
    PUT32(gpio_sel0 + addr_offset * 4, msg);
}

// set GPIO <pin> on.
void gpio_set_on(unsigned pin) {
    if(pin >= 32)
        return;

    PUT32(gpio_set0, 1 << pin);
}

// set GPIO <pin> off
void gpio_set_off(unsigned pin) {
    if(pin >= 32)
        return;

    PUT32(gpio_clr0, 1 << pin);
}

// set <pin> to <v> (v \in {0,1})
void gpio_write(unsigned pin, unsigned v) {
    if(pin >= 32)
        return;
    if(v)
        gpio_set_on(pin);
    else
        gpio_set_off(pin);
}

//
// Part 2: implement gpio_set_input and gpio_read
//

// set <pin> to input.
void gpio_set_input(unsigned pin) {
    if(pin >= 32)
        return;
    uint32_t addr_offset = pin/10;
    uint32_t bit_offset = pin%10 * 3;

    uint32_t old = GET32(gpio_sel0 + addr_offset * 4);

    uint32_t mask = 0xffffffff ^ (0x7 << bit_offset);

    uint32_t msg = (old & mask) | (0 << bit_offset);
    PUT32(gpio_sel0 + addr_offset * 4, msg);
}

// return the value of <pin>
int gpio_read(unsigned pin) {
    if(pin >= 32)
        return;
    return (GET32(gpio_lev0) >> pin) & 1;
}
