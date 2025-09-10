#pragma once
#include <iostream>
#include <vector>
#include "TGen.h"


class TOsobnik {

protected:

	static unsigned int candidates_count;
	unsigned int id;
	const int l_genow;

	/*
	TGen geny[L_GENOW] =
	{
		TGen ("oczka", 0, 10, 0.5),
		TGen ("uszka", -1, 5, 0.1)
	};
	*/

	std::vector<TGen> genotyp;
	double mark;


public:
	TOsobnik(int l_genow = 0);
	TOsobnik(const TOsobnik &kopia);

	virtual TOsobnik* create() = 0;
	virtual TOsobnik* create_copy() = 0;

	void halotest(double zmien);
	virtual void rate() = 0;
	void set_gen(TGen gen, int index) { genotyp[index] = gen; }
	TGen get_gen(int index) const { return genotyp[index]; }
	double get_rate() const { return mark; }
	unsigned int get_id() { return id; }
	std::vector<TGen> get_genotyp() { return genotyp; }
	void info();
	void short_info();

protected:
	void losuj(int ile_genow);
	void set_gens_names();
	void init_vector();
};
