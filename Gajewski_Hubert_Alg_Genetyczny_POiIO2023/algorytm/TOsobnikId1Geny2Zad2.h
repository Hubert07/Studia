#pragma once
#include <iostream>
#include "TOsobnik.h"


class TOsobnikId1Geny2Zad2 : public TOsobnik {

public:
	TOsobnikId1Geny2Zad2() : TOsobnik(2) {
		genotyp[0].set_zakres(100, 200, 3);
		genotyp[1].set_zakres(100, 200, 20);
		losuj(l_genow);
	}
	TOsobnikId1Geny2Zad2(const TOsobnikId1Geny2Zad2& kopia) : TOsobnik(kopia) {}

	TOsobnik* create() {
		return new TOsobnikId1Geny2Zad2;
	}

	TOsobnik* create_copy() {
		return new TOsobnikId1Geny2Zad2(*this);
	}

	void rate() {
		double x1 = genotyp[0].get_wartosc();
		double x2 = genotyp[1].get_wartosc();
		this->mark = x1 + x2;
	}

};
