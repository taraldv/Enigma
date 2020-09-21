#include "rotor.h"

Rotor::Rotor(std::string name, char initialVal, int initialOffset){
	value = ((int)initialVal)-65;
	offset = initialOffset-1;
	if(name.compare("i") == 0){
		turnover = ((int)'R')-65;
		sub = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
	} else if(name.compare("ii") == 0){
		turnover = ((int)'F')-65;
		sub = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
	} else if(name.compare("iii") == 0){
		turnover = ((int)'W')-65;
		sub = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
	} else if(name.compare("iv") == 0){
		turnover = ((int)'K')-65;
		sub = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
	} else if(name.compare("v") == 0){
		turnover = ((int)'A')-65;
		sub = "VZBRGITYUPSDNHLXAWMJQOFECK";
	}
}

int Rotor::inverse(int input){
	input = (input + value - offset) % 26;
	if(input < 0){
		input = 26 + input;
	}
	int index = sub.find((char)input+65);
	index = (index - value + offset) % 26;
	if(index < 0){
		index = 26 + index;
	}
	return index;
}

int Rotor::encode(int input){
	int index = (input + value - offset) % 26;
	if(index < 0){
		index = 26 + index;
	}
	int newIndex = ((int)sub[index])-65;
	int output = (newIndex - value + offset) % 26;
	if(output < 0){
		output = 26 + output;
	}
	return output;
}

//Used to debug double stepping
char Rotor::getVal(){
	return value;
}

bool Rotor::step(){
	value = (value + 1) % 26;
	return value == turnover;
}
