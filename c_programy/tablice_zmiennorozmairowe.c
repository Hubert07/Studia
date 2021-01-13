/*
 * tablice_zmiennorozmairowe.c
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
#include <stdlib.h>

int main(int argc, char **argv)
{

/*
int w,k;
int *tab;
int rozmiar_1;

scanf("%d", rozmiar_1);

tab = malloc(rozmiar_1 * sizeof(*tab));  //rozmiar znaków talicy

tab[0] = 512;

printf("wartosc w 0 to: %d", tab[0]);

tab = realloc(tab, rozmiar_2 * sizeof(*tab)); //dynamincznie powiększa rozmiar

free(tab);
*/

int w,k;
int**tab2d;
w=3;
k=6;
int i;

//najpierw 1 wymair potem dodajemy 2
tab2d = malloc(w * sizeof(int*));
for(i = 0; i<w; i++) {
    tab2d[i] = malloc(k * sizeof(int));
}

tab2d[0][0] =678;
printf("wartoscw w 0,0 to: %d\n", tab2d[0][0]);

for(i = 0; i < w; i++) {
    free(tab2d[i]);
}
free(tab2d);
return 0;
}

