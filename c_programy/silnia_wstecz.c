/*
 * silnia_wstecz.c
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

int main(int argc, char **argv)
{
    long long int a, i;
    printf("Podaj liczbe: ");
    scanf("%I64d", &a);
    i = a;
    while (i > 1) {
        printf("%I64d\n", a);
        a = a*(i - 1);
        i = i - 1;
    }
    return 0;
}

