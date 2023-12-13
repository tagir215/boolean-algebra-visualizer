#include "GarbageCollector.h"

void GarbageCollector::deleteGates(LogicGate* gate){
	for(Signal* s : gate->inputs){
		if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
			deleteGates(g);
		}
		else{
			delete s;
		}
	}
	delete gate;

}

