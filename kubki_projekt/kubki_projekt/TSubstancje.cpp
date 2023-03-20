#include "TSubstancje.h"
using namespace std;

TSubstancje::TSubstancje(string name, double ro) {

	this->name = name;
	this->ro = ro;

}

string TSubstancje::get_name(){
	return name;
}

double TSubstancje::get_ro(){
	return ro;
}

vector<TSubstancje> substancje = {
TSubstancje{"woda", 997.8},
TSubstancje{"mleko", 1030.0},
TSubstancje{"oliwa", 920.0},
TSubstancje{"krew", 1050.0}
};