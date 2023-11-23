#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

int c[300][2], pontos=1, cx=2, cy=2, comida[2], velocidade=150;
char tecla;

void gotoxy(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void desenha() {
    for(int i=0; i<pontos; i++) {
        gotoxy(c[i][0], c[i][1]);
        printf("%c",219);
    }
}

void atualiza() {
    gotoxy(c[pontos][0], c[pontos][1]);
    printf(" ");
    for(int i=pontos; i>=0; i--) {
        c[i+1][0] = c[i][0];
        c[i+1][1] = c[i][1];
    }
}

int analisa() {
    int retorno=0;
    for(int i=0; i<pontos; i++) {
        if(cx==c[i][0] && cy==c[i][1]) {
            retorno=1;
        }
    }
    return retorno;
}

void geraComida() {
    gotoxy(comida[0],comida[1]);
    printf(" ");
    srand(time(NULL));
    comida[0] = (rand()%48)+1;
    comida[1] = (rand()%18)+1;
    gotoxy(comida[0], comida[1]);
    printf("%c", 4);
}

int main() {
    int gameover=0;
    char letra;

    for(int i=0; i<50; i++) {
        gotoxy(i,0);
        printf("%c", 219);
        Sleep(5);
    }

    for(int i=0; i<20; i++) {
        gotoxy(50, i);
        printf("%c", 219);
        Sleep(5);
    }

    for(int i=50; i>=0; i--) {
        gotoxy(i, 20);
        printf("%c", 219);
        Sleep(5);
    }

    for(int i=20; i>=0; i--) {
        gotoxy(0, i);
        printf("%c", 219);
        Sleep(5);
    }

    geraComida();
    desenha();
    tecla = 'd';

    while(gameover==0) {
        gotoxy(52,2);
        printf("Pontos: %d", pontos);
        gotoxy(52,4);
        c[0][0]=cx;
        c[0][1]=cy;

        if(kbhit()) {
            tecla = getch();
        }

        if(tecla=='w' || tecla=='W' || tecla==72) {
            cy--;
            if(cy==0) {
                break;
            }
        }

        if(tecla=='a' || tecla=='A' || tecla==75) {
            cx--;
            if(cx==0) {
                break;
            }
        }

        if(tecla=='s' || tecla=='S' || tecla==80) {
            cy++;
            if(cx==50) {
                break;
            }
        }

        if(tecla=='d' || tecla=='D' || tecla==77) {
            cx++;
            if(cx==50) {
                break;
            }
        }

        if(cx==comida[0] && cy==comida[1]) {
            pontos++;
            if(velocidade>50) {
                velocidade-=50;
            }
            geraComida();
        }

        gameover=analisa();
        atualiza();
        desenha();
        gotoxy(50,20);
        Sleep(velocidade);
    }
    system("cls");
    printf("Você perdeu");
    system("pause");
}
