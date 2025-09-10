#include"TPopulacja.h"

using namespace std;

unsigned int TPopulacja::id = 0;

// ************** PUBLIC **************
TPopulacja::TPopulacja() {
	id++;
	init();
	for (int i = 0; i < (int)l_osobnikow; i++) {
		osobnicy.push_back( pattern->create() );
	}
}


TPopulacja::TPopulacja(unsigned int size) {
	// Jeœli uzyjemy konstruktora z wielkoœci¹ populacji to bêdzie jakiœ domyœlny typ osobnika
	this->id++;
	this->l_osobnikow = size;
	this->pattern = new TOsobnikId0Geny2Zad1{};
	
	for (int i = 0; i < (int)l_osobnikow; i++) {
		osobnicy.push_back(pattern->create());
	}
}


TPopulacja::TPopulacja(const TPopulacja &wzor) {
	this->id++;
	this->l_osobnikow = wzor.get_l_osobnikow();
	pattern = wzor.get_pattern();

	osobnicy.clear();
	for (int i = 0; i < (int)l_osobnikow; i++) {
		osobnicy.push_back(pattern->create());
	}
}


TPopulacja::~TPopulacja() {
	for (int i = 0; i < (int)l_osobnikow; i++) {
		delete osobnicy[i];
		osobnicy[i] = nullptr;
	}
}


void TPopulacja::calculate() {
	double best_mark = -10000000000;
	for (int i = 0; i < (int)l_osobnikow; i++) {
		osobnicy[i]->rate();
		double tmp_mark = osobnicy[i]->get_rate();
		if (tmp_mark > best_mark) {
			best_mark = tmp_mark;
		}
	}
	this->best_val = best_mark;
}


TOsobnik* TPopulacja::get_best_candidate() {
	calculate();
	for (int i = 0; i < (int)l_osobnikow; i++) {
		osobnicy[i]->rate();
		double tmp_mark = osobnicy[i]->get_rate();
		if (tmp_mark == best_val) {
			return osobnicy[i];
		}
	}
}


double TPopulacja::get_best_val() {
	calculate();
	return this->best_val;
}


void TPopulacja::info() {
	cout << "\n&&&&&&&& Populacja #" << id << " &&&&&&&&\n";
	for (int i = 0; i < (int)l_osobnikow; i++) {
		cout << "&& osobnik#" << i << ": " << osobnicy[i]->get_rate() << "  " << "\n";
	}
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
}


// ************** PRIVATE **************
void TPopulacja::init() {
	unsigned int id_osobnika;
	cout << "\nPodaj id osobinka dla ktorego stworzy sie populacje: ";
	cin >> id_osobnika;

	if (id_osobnika < 0 || id_osobnika > 3)
		id_osobnika = 0;

	switch (id_osobnika) {
	case 0:
		pattern = new TOsobnikId0Geny2Zad1{};
		break;
	case 1:
		pattern = new TOsobnikId1Geny2Zad2{};
		break;
	case 2:
		pattern = new TOsobnikId2Geny3Zad3{};
		break;
	}

	unsigned int liczebnosc;
	cout << "\nPodaj ilu osobnikow w populacji: ";
	cin >> liczebnosc;
	if (liczebnosc % 2)
		liczebnosc++;
	this->l_osobnikow = liczebnosc;
}
