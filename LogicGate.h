#ifndef LOGIC_GATE
#define LOGIC_GATE
#include <list>
#include "Signal.h"

class LogicGate : public Signal{
public:
	char type;
	std::list<Signal*>inputs;

	LogicGate(){
		type = '\0';
	}

	char getType() override {
		return type;
	}
};

#endif
