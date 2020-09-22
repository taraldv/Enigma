#include <iostream>
#include "enigma.h"

int main(int argc, char const *argv[])
{
	//Array of plugboard settings
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

	//This engima does not check if a letter is only used once in a plugboard.
	std::vector<char*> plugboard;
	plugboard.push_back(plugOne);
	plugboard.push_back(plugTwo);
	plugboard.push_back(plugThree);
	plugboard.push_back(plugFour);
	plugboard.push_back(plugFive);
	plugboard.push_back(plugSix);
	plugboard.push_back(plugSeven);
	plugboard.push_back(plugEight);
	plugboard.push_back(plugNine);
	plugboard.push_back(plugTen);

	Rotor fastRotor("iii",'N',5);
	Rotor middleRotor("iv",'D',9);
	Rotor slowRotor("v",'A',11);

	//The fast rotor first to the vector.
	std::vector<Rotor> list;
	list.push_back(fastRotor);
	list.push_back(middleRotor);
	list.push_back(slowRotor);

	//Create two objects with the same settings, one for encryption, and one for decryption.
	Enigma encryption(list, 'B', plugboard);
	Enigma decryption(list, 'B', plugboard);

	std::string original = "kongsberg";
	std::string kryptert = encryption.encryptString(original);
	std::string dekryptert = decryption.encryptString(kryptert);
	std::cout << "original: " << original << std::endl;
	std::cout << "kryptert: " << kryptert << std::endl;
	std::cout << "dekryptert: " << dekryptert << std::endl;
	return 0;
}

