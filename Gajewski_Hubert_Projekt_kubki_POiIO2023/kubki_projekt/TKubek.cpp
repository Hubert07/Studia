#include "TKubek.h"
#include "TSubstancje.h"
using namespace std;


// ************** PUBLIC **************
void TKubek::add(TSubstancje substancja, double volume_in_ml) {
	string nazwa = substancja.get_name();
	int substancja_pos_in_cup = get_substance_id(this->substancje_w_kubku, nazwa, false);
	if (substancja_pos_in_cup == -1) {
		substancje_w_kubku.push_back(substancja);
		volumes.push_back(volume_in_ml / 1e6);
	}
	else {
		this->volumes[substancja_pos_in_cup] += volume_in_ml / 1e6;
	}
}


void TKubek::add(string name, double volume_in_ml) {
	int _id = get_substance_id(substancje, name);
	if (_id >= 0) {
		this->add(substancje[_id], volume_in_ml);
	}
}


void TKubek::addbymass(std::string name, double pctofmass){
	double total_mass = 0;
	double cododac;
	vector<double> masy;
	int count = volumes.size();
	int id = get_substance_id(substancje_w_kubku, name);

	// sprawdzenie czy ta substancja istnieje w kubku
	if ( id > -1) {

		// liczenie ca³kowitej masy
		for (int i = 0; i < count; i++) {
			masy.push_back(volumes[i] * substancje_w_kubku[i].get_ro());
			total_mass += masy[i];
		}

		//  liczenie aktualnego stosunku masy danej substancji
		double coef = masy[id] / total_mass;
		if ((coef) >= pctofmass) {
			cout << "Mass already exceeded: " << coef << endl;
		}
		else {
			cododac = ((total_mass * pctofmass) - masy[id]) / (1 - pctofmass) / substancje_w_kubku[id].get_ro();
			add(name, (cododac * 1e6));
		}
	}
	else
		cout << "Nie ma takiej substancji w kubku\n";
}


void TKubek::addbyvolume(std::string name, double pctofvol){
	double total_vol = 0;
	int count = volumes.size();
	int id = get_substance_id(substancje_w_kubku, name);
	double cododac;

	if (id > -1) {
		// liczenie ca³kowitej objêtoœci
		for (int i = 0; i < count; i++) {
			total_vol += volumes[i];
		}
		double coef = volumes[id] / total_vol;
		if ((coef) >= pctofvol) {
			cout << "Volume already exceeded: " << coef << endl;
		}
		else {
			cododac = ((total_vol * pctofvol) - volumes[id]) / (1 - pctofvol);
			add(name, (cododac * 1e6));
		}
	} else
		cout << "Nie ma takiej substancji w kubku\n";
}


void TKubek::przelejdo(TKubek &kubek2){
	int count = volumes.size();

	for (int i = 0; i < count; i++) {
		string nazwa = this->substancje_w_kubku[0].get_name();
		double objetosc = this->volumes[0] * 1e6;

		kubek2.add(nazwa, objetosc);

		this->substancje_w_kubku.erase(substancje_w_kubku.begin());
		this->volumes.erase(volumes.begin());
	}
}


void TKubek::show() {
	int count = substancje_w_kubku.size();
	cout << "\n";
	for (int i = 0; i < count; i++) {
		double mass = substancje_w_kubku[i].get_ro() * volumes[i] * 1e3;
		cout << substancje_w_kubku[i].get_name()
			<< "; volume: " << volumes[i] * 1e6 << " ml"
			<< "; mass: " << mass << " g" << endl;
	}

	volcoe();
	masscoe();
}


// ************** PRIVATE **************

int TKubek::get_substance_id(std::vector<TSubstancje> substances_buffer, string name, bool alert) {
	int count = substances_buffer.size();
	int _id = -1;
	bool run = count;

	while (run) {
		_id += 1;
		string sub_name = substances_buffer[_id].get_name();

		if (sub_name == name)
			run = false;

		if ((_id + 1 == count) && (run == true)) {
			if (alert) cout << "Nie znaleziono plynu o danej nazwie: \"" << name << "\"!\n";

			run = false;
			_id = -1;
		}
	}
	return _id;
}


void TKubek::volcoe() {
	double total_vol = 0;
	int count = volumes.size();
	for (int i = 0; i < count; i++) {
		total_vol += volumes[i];
	}
	cout << "Volume coe: ";
	for (int i = 0; i < count; i++) {
		cout << volumes[i] / total_vol * 100 << " - ";
	}
	cout << "\n";
}


void TKubek::masscoe() {
	double total_mass = 0;
	vector<double> masy;
	int count = volumes.size();

	for (int i = 0; i < count; i++) {
		masy.push_back(volumes[i] * substancje_w_kubku[i].get_ro());
		total_mass += masy[i];
	}
	cout << "Mass coe: ";
	for (int i = 0; i < count; i++) {
		cout << masy[i] / total_mass * 100 << " - ";
	}
	cout << "\n\n";
}