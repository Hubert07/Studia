/*
 * wsjazniki.c
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

int main(int argc, char **argv)
{

int a,b,c;
char d,e,f;
int tab[]={95,2,34,5,-1,6};

int *adres_zmiennej;
int *adres_tablicy;

adres_tablicy = &tab[0]; // adres_tablicy = tab;

/*
printf("Wartosc tablicy w 0 = %d\n", tab[0]);
printf("Wartosc tablicy w 0 = %d\n\n", *adres_tablicy);

printf("Wartosc tablicy w 0 = %d\n", *adres_tablicy);
printf("Wartosc tablicy w 0 = %d\n", *++adres_tablicy);
printf("Wartosc tablicy w 0 = %d\n", *++adres_tablicy);
printf("Wartosc tablicy w 0 = %d\n", *++adres_tablicy);
*/

int i;
for (i=0; i < 6; i++) {
    printf("wartosc talbicy w %d: %d\n", i, *adres_tablicy++);
}


/*
a = 12;

adres_zmiennej = &a;

printf("klasyczny: Wartosc a = %d\n", a);
printf("wskaznik: Wartosc a = %d\n", *adres_zmiennej);

*adres_zmiennej=77;

printf("klasyczny: Wartosc a = %d\n", a);
printf("wskaznik: Wartosc a = %d\n\n\n\n\n\n", *adres_zmiennej);


//printf("adres zmiennej a to: %p\n", &a);
//printf("adres zmiennej a to: %p\n", adres_zmiennej);
printf("adres zmiennej a to: %p\n", &a);
printf("adres zmiennej b to: %p\n", &b);
printf("adres zmiennej c to: %p\n", &c);

printf("adres zmiennej d to: %p\n", &d);
printf("adres zmiennej e to: %p\n", &e);
printf("adres zmiennej f to: %p\n", &f);
*/

return 0;
}

