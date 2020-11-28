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

void wstawdotab(int wynik[], int rozmiar) {
    // funkcja uzupełnia komórki tabeli w sposób 0...01
    int i;
    for (i = rozmiar; i >= 0; i--) {
        if (i == rozmiar)
            wynik[i] = 1;
        else
            wynik[i] = 0;
    }
}

void rozloz_dane(int wynik[], int rozmiar) {
    /*
     * jezeli w komórce liczba >10, to zostaw część jedności
     * resztę oddaje poprzedniej komórce (taka reszta to zmienna aa)
    */
    int i;
    int aa;
    for (i = rozmiar; i > 0; i--) {
        aa = wynik[i]/10;
        if (wynik[i] > 9) {
            wynik[i] = wynik[i]%10;
            wynik[i-1] = wynik[i-1] + aa;
        }

        else
            wynik[i] = wynik[i];
    }
}

void wyswietl(int wynik[], int rozmiar) {
    int i;
    for (i = 0; i < rozmiar; i++)
        printf("%d", wynik[i]);
}

int main(int argc, char **argv)
{
    int i, liczba, silnia;
    printf("Podaj liczbe z ktorej chcesz policzyc silnie: ");
    scanf("%d", &liczba);

    //deklaracja tabeli i zapełnienie ją 0
    int rozmiar, smallrozmiar;
    printf("Podaj rozmiar (zalecany >= silni): ");
    scanf("%d", &rozmiar);
    smallrozmiar = rozmiar - 1;
    int wynik[rozmiar];
    wstawdotab(wynik, smallrozmiar);

    // obliczanie silni
    for (silnia = liczba; silnia > 1; silnia--) {
        for (i = smallrozmiar; i >= 0; i --) {
            wynik[i] = wynik[i]*silnia;
        }
        rozloz_dane(wynik, smallrozmiar);
    }
    wyswietl(wynik, rozmiar);
    return 0;
}

