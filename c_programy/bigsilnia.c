/*
 * bigsilnia.c
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

void wstawdotab(int wynik[]) {
    // funkcja uzupełnia komórki tabeli w sposób 0...01
    int i;
    for (i = 24; i >= 0; i--) {
        if (i == 24)
            wynik[i] = 1;
        else
            wynik[i] = 0;
    }
}

void rozloz_dane(int wynik[]) {
    /*
     * jezeli w komórce liczba >10, to zostaw cześć jednosci
     * resztę oddaje poprzedniej komórce (taka reszta to zmienna aa)
    */
    int i;
    int aa;
    for (i = 24; i > 0; i--) {
        aa = wynik[i]/10;
        if (wynik[i] > 9) {
            wynik[i] = wynik[i]%10;
            wynik[i-1] = wynik[i-1] + aa;
        }

        else
            wynik[i] = wynik[i];
    }
}

void wyswietl(int wynik[]) {
    int i;
    for (i = 0; i < 25; i++)
        printf("%d", wynik[i]);
}

int main(int argc, char **argv)
{

    //deklaracja tabeli i zapełnienie ją 0
    int wynik[25];
    wstawdotab(wynik);
    
    int i, liczba, silnia;
    printf("Podaj liczbe z ktorej chcesz policzyc silnie: ");
    scanf("%d", &liczba);

    for (silnia = liczba; silnia > 1; silnia--) {
        for (i = 24; i >= 0; i --) {
            wynik[i] = wynik[i]*silnia;
        }
        rozloz_dane(wynik);
    }
    wyswietl(wynik);
    return 0;
}

