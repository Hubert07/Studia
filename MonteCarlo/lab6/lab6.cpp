#include <iostream>
#include <cstdlib>
#define M_PI 3.14159265358979323846
#include <cmath>
#include <fstream>

using namespace std;

const int Nmax = 30; 

struct obszar {
    double x;
    double y;
    double R;
};

struct czastka {
    // polozenie czastki oraz jej aktywnosc
    double x;
    double y;
    bool tet;
};

struct prosta {
    double a;
    double b;
};



double randUni() {
    // znormalizowany rozkład jednorodny
        return rand() / (double)(RAND_MAX+1);
    }



double rozNorm(double u, double sigm) {
    // losownanie liczby z rozkladu normalnego
    return sigm * sqrt(-2 * log(randUni())) * cos(2*M_PI*randUni()) + u;
}



// liczenie odleglosci
double length(double x1, double y1, double x2, double y2) { return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)); }



// liczenie wspolczynnikow prostej
prosta obliczProsta(double x1, double y1, double x2, double y2) {
    prosta fX;
    // liczenie wspolczynnikow funkcji liniowej
    fX.a = y2 - y1 / x2 - x1;
    fX.b = y1 - fX.a * x1;
    return fX;
}



void sym_init(czastka* tab, obszar source) {
    // inicjalziacja czastek
    // na poczatku wszystkie martwe i x,y = x,y zrodla
    for(int i = 0; i < Nmax; i++) {
        tab[i].x = source.x;
        tab[i].y = source.y;
        tab[i].tet = 0;
    } 
}



bool czy_pochlonieta(double x1, double y1, double x2, double y2, obszar absp) {
    bool pochloniecie = 0;
    // sprawdzenie czy prosta laczaca punkt 1 z koncem trasy czastki (pkt 2) nie przecina powierzchni
    // absorbera
    prosta fX = obliczProsta(x1, y1, x2, y2);
    // postac rownania kwadratowego:
    // (1+a^2)x^2 + x( 2a(b-absp.y) - 2absp.x ) + ( absp.x^2 - absp.R^2 + (b+absp.y)^2 ) <= 0
    // wspolczynniki rownania kwdratowego y = ax^2 + bx + c
    double a = 1 + fX.a*fX.a;
    double b = 2*fX.a*(fX.b-absp.y) - 2*absp.x;
    double c = absp.x*absp.x - absp.R*absp.R + (fX.b - absp.y)*(fX.b - absp.y);
    double delta = b*b - 4*a*c;

    // jesli delta nieujemna to sprawdzamy czy pkt przeciecia prostej z pow absorbenta
    // jest w przedziale [x1 x2]
    if (delta >= 0) {
        double x1przec = -1*b - sqrt(delta) / (2*a);
        double x2przec = -1*b + sqrt(delta) / (2*a);
        // w zaleznosci od rozmieszczenia x1 i x2 trzeba zdefiniowac przedzial wartosci
        if (x1 < x2) {
            // sprawdzenie czy x1przec albo x2przec maja wartosci z zakresu [x1 x2]
            // czyli czy pkt  przeciecia prostej z pow absorbenta lezy na drodze czastki
            if ( ((x1 <= x1przec) && (x1przec <= x2)) || ((x1 <= x2przec) && (x2przec <= x2)) ) { pochloniecie = 1; }
        } else {
            if ( ((x2 <= x1przec) && (x1przec <= x1)) || ((x2 <= x2przec) && (x2przec <= x1)) ) { pochloniecie = 1; }
        }
    }
    return pochloniecie;
}



