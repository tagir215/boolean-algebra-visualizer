#include "CoordinateHandler.h"


void CoordinateHandler::handle(LogicGate* logicGate) {
	int maxD = setX(logicGate, 0);
	set0(logicGate,(maxD+1)*SCALE);
	setBaseY(logicGate,10);
	handleCollisions(logicGate);
	handleNext(logicGate);
}


int CoordinateHandler::setX(LogicGate* gate, int d){
	gate->x = d;
	int maxD = d;
	for(Signal* s : gate->inputs){
		if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
			int x = setX(g,d+1);
			maxD = (maxD > x) ? maxD : x; 
		}else{
			s->x -= WIRE_DIST;
		}
	}
	return maxD;	
}


void CoordinateHandler::set0(LogicGate* gate, int x){
	gate->x = x-gate->x*SCALE;
	for(Signal* s : gate->inputs){
		if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
			set0(g,x);
		}else{
			s->x = gate->x -WIRE_DIST;
		}
	}
}

void CoordinateHandler::setBaseY(LogicGate* gate, int y){
	gate->y = y;
	int middle = gate->inputs.size()/2;
	int skip = -1;
	if (gate->inputs.size()%2==0){
		skip = middle;
	}
	int i =0;
	for(Signal* s : gate->inputs){
		if(i==skip) i++;
		int y2 = gate->y - middle + i;	
		if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
			setBaseY(g,y2);
		}
		else{
			s->y = y2;
		}
		i++;
	}

}

void CoordinateHandler::CoordinateHandler::moveGate(LogicGate* gate, int translateY){
	gate->y += translateY;
	for(Signal* s : gate->inputs){
		if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
			moveGate(g,translateY);
		}
		else{
			s->y += translateY;
		}
	}
}

void CoordinateHandler::handleCollisions(LogicGate* gate){
	std::queue<LogicGate*>gateQueue;
	int i=0;
	for(Signal* s : gate->inputs){
		if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
			handleCollisions(g);
			gateQueue.push(g);
		}
		if(gateQueue.size()>1){
			LogicGate* gate1 = gateQueue.front();
			LogicGate* gate2 = gateQueue.back();
			while(checkIfCollides(gate1,gate2)){
				if(i==0){
					moveGate(gate1,-1);
				}else{
					moveGate(gate2,1);
				}
			}
			gateQueue.pop();

		}
		i++;
	}
}

bool CoordinateHandler::checkIfCollides(LogicGate* gate1, LogicGate* gate2){
	LogicGate* lower = gate1->y > gate2->y ? gate1 : gate2;	
	LogicGate* higher = gate1->y < gate2->y ? gate1 : gate2;	
	int yl = lower->y - lower->inputs.size()/2;
	int yh = higher->y + higher->inputs.size()/2;
	return yl-1 <= yh;
}
