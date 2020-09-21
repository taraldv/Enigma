#include "enigma.h"

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

int Enigma::reflect(int i){
	return ((int)reflectorString[i])-65;
}

char Enigma::toChar(int val){
	return val+65;
}

std::string Enigma::encryptString(std::string s){
	std::string output = "";
	int x = 0;
	for(int i=0;i<s.size();i++){
		if(s[i] == ' '){
			continue;
		}
		if(x > 0 && x % 5 == 0){
			output = output + " ";
		}
		x++;
		output = output + encryptChar(s[i]);
	}
	return output;
}

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

char Enigma::encryptChar(char c){
	step();
	int signal;
	if(c < 97){
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

	return toChar(signal);

}

void Enigma::step(){
	if(rotorList[0].step()){
		//doubleStep = true;
		if(rotorList[1].step()){
			rotorList[2].step();
		}
	} else if(doubleStep){
		if(rotorList[1].step()){
			rotorList[2].step();
		}
		doubleStep = false;
	}

	/*std::cout << "" << toChar(rotorList[2].getVal());
	std::cout << " " << toChar(rotorList[1].getVal());
	std::cout << " " << toChar(rotorList[0].getVal()) << std::endl;*/
}