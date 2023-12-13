#include "Input.h"

Input::Input() {
	std::cout << "BOOLEN ALGEBRA"<< std::endl;
	std::cout << "kirjoita boolen algebra lauseke esim. AB'+(AC+C)"<< std::endl;

}

std::string Input::getInput(){
	std::string string = "";
	std::cin >> string;
	return string;

}
