#include "rotor.h"

/*
*	The rotor wiring table is hardcoded depending on which name is given to the constructor.
*	I copied the wiring table from http://users.telenet.be/d.rijmenants/en/enigmatech.htm#wiringtables
*
*/
Rotor::Rotor(std::string name, char initialVal, int initialOffset){
	value = ((int)initialVal)-65;
	offset = initialOffset-1;
	if(name.compare("i") == 0){
		turnover = ((int)'R')-65;
		alphabetMap = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
	} else if(name.compare("ii") == 0){
		turnover = ((int)'F')-65;
		alphabetMap = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
	} else if(name.compare("iii") == 0){
		turnover = ((int)'W')-65;
		alphabetMap = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
	} else if(name.compare("iv") == 0){
		turnover = ((int)'K')-65;
		alphabetMap = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
	} else if(name.compare("v") == 0){
		turnover = ((int)'A')-65;
		alphabetMap = "VZBRGITYUPSDNHLXAWMJQOFECK";
	}
}

/*
*	This function emulates sending the signal backwards through a rotor.
*	It needs to find which position in the alphabetMap the input is found at.
*/
int Rotor::inverse(int input){
	int offsetInput = (input + value - offset) % 26;
	if(offsetInput < 0){
		offsetInput = 26 + offsetInput;
	}

	int mappedSignal = alphabetMap.find((char)offsetInput+65);

	int offsetOutput = (mappedSignal - value + offset) % 26;
	if(offsetOutput < 0){
		offsetOutput = 26 + offsetOutput;
	}
	return offsetOutput;
}

/*
*	This function emulates sending the signal through a rotor.
*	It needs to find the letter at the position "input" in the alphabetMap
*/
int Rotor::encode(int input){
	int offsetInput = (input + value - offset) % 26;
	if(offsetInput < 0){
		offsetInput = 26 + offsetInput;
	}
	int mappedSignal = ((int)alphabetMap[offsetInput])-65;
	
	int offsetOutput = (mappedSignal - value + offset) % 26;
	if(offsetOutput < 0){
		offsetOutput = 26 + offsetOutput;
	}
	return offsetOutput;
}

bool Rotor::step(){
	value = (value + 1) % 26;
	return value == turnover;
}
