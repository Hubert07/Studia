/*
 * cw07.c
 * 
 * sprawdzic 2 okregi x1,y1,r1 i x2,y2,r2 sie stykaja i czy wew czy zew
 * wyznaczyc miejsce przecieica lub styku 
 */


#include <stdio.h>
#include <math.h>

void sprawdz(float x1, float y1, float r1, float x2, float y2, float r2) {
    
    double potega = 2;
    double xkw = pow((double)(x1 - x2), potega);
    double ykw = pow((double)(y1 - y2), potega);
    double odleglosckw = xkw + ykw;
    
    double odleglosc = sqrt(odleglosckw);
    
    if(odleglosc > (r1+r2))
        printf("Okregi nie stykaja sie\n");
    else if(odleglosc == (r1+r2))
        printf("Okregi stykaja sie zewnetrznie\n");
    else if(odleglosc == (r1-r2) || odleglosc == (r2-r1))
        printf("Okregi stykaja sie wewnetrznie\n");
    else
        printf("Okregi sie przecinaja\n");
}


void styk(float x1, float y1, float r1, float x2, float y2, float r2) {

    /* (x - x1)^2 + (y - y1)^2 - r1^2 == (x - x2)^2 + (y - y2)^2 - r2^2
    * y = (y-y1)^2 = r^2 - (x- x1)^2 DELTĄ TRZEBA 
    * x = x
    * 
    * x <x1 - r ; x1 + r>  W PRZYSZŁOŚCI ZROBIĆ TAK, ŻEBY WYBIERAŁO OKRĄG O MNIEJSZYM PROMIENIU
    * 
    * 1. wyznaczyć y dla danego x z pętli takie, że (x-x1)^2 + (y-y1)^2 = r1^2
    *   1a. y^2 - 2y1y +[y1^2 -r1^2 + (x-x1)^2] = 0
    * 2. sprawdzić czy podstawiając x i y do wzoru na 2 okrąg wyjdzie ładnie
    * 3. jak tak, to wypisać, jak nie to zwiększyć x o małą wartość 
    */
     
    double ya, yb;
    double x = (x1 + r1);
    double odp;
    int ktorytoraz = 1;
    printf("x = %f\n", x);


    //double prawa = (double)(x2*x2 - x1*x1 + y2*y2 - y1*y1 + r1*r1 - r2*r2);
    // x*(2*x2 - 2*x1) + y*(2*y2 - 2*y1) = prawa;
    // ya yb pierwiastki rownania okregu z zadanym x 
    
    while (x >= x1-r1) {

        // delta równania: y^2 + (-2y1)y + (y1^2 - r1^2 + (x-x1)^2) = 0
        double delta = pow((double)(2*y1),2) - 4*(pow((double)y1,2) - pow((double)r1,2) + pow((double)(x-x1),2));

        //liczenie współrzędnych 2 pkt dla x należącego do dziedziny 1st oktęgu (x,ya),(x,yb)
        ya = (2*y1 + sqrt(delta))/2;
        yb = (2*y1 - sqrt(delta))/2;

        //podstawienie 2 pkt do równania 2 okręgu i spr czy punkty te należą do 2 okregu
        double okrag2a = pow((double)(x-x2),2) + pow((double)(ya-y2),2) - pow((double)r2,2);
        double okrag2b = pow((double)(x-x2),2) + pow((double)(yb-y2),2) - pow((double)r2,2);
        
        // dla pkt styczności
        if(okrag2a == okrag2b) {
            if(round(10000*fabs(okrag2a)) == 0) {
                printf("Okregi przecinaja sie w pkt x = %lf y = %lf\n", x, ya);
            }
        }

        else {
            if(round(10000*fabs(okrag2a)) == 0) {
                // sprawdzanie czy odp się nie powtórzyła
                if(ktorytoraz == 1) {
                    odp = okrag2a;
                    printf("Okregi przecinaja sie w pkt x = %lf y = %lf\n", x, ya);
                    ktorytoraz = 2;
                }
                else if (ktorytoraz == 2) {
                    if(fabs(odp - okrag2a) > 0.0001) {
                        printf("Okregi przecinaja sie w pkt x = %lf y = %lf\n", x, ya);
                    }
                }
            }

            if(round(10000*fabs(okrag2b)) == 0) {
                // sprawdzanie czy odp się nie powtórzyła
                if(ktorytoraz == 1) {
                    odp = okrag2b;
                    printf("Okregi przecinaja sie w pkt x = %lf y = %lf\n", x, yb);
                    //to wyłącza możliwość, żeby obydwa pkt były na tej samej połowie koła (zakładamy, że istnieje górna połowa(okrag2a) i dolna (okrag2b))
                    ktorytoraz = 2;
                }
                else if (ktorytoraz == 2) {
                    if(fabs(odp - okrag2b) > 0.0001) {
                        printf("Okregi przecinaja sie w pkt x = %lf y = %lf\n", x, yb);
                    }
                }
            }
        }
        //sprawdzenie czy okrąg 2 po podstawieniu == 0
        printf("2a=%fl 2b=%fl\n", okrag2a, okrag2b);
        x = x - 0.000001;
    }
}


int main(int argc, char **argv)
{
    float x1, y1, r1;
    float x2, y2, r2;
    int i;
    
    for (i = 1; i < 3; i++) {
        printf("Podaj wspolrzedne srodka %d okregu oraz jego promien: ", i);
            if(i == 1)
                scanf("%f %f %f", &x1, &y1, &r1);
            else
                scanf("%f %f %f", &x2, &y2, &r2);
    }
    sprawdz(x1, y1, r1, x2, y2, r2);
    styk(x1, y1, r1, x2, y2, r2);
    return 0;
}

