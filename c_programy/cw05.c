/*
 * cw05.c
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

int main(int argc, char **argv)
{
    int tablica[10], i, zarodek;
    
    zarodek = time(NULL);
    srand(zarodek);
    int max = 0;
    
    for (i=0; i<10; i++) {
        tablica[i] = rand()%1000;
        printf("liczba pseudoloswa w %d komorce %d\n", i,tablica[i]);
        if (tablica[i] > max)
            max = tablica[i];
    }
    printf("Najwieksza wygenerowana wartosc to %d", max);
    return 0;
}

