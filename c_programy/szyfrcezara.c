/*
 * szyfrcezara.c
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
    char zdanie[]="ALA MA KOTA";
    int i, klucz, j;

    printf("Podaj klucz: ");
    scanf("%d", &klucz);
    
    for(i = 0; i < 11; i++){
        if(zdanie[i] > 96) {
            if(zdanie[i]+klucz > 122) {
                zdanie[i] = zdanie[i]+klucz-26;
            }
            else {
                zdanie[i] = zdanie[i]+klucz;
            }
        }

        else if (zdanie[i] > 64) {
            if(zdanie[i]+klucz > 90) {
                zdanie[i] = zdanie[i]+klucz-26;
            }
    
            else
                zdanie[i] = zdanie[i]+klucz;
        }
        else
            continue;
    }
    
    for(j = 0; j <11; j++) {
        printf("%c", zdanie[j]);
        }
    return 0;
}

