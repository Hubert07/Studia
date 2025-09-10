#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdio>
#include "TOsobnik.h"

using namespace std;

unsigned int TOsobnik::candidates_count = 0;

// ************** PUBLIC **************
TOsobnik::TOsobnik(int l_genow) : l_genow { l_genow }  {
	candidates_count++;
	this->id = candidates_count;
	this->mark = 0;

	init_vector();
	losuj(l_genow);
	//cout << "Utworzono osobnika nr: "<< id <<"\n";
}


TOsobnik::TOsobnik(const TOsobnik& kopia) : l_genow{ kopia.l_genow } {
	candidates_count++;
	this->id = candidates_count;

	init_vector();
	set_gens_names();

	this->mark = kopia.get_rate();
	for (int i = 0; i < kopia.l_genow; i++) {
		// przypisanie wartoœci z orygina³u do nowego osobnika
		// wyciagniêcie po koeli ka¿dego genu odczytanie wartoœci jak¹ ma oraz zakresu
		// bo domyœlnie tworzy³by siê gen z zakresem zdef w TOsobnik
		TGen gen = kopia.get_gen(i);
		//gen.info();
		// pobranie wartoœci genu
		double war = gen.get_wartosc();
		// cout << "wartosc skopiowanego genu: " << war << endl;
		// pobranie zakresu wartosci
		vector<double> zakres = gen.get_zakres();
		//ustawienie zakresu oraz warotsic genu
		genotyp[i].set_zakres(zakres[0],zakres[2],zakres[1]);
		genotyp[i].set_val(war);
		set_gens_names();
	}
	//cout << "Utowrzono osobnika nr: " << id << " za pomoca konstruktora kopiujacego\n";
}


void TOsobnik::halotest(double zmien) {
	// funckja do sprawdzenia czy kopiowanie i ustawianie wartoœci genu dzia³a prawid³owo
	// czy get_wartossc() oraz set_val() dobrze dzia³aj¹
	double wartosc = genotyp[1].get_wartosc();
	genotyp[1].set_val(wartosc + zmien);

}


void TOsobnik::init_vector() {
	// utowrzenie liczby genów w genotypie odpowiadaj¹cej wartoœci podanej w konnstruktorze
	for (int i = 0; i < l_genow; i++) {
		genotyp.push_back(TGen{ 0, 10, 1 });
	}
}


void TOsobnik::info() {
	int size = l_genow;
	for (int i = 0; i < l_genow; i++) {
		genotyp[i].info();
		cout << endl;
	}
	cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
	cout << "+ Liczba genow: " << size << "\n";
	for (int i = 0; i < l_genow; i++) {
		cout << "+ " << genotyp[i].get_name() << ": " << genotyp[i].get_wartosc() << "\n";
	}
	cout << "+ Rate: " << get_rate() << "\n";
	cout << "+++++++++++++++++++++++++++++++++++++++\n";
}


void TOsobnik::short_info() {
	cout << "<> Liczba genow: " << l_genow << "\n";
	for (int i = 0; i < l_genow; i++) {
		cout << "<> " << genotyp[i].get_name() << ": " << genotyp[i].get_wartosc() << "\n";
	}
	cout << "<> Rate: " << get_rate() << "\n";
	cout << "<><><><><><><><><><><><><><><>\n";
}


// ************** PRIVATE **************
void TOsobnik::losuj(int ile_genow) {
	for (int i = 0; i < ile_genow; i++) {
		vector<double> zakres_wartosci = genotyp[i].get_zakres();
		double step = zakres_wartosci[1];
		int ile_id = (zakres_wartosci[2]-zakres_wartosci[0]) / step + 1;
		int rand_id = rand() % ile_id;
		genotyp[i].set_val(zakres_wartosci[0] + (rand_id * step));

		/*
		cout << "\n Oto co sie wylosowalo: " <<
			"\nMin: " << zakres_wartosci[0] <<
			"\nMax: " << zakres_wartosci[zakres_wartosci.size() - 1] <<
			"\nStep: " << step <<
			"\nIle Id: " << ile_id <<
			"\nRand Id: " << rand_id;
		*/
	}
}


	void TOsobnik::set_gens_names() {
		for (int i = 0; i < l_genow; i++) {
			string nazwa = "Osobnik";
			nazwa += to_string(id);
			nazwa += "_gen";
			nazwa += to_string(i);
			genotyp[i].set_name(nazwa);
		}
	}
