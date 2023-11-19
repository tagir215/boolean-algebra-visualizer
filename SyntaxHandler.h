#ifndef SYNTAX_HELPER
#define SYNTAX_HELPER

#include <string>
#include <vector>
#include <iostream>
#include "BaseHandler.h"

class SyntaxHandler : public BaseHandler{
public:	
	void handle(const std::string& input) override {
		if(checkSyntax(input)){
			next->handle(input);
		}else{
			std::cout<<"error"<<std::endl;
		}
	}
private:
	std::vector<char>acceptedStuff = {'+','*','\'','(',')'};

	bool checkSyntax(const std::string& input){

		int braceBalance = 0;

		for(const char& c : input){
			if(!checkCharacter(c)){
				return false;
			}
			if(c=='('){
				braceBalance++;
			}else if(c==')'){
				braceBalance--;
			}
		}
		if(braceBalance==0){
			return true;
		}else{
			return false;
		}
	}
	bool checkCharacter(const char& ch){
		if(isalpha(ch)){
			return true;
		}else{
			for(const char& c : acceptedStuff){
				if(ch==c) return true;
			}
			return false;
		}
	}
};

#endif 