void particle_translation(double& dist, double& x1, double& y1, double& x2, double& y2, czastka& particle, obszar space, obszar absp) {
    double x3, y3;
    if (length(x2,y2, space.x, space.y) > space.R) { // jesli P2 jest poza granicami obsszaru to wykonaj translacje
        /*  1. obliczyc pkt przeciecia z granica obszaru roboczego
            2. sprawdzic czy miedzy tymi punktami czastki nie pochlonie absorbent
            3. przesunanc czastke na granice obszaru (wirtualnie, nie trzeba faktycznie zmieniac tej wartosci)
            4. zmienic wspolrzedne x2 i y2 na takie ktore odbija pozostala czesc wektora pierwotnego
            5. odleglosc miedzy nowym polozeniem
            6. particle_translation() dla nowego punktu */

        // ************** 1 **************
        prosta fX = obliczProsta(x1, y1, x2, y2);
        double a = 1 + fX.a * fX.a;
        double b = 2 * fX.a * (fX.b - space.y) - 2 * space.x;
        double c = space.x * space.x - space.R * space.R +
                (fX.b - space.y) * (fX.b - space.y);

        double x1przec = -1 * b - sqrt(b * b - 4 * a * c) / (2 * a);
        double x2przec = -1 * b + sqrt(b * b - 4 * a * c) / (2 * a);

        // sprawdzenie ktory z obliczonych x znajduje sie na trajekotri lotu czastki
        if (x1 < x2) {
            if ((x1 <= x1przec) && (x1przec <= x2)) { x3 = x1przec; } else { x3 = x2przec; }
        } else {
            if ((x2 <= x1przec) && (x1przec <= x1)) { x3 = x1przec; } else { x3 = x2przec; }
        }

        // obliczenie drugiej wspolrzednej styku trajektorii z obszarem
        y3 = fX.a * x3 + fX.b;

        // ************** 2,3 **************
        if (czy_pochlonieta(x1, y1, x3, y3, absp)) {
        particle.tet = 0;
        cout << "\nczasta umarla ";
        } else { // na trajektorii z P1 do P3 nie zostala pochlonieta wiec ja przesuwamy do pkt p3
        x1 = x3;
        y1 = y3;
        }

        // ************** 4 **************
        // we spolrzednych sferycznych pozostala odleglosc do obicia Rodb = |P3P2|,
        // a kat obrotu to PI+2alfa+fi fi to kat nachylenia wektora do osi X czyli
        // tan^-1(fX.a) alfa to kat miedzy P1P3 a promienniem obszaru roboczego i P3
        // czyli |SP3|
        double p1p3 = length(particle.x, particle.y, x3, y3);
        double p1s = length(particle.x, particle.y, space.x, space.y);

        double alfa = acos(p1p3*p1p3 + space.R*space.R - p1s*p1s) / (2*p1p3*space.R);
        double fi = atan(fX.a);

        x2 = x3 + length(x3, y3, x2, y2) * cos(M_PI + fi + 2 * alfa);
        y2 = y3 + length(x3, y3, x2, y2) * sin(M_PI + fi + 2 * alfa);

        // ************** 5 **************
        dist = length(x1, y1, x2,y2); // to juz po zmianie P1 = P3, a P2 = P2 po odbiciu

    } else { // jak P2 w obszarze to po prostu sprawdz czy nie pochloniete i przenies na p2
        if(!czy_pochlonieta(x1, y1, x2, y2, absp)) {
            dist = 0;
        } else { particle.tet = 0; cout << "\nczasta umarla "; }
     }
}




void symulacja(double D, double tmax, double dt, double source_eff, obszar space, obszar absp, obszar source, czastka* czastki){
    int N = tmax/dt;
    int deltaN = source_eff*dt; 
    double x1, y1, x2, y2, dist;

    // it- iteracja w czasie, przeskok z momentu t_n do t_n+1
    for (int it = 1; it < N; it++) {
        int n = 0; // licznik aktywnych czastek
        int n_new = 0; //licznik nowych czastek dodanych ze zrodla

        for (int i = 0; i < Nmax; i++) {
            if (czastki[i].tet == 0 && n_new < deltaN) { // jak czastka nie zyje ale generator pozwala wytworzyc, to ja tworzymy w zrodle
                czastki[i].x = source.x;
                czastki[i].y = source.y;
                czastki[i].tet = 1;
                n_new++;
            }
            
            if (czastki[i].tet == 1) { // aktywne czastki sie przemieszczaja
                // P1
                x1 = czastki[i].x;
                y1 = czastki[i].y;
                // P2
                x2 = x1 + rozNorm(0, sqrt(2*D*dt));
                y2 = y1 + rozNorm(0, sqrt(2*D*dt));
                dist = length(czastki[i].x, czastki[i].y, x2, y2);

                // czastka wyrusza w podroz do P2 (zmienia sie wartosc P2 jesli jest poza obszarem), sprawdzenie czy nie zostala pochlonieta
                if (length(x2,y2, space.x, space.y) <= space.R) { // sprawdzenie czy P2 jest w obszarze roboczym 
                    if(czy_pochlonieta(x1, y1, x2, y2, absp)) { // sprawdzenie czy zostala pochlonieta
                        czastki[i].tet = 0;
                        cout << "\nczasta umarla ";
                    }
                } else { // P2 poza obszarem, trzeba przesunac na koniec 
                    do {
                        particle_translation(dist, x1, y1, x2, y2, czastki[i], space, absp);
                    }while (dist > 10e-6 && czastki[i].tet == 1);
                }
                
                if (czastki[i].tet == 1) {
                    czastki[i].x = x2;
                    czastki[i].y = y2;
                    n++; // czastka nie zostala pochlonieta
                }
            }

        }
        if (it%3 == 0) {
            cout << "\nchwila: " << it << " n: " << n << " n_new: " << n_new << endl;
            cout << czastki[5].x << "\t" << czastki[5].y << "\t" << czastki[5].tet << "\n";
        }
    }
}



int main(int argc, char **argv){
    // inicjalizacja obszaru
    obszar space;
    space.x = 0;
    space.y = 0;
    space.R = 1000;

    // inicjalizacja absorbera
    obszar absp;
    absp.x = -10000;
    absp.y = -10000;
    absp.R = 0;
    
    // inicjalizacja zrodla
    obszar source;
    source.x = 0;
    source.y = 0;

    // parametry symulacji
    // Nmax w lini 10
    double tmax = 10; double dt = 0.1;
    double D = 1; double source_eff = 10;

    // utworzenie tablicy czastek i inicjalizacja
    czastka czastki[Nmax];
    sym_init(czastki, source);
    //cout << czastki[5].x << "\t" << czastki[5].y << "\t" << czastki[5].tet << "\n\n";
    symulacja(D, tmax, dt, source_eff, space, absp, source, czastki);
    //cout << czastki[5].x << "\t" << czastki[5].y << "\t" << czastki[5].tet << "\n\n";

}