// Q: does push change sp before writing to it or after?
// Implement the <todo>
#include "rpi.h"

enum { push_val = 0xdeadbeef };

static inline uint32_t *sp_get(void) {
    uint32_t *sp = 0;
    asm volatile("mov %0, sp" : "=r"(sp));
    assert(sp);
    return sp;
}


// called with:
//   - <sp_after_push>: value of the <sp> after the push 
//   - <sp_before_push>: value of the <sp> before the push 
void after_push(uint32_t *sp_after_push, uint32_t *sp_before_push) {
    trace("sp_after=[%p] val=%x, sp_before=[%p] [val=%x]\n",
                    sp_after_push, 
                    *sp_after_push, 
                    sp_before_push, 
                    *sp_before_push);

    // if(sp_after_push < sp_before_push)
    //     trace("stack grows down\n");
    // else if(sp_after_push > sp_before_push)
    //     trace("stack grows up\n");
    // else
    //     panic("impossible\n");
    if (*sp_after_push == push_val)
        trace("wrote to stack after modifying sp\n");
    else
        trace("wrote to stack before modifying sp\n");

    // we can't return b/c didn't obey calling convention.
    clean_reboot();
}

// should take a few lines: 
//   - push argument (in r0) onto the stack.
//   - call <after_push> with:
//      - the first argument: sp after you do the push.
//      - second argument: sp before you do the push.

// implement this assembly routine in <asm-checks.S>
void check_push_asm(uint32_t push_val) {
    // poison
    asm volatile("push {%0}" :: "r"(1));
    asm volatile("push {%0}" :: "r"(1));
    asm volatile("push {%0}" :: "r"(1));
    asm volatile("pop {%0}" :: "r"(0));
    asm volatile("pop {%0}" :: "r"(0));
    asm volatile("pop {%0}" :: "r"(0));
    uint32_t *sp_before = sp_get();
    asm volatile("push {%0}" :: "r"(push_val));
    uint32_t *sp_after = sp_get();
    after_push(sp_after, sp_before);
    asm volatile("pop {%0}" :: "r"(0));
};

void notmain() {
    printk("about to check asm push\n");
    check_push_asm(push_val);
    not_reached();
}
