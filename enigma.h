#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <vector>
#include "rotor.h"
#include <tuple>

class Enigma{
public:
	Enigma(std::vector<Rotor> _rotorList, char reflector, std::vector<char*> _plugboard);
	std::string encryptString(std::string);
private:
	int sendSignalThroughPlugboard(int signal);
	char encryptChar(char c);
	int reflect(int i);
	std::vector<Rotor> rotorList;
	bool doubleStep = false;
	void step();
	char toChar(int val, bool uppercase);
	std::vector<char*> plugboard;
	std::string reflectorString;
};

#endif