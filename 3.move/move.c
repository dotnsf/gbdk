#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE 10

#define min_x 1
#define min_y 3
#define max_x ( min_x + SIZE - 1 )
#define max_y ( min_y + SIZE - 1 )

void clearScreen(){
    uint8_t i;
    //char line[] = "          ";
    char line[SIZE+1];

    //. line 生成
    for( i = 0; i < SIZE; i ++ ){
        line[i] = ' ';
    }
    line[SIZE] = NULL;

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
        add_SIO(nowait_int_handler);
    }
    set_interrupts(SIO_IFLAG);

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
