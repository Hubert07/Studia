#include "TGen.h"

using namespace std;

unsigned int TGen::gens_count = 0;

// ************** PUBLIC **************
TGen::TGen(double start, double stop, double step) : name{ "" }, opis{ "" }, val_id{ 0 } {
	gens_count++;
	this->id = gens_count;

	set_zakres(start, stop, step);
	//cout << "Utworzono gen z id: " << id << "\n";
}


TGen::TGen(const TGen &kopia) {
	this->zakres_wartosci = kopia.get_zakres();
	this->name = kopia.get_name();
	this->opis = kopia.get_opis();
	this->wartosc = kopia.get_wartosc();
	this->val_id = get_val_id(this->wartosc);

	gens_count++;
	this->id = gens_count;
	//cout << "Utworzono gen z id: "<< id <<" za pomoca konstruktora kopiujacego\n";
}


TGen::TGen(string name, double start, double stop, double step) : TGen::TGen(start,stop,step) {
	// id = value/stop -1
	set_name(name);
}


TGen::TGen(string name, double start, double stop, double step, double value) : TGen::TGen(name,start,stop,step) {
	// id = value/stop -1
	set_val(value);
}


TGen::TGen(string name, string opis, double start, double stop, double step) : TGen::TGen(name, start, stop, step) {
	// id = value/stop -1
	set_opis(opis);
}


TGen::TGen(string name, string opis, double start, double stop, double step, double value) : TGen::TGen(name, opis, start, stop, step) {
	// id = value/stop -1
	set_val(value);
}


TGen::~TGen() {
	//cout << "Usunieto gen o id: " << id << "\n";
}


void TGen::set_zakres(double min, double max, double step) {
	// usuniêcie starego zakresu wartosci ¿eby wektor by³ czysty i indeksowanie dzia³a³o poprawnie
	this->zakres_wartosci.clear();
	this->zakres_wartosci.push_back(min);
	this->zakres_wartosci.push_back(step);
	this->zakres_wartosci.push_back(max);
}


void TGen::set_val(double value) {
	/* Dodaæ dopasowanie wartosci do mozliwych wartosci
	*  Czyli jak mamy zakres genu 0:1:10 to
	   po podaniu 9.5 zaokr¹gli³o nam do mo¿liwej wartoœci
	*/
	double step = this->zakres_wartosci[1];
	if (value < zakres_wartosci[0])
		this->wartosc = zakres_wartosci[0];
	else if (value > zakres_wartosci[2])
		this->wartosc = zakres_wartosci[2];
	else
		this->wartosc = (round((value - zakres_wartosci[0]) / step) * step) + zakres_wartosci[0];
	this->val_id = get_val_id(wartosc);
}


void TGen::info() {

	cout << "######################################\n";
	cout << "#  Dane dotyczace wektora: " << endl;
	cout << "#  Nazwa: " << name << "\n";
	cout << "#  Opis: " << opis << "\n";
	cout << "#  start value: " << zakres_wartosci[0] << "\n";
	cout << "#  end value: " << zakres_wartosci[2] << "\n";
	cout << "#  step: " << zakres_wartosci[1] << "\n#\n";
	cout << "#  current val: " << wartosc << "\n";
	cout << "#  val_id: " << val_id << "\n";
	cout << "######################################\n";
}

// ************** PRIVATE **************
int TGen::get_val_id(double value) {
	double step = zakres_wartosci[1];
	double id = (value - zakres_wartosci[0]) / step;
	return (int)id;
}
