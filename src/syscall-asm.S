#include "rpi-asm.h"

MK_FN(syscall_hello)
    push {lr}
    svc 1
    pop {lr}
    bx lr

MK_FN(run_user_code_asm)
    msr cpsr, #(0b11111) @ user mode

    mov sp, r1
    blx r0

    bl clean_reboot