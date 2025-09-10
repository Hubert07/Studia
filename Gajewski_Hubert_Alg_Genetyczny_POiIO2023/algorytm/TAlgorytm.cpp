#include <math.h>
#include<vector>
#include "TAlgorytm.h"

using namespace std;

// ************** PUBLIC **************
TAlgorytm::TAlgorytm(double min_polepszenie,  int ile_pop){
	this->stop_min_improv_proc = min_polepszenie;
	this->stop_max_pop_id = ile_pop;
	cout << "Zaraz wybierzesz wariant osobnika dla ktorej bedzie dzialal algorytm\n";
	this->wsk_curr_pop = new TPopulacja {};
	this->pop_size = (int)wsk_curr_pop->get_l_osobnikow();
}


TAlgorytm::~TAlgorytm(){
	delete wsk_curr_pop;
	delete wsk_n_pop;
	cout << "Memory cleared! \n";
}


/*
******************* Zadania algorytmu genetycznego: ******************* 
* 1# Ruletka 30% na przejœcie na czysto 70% na krzyzowanie
*  * Zamiast tego mo¿na byby³o braæ k najlepszych osobników
* 2# Krzy¿owanie dec2bin i fragment tego wzi¹æ wymieszaæ, mo¿na 2 osobników stworzyæ
* 3# Mutacja genu, znowu ruletka czy mutowaæ czy nie, póŸniej mutacja
*  * o sta³y krok albo mo¿e sigmoid? lub inny zienny w casie krok
*/


