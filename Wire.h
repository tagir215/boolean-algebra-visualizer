#ifndef WIRE
#define WIRE
#include "Signal.h"

class Wire : public Signal{
public:
	char name;
	Wire(char name){
		this->name = name;
	}
	char getType() override {
		return name;
	}
};

#endif 
