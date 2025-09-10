#include <iostream>
#include <cstdlib>
#define M_PI 3.14159265358979323846
#include <cmath>
#include <fstream>

using namespace std;

// tablica punktow [X1;Y1][X2;Y2]...
double punkty[2][10000];


void wyplujdane(int nr){
    // dodawanie danych
    ofstream myfile;
    switch (nr)
    {
    case 1:
    myfile.open ("dane1.csv");
        break;

    case 2:
    myfile.open ("dane2.csv");
        break;

    case 3:
        myfile.open ("dane4.csv");
            break;
    
    default:
        break;
    }

    for (int i = 0; i < 10000; i++) {
        myfile << punkty[0][i] <<",";
    }

    myfile << "\n";

    for (int i = 0; i < 10000; i++) {
        myfile << punkty[1][i] << ",";
    }
    myfile.close();
}

double randNorm() {
    // znormalizowany rozkład jednorodny
        return rand() / (double)(RAND_MAX+1);
    }

void rozklBM() {
    for (int i = 0; i < 10000; i++) {
        double U1 = randNorm(); double U2 = randNorm();
        // wspolrzedna X
        punkty[0][i] = sqrt(-2 * log(1-U1)) * cos(2*M_PI*U2);
        // wspolrzedna Y
        punkty[1][i] = sqrt(-2 * log(1-U1)) * sin(2*M_PI*U2);
    }

    wyplujdane(4);
}

void rozklSferKontur() {
    for (int i = 0; i < 10000; i++) {
        double U1 = randNorm(); // double U2 = randNorm();
        double R =sqrt(U1);

        double xy = sqrt(punkty[0][i]*punkty[0][i] + punkty[1][i]*punkty[1][i]);
        // wspolrzedna X''
        punkty[0][i] = R * punkty[0][i] / xy;

        // wspolrzedna Y''
        punkty[1][i] = R * punkty[1][i] / xy;

    }

    wyplujdane(4);
}

void rozklAfin() {
    // INDEKSOWANIE WARTOSCI OD 0
    double alfa = 3.14159/4;
    double b1 = 1; double b2 = 0.2;
    double Ralfa[2][2] = {cos(alfa), -sin(alfa), sin(alfa), cos(alfa)};

    //cout << " " << Ralfa[0][0] << "\t" << Ralfa[0][1] << "\n";
    //cout << " " << Ralfa[1][0] << "\t" << Ralfa[1][1] << "\n";

    double r1[2][1] = {b1*Ralfa[0][0], b1*Ralfa[1][0]};
    double r2[2][1] = {b2*Ralfa[0][1], b2*Ralfa[1][1]};

    // przeobrazenie kuli w elipse
    for (int i = 0; i < 10000; i++) {
        double x = punkty[0][i];
        double y = punkty[1][i];

        // wspolrzedna X
        punkty[0][i] = r1[0][0]*x + r2[0][0]*y;
        // wspolrzedna Y
        punkty[1][i] = r1[1][0]*x + r2[1][0]*y;
    }

    wyplujdane(4);

    // macierz kowariancji i jej skladniki (gnuplot)
    double x_mean = 0; double x_mean2= 0;
    double y_mean = 0; double y_mean2 = 0;
    double xy_mean = 0;
    double sigm_x = 0; double sigm_y = 0; double sigm_xy = 0;
    double n = 10000;

    for (int i = 0; i < 10000; i++) {
        x_mean = x_mean + punkty[0][i];
        x_mean2 = x_mean2 + punkty[0][i]*punkty[0][i];

        y_mean = y_mean + punkty[1][i];
        y_mean2 = y_mean2 + punkty[1][i]*punkty[1][i];

        xy_mean = xy_mean + punkty[0][i]*punkty[1][i];
    }
    x_mean = x_mean / n; x_mean2 = x_mean2 / n;
    y_mean = y_mean / n; y_mean2 = y_mean2 / n;
    xy_mean = xy_mean / n;


    sigm_x = x_mean2 - x_mean*x_mean;
    sigm_y = y_mean2 - y_mean*y_mean;
    sigm_xy = xy_mean - x_mean*y_mean;

    double r_xy = sigm_xy / sqrt(sigm_x*sigm_y);

    // wypisanie macierzy kowariancji
    cout << "|" << sigm_x << "          " << sigm_xy << "|" << "\n";
    cout << "|" << sigm_xy << "          " << sigm_y << "|" << "\n";
    //cout << sigm_xy << "     " << sigm_y << "\n";
    cout << "r_xy = " << r_xy << "\n";
}

int main(int argc, char **argv)
{
    rozklBM();
    //rozklSferKontur();
    rozklAfin();
    return 0;
}
