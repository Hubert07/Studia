/*
 * cw03.c
 * 
 * generator szachownicy
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i, j, k, w;
    int **tab;
    printf("Podaj liczbe kolumnm i wierszy: ");
    scanf("%d %d", &k, &w);

// tworzenie tablicy
    tab = malloc(w * sizeof(int*));
    for (i = 0; i < w; i++) {
        tab[i] = malloc(k * sizeof(int));
    }

// dodawanie 1/0 do pól
    for (i = 0; i<w; i++) {
        for(j = 0; j<k; j++) {
            tab[i][j] = (i+j)%2;
        }
    }

// wyświetlanie talbicy
    for (i = 0; i<w; i++) {
        for(j = 0; j < k; j++) {
            printf("%d  ", tab[i][j]);
        }
        printf("\n");
    }

// czyszczenie pamięci
    for(i = 0; i < w; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;
}

