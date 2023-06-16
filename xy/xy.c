#include <gb/gb.h>
#include <gb/console.h>
#include <stdint.h>
#include <stdio.h>

void main( void ){
    uint8_t key;

    gotoxy( 1, 1 );
    printf( "Hello World!" );

    CRITICAL {
        add_SIO(nowait_int_handler);    // disable waiting VRAM state before return
    }
    set_interrupts(SIO_IFLAG);          // disable other interrupts. note: this disables sprite movement

    while( 1 ) {
        key = waitpad( J_A | J_B | J_START | J_SELECT | J_UP | J_DOWN | J_LEFT | J_RIGHT );
        waitpadup();

        gotoxy( 1, 3 );
        if( key == J_A ){
            // A Button
            printf( "A" );
        }else if( key == J_B ){
            // B Button
            printf( "B" );
        }else if( key == J_START ){
            // START Button
            printf( "START" );
        }else if( key == J_SELECT ) {
            // SELECT Button
            gprintf( "SELECT" );
        }else if( key == J_UP ) {
            // UP Button
            gprintf( "UP" );
        }else if( key == J_DOWN ) {
            // DOWN Button
            gprintf( "DOWN" );
        }else if( key == J_LEFT ) {
            // LEFT Button
            gprintf( "LEFT" );
        }else if( key == J_RIGHT ) {
            // RIGHT Button
            gprintf( "RIGHT" );
        }

        /* In case of user cancellation */
        waitpadup();
    }
}
