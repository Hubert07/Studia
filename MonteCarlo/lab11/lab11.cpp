# include "dsmc_2d.cpp"

using namespace std;

int main(){
    DSMC_2D ob;

    ob.read("start_param_r1.dat"); // wczytujemy dane zpliku wejściowego
    ob.init(); // automatyczna inicjalizacja położeń i prędkości
    ob.write_position_velocity("rv.dat"); //zapis ustawień początkowych
    ob.nthreads = 1; //obliczenia na jednym rdzeniu
    ob.icol=1; //cząstki zderzają się
    ob.evolution(0.0 ,20000); // wykonujemy 20 tysięcy kroków (tmax - nieznany)
    ob.hist_velocity_all("hist2.dat" ,5.0 ,50); //zapis histogramu prędkosci do pliku
    ob.write_position_velocity("rv.dat"); //zapis położeń i prędkości końcowych do pliku
    cout << "zrobilo sie";    // zakomentowalem linie 259 i ta linijka wskazuje ze sie program skonczyl robic
    return 0;
}
