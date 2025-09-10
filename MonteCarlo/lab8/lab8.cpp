#include <iostream>
#include <cstdlib>
#include <iterator>
#define M_PI 3.14159265358979323846
#include <cmath>
#include "vector"
#include <functional>
#include <fstream>

using namespace std;

const int n = 12;

struct atom {
    //double phi;
    //double tet;
    double x; //= r*sin(tet)*cos(phi);
    double y; //= r*sin(tet)*sin(phi);
    double z; //= r*cos(tet);
    double r = sqrt(x*x + y*y + z*z);
    double phi = atan(y/x);
    double tet = acos(z/r);
};



double dist(atom atom1, atom atom2) {
    return sqrt(pow((atom1.x-atom2.x),2) + pow(atom1.y-atom2.y,2) + pow(atom1.z-atom2.z,2));
}



vector<double> makePCF(atom *atomy, int M) {
    // funkcja korelacji pari M - ilosc podprzedzialow w histogramie
    vector<double> pcf;
    // inicjalizacja wektora
    for(int i = 0; i < M; i++) {
        pcf.at(i) = 0;
    }

    double r_sr = 0;
    for(int i = 0; i < n; i++) {
        r_sr += atomy[i].r / n;
    }
    double r_max = 2.5*r_sr;
    double dr = r_max/(double)M;

    for(int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            double r = dist(atomy[j], atomy[i]);
            int m = floor(r/dr);
            if (m < M)
                pcf[m] += 8*M_PI*r*r / ((double)n*(double)n*2*M_PI*r*dr);
        }
    }
    return pcf;
}



double fcut(atom* atomy, int i, int j, double r1, double r2) {
    double wartosc = 0;
    double r = dist(atomy[i], atomy[j]);
    if (r <= r1) {
        wartosc = 1;
    } else if (r <= r2) {
        wartosc = 0.5;
    }
    return wartosc;
}



double dzeta(int i, int j, atom* atomy){
    double a0 = 0.011304; double c0 = 19; double d0 = 2.5;
    double r1 = 1.70; double r2 = 2.00;
    double value = 0;
    atom rik, rij;

    for (int k = 0; k < n; k++) {
        if (k!= i && k !=j) {
            rij.x = atomy[j].x - atomy[i].x;
            rij.y = atomy[j].y - atomy[i].y;
            rij.z = atomy[j].z - atomy[i].z;

            rik.x = atomy[k].x - atomy[i].x;
            rik.y = atomy[k].y - atomy[i].y;
            rik.z = atomy[k].z - atomy[i].z;

            double cosTet = 
            value += fcut(atomy, i, k, r1, r2)*1;
        }
    }
    
}



double potencjalBren(atom* atomy, int size, int index){
    // parametry
    double r0 = 1.315; double r1 = 1.70; double r2 = 2.00;
    double de = 6.325; double s = 1.29;
    double lam = 1.5; double dlt = 0.80469;
    
    double V = 0;

    // potencjal atomu o indexie = index z najblizszymi sasiadami 
    for(int j = 0; j < size; j++) {
        if (j != index) {
            double r = dist(atomy[index], atomy[j]);
            // potemcjal odpychania
            double Vr = de/(s-1) * exp(-1*sqrt(2*s)*lam*(r-r0));
            // energia przyciagania
            double Va = de*s/(s-1) * exp(-1*sqrt(2/s)*lam*(r-r0));
            double skalB = (pow(1+dzeta(index,j, atomy),-1*dlt) + pow(1+dzeta(j,index, atomy),-1*dlt) ) / 2;

            V += fcut(atomy, index, j, r1, r2)*(Vr-skalB*Va);
        }
    }
    return V;
}



atom przesuniecie(atom* atomy) {
    double u1,u2,u3;
    return *atomy;
}



int main(int argc, char **argv){
    atom atomy[12] = {};
    potencjalBren(atomy,n,0);

return 0;
}