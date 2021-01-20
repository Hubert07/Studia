#include <stdio.h>
#include <stdlib.h>


void display(FILE* plik);
void dodajpieniadze(int oile, int ktora);
void dodajprzedmioty(int oile, int ktora);
void zwroc(float reszta);
void kup(float nominal, float cena);
void kupmenu(int nr);
void uzupelnijzapasy();
void help();



int main(int argc, char **argv)
{
    FILE* fhelp = fopen("data/help.txt", "r");
    FILE* fitems = fopen("data/items.txt", "r");
    FILE* fnominaly = fopen("data/nominaly.txt", "r");
    int nr, ile, odp, ok = 0;

    printf("Co chcesz zrobic?\
    \n1.Kup produkt\
    \n2.Uzupelnij zapasy\
    \n3.Dodaj pieniadze\
    \n4.Pomoc\n");
    scanf("%d", &odp);

    while (ok == 0) {
        switch (odp) {
            case 1:
            ok=1;
            system("cls");
            display(fitems);
            printf("\nPodaj nr produktu ktory chcesz kupic: ");
            scanf("%d", &nr);
            kupmenu(nr);
            break;

            case 2:
            ok=1;
            system("cls");
            display(fitems);
            printf("\nPodaj nr produktu ktory chcesz uzuplenic: ");
            scanf("%d", &nr);
            printf("\nPodaj ilosc jaka chcesz dodac: ");
            scanf("%d", &ile);
            dodajprzedmioty(ile, nr);
            break;

            case 3:
            ok=1;
            system("cls");
            display(fnominaly);
            printf("\nPodaj nr banknotu/monety ktory chcesz uzuplenic: ");
            scanf("%d", &nr);
            printf("\nPodaj ilosc jaka chcesz dodac: ");
            scanf("%d", &ile);
            dodajpieniadze(ile, nr);
            break;

            case 4:
            ok=1;
            system("cls");
            display(fhelp);
            break;

            default :
            printf("Niewlasciwy parametr, prosze wybrac ponownie\n");
            scanf("%d", &odp);
            break;
        }
    }
    return 0;
}


void display(FILE* plik)
{
    int x;
    int znak = 0;
    char *tab;

    while(getc(plik) != EOF) {
        znak++;
    }
    rewind(plik);
    tab = malloc(znak * sizeof(char));
    for(x = 0; x < znak; x++) {
        tab[x] = getc(plik);
    }
    fclose(plik);
    printf("%s", tab);
    free(tab);
}


void dodajpieniadze(int oile, int ktora)
{
    FILE* plik = fopen("data/money.txt", "a+");
    FILE* tmp = fopen("data/tmp.txt", "a+");
    char adres[] = "data/money.txt";
    char tmpadres[] = "data/tmp.txt";
    int il1;
    int il2;
    int il3;
    int il4;
    int il5;
    int il6;
    int il7;
    int il8;
    int il9;
    int il10;
    fscanf(plik, "%d %d %d %d %d %d %d %d %d %d", &il1, &il2, &il3, &il4, &il5, &il6, &il7, &il8, &il9, &il10);
    switch(ktora)
    {
        case 1:
            il1 += oile;
        break;

        case 2:
            il2 += oile;
        break;

        case 3:
            il3 += oile;
        break;

        case 4:
            il4 += oile;
        break;

        case 5:
            il5 += oile;
        break;

        case 6:
            il6 += oile;
        break;

        case 7:
            il7 += oile;
        break;

        case 8:
            il8 += oile;
        break;

        case 9:
            il9 += oile;
        break;

        case 10:
            il10 += oile;
        break;
    }
    fclose(plik);
    remove(adres);
    fprintf(tmp, "%d %d %d %d %d %d %d %d %d %d", il1, il2, il3, il4, il5, il6, il7, il8, il9, il10);
    fclose(tmp);
    rename(tmpadres, adres);
}


void dodajprzedmioty(int oile, int ktora)
{
    FILE* plik = fopen("data/ilosc.txt", "a+");
    FILE* tmp = fopen("data/tmpilosc.txt", "a+");
    char adres[] = "data/ilosc.txt";
    char adrestmp[] = "data/tmpilosc.txt";
    int il1;
    int il2;
    int il3;
    int il4;
    int il5;
    fscanf(plik, "%d %d %d %d %d", &il1, &il2, &il3, &il4, &il5);
    switch(ktora)
    {
        case 1:
            il1 += oile;
        break;

        case 2:
            il2 += oile;
        break;

        case 3:
            il3 += oile;
        break;

        case 4:
            il4 += oile;
        break;

        case 5:
            il5 += oile;
        break;
    }
    fclose(plik);
    remove(adres);
    fprintf(tmp, "%d %d %d %d %d", il1, il2, il3, il4, il5);
    fclose(tmp);
    rename(adrestmp, adres);
}


