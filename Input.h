#include <iostream>

//ottaa käyttäjän inputit talteen
class Input{
public:
	Input(){
		std::cout << "BOOLEN ALGEBRA"<< std::endl;
		std::cout << "kirjoita boolen algebra lauseke esim. AB'+(AC+C)"<< std::endl;
	}
	
	std::string getInput(){
		std::string string = "";
		std::cin >> string;
		return string;
	}
};
