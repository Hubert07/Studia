#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "TGen.h"
#include "TOsobnik.h"
#include "TOsobnikId0Geny2Zad1.h"
#include "TOsobnikId1Geny2Zad2.h"
#include "TOsobnikId2Geny3Zad3.h"
#include"TPopulacja.h"
#include"TAlgorytm.h"


using namespace std;

int main() {

	srand((unsigned)time(NULL));

	/*
	
	TGen gen1("oczka", 0, 2, 0.5, 1);
	TGen gen2("uszka", 0, 5, 1);

	cout << "\n\nGen 1 \n";
	gen1.info();


	cout << "\n\nGen 2 \n";
	gen2.set_val(4);
	gen2.info();
	

	cout << "##### Tworzenie osobinika #####\n\n";
	TOsobnik kotek1;
	kotek1.info();
	srand((unsigned)time(NULL));
	TPopulacja pop1(10);
	cout << "\n Stworznie populacji \n";
	pop1.info();
	pop1.calculate();
	cout << "\n\nObliczenia ocen dopasowania \n";
	pop1.info();
	cout << "\n\n<><> Najlepszy w rodzinie <><>\n";
	pop1.get_best_candidate().short_info();

	*/

	

	/*
	TOsobnikId0Geny2Zad1 osobnik2{};
	TOsobnikId2Geny3Zad3 osobnik3{};
	TOsobnikId2Geny3Zad3 osobnik4(osobnik3);


	osobnik2.rate();
	osobnik3.rate();
	osobnik4.rate();

	cout << "Osobnik 3\n\n";
	osobnik2.info();
	cout << "Osobnik 4\n\n";
	osobnik3.info();
	cout << "Osobnik 5\n\n";
	osobnik4.info();
	*/

	/*
	
	TPopulacja pop {};
	pop.calculate();
	pop.info();

	TOsobnik* najlepszy = pop.get_best_candidate();
	najlepszy->info();

	*/


	TAlgorytm test(0.001, 20);
	test.wio();
	cout << "\nKoniec\n";

	return 0;
}