void zwroc(float reszta)
{
    FILE* plik = fopen("data/money.txt", "a+");
    int ile;
    int il1;
    int il2;
    int il3;
    int il4;
    int il5;
    int il6;
    int il7;
    int il8;
    int il9;
    int il10;
    fscanf(plik, "%d %d %d %d %d %d %d %d %d %d", &il1, &il2, &il3, &il4, &il5, &il6, &il7, &il8, &il9, &il10);
    fclose(plik);

    if(reszta >= 100 && il1 > 0) {
        ile = reszta/100;
        reszta = reszta - (ile*100);
        printf("Wydano Ci %d banknoty 100zl\n", ile);
        dodajpieniadze(((-1)*ile), 1);
        zwroc(reszta);
    }
    else if (reszta >= 50 && il2 > 0) {
        ile = reszta/50;
        reszta = reszta - (ile*50);
        printf("Wydano Ci %d banknoty 50zl\n", ile);
        dodajpieniadze(((-1)*ile), 2);
        zwroc(reszta);
    }
    else if (reszta >= 20 && il3 > 0) {
        ile = reszta/20;
        reszta = reszta - (ile*20);
        printf("Wydano Ci %d banknoty 20zl\n", ile);
        dodajpieniadze(((-1)*ile), 3);
        zwroc(reszta);
    }
    else if (reszta >= 10 && il4 > 0) {
        ile = reszta/10;
        reszta = reszta - (ile*10);
        printf("Wydano Ci %d banknoty 10zl\n", ile);
        dodajpieniadze(((-1)*ile), 4);
        zwroc(reszta);
    }
    else if (reszta >= 5 && il5 > 0) {
        ile = reszta/5;
        reszta = reszta - (ile*5);
        printf("Wydano Ci %d monety 5zl\n", ile);
        dodajpieniadze(((-1)*ile), 5);
        zwroc(reszta);
    }
    else if (reszta >= 2 && il6 > 0) {
        ile = reszta/2;
        reszta = reszta - (ile*2);
        printf("Wydano Ci %d monety 2zl\n", ile);
        dodajpieniadze(((-1)*ile), 6);
        zwroc(reszta);
    }
    else if (reszta >= 1 && il7 > 0) {
        ile = reszta/1;
        reszta = reszta - (ile*1);
        printf("Wydano Ci %d monety 1zl\n", ile);
        dodajpieniadze(((-1)*ile), 7);
        zwroc(reszta);
    }
    else if (reszta >= 0.5f && il8 > 0) {
        ile = reszta/(0.5);
        reszta = reszta - (ile*0.5);
        printf("Wydano Ci %d monety 50gr\n", ile);
        dodajpieniadze(((-1)*ile), 8);
        zwroc(reszta);
    }
    else if (reszta >= 0.2f && il9 > 0) {
        ile = reszta/0.2;
        reszta = reszta - (ile*0.2);
        printf("Wydano Ci %d monety 20gr\n", ile);
        dodajpieniadze(((-1)*ile), 9);
        zwroc(reszta);
    }
    else if (reszta > 0 && il10 > 0){
        ile = reszta/0.1;
        printf("Wydano Ci %d monety 10gr\n", ile);
        dodajpieniadze(((-1)*ile), 10);
        printf("Dzikeujemy za skorzystanie\n");
    }
}


void kup(float nominal, float cena)
{
    float reszta = 0, brak;
    while(cena - reszta > 0) {
        brak = (cena - reszta);
        printf("\nBrakuje %.2f\n", brak);
        printf("Podaj nominal: ");
        scanf("%f", &nominal);
        reszta = reszta + nominal;
        if(nominal == 100)
            dodajpieniadze(1, 1);
        else if(nominal == 50)
            dodajpieniadze(1, 2);
        else if(nominal == 20)
            dodajpieniadze(1, 3);
        else if(nominal == 10)
            dodajpieniadze(1, 4);
        else if(nominal == 5)
            dodajpieniadze(1, 5);
        else if(nominal == 2)
            dodajpieniadze(1, 6);
        else if(nominal == 1)
            dodajpieniadze(1, 7);
        else if(nominal == 0.50f)
            dodajpieniadze(1, 8);
        else if(nominal == 0.20f)
            dodajpieniadze(1, 9);
        else if(nominal == 0.10f)
            dodajpieniadze(1, 10);
        else
            printf("Niepoprawny nominal");
    }
    reszta = reszta - cena;
    printf("Twoja reszta to: %.2f\n", reszta);
    zwroc(reszta);
}


void kupmenu(int nr)
{
    float cena;
    switch (nr)
    {
        case 1:
            cena = 1.00;
            printf("Woda kosztuje %.2f\n", cena);
            kup(0, cena);
            dodajprzedmioty(-1, 1);
        break;

        case 2:
            cena = 2.50;
            printf("Sok kosztuje %.2f", cena);
            kup(0, cena);
            dodajprzedmioty(-1, 2);
        break;

        case 3:
            cena = 5.50;
            printf("Cola kosztuje 5.50");
            kup(0, cena);
            dodajprzedmioty(-1, 3);
        break;

        case 4:
            cena = 3.20;
            printf("Paluszki kosztuja 3.20");
            kup(0, cena);
            dodajprzedmioty(-1, 4);
        break;

        case 5:
            cena = 0.60;
            printf("Lizak kosztuje 0.60");
            kup(0, cena);
            dodajprzedmioty(-1, 5);
        break;

        default:
            printf("Nie ma takiego produktu");
        break;
    }
}
