#ifndef HANDLER
#define HANDLER
#include <string>
#include "LogicGate.h"

class BaseHandler{
public:

	BaseHandler* next;

	virtual void handle(const std::string& input) {};

	virtual void handle(LogicGate* logicGate) {};

	void setNextHandler(BaseHandler* next){
		this->next = next;
	}

	void handleNext(std::string& input){
		if(next == nullptr){
			return;
		}
		next->handle(input);
	}
};

#endif
