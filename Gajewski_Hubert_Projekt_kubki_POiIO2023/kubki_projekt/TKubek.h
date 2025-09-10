#pragma once
#include <iostream>
#include <vector>

#include "TSubstancje.h"

class TKubek {

	std::vector<TSubstancje> substancje_w_kubku;
	std::vector<double> volumes;

public:
	void add(TSubstancje substancja, double volume_in_ml);
	void add(std::string name, double volume_in_ml);
	void addbymass(std::string name, double pctofmass);
	void addbyvolume(std::string name, double pctofvol);

	void przelejdo(TKubek &kubek2);

	void show();

private:
	void volcoe();
	void masscoe();
	int get_substance_id(std::vector<TSubstancje> substances_buffer, std::string name, bool alert=true);
};