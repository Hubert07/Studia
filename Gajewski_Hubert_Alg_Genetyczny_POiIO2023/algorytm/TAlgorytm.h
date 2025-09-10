#pragma once
#include<iostream>
#include<vector>
#include"TPopulacja.h"

class TAlgorytm {
	int stop_max_pop_id;
	int pop_size;
	double stop_min_improv_proc;
	TPopulacja* wsk_curr_pop;
	TPopulacja* wsk_n_pop;

public:
	TAlgorytm(double min_polepszenie, int ile_pop = -1);
	//TAlgorytm(double min_polepszenie, int pop_size, int ile_pop = -1);
	~TAlgorytm();
	void wio();
private:
	bool var_check();
	bool losowanie(int destiny1, int destiny2);
	std::vector<int> dec2bin(int num, int rozmiar);
	int bin2dec(std::vector<int> bin);
	void show(std::vector<int>liczba);
	TOsobnik* losuj_rodzica(TPopulacja* wsk_populacji, TOsobnik* rodzic1 = nullptr);
};