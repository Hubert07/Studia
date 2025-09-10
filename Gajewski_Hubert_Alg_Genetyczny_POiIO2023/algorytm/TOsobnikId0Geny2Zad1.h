#pragma once
#include <iostream>
#include "TOsobnik.h"


class TOsobnikId0Geny2Zad1 : public TOsobnik {

public:
	TOsobnikId0Geny2Zad1() : TOsobnik(2) {
		genotyp[0].set_zakres(0, 10, 0.1);
		genotyp[1].set_zakres(0, 10, 0.1);
		losuj(l_genow);
	}
	TOsobnikId0Geny2Zad1(const TOsobnikId0Geny2Zad1 &kopia) : TOsobnik(kopia) {}
	

	TOsobnik* create() {
		return new TOsobnikId0Geny2Zad1;
	}

	TOsobnik* create_copy() {
		return new TOsobnikId0Geny2Zad1(*this);
	}

	void rate() {
		double x0 = genotyp[0].get_wartosc();
		double x1 = genotyp[1].get_wartosc();
		//this->mark = 2 * (x0 + x1);
		double funkcja = abs(sin(x0/3)*sin(x1/3));
		if (funkcja <= 0)
			this->mark = 0.00001;
		else
			this->mark = funkcja;
	}
};