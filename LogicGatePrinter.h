#ifndef LOGIC_GATE_PRINTER
#define LOGIC_GATE_PRINTER

//tämä on vain debuggaamista varten. Se printtaa porttien struktuurit
class LogicGatePrinter : public BaseHandler{
public:
	void handle(LogicGate* logicGate) override{
		printGate(logicGate);
		next->handle(logicGate);
	}
private:
	void printGate(LogicGate* g){
		std::cout<<g->getType()<<" ("<<g->x<<","<<g->y<<") ";
		std::queue<LogicGate*>parentGates;
		for(Signal* s : g->inputs){
			if(!s->inverted)
				std::cout<<s->getType();
			else
				std::cout<<"(NOT)"<<s->getType();
			if(LogicGate* gate = dynamic_cast<LogicGate*>(s)){
				parentGates.push(gate);
			}
		}
		std::cout<<std::endl;
		while(parentGates.size()>0){
			printGate(parentGates.front());
			parentGates.pop();
		}
	}
};

#endif
