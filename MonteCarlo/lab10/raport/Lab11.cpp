#include <cmath>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "photon_diffusion.cpp"

using namespace std;

int main() {
    PHOTON_DIFFUSION_2D ob;
    ob.nlayers =3;
    ob.xmax =0.2;
    ob.x_source =0.1;
    ob.dx_source =0.0;
    ob.x_detect =0.15;
    ob.dx_detect =0.01;
    ob.nx =100;
    ob.ny =100;
    ob.rx0 =0.0;
    ob.ry0 =1.0;

// 1 warstwa
    ob.layers_data [1][0]=1.; // absorption
    ob.layers_data [1][1]=10.; // scattering
    ob.layers_data [1][2]=0.02; // width
    ob.layers_data [1][3]=0.75; // g_anizo
    ob.layers_data [1][4]=1.3; // n_refraction
// 2 warstwa
    ob.layers_data [2][0]=1.; // absorption
    ob.layers_data [2][1]=190.; // scattering
    ob.layers_data [2][2]=0.02; // width
    ob.layers_data [2][3]=0.075; // g_anizo
    ob.layers_data [2][4]=1.0; // n_refraction
// 3. warstwa
    ob.layers_data [3][0]=10.; // absorption
    ob.layers_data [3][1]=90.; // scattering
    ob.layers_data [3][2]=0.02; // width
    ob.layers_data [3][3]=0.95; // g_anizo
    ob.layers_data [3][4]=1.0; // n_refraction
    ob.init ();

    int N = 20000;
    ob.write_all_paths =1;
    ob.write_source_detection_paths =1;

    for ( int k =0; k <N ;k ++){
        // cout << "Hello, World!" << endl;
        ob.single_path();
    }


    cout << "Koniec symulacji" << endl;
    return 0;
}
