#include <iostream>
#include <cstdlib>
#include <iterator>
#define M_PI 3.14159265358979323846
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>

using namespace std;



// *****************************
// *    Potrzebne funkjce      *
// *************************** *
double randUni() {
    // znormalizowany rozkład jednorodny
        return rand() / ((double)(RAND_MAX)+1);
    }


double rozNorm(double u, double sigm) {
    // losownanie liczby z rozkladu normalnego
    return sigm * sqrt(-2 * log(randUni())) * cos(2*M_PI*randUni()) + u;
}


struct wynik {
    double value;
    double var;
};


double psi100(double r) { return 2*exp(-1*r); }
double psi200(double r) { return (2-r)*exp(-1*r/2) / sqrt(8); }
double fProb(double a, double c, double r){ return (1 + c*r)*exp(-a*r);}

double eloc(double r, double a, double c){
    // licznik
    double value = -1*(a*a)*c*r*r + (-1*a*a + 4*a*c -2*c)*r + 2*a - 2*c - 2;
    // mianownik
    value = value / (2*c*r*r + 2*r);
    return value;
}






wynik vqmc(double a, double c, double dr, int N){
    wynik calka;
    double moment1, moment2, rnew, pacc = 0;

    // polozenie gnereujemy losowo z rozkladu normalnego mam nadzieje
    double r = rozNorm(0, 1);
    // funkcjaProbna = (1 + c*r)*exp(-a*r);
    for (int i = 0; i < N; i++) {
        moment1 += eloc(r, a, c);
        moment2 = eloc(r, a, c)*eloc(r, a, c);
        rnew = r + dr*(2*randUni() - 1);
        pacc = rnew*rnew*pow(abs(fProb(a, c, rnew)),2) / r*r*pow(abs(fProb(a, c, r)),2);
        if (pacc > 1) {pacc = 1;}
        // sprawdzenie polozenia nowego punktu
        if (randUni() <= pacc ) {r = rnew;}
    }
    // usrednienie momentow
    moment1 = moment1/(double)N;
    moment2 = moment2/(double)N;
    return calka;
}

int main(){
    int N = 1e6;
    int ileCol = (float)((1.2-0.3)/0.02);
    int ileRow = (0.3 + 0.7)/0.02;
    cout << ileCol << "   " << (float)ileRow << endl;
    double a, c = 0;
    double dr = 0.1;
    struct tmpWynik;

    vector<vector<double>> wyniki(ileRow, vector<double>(ileCol));
    vector<vector<double>> wariancje(ileRow, vector<double>(ileCol)); 
    for (int i = 0; i<ileRow; i++) {
        for (int j = 0; j<ileCol; j++) {
            // index i oznacza zmienna a
            // index j oznacza zmienna c
            a = 0.3 + i*0.02;
            c = -0.7 + j*0.02;
            tmpWynik = vqmc(a, c, dr, N);
            wyna
        }
    }
}