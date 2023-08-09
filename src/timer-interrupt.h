enum {
    IRQ_Base            = 0x2000b200,
    IRQ_basic_pending   = IRQ_Base+0,       // 0x200
    IRQ_pending_1       = IRQ_Base+4,       // 0x204
    IRQ_pending_2       = IRQ_Base+8,       // 0x208
    FIQ_control         = IRQ_Base+0xc,     // 0x20c
    Enable_IRQs_1       = IRQ_Base+0x10,    // 0x210
    Enable_IRQs_2       = IRQ_Base+0x14,    // 0x214
    Enable_Basic_IRQs   = IRQ_Base+0x18,    // 0x218
    Disable_IRQs_1      = IRQ_Base+0x1c,    // 0x21c
    Disable_IRQs_2      = IRQ_Base+0x20,    // 0x220
    Disable_Basic_IRQs  = IRQ_Base+0x24,    // 0x224
};

#define RPI_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define AMR_TIMER_LOAD                  0x2000B400

void timer_interrupt_init(unsigned ncycles);