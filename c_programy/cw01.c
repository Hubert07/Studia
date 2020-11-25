#include <stdio.h>

int main()
{
float a,b;
char znak, koniec;
printf("podaj pierwsza liczba: ");
scanf("%f", &a);
printf("podaj znak: ");
scanf(" %c", &znak);
printf("podaj druga liczba: ");
scanf("%f", &b);

do {

switch(znak)
{
    case '+':
    printf("\nDodawanie: %.2f + %.2f = %.2f", a,b,a+b);
    break;

    case '-':
    printf("\nOdjemownaie: %.2f - %.2f = %.2f", a,b,a-b);
    break;
    
    case '*':
    printf("\nMnozenie: %.2f * %.2f = %.2f", a,b,a*b);
    break;
    
    case '/':
    printf("\nDzilenie: %.2f / %.2f = %.2f\n\n", a,b,a/b);
    break;
    
//    case '%':
//    printf("\nDzilenie modulo: %f % %f = %d\n\n", a,b,(int)a%(int)b;
//    break;

    default :
    printf("Niewlasicwy znak");
    break;

}

printf("\nKonczymy? t/n");
scanf("%c", &koniec);

}while(koniec=='n');

return 0;
}
