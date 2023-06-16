#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdint.h>
#include <stdio.h>

uint8_t min_x = 1, max_x = 10, min_y = 3, max_y = 12;

void clearScreen(){
    uint8_t i;
    char *line = "          ";

    //. line 生成
    for( i = min_x; i <= max_x; i ++ ){
    }

    for( i = min_y; i <= max_y; i ++ ){
        gotoxy( min_x, i );
        printf( line );
    }
}

void moveTo( uint8_t x, uint8_t y ){
    clearScreen();
    gotoxy( x, y );
    printf( "X" );
}

void main( void ){
    uint8_t key;
    uint8_t pos_x = 1, pos_y = 3;

    gotoxy( 1, 1 );
    printf( "move" );

    CRITICAL {
        add_SIO(nowait_int_handler);    // disable waiting VRAM state before return
    }
    set_interrupts(SIO_IFLAG);          // disable other interrupts. note: this disables sprite movement

    while( 1 ) {
        key = waitpad( J_A | J_B | J_START | J_SELECT | J_UP | J_DOWN | J_LEFT | J_RIGHT );
        waitpadup();

        clearScreen();

        if( key == J_A ){
            // A Button
            //printf( "A" );
        }else if( key == J_B ){
            // B Button
            //printf( "B" );
        }else if( key == J_START ){
            // START Button
            //printf( "START" );
        }else if( key == J_SELECT ) {
            // SELECT Button
            //printf( "SELECT" );
        }else if( key == J_UP ) {
            // UP Button
            if( pos_y > min_y ){
                pos_y --;
            }
        }else if( key == J_DOWN ) {
            // DOWN Button
            if( pos_y < max_y ){
                pos_y ++;
            }
        }else if( key == J_LEFT ) {
            // LEFT Button
            if( pos_x > min_x ){
                pos_x --;
            }
        }else if( key == J_RIGHT ) {
            // RIGHT Button
            if( pos_x < max_x ){
                pos_x ++;
            }
        }
        moveTo( pos_x, pos_y );

        /* In case of user cancellation */
        waitpadup();
    }
}
