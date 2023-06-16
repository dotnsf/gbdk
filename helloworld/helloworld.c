#include <gb/gb.h>
#include <gb/drawing.h>
#include <stdint.h>
#include <stdio.h>

void main( void ){
    uint8_t i;

    gotogxy( 1, 1 );
    color( 3, 1, SOLID );
    gprintf( "Hello World!" );

    CRITICAL {
        add_SIO(nowait_int_handler);    // disable waiting VRAM state before return
    }
    set_interrupts(SIO_IFLAG);          // disable other interrupts. note: this disables sprite movement

    while( 1 ) {
        i = waitpad( J_A | J_B | J_START | J_SELECT | J_UP | J_DOWN | J_LEFT | J_RIGHT );
        waitpadup();

        gotogxy( 1, 3 );
        if( i == J_A ){
            // A Button
            gprintf( "A" );
        }else if( i == J_B ){
            // B Button
            gprintf( "B" );
        }else if( i == J_START ){
            // START Button
            gprintf( "START" );
        }else if( i == J_SELECT ) {
            // SELECT Button
            gprintf( "SELECT" );
        }else if( i == J_UP ) {
            // UP Button
            gprintf( "UP" );
        }else if( i == J_DOWN ) {
            // DOWN Button
            gprintf( "DOWN" );
        }else if( i == J_LEFT ) {
            // LEFT Button
            gprintf( "LEFT" );
        }else if( i == J_RIGHT ) {
            // RIGHT Button
            gprintf( "RIGHT" );
        }

        /* In case of user cancellation */
        waitpadup();
    }
}
