#include <iostream>
#include <cstdlib>
#define M_PI 3.14159265358979323846
#include <cmath>
#include <functional>
#include <fstream>

using namespace std;

/*********************************************************
   wzor 12 granice calkowania sa Xm+1 do Xm w pm = Sf(x)dx
**********************************************************/

// funckje podcalkowe g(x)
double g1(double x) { return(1 + tanh(x)); }
double g2(double x) { return 1/(1+x*x); }
double g3(double x) { return pow(cos(M_PI*x),10); }



double randNorm(double a, double b) {
    // rozkład jednorodny z zakresu a < b
    return a + (b-a) * (rand() / ((double)RAND_MAX+1));
}



struct wyniki {
    double war_oczek = 0;
    double wariancja = 0;
    int histogram[10] = {};
};



void showHistogram(wyniki wynik) {
    cout << endl;
    for (int i =0; i < 10; i++) {
        cout << wynik.histogram[i] << ",";
    }
}



wyniki metPodstawowa(int M, double N, double a, double b, function<double(double x)> g) {

    double c = 0; double var = 0; double moment2 = 0;
    //struktura przechowująca wynik całkowania, wariancje oraz histogram
    wyniki stat;
    // dx to max zmiana argumentu funkcji miedzy przedzialami
    double dX = (b-a) / (double)M;
    for (int i = 0; i < N; i++) {
        double x = randNorm(a,b);
        // w zaleznosci od wylosowanego x dodajemy 1 do histogramu
        int index = floor((x-a) / dX);
        stat.histogram[index]++;

        // czesc wlasciwa, zwiazana z szacowaniem wartosci calki 
        var = (b-a) * g(x);
        c += var;
        moment2 += var*var;
    }
    stat.war_oczek = c/N;
    stat.wariancja = (moment2/N - stat.war_oczek*stat.war_oczek) / N;
    return stat;
}



wyniki metLosSys(int M, double N, double a, double b, function<double(double x)> g) {

    double Nm = N/(double)M;
    double dX = (b-a) / (double)M;
    wyniki stat; wyniki tmp;

    for (int i = 0; i < M; i++) {
        // zmieniamy w wywolaniu metPods M na 1 żeby koncowy histogram sie zgadzal
        // kazde wywolanie metPodst doda w itej komorce histopramu Nm wartosc 
        tmp = metPodstawowa(1,Nm, a+i*dX, a+(i+1)*dX, g);
        stat.war_oczek += tmp.war_oczek;
        stat.wariancja += tmp.wariancja;
        stat.histogram[i] = tmp.histogram[0];
        
       // cout << "próba " << i << " Nm = " << Nm << endl;
       // cout << "prawdopodobienstwo pm: " << Nm/N << "\n wartosc pm^2*M^2: " << Nm*Nm*100.0 / (N*N) << "\n";
    }
    /* ponizsza linia to relikt, wczesniej bylo zgodnie ze wzorem przemnozenie przez pm,
    ale z racji korzystania z funkcji metPodstawowa wzor 14 z instrukcji zamiast (b-a)
    ma (Xm+1 - Xm) co wynosi (b-a)/M wiec wzor 16 trzeba zmodyfikowac o przemnozenie wartosci
    przez 1/pm lub po prostu zamiast sredniej policzyc sume co zostalo zrobione;
    wariancja w metodzie podstawowej to srednia, a więc zeby ja uzyc do wzoru 15,
    trzeba jej wartosc pomnozyc przez Nm i dodatkowo przez M^2
    */
    
    stat.war_oczek = stat.war_oczek;
    stat.wariancja = stat.wariancja;
    return stat;
}



