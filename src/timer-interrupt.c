#include "rpi.h"
#include "asm-funcs.h"
#include "timer-interrupt.h"

void timer_interrupt_init(unsigned ncycles) {
    // check timer offsets?

    PUT32(Enable_Basic_IRQs, RPI_BASIC_ARM_TIMER_IRQ);
    PUT32(AMR_TIMER_LOAD, ncycles);

    
}