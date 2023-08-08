

/************************************************************
 * GPIO routines: you will implement these.
 */

// different functions we can set GPIO pins to.
typedef enum {
    GPIO_FUNC_INPUT   = 0,
    GPIO_FUNC_OUTPUT  = 1,
    GPIO_FUNC_ALT0    = 4,
    GPIO_FUNC_ALT1    = 5,
    GPIO_FUNC_ALT2    = 6,
    GPIO_FUNC_ALT3    = 7,
    GPIO_FUNC_ALT4    = 3,
    GPIO_FUNC_ALT5    = 2,
} gpio_func_t;


/**
 * Configure GPIO <pin> as an output pin.
 */
void gpio_set_output(unsigned pin);

/**
 * Configure GPIO <pin> as an input pin.
 */
void gpio_set_input(unsigned pin);

/**
 * Set GPIO <pin> on.
 */
void gpio_set_on(unsigned pin);

/**
 * Set GPIO<pin> off.
 */
void gpio_set_off(unsigned pin);

/**
 * Set GPIO <pin> to <v>.
 *
 * <v> should be interepreted as a C "boolean"; i.e., 0 is false, anything else
 * is true.
 */
void gpio_write(unsigned pin, unsigned v);

/**
 * Read the current value of GPIO <pin>.
 * Returns either 0 or 1.
 */
int gpio_read(unsigned pin);

/***********************************************************
 * GPIO Pullup/Down routines; these aren't necessary for many things, but can be
 * useful.  They let an input pin have a "default" state when the pin isn't
 * connected, instead of randomly reading as 0 or 1.
 */

/**
 * Activate the pullup register on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
void gpio_set_pullup(unsigned pin);

/**
 * Activate the pulldown register on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
void gpio_set_pulldown(unsigned pin);

/**
 * Deactivate both the pullup and pulldown registers on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
void gpio_pud_off(unsigned pin);

/**
 * Counts down <ticks> cycles.
 */
void delay_cycles(unsigned ticks);
