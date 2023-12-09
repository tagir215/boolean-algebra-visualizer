#ifndef HANDLER
#define HANDLER
#include <string>
#include "LogicGate.h"
#include <iostream>

class BaseHandler{
public:

	BaseHandler* next = nullptr;

    //logiikka minkä handleri suorittaa
	virtual void handle(const std::string& input) {};

    //logiikka minkä handleri suorittaa loggiikka portti inputista
	virtual void handle(LogicGate* logicGate) {};

    //asettaa seuraavan handlerin
	void setNextHandler(BaseHandler* next){
		this->next = next;
	}

    //aloittaa seuraavan handlerin toiminnon ketjussa
	template <typename T>
	void handleNext(T input){
		if(next == nullptr){
			std::cout<<"0";
			return;
		}
		next->handle(input);
	}
};

#endif
