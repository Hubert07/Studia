#include <iostream>
#include <cstdlib>
#include <stdio.h>
#define M_PI 3.14159265358979323846
#include <cmath>
#include <fstream>

using namespace std;

// ****** zmien rozmiar takze w funkcji rozklKolowy *****
const int rozmiar = 1000000; 
double Kolo1[2][rozmiar];
double Kolo2[2][rozmiar];


double randNorm() {
    // znormalizowany rozkład jednorodny
    return rand() / ((double)RAND_MAX+1);
}

// ******* zmienic rozmiar parametru-tablicy *******
void rozklKolowy(double tablica[2][rozmiar], double R, double rX, double rY) {
    for (int i = 0; i < rozmiar; i++) {
        double U1 = randNorm(); double U2 = randNorm(); double U3 = randNorm();
        double x; double y;

        // Generowanie puntktow
        // wspolrzedna X
        x = sqrt(-2 * log(1-U1)) * cos(2*M_PI*U2);
        // wspolrzedna Y
        y = sqrt(-2 * log(1-U1)) * sin(2*M_PI*U2);

        /* Rozlozenie punktow na kole
        Gdzie:
            x / sqrt(x*x + y*y) -> znormalizowna wspolrzedna x
            R * sqrt(U3) wspolzynnik odleglosci punktu od srodka okregu
            rX - przesuniecie w osi X
        */
        // wspolrzedna X
        tablica[0][i] = R*sqrt(U3) * x / sqrt(x*x + y*y) + rX;
        // wspolrzedna Y
        tablica[1][i] = R*sqrt(U3) * y / sqrt(x*x + y*y) + rY;


    }
}

bool czyWkole(double x, double y, double R, double rX, double rY) {
    // R - promien rX - pierwsza wspolrzedna srodka kola rY - druga wspolrzedna
    bool odp  = (pow((x-rX),2) + pow((y-rY),2) <= R*R) ?  1 : 0;
    return odp;
}

// ******* zmienic rozmiar parametru-tablicy *******
double powWspol (double koloAlfa[2][rozmiar], double Rbeta, double rBetax, double rBetay, int l_pkt) {
    int zliczenia = 0;
    for (int i = 0; i < l_pkt; i++) {
        // sprawdzenie czy punkt z kola alfa jest w kole beta
        zliczenia += czyWkole(koloAlfa[0][i], koloAlfa[1][i], Rbeta, rBetax, rBetay);
    }
    return (double)zliczenia/l_pkt;
}


int main(int argc, char **argv)
{
    double Ra = 1; double Rb = Ra*sqrt(2);
    double xa = 0.5*Ra + Rb;
    double Ralfa = Rb;
    double rAx = xa; double rAy = 0;
    double rBx = 0; double rBy = 0;
    
    rozklKolowy(Kolo1, Ra, rAx, rAy);
    rozklKolowy(Kolo2, Rb, rBx,rBy);    


    // Zapis danych z MC do pliku
   ofstream plik_dane;
   plik_dane.open("dane_c.csv");

    for (int k = 2; k < 7; k++) {
        int ile = pow(10,k);
        //alfa = A
        //double Sab = powWspol(Kolo1, Rb, rBx, rBy, ile) * M_PI*Ralfa*Ralfa;
        // alfa = B
        double Sab = powWspol(Kolo2, Ra, rAx, rAy, ile) * M_PI*Ralfa*Ralfa;

        double Sab2 = Sab * M_PI * Ralfa*Ralfa;
        double Var = (Sab2 - Sab*Sab) / (double)ile;
        double odchylenie = sqrt(Var);

        cout << "\n******************************************";
        cout << "\nWylicznia dla: "<< ile << " punkotw";
        cout << "\nPowierzchnia wspolna = " << Sab << endl;
        cout << "\nDrugi moment = " << Sab2 << endl;
        cout << "\nWariancja = " << Var << endl;
        cout << "\nOdchylenie standardowe = " << odchylenie << endl;
        cout << "\n******************************************\n";
        if (k < 6) {plik_dane << ile << "," << Sab << "," << odchylenie << "\n";
        } else {
            plik_dane << ile << "," << Sab << "," << odchylenie;
        }
        
    }
    plik_dane.close();


    // zapis wygenerowanych punktów do pliku
    // ofstream kolo1; ofstream kolo2;
    // kolo1.open("pkt_kolo1.csv");
    // kolo2.open("pkt_kolo2.csv");
    // for (int i = 0; i < rozmiar; i++) {
    //     if (i < rozmiar- 1) {
    //         kolo1 << Kolo1[0][i] << "," << Kolo1[1][i] << "\n";
    //         kolo2 << Kolo2[0][i] << "," << Kolo2[1][i] << "\n";
    //     } else {
    //         kolo1 << Kolo1[0][i] << "," << Kolo1[1][i];
    //         kolo2 << Kolo2[0][i] << "," << Kolo2[1][i];
    //     }
        
    // }
    // kolo1.close(); kolo2.close();
}