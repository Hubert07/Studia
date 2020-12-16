/*
 * funkcje.c
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

float dodawanie(float a, float b);
void menu(void);
int silnia(int n);

int main(int argc, char **argv)
{
    menu();

    printf("wynik dodawania %f\n", dodawanie(10, 5));

    menu();
    return 0;
}

float dodawanie(float a, float b) {
    return(a+b);
}

void menu(void) {
    printf("Oto menu\n");
    printf("1 - opcja 1\n");
    printf("2 - opcja 2\n");
    printf("0 - wyjscie\n");
}

int silnia(int n) {
    if (n == 0)
        returtn 1;
    return n*silnia(n-1);
}
