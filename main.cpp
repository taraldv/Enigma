#include <iostream>
#include "enigma.h"

int main(int argc, char const *argv[])
{
	char plugOne [2] = {'A', 'B'};
	char plugTwo [2] = {'C', 'D'};
	char plugThree [2] = {'E', 'F'};
	char plugFour [2] = {'G', 'H'};
	char plugFive [2] = {'I', 'J'};
	char plugSix [2] = {'K', 'L'};
	char plugSeven [2] = {'M', 'N'};
	char plugEight [2] = {'O', 'P'};
	char plugNine [2] = {'Q', 'R'};
	char plugTen [2] = {'S', 'T'};
	std::vector<char*> plugboard;
	plugboard.push_back(plugOne);
	plugboard.push_back(plugTwo);
	plugboard.push_back(plugThree);
	plugboard.push_back(plugFour);
	plugboard.push_back(plugFive);
	
	/*Rotor fastRotor("i",'N',1);
	Rotor middleRotor("ii",'D',1);
	Rotor slowRotor("iii",'A',1);*/

	Rotor fastRotor("i",'L',1);
	Rotor middleRotor("ii",'Q',1);
	Rotor slowRotor("iii",'A',1);

	std::vector<Rotor> list;
	list.push_back(fastRotor);
	list.push_back(middleRotor);
	list.push_back(slowRotor);

	Enigma e(list, 'B', plugboard);

	std::cout << e.encryptString("kongsberg") << std::endl;

	return 0;
}
