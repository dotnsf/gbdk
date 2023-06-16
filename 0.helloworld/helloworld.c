#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

void main( void ){
    printf( "Hello World!" );

    CRITICAL {
        add_SIO(nowait_int_handler);    // disable waiting VRAM state before return
    }
    set_interrupts(SIO_IFLAG);          // disable other interrupts. note: this disables sprite movement
}
