/*
 * cw03.c
 * 
 * generator szachownicy
 * 
 * 
 */


#include <stdio.h>

int main(int argc, char **argv)
{
    int i, j, k, w;
    printf("Podaj liczbe kolumnm i wierszy: ");
    scanf("%d %d", &k, &w);

    for(i = 1; i <= w; i++) {
        for(j = 1; j <= k; j++) {
            printf("%d  ", (i+j)%2);
            }
        printf("\n");
    }
    




    return 0;
}

