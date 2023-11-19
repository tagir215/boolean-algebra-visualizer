#include <iostream>

class Input{
public:
	Input(){
		std::cout << "BOOLEN ALGEBRA"<< std::endl;
	}
	
	std::string getInput(){
		std::string string = "";
		std::cin >> string;
		return string;
	}
};
