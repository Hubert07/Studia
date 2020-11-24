#include <stdio.h>

int main()
{
float a,b;
printf("Podaj a i b");
scanf("%f %f", &a, &b);

// komentarz nie jest uwzgledniany w kompilacji wiec git

printf("\nNasze liczby to %.2f i %.2f",a,b);
printf("\nDodawanie: %.2f + %.2f = %.2f", a,b,a+b);
printf("\nOdjemownaie: %.2f - %.2f = %.2f", a,b,a-b);
printf("\nMnozenie: %.2f * %.2f = %.2f", a,b,a*b);
printf("\nDzilenie: %.2f / %.2f = %.2f\n\n", a,b,a/b);

printf("stare a = %f\n", a);
a=a*b;
printf("Nowe a = %f\n", a);

return 0;
}