wyniki metLosWarstw(int M, double N, double a, double b, function<double(double x)> g){

    double dX = (b-a) / (double)M;
    int losowanie_1st = (N > 100) ? 1000 : 100;
    double wstepne_sigmy[10];
    double suma_sigm = 0;
    wyniki stat; wyniki tmp; wyniki prognoza;

    // krotka metoda podstawowa do okreslenia wstepnych wariancji
    // z kazdego podprzedzialu zapisana zostanie uzyskana wariancja
    // w celu uzyskania lepszego okreslenia ilosci losowan w podprzedziale
    for (int i = 0; i < M; i++) {
        prognoza = metPodstawowa(1, losowanie_1st, a+i*dX, a+(i+1)*dX, g);
        wstepne_sigmy[i] = sqrt(prognoza.wariancja);
        // prawdopodobienstwo wylosownia zmiennej z kazdego przedzialu jest takie samo = 1/M
        suma_sigm += wstepne_sigmy[i] / (double)M;
    }

    // okreslenie ilosci losowan dla kazdego przedzialu i obliczanie wartosci dla kazdego podprzedzialu

    int licznik = 0;
    for (int i = 0; i < M; i++) {
        double Nm  = round(wstepne_sigmy[i] / (suma_sigm*(double)M) * N);
        // dodajemy do ostatniego zakresu kilka losowan tak zeby suma losowan = N
        if (i == 9) {
            Nm = Nm + (N-licznik-Nm);
        }
        // w tym przypadku prawdopodobiensto wylosowania zmiennej z przedzialu
        // uwarunkowane jest jako p(m) = N(m)/N
        // wyniki sa mnozone prze M ze względu na obszar calkowania rowny 1/M * (b-a)
        if (Nm != 0) {
            tmp = metPodstawowa(1,Nm, a+i*dX, a+(i+1)*dX, g);
        }
        // stat.war_oczek += tmp.war_oczek*Nm*(double)M / N;
        //stat.wariancja += tmp.wariancja;*(double)M*(double)M*Nm*Nm / (N*N)

        // cout << "próba " << i << " Nm = " << Nm << endl;
        // cout << "prawdopodobienstwo pm: " << Nm/N << "\n wartosc pm^2*M^2: " << Nm*Nm*100.0 / (N*N) << "\n";
        stat.war_oczek += tmp.war_oczek;
        stat.wariancja += tmp.wariancja;
        stat.histogram[i] = Nm;
        
        // cout << "\nDebug: " << i << "\n gm: " << tmp.war_oczek << "    gm_skal: " << tmp.war_oczek*Nm*(double)M / N;
        // cout << "\nsigm: " << tmp.wariancja << "    sigm_skal: " << tmp.wariancja*(double)M*(double)M*Nm*Nm / (N*N);
        // cout << "\nStaatystyka g i sigm   " << stat.war_oczek << "    " << stat.wariancja << endl;
         licznik += Nm;
        // cout << stat.histogram[i] << endl;
    }
    //cout << "Suma losowan: " << licznik;
    return stat;
}



int main(int argc, char **argv){
    // M - l_przedzialow; N - l_all_losowan; a,b - granice calki; g{1,2...} - wariant funckji
    /*
    wyniki met_podstawowa1 = metPodstawowa(10,100000, -3, 3, g1);
    cout << "\nMetoda podstawowa";
    cout << "\nWynik to: " << met_podstawowa1.war_oczek;
    cout << "\nOdchylenie standardowe to: " << sqrt(met_podstawowa1.wariancja);


    wyniki met_losowania1 = metLosSys(10, 100000, -3, 3, g1);
    cout << "\n\nMetoda losowania systematyczego";
    cout << "\nWynik to: " << met_losowania1.war_oczek;
    cout << "\nOdchylenie standardowe to: " << sqrt(met_losowania1.wariancja) << endl;

    wyniki met_warstwowo1 = metLosWarstw(10, 100000, -3, 3, g1);
    cout << "\n\nMetoda losowania warstwowego";
    cout << "\nWynik to: " << met_warstwowo1.war_oczek;
    cout << "\nOdchylenie standardowe to: " << sqrt(met_warstwowo1.wariancja);
    */
    int x;
    for (int N = 2; N <= 5; N++) {
        x = round(pow(10,N));
        //wyniki met_podstawowa2 = metPodstawowa(10,x, 0, 1, g3);
        //cout << "\nMetoda podstawowa x = " << x;

        //wyniki met_podstawowa2 = metLosSys(10,x, 0, 1, g3);
        //cout << "\nMetoda losowania systematycznego x = " << x;

        wyniki met_podstawowa2 = metLosWarstw(10,x, -3, 3, g1);
        cout << "\nMetoda losowania warstwowego x = " << x;


        //cout << "\nWynik to: " << met_podstawowa2.war_oczek;
        //cout << "\nOdchylenie standardowe to: " << sqrt(met_podstawowa2.wariancja);
        //cout << "\nBlad wzgledny to: " << sqrt(met_podstawowa2.wariancja)/met_podstawowa2.war_oczek;
        cout << "\n" << met_podstawowa2.war_oczek << "," << sqrt(met_podstawowa2.wariancja) << "," << sqrt(met_podstawowa2.wariancja)/met_podstawowa2.war_oczek*100;
        showHistogram(met_podstawowa2);
        //cout << endl;
    }

    /*
    wyniki met_losowania2 = metLosSys(10,1000, 0, 10, g2);
    cout << "\n\nMetoda losowania systematyczego";
    cout << "\nWynik to: " << met_losowania2.war_oczek;
    cout << "\nOdchylenie standardowe to: " << sqrt(met_losowania2.wariancja) << endl;


    wyniki met_warstwowo2 = metLosWarstw(10,1000, 0, 10, g2);
    cout << "\n\nMetoda losowania warstwowego";
    cout << "\nWynik to: " << met_warstwowo2.war_oczek;
    cout << "\nOdchylenie standardowe to: " << sqrt(met_warstwowo2.wariancja);
    */
}