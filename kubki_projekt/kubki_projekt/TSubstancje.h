#pragma once
#include <iostream>
#include <vector>

class TSubstancje {

	std::string name;
	double		ro;


public:
	TSubstancje(std::string name, double ro);

	std::string get_name();
	double		get_ro();
	
};


extern std::vector<TSubstancje> substancje;