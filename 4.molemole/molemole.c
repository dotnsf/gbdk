#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE 10

#define min_x 1
#define min_y 3
#define max_x ( min_x + SIZE - 1 )
#define max_y ( min_y + SIZE - 1 )
/*
-    主人公 @
- 0. 何もない （半角スペース）
- 1. 土 .
- 2. はしご >
- 3. 芋 *
- 4. 石 #
- 5. ドア D
*/
const uint8_t boards[3][SIZE][SIZE] = {
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
        { 2, 4, 4, 4, 4, 4, 4, 4, 4, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 3, 3, 3, 3, 3, 3, 3, 3, 2 }
    },
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
        { 2, 4, 4, 4, 4, 4, 4, 4, 4, 2 },
        { 2, 4, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 2, 3, 3, 3, 3, 3, 3, 3, 3, 2 }
    },
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
        { 1, 4, 4, 4, 4, 4, 4, 4, 4, 2 },
        { 1, 4, 1, 1, 1, 1, 1, 1, 4, 2 },
        { 1, 4, 1, 0, 0, 0, 0, 1, 4, 2 },
        { 1, 4, 1, 0, 3, 3, 0, 1, 4, 2 },
        { 1, 4, 1, 0, 1, 1, 0, 1, 4, 2 },
        { 1, 4, 1, 1, 1, 1, 1, 1, 4, 2 },
        { 1, 1, 4, 4, 4, 4, 4, 4, 1, 2 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 }
    }
};
const uint8_t init_positions[SIZE][SIZE] = {
    { 0, 0 },
    { 0, 0 },
    { 4, 0 }
};
uint8_t stage = 0;
int items = 0;
uint8_t current_board[SIZE][SIZE];
uint8_t pos_x, pos_y;

void cleared( void ){
    gotoxy( 3, 7 );
    printf( "        " );
    gotoxy( 3, 8 );
    printf( " CLEAR! " );
    gotoxy( 3, 9 );
    printf( "        " );
}

void clearScreen( void ){
    uint8_t i;
    char line[SIZE+3];

    //. line 生成
    for( i = 1; i < SIZE + 1; i ++ ){
        line[i] = ' ';
    }
    line[0] = '#';
    line[SIZE+1] = '#';
    line[SIZE+2] = NULL;

    for( i = 3; i < 3 + SIZE; i ++ ){
        gotoxy( 0, i );
        printf( line );
    }
}

int countLeftItems( void ){
    uint8_t i, j, cnt = 0;
    for( i = 0; i < SIZE; i ++ ){
        for( j = 0; j < SIZE; j ++ ){
            if( current_board[i][j] == 3 ){
                cnt ++;
            }
        }
    }

	items = cnt;
	if( cnt == 0 ){
		if( current_board[pos_y-1][pos_x-1] == 5 ){
            items = -1;
		}
	}

	return cnt;
}

void displayChar( void ){
    gotoxy( pos_x + 1, pos_y + 3 );
    printf( "@" );
}

void displayScore( void ){
    int s, i;
	
	countLeftItems();
    s = stage + 1;
    i = items;
    if( i < 0 ){ i = 0; }

    gotoxy( 1, 2 );
    printf( "%02d         %02d", s, i );
}

void displayBoard( void ){
    uint8_t i, j;
    char line[SIZE+3];

    for( i = 0; i < SIZE; i ++ ){
        //. line 生成
        for( j = 0; j < SIZE; j ++ ){
            if( current_board[i][j] == 0 ){
                line[1+j] = ' ';
            }else if( current_board[i][j] == 1 ){
                line[1+j] = '.';
            }else if( current_board[i][j] == 2 ){
                line[1+j] = '>';
            }else if( current_board[i][j] == 3 ){
                line[1+j] = '*';
            }else if( current_board[i][j] == 4 ){
                line[1+j] = '#';
            }else if( current_board[i][j] == 5 ){
                line[1+j] = 'D';
            }
        }

        line[0] = '#';
        line[SIZE+1] = '#';
        line[SIZE+2] = NULL;

        gotoxy( 0, i + 3 );
        printf( line );
    }

    for( j = 0; j < SIZE + 2; j ++ ){
        line[j] = '#';
    }
    line[SIZE+2] = NULL;
    gotoxy( 0, SIZE + 3 );
    printf( line );
}

void displayStage( void ){
    displayBoard();
    displayScore();
    displayChar();
}

