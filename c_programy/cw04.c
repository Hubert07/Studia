/*
 * cw04.c
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
 *           WAŻNE
 * gcc cw04.c -o programdomiejsc -lm
 * -lm <- to jest przełącznik dla bibliotek
 */


#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    float a,b,c, delta, x1,x2, pierwiastek;
    printf("Podaj wspolczynniki rownania a,b i c: ");
    scanf("%f %f %f", &a, &b, &c);

    printf("Rownanie ma postac:\n (%1.f)x^2 + (%1.f)x + (%1.f)\n", a,b,c);
    
    delta = b*b - 4*a*c;

    pierwiastek = sqrt(delta);

    if (delta < 0)
        printf("brak miejsc zerwoych");
    if (delta == 0) {
        x1 = (-1 * b)/(2*a);
        x2 = x1;
        printf("Istnieje 1 miejsce zerowse x1=x2 = %2.f", x1);
    }
    if (delta > 0) {
        x1 = ((-1 * b) + pierwiastek)/(2*a);
        x2 = ((-1 * b) - pierwiastek)/(2*a);
        printf("Istnieja 2 miejsca zerowe x1 = %f x2 = %f", x1,x2);
    }
    return 0;
}

