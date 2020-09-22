#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>

class Rotor{
public:
	Rotor(std::string name, char initialVal, int initialOffset);
	bool step();
	int encode(int input);
	int inverse(int input);
	std::string getName();
	int getValue();
	int getOffset();
private:
	int offset;
	int value;
	int turnover;
	std::string alphabetMap;
	std::string name;
};

#endif