int checkMove( int dir ){  //. dir: 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
    uint8_t cnt = 0;
    
    if( dir == 0 ){
        if( pos_y > 0 && current_board[pos_y][pos_x] == 2 && current_board[pos_y-1][pos_x] != 4 ){
            pos_y --;
            if( current_board[pos_y][pos_x] != 2 && current_board[pos_y][pos_x] != 5 ){
                current_board[pos_y][pos_x] = 0;
            }

            return 1;
        }else{
            return 0;
        }
    }else if( dir == 1 ){
        if( pos_x < SIZE - 1 && current_board[pos_y][pos_x+1] != 4 ){
        	//. 上が石だった場合
        	if( pos_y > 0 && current_board[pos_y-1][pos_x] == 4 ){
        		current_board[pos_y-1][pos_x] = 0;
        		current_board[pos_y][pos_x] = 4;
        	}
        	
            pos_x ++;
            if( current_board[pos_y][pos_x] != 2 && current_board[pos_y][pos_x] != 5 ){
            	//. ドアの上にくるとここが実行されてしまう？？
                current_board[pos_y][pos_x] = 0;
            }

            //. Gravity
            while( pos_y < SIZE - 1 && current_board[pos_y+1][pos_x] == 0 ){
	        	//. 上が石だった場合
        		if( pos_y > 0 && current_board[pos_y-1][pos_x] == 4 ){
        			current_board[pos_y-1][pos_x] = 0;
        			current_board[pos_y][pos_x] = 4;
        		}
                pos_y ++;
            }

            return 1;
        }else{
            return 0;
        }
    }else if( dir == 2 ){
        if( pos_y < SIZE - 1 && current_board[pos_y+1][pos_x] != 4 ){
        	//. 上が石だった場合
        	if( pos_y > 0 && current_board[pos_y-1][pos_x] == 4 ){
        		current_board[pos_y-1][pos_x] = 0;
        		current_board[pos_y][pos_x] = 4;
        	}

            pos_y ++;
            if( current_board[pos_y][pos_x] != 2 && current_board[pos_y][pos_x] != 5 ){
                current_board[pos_y][pos_x] = 0;
            }
        	
            //. Gravity
            while( pos_y < SIZE - 1 && current_board[pos_y+1][pos_x] == 0 ){
	        	//. 上が石だった場合
        		if( pos_y > 0 && current_board[pos_y-1][pos_x] == 4 ){
        			current_board[pos_y-1][pos_x] = 0;
        			current_board[pos_y][pos_x] = 4;
        		}
                pos_y ++;
            }

            return 1;
        }else{
            return 0;
        }
    }else if( dir == 3 ){
        if( pos_x > 0 && current_board[pos_y][pos_x-1] != 4 ){
        	//. 上が石だった場合
        	if( pos_y > 0 && current_board[pos_y-1][pos_x] == 4 ){
        		current_board[pos_y-1][pos_x] = 0;
        		current_board[pos_y][pos_x] = 4;
        	}
        	
            pos_x --;
            if( current_board[pos_y][pos_x] != 2 && current_board[pos_y][pos_x] != 5 ){
                current_board[pos_y][pos_x] = 0;
            }

            //. Gravity
            while( pos_y < SIZE - 1 && current_board[pos_y+1][pos_x] == 0 ){
	        	//. 上が石だった場合
        		if( pos_y > 0 && current_board[pos_y-1][pos_x] == 4 ){
        			current_board[pos_y-1][pos_x] = 0;
        			current_board[pos_y][pos_x] = 4;
        		}
                pos_y ++;
            }

            return 1;
        }else{
            return 0;
        }
    }else{
    	return 0;
    }
}

void initStage( void ){
    uint8_t i, j;
    for( i = 0; i < SIZE; i ++ ){
        for( j = 0; j < SIZE; j ++ ){
            current_board[i][j] = boards[stage][i][j];
        }
    }
    pos_x = init_positions[stage][0];
    pos_y = init_positions[stage][1];

    displayStage();
}

void initGame(){
    initStage();
}

void main( void ){
    uint8_t key;
    int dir;

    gotoxy( 2, 1 );
    printf( "MoleMole" );

    stage = 0;
    initGame();

    CRITICAL {
        add_SIO(nowait_int_handler);
    }
    set_interrupts(SIO_IFLAG);

    while( 1 ) {
        key = waitpad( J_A | J_B | J_START | J_SELECT | J_UP | J_DOWN | J_LEFT | J_RIGHT );
        waitpadup();

        dir = -1;
        if( key == J_A ){
            // A Button
        	if( items == -1 ){
        		if( stage < 2 ){
	        		//. 次のステージ
        			stage ++;
        			initGame();
        		}else{
        			//. ゲーム終了
        		}
        	}
        }else if( key == J_B ){
            // B Button
            //. 現在のステージをやり直し
            initGame();
        }else if( key == J_START ){
            // START Button
            //printf( "START" );
        }else if( key == J_SELECT ) {
            // SELECT Button
            //printf( "SELECT" );
        }else if( key == J_UP ) {
            // UP Button
        	if( items > -1 ){
	            dir = 0;
        	}
        }else if( key == J_DOWN ) {
            // DOWN Button
        	if( items > -1 ){
	            dir = 2;
        	}
        }else if( key == J_LEFT ) {
            // LEFT Button
        	if( items > -1 ){
	            dir = 3;
        	}
        }else if( key == J_RIGHT ) {
            // RIGHT Button
        	if( items > -1 ){
	            dir = 1;
        	}
        }

        if( dir != -1 ){
            if( checkMove( dir ) ){
                displayStage();
                if( countLeftItems() == -1 ){
                    //. ステージクリア
                    cleared();
                }
            }
        }

        /* In case of user cancellation */
        waitpadup();
    }
}
