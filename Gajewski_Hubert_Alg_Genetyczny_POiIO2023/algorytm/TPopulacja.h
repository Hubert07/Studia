#pragma once
#include<iostream>
#include<vector>
#include"TOsobnik.h"
#include "TOsobnikId0Geny2Zad1.h"
#include "TOsobnikId1Geny2Zad2.h"
#include "TOsobnikId2Geny3Zad3.h"

class TPopulacja {

	static unsigned int id;
	unsigned int l_osobnikow;
	TOsobnik* pattern = nullptr;
	std::vector<TOsobnik*> osobnicy;
	double best_val = 0;

public:
	TPopulacja();
	TPopulacja(unsigned int size);
	TPopulacja(const TPopulacja &wzor);
	~TPopulacja();


	void calculate();
	TOsobnik* get_best_candidate();
	double get_best_val();
	unsigned int get_l_osobnikow() const { return l_osobnikow; }
	TOsobnik* get_pattern() const { return pattern; }
	TOsobnik* get_osobnik(int id) { return osobnicy[id]; }
	int get_id() { return id; }

	void info();

private:
	void init();
};