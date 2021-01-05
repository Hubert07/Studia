/*
 * choinka.c
 * 
 * Copyright 2021 Hubert <Hubert@DESKTOP-27EU2EG>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

void wybor();
void wyswietl(int x, int y, char tab[40][40]);
void wyswietl_mig(int x, int y, char tab[40][40]);
void rysuj1(int h, char tab[40][40]);
void rysuj2(int h, char tab[40][40]);
void rysuj3(int h, char tab[40][40]);
void rysuj4(int h, char tab[40][40]);



int main(int argc, char **argv)
{
    int h, odp;
    char tab[40][40];
    
    printf("Podaj wysokosc choinki: ");
    scanf("%d", &h);
    wybor();
    scanf("%d", &odp);
    system("cls");

    switch (odp)
    {
    case 1:
    if (h > 9) {
        h = 9;
        rysuj1(h, tab);
    }
    else
        rysuj1(h, tab);
    break;

    case 2:
    if (h > 9) {
        h = 9;
        rysuj2(h, tab);
    }
    else
        rysuj2(h, tab);
    break;

    case 3:
    rysuj3(h, tab);
    break;

    case 4:
    rysuj4(h, tab);
    break;
    
    default :
    printf("Niewlasciwa liczba");
    break;
    
    }

    return 0;
}


void wybor() {
    printf("Jaka choinke chcesz?\n(Male choinki sa przyciane do wysokosci \
rownej 9)\n1. Mala\n2. Mala z bombkami\n3. Duza\n4. Duza z bombkami\n");
    }


void wyswietl(int x, int y, char tab[40][40]) {
    int i,j;
    for(i = 0; i < y; i++) {
        for(j = 0; j < x; j++) {
            printf("%c", tab[i][j]);
        }
    printf("\n");
    }
}


void wyswietl_mig(int x, int y, char tab[40][40]) {
    int i,j;
    while(x != 0) {

        for(i = 0; i < y; i++) {
            for(j = 0; j < x; j++) {
                printf("%c", tab[i][j]);
            }
        printf("\n");
        }

        Sleep(1000);
        system("cls");

        //zamiana bombek
        for(i = 0; i < y; i++) {
            for(j = 0; j < x; j++) {
                if(tab[i][j] == 'o')
                    tab[i][j] = '*';

                else if(tab[i][j] == '*')
                    tab[i][j] = 'o';
            }
        }
    }
}


void rysuj1(int h, char tab[40][40])
{
    int srodek, w, y, x;
    w = (2*h - 3);
    srodek = w/2;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {


            if(y == h-1) {
                if((x == srodek-1) || (x == srodek+1))
                    tab[y][x] = '|';

                else
                    tab[y][x] = ' ';
                }

            else {
                if(abs(srodek-x) <= y) {
                    tab[y][x] = '^';
                }
                else {
                    tab[y][x] = ' ';
                }
            }


        }
    }
    wyswietl(w, h, tab);

}


void rysuj2(int h, char tab[40][40]) {
    int srodek, ziarno, w, y, x;
    
    w = (2*h - 3);
    srodek = w/2;
    ziarno = time(NULL);
    srand(ziarno);

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {


            if(y == h-1) {
                if((x == srodek-1) || (x == srodek+1))
                    tab[y][x] = '|';

                else
                    tab[y][x] = ' ';
                }

            else {
                if(abs(srodek-x) <= y) {
                    if((rand()%4 == 0) && (y != 0))
                        tab[y][x] = 'o';
                    else
                        tab[y][x] = '^';
                }
                else {
                    tab[y][x] = ' ';
                }
            }


        }
    }
    wyswietl_mig(w, h, tab);
}


void rysuj3(int h, char tab[40][40]) {
    
    int srodek, w , y, x;

    //określe ile segmentów będize miała choinka
    int segmenty;
    if((h-1)/3 >= 4)
        segmenty = 3;
    else
        segmenty = 2;


    if (segmenty == 2 ){
        w = (2*h - 9);
        srodek = w/2;

        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {


                if(y == h-1) {
                    if((x == srodek-1) || (x == srodek+1))
                        tab[y][x] = '|';

                    else
                        tab[y][x] = ' ';
                    }

                else {
                    //górny, mnieujszy segment
                    if(y < (h-1)/2){
                        if(abs(srodek-x) <= y) {
                            tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }
                    else {
                        //dolny, większy, zaczęcie od płaskiego szpicu (y-3)
                        if(abs(srodek-x) <= (y-3)) {
                            tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }
                }

            }
        }
    }


    if (segmenty == 3) {
        w = (2*h - 13);
        srodek = w/2;

        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {


                if(y == h-1) {
                    if((x == srodek-1) || (x == srodek+1))
                        tab[y][x] = '|';

                    else
                        tab[y][x] = ' ';
                    }

                else {
                    //górny, mnieujszy segment
                    if(y < (h-1)/3) {
                        if(abs(srodek-x) <= y) {
                            tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }

                    else if (y < (2*(h-1)/3)) {
                        //dolny, większy, zaczęcie od płaskiego szpicu (y-3)
                        if(abs(srodek-x) <= y-3) {
                            tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }

                    else {
                        if(abs(srodek-x) <= y-6) {
                            tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }
                }

            }
        }
    }
    wyswietl(w, h, tab);

}


void rysuj4(int h, char tab[40][40]) {
    int ziarno, srodek, w , y, x;
    ziarno = time(NULL);
    srand(ziarno);

    //określe ile segmentów będize miała choinka
    int segmenty;
    if((h-1)/3 >= 4)
        segmenty = 3;
    else
        segmenty = 2;


    if (segmenty == 2 ) {
        w = (2*h - 9);
        srodek = w/2;

        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {


                if(y == h-1) {
                    if((x == srodek-1) || (x == srodek+1))
                        tab[y][x] = '|';

                    else
                        tab[y][x] = ' ';
                    }

                else {
                    //górny, mnieujszy segment
                    if(y < (h-1)/2){
                        if(abs(srodek-x) <= y) {
                            if((rand()%4 == 0) && (y != 0))
                                tab[y][x] = 'o';
                            else
                                tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }
                    else {
                        //dolny, większy, zaczęcie od płaskiego szpicu (y-3)
                        if(abs(srodek-x) <= (y-3)) {
                            if((rand()%4 == 0) && (y != 0))
                                tab[y][x] = 'o';
                            else
                                tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }
                }

            }
        }
    }

    if (segmenty == 3) {
        w = (2*h - 13);
        srodek = w/2;


        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {


                if(y == h-1) {
                    if((x == srodek-1) || (x == srodek+1))
                        tab[y][x] = '|';

                    else
                        tab[y][x] = ' ';
                    }

                else {
                    //górny, mnieujszy segment
                    if(y < (h-1)/3) {
                        if(abs(srodek-x) <= y) {
                            if((rand()%4 == 0) && (y != 0))
                                tab[y][x] = 'o';
                            else
                                tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }

                    else if (y < (2*(h-1)/3)) {
                        //dolny, większy, zaczęcie od płaskiego szpicu (y-3)
                        if(abs(srodek-x) <= y-3) {
                            if(rand()%4 == 0)
                                tab[y][x] = 'o';
                            else
                                tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }

                    else {
                        if(abs(srodek-x) <= y-6) {
                            if(rand()%4 == 0)
                                tab[y][x] = 'o';
                            else
                                tab[y][x] = '^';
                        }
                        else {
                            tab[y][x] = ' ';
                        }
                    }
                }

            }
        }
    }
    wyswietl_mig(w, h, tab);

}
