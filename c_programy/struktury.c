/*
 * struktury.c
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
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    struct osoba {
        int wiek;
        int waga;
        double wzrost;
//        char imie[20];
    };


    union u_osoba {
        int u_wiek;
        int u_waga;
        double u_wzrost;
    };



    struct osoba czlowiek_1;
    union u_osoba u_osoba_1;
    printf("rozmiar struktury %d\n", sizeof(czlowiek_1));
    printf("rozmiar unii w pamieci %ld\n", sizeof(u_osoba_1));

/*
    struct osoba czlowiek_1;
    struct osoba czlowiek_2;
    struct osoba tab[10];

    tab[0].wiek = 42;

    czlowiek_1.wiek = 19;
    czlowiek_2.wiek = 33;
    czlowiek_1.waga = 80;
    czlowiek_1.wzrost = 1.88;

    strcpy(czlowiek_1.imie, "Hubert");

    printf("wiek czlowieka 1 to: %d a wiek czlowieka 2 to: %d\n", czlowiek_1.wiek, czlowiek_2.wiek);
    printf("Wikek czlowieka 0 to: %d\n", tab[0].wiek);

    printf("waga:%d wzrost:%.2f imie:%s\n", czlowiek_1.waga, czlowiek_1.wzrost, czlowiek_1.imie);
*/

    return 0;
}

