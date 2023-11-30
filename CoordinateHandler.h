#ifndef COORDINATE_HANDLER
#define COORDINATE_HANDLER
#include "BaseHandler.h"
#include <vector>
#include <queue>

class CoordinateHandler : public BaseHandler{
public:
	void handle(LogicGate* logicGate) override{
		int maxD = setX(logicGate, 0);
		set0(logicGate,(maxD+1)*SCALE);
		setBaseY(logicGate,10);
		handleCollisions(logicGate);

		next->handle(logicGate);
	}


private:
	const int WIRE_DIST = 6;
	const int SCALE = 9;

	//sets x for all gates and signals
	int setX(LogicGate* gate, int d){
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


	//translates everything to fit the canvas
	void set0(LogicGate* gate, int x){
		gate->x = x-gate->x*SCALE;
		for(Signal* s : gate->inputs){
			if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
				set0(g,x);
			}else{
				s->x = gate->x -WIRE_DIST;
			}
		}
	}

	//sets initial ideal y for every gate and signal
	void setBaseY(LogicGate* gate, int y){
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

	//moves gate and it's children 
	void moveGate(LogicGate* gate, int translateY){
		gate->y += translateY;
		for(Signal* s : gate->inputs){
			if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
				moveGate(gate,translateY);
			}
			else{
				s->y += translateY;
			}
		}
	}

	//checks collisions and moves gates if needed
	void handleCollisions(LogicGate* gate){
		std::queue<LogicGate*>gateQueue;
		int middle = gate->inputs.size()/2;
		int i = -middle;
		for(Signal* s : gate->inputs){
			if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
				handleCollisions(g);
				gateQueue.push(g);
			}
			if(gateQueue.size()>1){
				int direction1 = gateQueue.front()->y <=0 ? -1 : 1;
				int direction2 = gateQueue.back()->y <=0 ? -1 : 1;
				while(checkIfCollides(gateQueue.front(),gateQueue.back())){
					if(direction1!=direction2){
						moveGate(gateQueue.front(),direction1);
						moveGate(gateQueue.back(),direction2);
					}else{
						if(direction1>0){
							moveGate(gateQueue.back(),direction1);
						}else{
							moveGate(gateQueue.front(),direction1);
						}
					}
				}
				gateQueue.pop();

			}
			i++;
		}
	}

	//checks if gates on same x collides. y is inverted
	bool checkIfCollides(LogicGate* gate1, LogicGate* gate2){
		LogicGate* lower = gate1->y > gate2->y ? gate1 : gate2;	
		LogicGate* higher = gate1->y < gate2->y ? gate1 : gate2;	
		int yl = lower->y - lower->inputs.size()/2;
		int yh = higher->y + higher->inputs.size()/2;
		return yl <= yh;
	}
};

#endif

