#ifndef GARBAGE
#define GARBAGE

class GarbageCollector{

public:
	static void deleteGates(LogicGate* gate){
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


};

#endif
