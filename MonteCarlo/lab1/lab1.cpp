#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <ctime>

using namespace std;

// Rozklad Bernouliego

double randNorm() {
// znormalizowany rozkład jednorodny
    return rand() / (double)RAND_MAX;
}


int rozBern(double p) {
// rozklad Bernouliego
    int X = 0;
    double U = randNorm();
        if (U <= p)
            X = 1;
    return X;
}

int main(int argc, char **argv)
{
    srand(time(0));
    double N = pow(10,7);
    double p = 0.9;
    double k = 2;
    double limit = pow(10, k);
    int X = 0;
    double sumX = 0; double sumX2 = 0;
    double xMean, xMean2, err_X, var_num, var_teo, err_var;
    
    ofstream myFile("DaneP09.csv");


    for (int i = 0; i <= N; i++) {
        // rozklad Bernouliego
        X = rozBern(p);
        sumX = sumX + X;
        // sumX2 takie samo jak sumX gdyz X^2 = X dla x{0,1}
        sumX2 = sumX;

        if (i == limit) {
            k++;
            limit = pow(10, k);
            xMean = sumX / i;
            xMean2 = sumX2 / i;
            err_X = abs((xMean-p) / p);
            var_num = (xMean2 - xMean*xMean) / i;
            var_teo = (p - p*p) / i;
            err_var = abs((var_num - var_teo) / var_teo);
            
            myFile << i <<"\t" << xMean <<"\t" << var_num <<"\t" << p <<"\t" << var_teo <<"\t" << err_X <<"\t" << err_var <<"\n";

            //printf("\n\nxMean: %lf    xMean2: %lf    err_X: %lf    \n",xMean, xMean2, err_X);
            //printf("var_num: %lf    var_teo: %lf    err_var: %lf\n", var_num, var_teo, err_var);
            
        }
    }
    myFile.close();
    return 0;
}
