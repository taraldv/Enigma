#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>

class Rotor{
public:
	Rotor(std::string name, char initialVal, int initialOffset);
	bool step();
	int encode(int input);
	int inverse(int input);
private:
	int offset;
	int value;
	int turnover;
	std::string alphabetMap;
};

#endif