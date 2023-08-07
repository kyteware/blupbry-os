// part2: test GPIO input.
//   - if we get a signal on the input pin 21, turn the LED on.
#include "rpi.h"

void notmain(void) {
    const int led = 20;
    const int flasher = 21;
    const int input = 16;

    gpio_set_output(led);
    gpio_set_output(flasher);
    gpio_set_input(input);

    int counter = 300000;
    int status = 0;
    while(1) {
        if (counter-- <= 0) {
            counter = 300000;
            status ^= 1;
            gpio_write(flasher, status);
        }
        // could also do: 
        //  gpio_write(input, gpio_read(led));
        if(gpio_read(input))
            gpio_set_on(led);
        else
            gpio_set_off(led);
    }
}
