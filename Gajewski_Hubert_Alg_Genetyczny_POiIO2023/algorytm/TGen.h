#pragma once
#include <iostream>
#include <vector>

class TGen {
	static unsigned int gens_count;
	unsigned int id;

	// zakres wartoœci: pierwsza komorka to stop, druga step, trzecia stop
	std::vector<double> zakres_wartosci;
	std::string name, opis;
	double				wartosc;
	int 				val_id;
public:
	TGen(double start, double stop, double step);
	TGen(const TGen &kopia);
	TGen(std::string name, double start, double stop, double step);
	TGen(std::string name, double start, double stop, double step, double value);

	TGen(std::string name, std::string opis, double start, double stop, double step);
	TGen(std::string name, std::string opis, double start, double stop, double step, double value);

	~TGen();

	void set_zakres(double min, double max, double step);
	void set_val(double value);
	void set_name(std::string name) { this->name = name; }
	void set_opis(std::string opis) { this->opis = opis; }

	std::vector<double> get_zakres() const { return this->zakres_wartosci; }
	double get_wartosc() const { return this->wartosc; }
	int get_index() { return get_val_id(this->wartosc); }
	std::string get_name() const { return this->name; }
	std::string get_opis() const { return this->opis; }
	void info();

private:
	int get_val_id(double value);
};
