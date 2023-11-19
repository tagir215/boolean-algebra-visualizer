#ifndef LOGICGATEHELPER
#define LOGICGATEHELPER
#include "LogicGate.h"
#include <vector>
#include "Signal.h"

class LogicGateHelper {
public:
	static void gatesToVector(LogicGate* g, std::vector<LogicGate*>& v){
		v.push_back(g);			
		for(Signal* s : g->inputs){
			if(LogicGate* gate = dynamic_cast<LogicGate*>(s)){
				gatesToVector(gate,v);
			}
		}
	}

};
#endif
