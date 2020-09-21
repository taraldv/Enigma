#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>

class Rotor{
public:
	Rotor(std::string name, char initialVal, int initialOffset);
	char getVal();
	bool step();
	int encode(int input);
	int inverse(int input);
private:
	int offset;
	int value;
	int turnover;
	std::string sub;
};

#endif