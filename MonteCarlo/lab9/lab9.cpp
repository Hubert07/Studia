#include <iostream>
#include <cstdlib>
#include <iterator>
#define M_PI 3.14159265358979323846
#include <cmath>
#include "vector"
#include <functional>
#include <fstream>

using namespace std;


void nadRelaks(){
    int nx,ny; int itmax = 10e4;
    double step = 0.1; double epsilon = 1;
    double w = 1.8; double tol = 10e-6;
    double f_old = 0; double f_new = 0;
    double sigm_ro = (double)nx/10; double ro_max = 1;
    double rr_max; double Vl, Vb, Vt; double czynnik, Ex, Ey;
    Vl = 1; Vt = Vb = -1;
    nx = ny = 30; 

    double V[nx+1][ny+1];
    double ro[nx+1][ny+1];

    // inicjalizacja tablic
    for (int i = 0; i < nx+1; i++) {
        for(int j = 0; j < ny+1; j++) {
            V[i][j] = 0.0;
            rr_max = pow(step*((double)i - (double)nx/2),2) + pow(step*((double)j - (double)ny/2),2);
            ro[i][j] = ro_max*exp(-1*pow(1,2)/(2*sigm_ro*sigm_ro));
        }
    }

    // WarunkiBrzegowe Dirichleta:
    for (int i = 0; i < nx+1; i++) {
        for(int j = 0; j < ny+1; j++) {
            if (i == 0) {
                V[i][j] = Vl*sin(M_PI*j/(double)ny);
            } else if (j == 0) {
                V[i][j] = Vb*sin(M_PI*i/(double)nx);
            } else {
                V[i][j] = Vt*sin(M_PI*i/(double)nx);
            }
        }
    }

    for (int it = 1; it < itmax; it++) {
        for (int i = 1; i < nx; i++) {
        for(int j = 1; j < ny; j++) {
            czynnik = V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]+step*step/epsilon*ro[i][j];
            V[i][j] = (1-w)*V[i][j] + w/4*(czynnik);
        }}

        // WarunkiBrzegowe Neumanna
        for(int j = 0; j < ny; j++) { V[nx][j] = V[nx-1][j]; }

        // Zbieznosc potencjalu
        f_old = f_new;
        f_new = 0;
        for (int i = 1; i < nx; i++) {
        for(int j = 1; j < ny; j++) {
            Ex = (V[i+1][j] - V[i-1][j])/(2*step);
            Ey = (V[i][j+1] - V[i][j-1])/(2*step);
            f_new = f_new + (Ex*Ex + Ey*Ey)/2 - ro[i][j]*V[i][j];
        }}
        if ( abs((f_new-f_old)/f_new) < tol)
            break;
    }

    
    // zapisanie tablicy
    for (int i = 1; i < nx; i++) {
        for(int j = 1; j < ny; j++) {
        }}
}

int main(int argc, char **argv) {
return 0;
}