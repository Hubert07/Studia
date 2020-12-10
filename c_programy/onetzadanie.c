/*
 * onetzadanie.c
 * 
 * Copyright 2020 Hubert <Hubert@DESKTOP-27EU2EG>
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
#include <stdlib.h>
#include <time.h>


void sprawdz(int tablica[10][15])
{
    int i,j;

    for(i =0; i < 10; i++) {
        for(j=0; j < 15; j++) {

        // deklaracja lcizb wokół sprawdzanej
        int poziom1 = tablica[i][j-1];
        int poziom2 = tablica[i][j+1];
        int pion1 = tablica[i-1][j];
        int pion2 = tablica[i+1][j];


        if(j-1 < 0)
            poziom1 = tablica[i][14];
        if(j+1 > 14)
            poziom2 = tablica[i][0];

        if(i-1 < 0)
            pion1 = tablica[9][j];
        if(i+1 > 9)
            pion2 = tablica[0][j];


        if(((pion1+pion2) > tablica[i][j] && (poziom1 + poziom2) < tablica[i][j]) || ((pion1+pion2) < tablica[i][j] && (poziom1 + poziom2) > tablica[i][j])) {
            printf("wiersz: %d kolumna :%d\n", i,j);
        }


        }

    }
}


int main(int argc, char **argv)
{
    int tablica[10][15], i,j, zarodek;
    
    zarodek = time(NULL);
    srand(zarodek);

    
    for(i = 0; i < 10; i++){
        for (j = 0; j< 15; j++) {
            tablica[i][j] = rand()%100;
            printf("%d\t", tablica[i][j]);
        }
        printf("\n");
    }
    
    sprawdz(tablica);
    return 0;
}
