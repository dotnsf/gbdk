#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdint.h>
#include <stdio.h>

void main( void ){
    uint8_t key;

    gotoxy( 1, 1 );
    printf( "Hello World!" );

    CRITICAL {
        add_SIO(nowait_int_handler);
    }
    set_interrupts(SIO_IFLAG);

    while( 1 ) {
        key = waitpad( J_A | J_B | J_START | J_SELECT | J_UP | J_DOWN | J_LEFT | J_RIGHT );
        waitpadup();

        gotoxy( 1, 3 );
        printf( "      " );
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
            printf( "SELECT" );
        }else if( key == J_UP ) {
            // UP Button
            printf( "UP" );
        }else if( key == J_DOWN ) {
            // DOWN Button
            printf( "DOWN" );
        }else if( key == J_LEFT ) {
            // LEFT Button
            printf( "LEFT" );
        }else if( key == J_RIGHT ) {
            // RIGHT Button
            printf( "RIGHT" );
        }

        /* In case of user cancellation */
        waitpadup();
    }
}
