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

//tämä luokka lajittelee logiikkaportit puu data struktuuriksi
class LogicGateSorter : public BaseHandler{

public:
	LogicGateSorter(){}
	
	void handle(const std::string& input) override{
		int i = 0;
		LogicGate* gate = syntaxToGate(input, i);
		next->handle(gate);
	}


private:

    //muuttaa string inputin logiikka porteiksi
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
	


    //määrittää onko signaali pelkkä signaali vai sitten logiikkaportti
    //tässä kohtaa katsotaan vain että onko se ja portti 
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

    //luo ja portin jonosta signaaleja
	LogicGate* andGate(std::queue<Signal*>& signalQueue){
		LogicGate* gate = new LogicGate();
		gate->type='&';
		while(signalQueue.size()>0){
			gate->inputs.push_back(signalQueue.front());
			signalQueue.pop();
		}
		return gate;
	}

    //tässä kohtaa ei ole vielä tietoa onko käsiteltävissä oleva portti ja vai tai portti
    //joten se muistaakseni määritellään tässä
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
