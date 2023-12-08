#ifndef HANDLER
#define HANDLER
#include <string>
#include "LogicGate.h"

class BaseHandler{
public:

	BaseHandler* next;

    //logiikka minkä handleri suorittaa
	virtual void handle(const std::string& input) {};

    //logiikka minkä handleri suorittaa loggiikka portti inputista
	virtual void handle(LogicGate* logicGate) {};

    //asettaa seuraavan handlerin
	void setNextHandler(BaseHandler* next){
		this->next = next;
	}

    //aloittaa seuraavan handlerin toiminnon ketjussa
	void handleNext(std::string& input){
		if(next == nullptr){
			return;
		}
		next->handle(input);
	}
};

#endif
