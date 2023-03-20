#include <iostream>
#include <iostream>
#include <vector>
#include "TSubstancje.h"
#include "TKubek.h"

using namespace std;

int main()
{
	
	for (int i = 0; i < 4; i++) {
		cout << substancje[i].get_name() << ": " << substancje[i].get_ro() << "kg/m3\n";
	}
	cout << endl;
	
	TKubek kubek1;
	kubek1.add(substancje[0], 100);
	kubek1.add(substancje[1], 50);
	kubek1.add("woda", 70);
	kubek1.add("krew", 30);
	kubek1.add("mleko", 50);
	kubek1.show();
	kubek1.addbyvolume("krew", 0.5);
	kubek1.show();

	int g;
	cin >> g;
}