void TAlgorytm::wio() {
	// sprawdzenie czy istnieje nowa populacja albo warunki s¹ spe³nione
	TOsobnik* najlepszy = nullptr;
	bool warunek = 1;
	while (!wsk_n_pop || warunek) {
			wsk_curr_pop->calculate();
			wsk_curr_pop->info();
			if(warunek)
				cout << "\n#  Population #" << wsk_curr_pop->get_id() << " best result: " << wsk_curr_pop->get_best_val() << endl;
			// Stworzenie nowej populacji na podstawie starej (ale osobnicy maj¹ losowe genotypy)
			this->wsk_n_pop = new TPopulacja{ *wsk_curr_pop };
// ****************** Ruletka i krzy¿owanie ******************
			for (int i = 0; i < pop_size; i++) {
				if (losowanie(70, 30)) {
					//cout << "\n Wylosowano krzyzowanie\n";
					// Wydobycie rodziców
					// im osobnik ma wiêkszy rate, tym wiêksza szansa na to ¿e bêdzie rodzicem
					TOsobnik* osobnnik1 = losuj_rodzica(wsk_curr_pop);
					TOsobnik* osobnnik2 = losuj_rodzica(wsk_curr_pop, osobnnik1);

					// Wydobycie z nich genów
					vector<TGen> genotyp_os1 = osobnnik1->get_genotyp();
					vector<TGen> genotyp_os2 = osobnnik2->get_genotyp();
					// Modyfikacja wartoœci poszczególnych genów, zamiana indexu dec2bin, tworzony bêdzie tylko 1 osobnik 
					for (int j = 0; j < genotyp_os1.size(); j++) {
						int index_osobnik1 = genotyp_os1[j].get_index();
						int index_osobnik2 = genotyp_os2[j].get_index();

						//cout << "\ngen przed krzyzowanien\n";
						//genotyp_os1[j].info();

						vector<double> zakres_wartosci = genotyp_os1[j].get_zakres();
						double step = zakres_wartosci[1];
						// zmienna rozmiar to d³ugoœæ wekotra zapisujacego indeks wartoœci genu w postaci binarnej
						int rozmiar = floor(log2((zakres_wartosci[2]-zakres_wartosci[0]) / step + 1)+1);
						vector<int> bin_osobnik1 = dec2bin(index_osobnik1, rozmiar);
						vector<int> bin_osobnik2 = dec2bin(index_osobnik2, rozmiar);

						vector<int> bin_potomek1 = bin_osobnik1;

						//cout << "\n\nIndex wartosci genu rodzica 1: ";
						//show(bin_osobnik1);
						//cout << " wartosc id: " << bin2dec(bin_osobnik1);
						//cout << "\nIndex wartosci genu rodzica 2: ";
						//show(bin_osobnik2);
						//cout << " wartosc id: " << bin2dec(bin_osobnik2);
						//cout << "\n\n";

						// Losowy wybór miejsca przeciêcia (od miejsca  2^0 do miejsca wskazanego przez gdzie_ciac
						// osobnik zatrzymuje swoje wartoœci, powy¿ej tego miejsca osobnik ma wartoœci po s¹siedzie)
						// czyli zmienna gdzie ciac mówi o tym ile dok³adnie pocz¹tkowych bitów wekotra zostanie niezmiennych
						int gdzie_ciac = rand() % rozmiar;
						for (int x = 0; x < rozmiar - gdzie_ciac; x++) {
							bin_potomek1[x] = bin_osobnik2[x];
						}

						//cout << "Gdzie ciac: " << gdzie_ciac << "\nWartosc id potomka: ";
						//show(bin_potomek1);
						//cout << " wartosc id: " << bin2dec(bin_potomek1);
						//cout << "\n\n";

						// Ustanowienie nowej wartoœci dla genu
						// Przypisane tej wartoœci do osobnika z nowej populacji
						TOsobnik* n_osobnik = wsk_n_pop->get_osobnik(i);
						vector<TGen> genotyp_n_os = n_osobnik->get_genotyp();
						genotyp_n_os[j].set_val(zakres_wartosci[0] + step * bin2dec(bin_potomek1));
						// Wstawienie genotypu dla osobnika w nowej populacji
						n_osobnik->set_gen(genotyp_n_os[j],j);

						//cout << "\n Wartosc nowa dla genu: " << genotyp_n_os[j].get_wartosc();
						//cout << "\ngen po krzyzowaniu\n";
						//genotyp_n_os[j].info();

					}

				} else {
					// Jeœli krzy¿owanie siê nie wylosuje, to mutacja albo nowy osobnik
					if (losowanie(70, 30)) {
						// Okreœlenie kroku mutacji, muutowanie bêdzie polega³o na:
						// nowa_wartosc = starawartoœæ + step_genu*<-krok_mutacji,krok_mutacji>
						// czyli np krok_mutacji = 3, wiêc wartoœæ genu mo¿emy zmieniæ o -3 -2 -1 0 +1 +2 +3 indeksy
						int krok_mutacji = 2;
						//cout << "\nWylosowano mutacje\n";
						TOsobnik* osobnik1 = wsk_curr_pop->get_osobnik(i);
						vector<TGen> genotyp_os1 = osobnik1->get_genotyp();
						for (int j = 0; j < genotyp_os1.size(); j++) {

							vector<double> zakres_genu = genotyp_os1[j].get_zakres();
							double step_genu = zakres_genu[1];
							//cout << "\ngen przed mutacja\n";
							//genotyp_os1[j].info();

							double stara_wartosc = genotyp_os1[j].get_wartosc();
							
							// losowe wyznaczenie zmiany wartoœci genu, przesuniêciewartoœci w lewo albo w prawo
							double rand_id = rand() % (2 * krok_mutacji + 1);
							double nowa_wartosc = stara_wartosc + step_genu*(-krok_mutacji+rand_id);

							// Przypisanie nowej wartoœci do nowego osobnika
							TOsobnik* n_osobnik = wsk_n_pop->get_osobnik(i);
							vector<TGen> genotyp_n_os = n_osobnik->get_genotyp();
							genotyp_n_os[j].set_val(nowa_wartosc);
							// Wstawienie genotypu dla osobnika w nowej populacji
							n_osobnik->set_gen(genotyp_n_os[j], j);

							//cout << "\n nowa wartosc: " << genotyp_n_os[j].get_wartosc();
							//cout << "\ngen po mutacji\n";
							//genotyp_n_os[j].info();
						}

					}
					else {
						//cout << "\n Wylosowano nowego osobnika\n";
						// Czyli nic nie trzeba robiæ bo losowe osobniki by³y stworzone w linii 39
					}
				}
			}
			wsk_n_pop->calculate();
			warunek = var_check();
			TOsobnik* stary_naj = wsk_curr_pop->get_best_candidate();
			TOsobnik* nowy_naj = wsk_n_pop->get_best_candidate();
			if (stary_naj->get_rate() > nowy_naj->get_rate())
				najlepszy = stary_naj;
			else
				najlepszy = nowy_naj;
			this->wsk_curr_pop = wsk_n_pop;
			if (!warunek) {
				wsk_curr_pop->info();
				cout << "\n#  Population #" << wsk_curr_pop->get_id() << " best result: " << wsk_curr_pop->get_best_val() << endl;
				cout << "\n Best Candidate: \n";
				najlepszy->info();
			}
	}
}


