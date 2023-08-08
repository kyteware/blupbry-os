
#include <stdint.h> // uint32_t

/**
 * Used to write to device memory.  Use this instead of a raw store.
 * Writes the 32-bit value <v> to address <addr>.
 *
 * Safer alternative to *(uint32_t *)addr = v;
 *
 * Like PUT32, but takes <addr> as a pointer.
 */
void put32(volatile void *addr, uint32_t v);

/**
 * Used to write to device memory.  Use this instead of a raw store.
 * Writes the 32-bit value <v> to address <addr>.
 *
 * Safer alternative to *(uint32_t *)addr = v;
 *
 * Like put32, but takes <addr> as an int.
 */
void PUT32(uint32_t addr, uint32_t v);

/**
 * Used to read from device memory.  Use this instead of a raw dereference.
 * Returns the 32-bit value at address <addr>.
 *
 * Safer alternative to *(uint32_t *)addr.
 *
 * Like GET32, but takes <addr> as a pointer.
 */
uint32_t get32(const volatile void *addr);

/**
 * Used to read from device memory.  Use this instead of a raw dereference.
 * Returns the 32-bit value at address <addr>.
 *
 * Safer alternative to *(uint32_t *)addr.
 *
 * Like get32, but takes <addr> as an int.
 */
uint32_t GET32(uint32_t addr);

/**
 * An assembly routine that does nothing.
 * The compiler cannot optimize away an external function call, so we can use
 * it to prevent the compiler optimizing away loops.
 */
void nop(void);