#include <cmath>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "dsmc_2d.cpp"

using namespace std;

int main () {
    DSMC_2D ob;
    // wczytujemy dane zpliku wejściowego
    ob.read("i.dat"); 
    // automatyczna inicjalizacja położeń i prędkości
    ob.init (); 
    // zapis ustawień początkowych
    ob.write_position_velocity ("rv.dat"); 
    // obliczenia na jednym rdzeniu
    ob.nthreads =1; 
    // cząstki zderzają się
    ob.icol =1; 
    // wykonujemy 20 tysięcy kroków ( tmax - nieznany )
    ob.evolution (0.0, 20000); 
    // zapis histogramu prędkosci do pliku
    ob.hist_velocity_all ("hist2.dat", 5.0, 50); 
    // zapis położeń i prędkości końcowych do pliku
    ob.write_position_velocity (" rv.dat "); 

    cout << "Koniec symulacji" << endl;
    return 0;
}