// ************** PRIVATE **************
bool TAlgorytm::var_check() {
	double old_best = wsk_curr_pop->get_best_val();
	double new_best = wsk_n_pop->get_best_val();
	double poprawa = (new_best - old_best)/old_best;
	int npop_id = wsk_n_pop->get_id();

	/*
	//******** Do testu ********
	cout << "Adres old_pop: " << wsk_curr_pop << endl;
	cout << "Adres n_pop: " << wsk_n_pop << endl;
	cout << "Old best: " << old_best << endl;
	cout << "New best: " << new_best << endl;
	cout << "Poprawa o: " << poprawa << endl;
	*/

	// taki pierwszy warunek bo max_pop_id nie jest wymaganym kryterium i domyœlnie daje -1
	if (stop_max_pop_id < 0) {
		if (poprawa > stop_min_improv_proc)
			return 1;
	}
	else {
		if (poprawa > stop_min_improv_proc && npop_id <= stop_max_pop_id)
			return 1;
		return 0;
	}
}


bool TAlgorytm::losowanie(int destiny1, int destiny2) {
	// Funkcja która pobiera prawdopodobieñstwa dwóch wydarzeñ (np losowanie(50, 50))
	// zwraca 1 jeœli trafi na pierwsze zdarzenie, 0 jak na drugie
	int wybor = rand() % (destiny1 + destiny2);
	if (wybor < destiny1) { return 1; }
	else { return 0; }
}


TOsobnik* TAlgorytm::losuj_rodzica(TPopulacja* wsk_populacji, TOsobnik* rodzic1) {
	// losowanie rodzica za pomoc¹ ko³a ruletki
	double suma = 0;
	TOsobnik* rodzic2 = nullptr;

	if (rodzic1) {
		for (int i = 0; i < pop_size; i++) {
			TOsobnik* osobnik = wsk_populacji->get_osobnik(i);
			if(osobnik->get_id() != rodzic1->get_id())
				suma += osobnik->get_rate();
		}
	}
	else {
		for (int i = 0; i < pop_size; i++) {
			TOsobnik* osobnik = wsk_populacji->get_osobnik(i);
			suma += osobnik->get_rate();
		}
	}

	double wylosowana_wartosc = (double)(rand() % (int)(suma * 100)) / 100;
	// Sprawdzenie który osobnik zosta³ wyloswoany, ka¿dy ma szansê zale¿n¹ od jego f dopasowania
	// np jeœli mamy 3 osobników których ocey wynosz¹ 5 3 10, to pierwszy zostanie wylosowany, jeœli
	// zmienna WYLOSOWANA_WARTOSC jest < 5, drugi, jeœli 5 < WYLOSOWANA_WARTOSC < 8 etc.

	// jak ranking jest ujemny to pojawiaj¹ siê komplikacje które trzeba naprawiæ, tak zdefiniowac funkcje celu zeby nie mia³a war < 0
 	bool run = 1;
	double zakres_osobnika = 0;
	int j = 0;

	while (run) {
		TOsobnik* osobnik = wsk_populacji->get_osobnik(j);
		zakres_osobnika += osobnik->get_rate();
		if (wylosowana_wartosc < zakres_osobnika) {
			rodzic2 = osobnik;
			run = 0;
		}
		else
			j++;
		if (j >= wsk_populacji->get_l_osobnikow())
			run = 0;
	}
	return rodzic2;
}


vector<int> TAlgorytm::dec2bin(int num, int rozmiar) {
	vector<int> bin;

	for (int i = 0; i < rozmiar; i++) {
		bin.insert(bin.begin(), num % 2);
		num = (num - num % 2) / 2;
	}
	return bin;
}


int TAlgorytm::bin2dec(vector<int> bin) {
	int dec = 0;
	for (int i = bin.size(); i > 0; i--) {
		dec += bin[i-1] * pow(2, bin.size() - i);
	}
	return dec;
}


void TAlgorytm::show(vector<int> liczba) {
	for (int i = 0; i < liczba.size(); i++) {
		cout << " " << liczba[i];
	}
}