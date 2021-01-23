/*
 * montecarlo.c
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
#include <math.h>

int main(int argc, char **argv)
{
    double tab[10000][2];
    double x, y;
    double dziesietna, setna, tysiac;
    int i, j, seed;
    double wkole = 0, poza = 0, wynik;
    double kolo;

    seed = time(NULL);
    srand(seed);
    
    for(i = 0; i < 10000; i++) {
        for (j = 0; j < 2; j++) {
            dziesietna = rand()%10;
            setna = rand()%10;
            tysiac = rand()%10;

            tab[i][j] = (dziesietna/10 + setna/100 + tysiac/1000);
            //printf("%lf\n", tab[i][j]);
        }
    }

    for(i = 0; i < 10000; i++) {
        x = tab[i][0];
        y = tab[i][1];
        kolo = pow((x-0.5), 2) + pow((y-0.5), 2);
        if(kolo <= 0.25f) {
            wkole++;
        }
        else
            poza++;
    }
    
    wynik = wkole/poza;
    printf("Liczba pi wynosi ok: %.4f", (4*wynik)/(1+wynik));

    return 0;
}

