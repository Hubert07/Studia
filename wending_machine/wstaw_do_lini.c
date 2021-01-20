#include <stdio.h>
#include <stdlib.h>


void zamieniloscitems(int linia, float oile);

int ilelin(FILE* plik);


int main(int argc, char **argv)
{
    int odp, ok = 0;

    printf("Co chcesz zrobic?\
    \n1.Kup produkt\
    \n2.Uzupelnij zapasy\
    \n3.Dodaj pieniadze\n");
    scanf("%d", &odp);

    while (ok == 0) {
        switch (odp) {
            case 1:
            ok=1;
            kup();
            break;

            case 2:
            ok=1;
            break;

            case 3:
            ok=1;
            break;

            default :
            printf("Niewlasciwy parametr, prosze wybrac ponownie\n");
            scanf("%d", &odp);
            break;
        }
    }
    return 0;
}


void zamieniloscitems(int linia, float oile) {
    FILE* tmp = fopen("data/datatmp.txt", "a+");
    FILE* fpilosc = fopen("data/ilosc.txt", "r");
    char iloscpath[] = "data/ilosc.txt";
    char tmppath[] = "data/datatmp.txt";
    
    int ktoralinia = 1, ilosc, raz = 1;

    while(getc(fpilosc) != EOF) {
        fseek(fpilosc, -1, SEEK_CUR);
        if(getc(fpilosc) == '\n')
            ktoralinia++;
        if(ktoralinia == linia && raz == 1) {
            fseek(fpilosc, -1, SEEK_CUR);
            switch (linia) {
                case 1:
                    fscanf(fpilosc, "woda %d", &ilosc);
                    fprintf(tmp, "woda %d", (int)(ilosc+oile));
                    raz = 2;
                break;

                case 2:
                    fscanf(fpilosc, "sok %d", &ilosc);
                    fprintf(tmp, "sok %d", (int)(ilosc+oile));
                    raz = 2;
                break;

                case 3:
                    fscanf(fpilosc, "cola %d", &ilosc);
                    fprintf(tmp, "cola %d", (int)(ilosc+oile));
                    raz = 2;
                break;

                case 4:
                    fscanf(fpilosc, "paluszki %d", &ilosc);
                    fprintf(tmp, "paluszki %d", (int)(ilosc+oile));
                    raz = 2;
                break;

                case 5:
                    fscanf(fpilosc, "lizak %d", &ilosc);
                    fprintf(tmp, "lizak %d", (int)(ilosc+oile));
                    raz = 2;
                break;

                default:
                    printf("Nie ma takiego przedmiotu");
                break;
            }
        }
        else {
            fseek(fpilosc, -1, SEEK_CUR);
            putc(getc(fpilosc), tmp);
        }
    }
    fclose(fpilosc);
    fclose(tmp);
    remove(iloscpath);
    rename(tmppath, iloscpath);
    fclose(fpilosc);
}


int ilelin(FILE* plik) {
    int linie = 1;
    while(getc(plik) != EOF) {
        fseek(plik, -1, SEEK_CUR);
        if(getc(plik) == 10) {
            linie = linie + 1;
        }
    }
    return linie;
    fclose(plik);
}
