#include<cmath>
#include<vector>
#include<stdlib.h>
#include "photon_diffusion.cpp"

// Suma  wag Absorbcji Transmitancji i Reflection / N = 1
using namespace std;

int main(int argc, char **argv) {
    int nlayers = 3;
    

    PHOTON_DIFFUSION_2D symulacja;
    symulacja.nlayers = 3;
    symulacja.xmax = 0.2; //symulacja.ymax = 0.2;
    symulacja.nx = symulacja.ny = 100;
    symulacja.x_source = 0.1;
    symulacja.dx_source = 0.0; symulacja.x_detect = 0.15;
    symulacja.dx_detect = 0.01;
    symulacja.rx0 = 0.8; symulacja.ry0 = 0.6;


    symulacja.layers_data[1][0] = 1;
    symulacja.layers_data[1][1] = 10;
    symulacja.layers_data[1][2] = 0.02;
    symulacja.layers_data[1][3] = 0.75;
    symulacja.layers_data[1][4] = 1.3;

    symulacja.layers_data[2][0] = 1;
    symulacja.layers_data[2][1] = 190;
    symulacja.layers_data[2][2] = 0.02;
    symulacja.layers_data[2][3] = 0.075;
    symulacja.layers_data[2][4] = 1.5;

    symulacja.layers_data[3][0] = 10;
    symulacja.layers_data[3][1] = 90;
    symulacja.layers_data[3][2] = 0.02;
    symulacja.layers_data[3][3] = 0.95;
    symulacja.layers_data[3][4] = 1.0;


    symulacja.write_all_paths = 1;

    symulacja.init();
    int N = 1;

    vector<vector<double>> sumaA;
    sumaA.resize(symulacja.nx+1,vector<double>(symulacja.ny+1,0));

    for (int i = 0; i < N; i++){
        symulacja.single_path();
        // z tablic z Absorbcja zsumowac wartosci wspolczynnikow tak samo z Transmisja i Odbiciem
        // sprawdzic czy suma wag / N  = +/-1
        for (int i = 0; i < symulacja.nx+1; i ++) {
            for (int j = 0; j < symulacja.ny+1; j ++) {
                sumaA[i][j] += symulacja.absorption[i][j];
        }
    }
    }

    return 0;
}