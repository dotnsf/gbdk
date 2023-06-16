#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

void main( void ){
    uint8_t i;

    puts( "Hello World!" );

    CRITICAL {
        add_SIO(nowait_int_handler);    // disable waiting VRAM state before return
    }
    set_interrupts(SIO_IFLAG);          // disable other interrupts. note: this disables sprite movement

    while( 1 ) {
        i = waitpad( J_A | J_B | J_START | J_SELECT );
        waitpadup();

        if( i == J_A ){
            // A Button
            printf( "A" );
        }else if( i == J_B ){
            // B Button
            printf( "B" );
        }else if( i == J_START ){
            // START Button
            printf( "START" );
        }else if( i == J_SELECT ) {
            // SELECT Button
            printf( "SELECT" );
        }
        /* In case of user cancellation */
        waitpadup();
    }
}
