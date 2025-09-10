#pragma once
#include <iostream>
#include "TOsobnik.h"


class TOsobnikId2Geny3Zad3 : public TOsobnik {

public:
	TOsobnikId2Geny3Zad3() : TOsobnik(3) {
		genotyp[0].set_zakres(-1, 10, 1);
		genotyp[1].set_zakres(100, 200, 20);
		genotyp[2].set_zakres(0, 200, 20);
		losuj(l_genow);
	}
	TOsobnikId2Geny3Zad3(const TOsobnikId2Geny3Zad3 &kopia) : TOsobnik(kopia) {}

	TOsobnik* create() {
		return new TOsobnikId2Geny3Zad3;
	}

	TOsobnik* create_copy() {
		return new TOsobnikId2Geny3Zad3(*this);
	}

	void rate() {
		double x0 = genotyp[0].get_wartosc();
		double x1 = genotyp[1].get_wartosc();
		double x2 = genotyp[2].get_wartosc();
		this->mark = 3*x0 + 2*x1 + x2;
	}
};
