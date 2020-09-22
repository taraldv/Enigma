#include "enigma.h"

/*
*	The rotors are stored in a vector, starting with the fast rotor at index 0
*/
Enigma::Enigma(std::vector<Rotor> _rotorList, char reflector, std::vector<char*> _plugboard){
	//I used the default wide reflectors for Wehrmacht and Luftwaffe:
	if(reflector == 'B'){
		reflectorString = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
	} else if(reflector == 'C'){
		reflectorString = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
	}
	rotorList = _rotorList;
	plugboard = _plugboard;
}


/*
*	Function to emulate the reflector and the end of the three rotors
*/
int Enigma::reflect(int i){
	return ((int)reflectorString[i])-65;
}

/*
*	Function to convert a 0-25 int range to a char.
*/
char Enigma::toChar(int val, bool uppercase){
	if(uppercase){
		return val+65;
	}
	return val+97;
}

/*
*	Iterates through the string and encrypts each char.
*	It skips spaces, and produces one long string.
*/
std::string Enigma::encryptString(std::string s){
	std::string output = "";
	for(int i=0;i<s.size();i++){
		if(s[i] == ' '){
			continue;
		}
		output = output + encryptChar(s[i]);
	}
	return output;
}

/*
*	This function loops through all the plugboard settings,
*	and if one of them matches the signal, it changes the signal
*	to the connected letter.
*/
int Enigma::sendSignalThroughPlugboard(int signal){
	if(plugboard.size()>0){
		for(int i=0;i<plugboard.size();i++){
			if(signal == (int)plugboard[i][0]-65){
				return (int)plugboard[i][1]-65;
			}
			if(signal == (int)plugboard[i][1]-65){
				return (int)plugboard[i][0]-65;
			}
		}
	}
	return signal;
}

/*
* This function emulates a button press and 
* the light flashing on a new letter.
*/
char Enigma::encryptChar(char c){
	//Increment the rotor by one before sending the signal through.
	step();
	int signal;

	//Convert the char to int in range 0-25
	bool uppercase = c < 97;
	if(uppercase){
		signal = c-65;
	} else {
		signal = c-97;
	}

	//Sends the signal through the plugboard
	signal = sendSignalThroughPlugboard(signal);

	//Sends the signal through the rotors
	for(int i=0;i<rotorList.size();i++){
		signal = rotorList[i].encode(signal);
	}

	//Sends the signal through the reflector
	signal = reflect(signal);

	//Sends the signal through the rotors inversed
	for(int j=rotorList.size()-1;j>=0;j--){
		signal = rotorList[j].inverse(signal);
	}

	//Sends the signal through the plugboard again
	signal = sendSignalThroughPlugboard(signal);

	//Convert the int back to letter and return it
	return toChar(signal,uppercase);

}

//Will increment the rotors by one, and included the double step feature.
void Enigma::step(){
	if(rotorList[0].step()){
		/*
		* Whenever the middle rotor is stepped, 
		* doubleStep is set to true, 
		* to make sure it also steps in the next increment
		*/
		doubleStep = true;
		if(rotorList[1].step()){
			rotorList[2].step();
		}
	} else if(doubleStep){
		if(rotorList[1].step()){
			rotorList[2].step();
		}
		doubleStep = false;
	}
}