#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

double wyniki[4][1000000];
double histogramy[4][10] = {0}; 


double randNorm() {
// znormalizowany rozkład jednorodny
    return rand() / (double)RAND_MAX;
}

double funGest(double x) {
    return (0.8)*(1 + x - x*x*x);
}

double funDystr( double x) {
    double wynik = (0.8)*(x + x*x/2 - x*x*x*x/4);
    return wynik;
}

double rozZloz() {
    double g1 = 0.8;
    double U1 = randNorm(); double U2 = randNorm();
    double x = 0;
    if (U1 <= g1) {
        x = U2;
    }
    else {
        x = sqrt(1-sqrt(1-U2));
    }
    return x;
}


void lanMarkow(int row, double delta) {
    int N = 1000000;
    double xNew;
    double pacc;
    
    // najpierw generujemy ciag, a potem modyfikujemy jego elementy
    for (int i = 0; i < N; i++) {
        wyniki[row][i] = randNorm();
    }
    
    for (int i = 0; i < N-1; i++) {
        pacc = ((funGest(wyniki[row][i+1]) / funGest(wyniki[row][i])) < 1) ? (funGest(wyniki[row][i+1]) / funGest(wyniki[row][i])) : 1;
        double U1 = randNorm(); double U2 = randNorm();
        xNew = wyniki[row][i] + (2*U1 - 1)*delta;

        if (xNew <= 1 and xNew >= 0 and U2 <= pacc) {
            wyniki[row][i+1] = xNew;
        } else {
            wyniki[row][i+1] = wyniki[row][i];
        }
    }

}


double metElimin() {
    double U1 = randNorm();
    double G2 = 1.15*randNorm();
    while (G2 > 0.8*(1 + U1 - pow(U1,3))) {
        U1 = randNorm();
        G2 = 1.15*randNorm();
    }
    return U1;
}


void liczHistogram() {
    int n;
    for (int i = 0; i < 1000000; i++) {

        n = 0;
        if (wyniki[n][i] < 0.1) {
            histogramy[n][0]++;}
        else if (wyniki[n][i] < 0.2) {
            histogramy[n][1]++;}
        else if (wyniki[n][i] < 0.3) {
            histogramy[n][2]++;}
        else if (wyniki[n][i] < 0.4) {
            histogramy[n][3]++;}
        else if (wyniki[n][i] < 0.5) {
            histogramy[n][4]++;}
        else if (wyniki[n][i] < 0.6) {
            histogramy[n][5]++;}
        else if (wyniki[n][i] < 0.7) {
            histogramy[n][6]++;}
        else if (wyniki[n][i] < 0.8) {
            histogramy[n][7]++;}
        else if (wyniki[n][i] < 0.9) {
            histogramy[n][8]++;}
        else {
            histogramy[n][9]++;}
   

        n = 1;
        if (wyniki[n][i] < 0.1) {
            histogramy[n][0]++;}
        else if (wyniki[n][i] < 0.2) {
            histogramy[n][1]++;}
        else if (wyniki[n][i] < 0.3) {
            histogramy[n][2]++;}
        else if (wyniki[n][i] < 0.4) {
            histogramy[n][3]++;}
        else if (wyniki[n][i] < 0.5) {
            histogramy[n][4]++;}
        else if (wyniki[n][i] < 0.6) {
            histogramy[n][5]++;}
        else if (wyniki[n][i] < 0.7) {
            histogramy[n][6]++;}
        else if (wyniki[n][i] < 0.8) {
            histogramy[n][7]++;}
        else if (wyniki[n][i] < 0.9) {
            histogramy[n][8]++;}
        else {
            histogramy[n][9]++;}

        n = 2;
        if (wyniki[n][i] < 0.1) {
            histogramy[n][0]++;}
        else if (wyniki[n][i] < 0.2) {
            histogramy[n][1]++;}
        else if (wyniki[n][i] < 0.3) {
            histogramy[n][2]++;}
        else if (wyniki[n][i] < 0.4) {
            histogramy[n][3]++;}
        else if (wyniki[n][i] < 0.5) {
            histogramy[n][4]++;}
        else if (wyniki[n][i] < 0.6) {
            histogramy[n][5]++;}
        else if (wyniki[n][i] < 0.7) {
            histogramy[n][6]++;}
        else if (wyniki[n][i] < 0.8) {
            histogramy[n][7]++;}
        else if (wyniki[n][i] < 0.9) {
            histogramy[n][8]++;}
        else {
            histogramy[n][9]++;}

        n = 3;
        if (wyniki[n][i] < 0.1) {
            histogramy[n][0]++;}
        else if (wyniki[n][i] < 0.2) {
            histogramy[n][1]++;}
        else if (wyniki[n][i] < 0.3) {
            histogramy[n][2]++;}
        else if (wyniki[n][i] < 0.4) {
            histogramy[n][3]++;}
        else if (wyniki[n][i] < 0.5) {
            histogramy[n][4]++;}
        else if (wyniki[n][i] < 0.6) {
            histogramy[n][5]++;}
        else if (wyniki[n][i] < 0.7) {
            histogramy[n][6]++;}
        else if (wyniki[n][i] < 0.8) {
            histogramy[n][7]++;}
        else if (wyniki[n][i] < 0.9) {
            histogramy[n][8]++;}
        else {
            histogramy[n][9]++;}

    }

    //skalowanie
    // for (int i = 0; i < 4; i++){
    //     for (int j = 0; j < 10; j++) {
    //         histogramy[i][j] =  histogramy[i][j]/100000;
    //     }
    // }
}


void zapiszHistogram() {
    ofstream plikHistogram;
    plikHistogram.open("histogramy_data2.csv");

    for (int j = 0; j < 10; j++) {
         plikHistogram << histogramy[0][j] <<  "," << histogramy[1][j] <<  "," << histogramy[2][j] <<  "," << histogramy[3][j] << "\n";
    }
    plikHistogram.close();
}


double chi2(int row) {
    int N = 1000000;
    double chi2 = 0;
    double pi = 0;
    for (int i = 0; i < 10; i++) {
        if (i == 0)
            pi = funDystr(0.1*(i+1));
        else
            pi = funDystr(0.1*(i+1)) - funDystr(0.1*(i));\
        //cout << "\n" << histogramy[row][i] << "    " << 0.1*(i+1) << "    " << N*pi << "\nDEBUG" << endl;
        chi2 = chi2 + (histogramy[row][i] - N*pi) * (histogramy[row][i] - N*pi) / (N*pi);
    }
return chi2;
}


int main(int argc, char **argv)
{
    int n = 1000000;
    
    for (int i = 0; i < n; i++) {
      wyniki[0][i] = rozZloz();
      wyniki[3][i] = metElimin();
    }
    lanMarkow(1, 0.5);
    lanMarkow(2, 0.05);
    liczHistogram();
    //zapiszHistogram();
    for (int j = 0; j < 4; j++) {
        cout << "\nWartosc Chi^2 dla generatora nr: " << j << "\n wynosi: " << chi2(j);
    }
     
    return 0;
}

