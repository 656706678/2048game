#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
int a[4][4]={0};
int empty;
void init();
void draw();
void draw_one();
void play();
void game_over();
int main(){
    init();
    play();
    endwin();
    return 0;
}
void init(){
    int x, y;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    empty = 15;

    srand(time(0));

    x = rand() % 4;
    y = rand() % 4;
    a[y][x] = 2;
    draw();
}
void draw(){
    int n, m, x, y;
    //char c[4] = {'0','0','0','0'};
    clear();
    for (n = 0; n < 9; n+=2 )
        for (m = 0; m < 21; m++){
            move(n, m);
            addch('-');
            refresh();
        }
    for (m = 0; m < 22; m += 5)
        for (n = 1; n < 8; n++){    
            move(n, m);
            addch('|');
            refresh();
        }
    for (y = 0; y < 4; y++)
        for (x = 0; x < 4; x++)
            draw_one(y,x);
    refresh();
}
void draw_one(int y, int x){
    int i, m, k, j;
    char c[5]={0x00};
    i = a[y][x];
    m = 0;
    while (i > 0){
        j = i % 10;
        c [ m++ ] = j + '0';
        i = i / 10;
    }

    m = 0;
    k = (x + 1) * 5 - 1;
    while (c[m] != 0x00){
        move(2*y+1, k);    
        addch(c[m++]);
        k--;
    }
}
void play(){
    int x, y, i, new_x, new_y, move1 = 0, old_empty = empty; 
    char ch;

    while (1){
        ch = getch();
        switch(ch){
            case 'a':
                for (y = 0; y < 4; y++)    
                    for (x = 0; x < 4;){
                        if (a[y][x] == 0 ){
                            x++;
                            continue;
                        } else{
                            for (i = x + 1; i < 4; i++){
                                if (a[y][i] == 0){
                                    continue;
                                } else{
                                    if (a[y][x] == a[y][i]){
                                        a[y][x] += a[y][i];
                                        a[y][i] = 0;
                                        empty++;
                                        break;
                                    } else{
                                        break;
                                    }
                                }
                            }
                            x = i;
                        }
                    }
                for (y = 0; y < 4; y++)
                    for (x = 0; x < 4; x++){
                        if (a[y][x] == 0){    
                            continue;
                        } else{
                            for (i = x; (i > 0) && (a[y][i-1] == 0); i--){
                                a[y][i-1] = a[y][i];
                                a[y][i] = 0;
                                move1 = 1;

                            }
                        }
                    }
                break;
            case 'd':
                for (y = 0; y < 4; y++)    
                    for (x = 3; x >= 0;){
                        if (a[y][x] == 0 ){
                            x--;
                            continue;
                        } else{
                            for (i = x - 1; i >= 0; i--){
                                if (a[y][i] == 0){
                                    continue;
                                } else{
                                    if (a[y][x] == a[y][i]){
                                        a[y][x] += a[y][i];
                                        a[y][i] = 0;
                                        empty++;
                                        break;
                                    } else{
                                        break;
                                    }
                                }
                            }
                            x = i;
                        }
                    }
                for (y = 0; y < 4; y++)
                    for (x = 3; x >= 0; x--){
                        if (a[y][x] == 0){    
                            continue;
                        } else{
                            for (i = x; (i < 3) && (a[y][i+1] == 0); i++){
                                a[y][i+1] = a[y][i];
                                a[y][i] = 0;
                                move1 = 1;

                            }
                        }
                    }
                break;
            case 'w':
                for (x = 0; x < 4; x++)    
                    for (y = 0; y < 4;){
                        if (a[y][x] == 0 ){
                            y++;
                            continue;
                        } else{
                            for (i = y + 1; i < 4; i++){
                                if (a[i][x] == 0){
                                    continue;
                                } else{
                                    if (a[y][x] == a[i][x]){
                                        a[y][x] += a[i][x];
                                        a[i][x] = 0;
                                        empty++;
                                        break;
                                    } else{
                                        break;
                                    }
                                }
                            }
                            y = i;
                        }
                    }
                for (x = 0; x < 4; x++)
                    for (y = 0; y < 4; y++){
                        if (a[y][x] == 0){    
                            continue;
                        } else{
                            for (i = y; (i > 0) && (a[i-1][x] == 0); i--){
                                a[i-1][x] = a[i][x];
                                a[i][x] = 0;
                                move1 = 1;

                            }
                        }
                    }
                break;
            case 's':
                for (x = 0; x < 4; x++)    
                    for (y = 3; y >= 0;){
                        if (a[y][x] == 0 ){
                            y--;
                            continue;
                        } else{
                            for (i = y - 1; i >= 0; i--){
                                if (a[i][x] == 0){
                                    continue;
                                } else{
                                    if (a[y][x] == a[i][x]){
                                        a[y][x] += a[i][x];
                                        a[i][x] = 0;
                                        empty++;
                                        break;
                                    } else{
                                        break;
                                    }
                                }
                            }
                            y = i;
                        }
                    }
                for (x = 0; x < 4; x++)
                    for (y = 3; y >= 0; y--){
                        if (a[y][x] == 0){    
                            continue;
                        } else{
                            for (i = y; (i < 3) && (a[i+1][x] == 0); i++){
                                a[i+1][x] = a[i][x];
                                a[i][x] = 0;
                                move1 = 1;

                            }
                        }
                    }
                break;
            case 'q':
                game_over();
                break;
            default:
                continue;
                break;
        }
        if (empty <= 0) game_over();
        if (old_empty != empty || move1 == 1){
            do {
                new_x = rand() % 4;
                new_y = rand() % 4;
            } while (a[new_y][new_x] != 0);
            a[new_y][new_x] = 2;
            empty--;
        }
        draw();
    }
}
void game_over(){
    sleep(1);
    endwin();
    exit(0);
}