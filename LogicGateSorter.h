#ifndef LOGIC_GATE_SORTER 
#define LOGIC_GATE_SORTER 
#include "BaseHandler.h"
#include <string>
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include "LogicGate.h"
#include "Wire.h"

class LogicGateSorter : public BaseHandler{

public:
	LogicGateSorter(){}
	
	void handle(const std::string& input) override{
		int i = 0;
		LogicGate* gate = syntaxToGate(input, i);
		next->handle(gate);
	}


private:

	LogicGate* syntaxToGate(const std::string& input, int& i) {
		std::queue<Signal*>andQueue;
		std::queue<Signal*>orQueue;
		
		while(i<input.length()){
			char ch = input[i];
			if(isalpha(ch)){
				andQueue.push(new Wire(ch));
			}
			else if(ch=='\''){
				Signal* s = andQueue.back();
				s->inverted = !s->inverted;
			}
			else if(ch=='+'){
				Signal* signal = defineSignal(andQueue);
				orQueue.push(signal);
			}
			else if(ch=='('){
				i++;
				LogicGate* g = syntaxToGate(input,i);
				andQueue.push(g);
			}
			else if(ch==')'){
				break;
			}
			i++;
		}
		if(andQueue.size()>0){
			Signal* signal = defineSignal(andQueue);
			orQueue.push(signal);
		}

		LogicGate* finalGate = defineFinalGate(orQueue);
		return finalGate;
	}
	


	Signal* defineSignal(std::queue<Signal*>& signalQueue){
		if(signalQueue.size()==1){
			Signal* signal = signalQueue.front();
			signalQueue.pop();
			return signal;
		}
		else{
			LogicGate* gate = andGate(signalQueue);
			return gate;
		}
	}

	LogicGate* andGate(std::queue<Signal*>& signalQueue){
		LogicGate* gate = new LogicGate();
		gate->type='&';
		while(signalQueue.size()>0){
			gate->inputs.push_back(signalQueue.front());
			signalQueue.pop();
		}
		return gate;
	}

	LogicGate* defineFinalGate(std::queue<Signal*>& signalQueue){
		if(signalQueue.size()>1){
			LogicGate* gate = new LogicGate();
			gate->type = '+';
			while(signalQueue.size()>0){
				gate->inputs.push_back(signalQueue.front());
				signalQueue.pop();
			}
			return gate;
		}
		else{
			LogicGate* gate = 
				dynamic_cast<LogicGate*>(signalQueue.front());
			gate->type = '&';
			return gate;
		}
	}


};

#endif
