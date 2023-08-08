@ trivial routine to write a 32-bit passed as the second argument
@ (register r1) to the address passed as the first argument (register 
@ r0)
.globl put32
.globl PUT32
put32:
PUT32:
    str r1,[r0]
    bx lr

@ trivial routine to do a 32-bit load of the address passed as
@ the first argument.
.globl get32
.globl GET32
get32:
GET32:
    ldr r0,[r0]
    bx lr
