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
	const int WIRE_DIST = 8;
	const int SCALE = 16;

    //asettaa aluksi x koordinaatit signaali elementeille
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


    //siirtää kaiken alkamaan 0 kohdasta
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

    //asettaa ideaalin y lokaation signaali elementeille
	void setBaseY(LogicGate* gate, int y){
		gate->y = y;
		int middle = gate->inputs.size()/2;
		int skip = -1;
//		if (gate->inputs.size()%2==0){
//			skip = middle;
//		}
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

    //siirtää porttia ja sen lapsia y suunnassa
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

    //tarkistaa onko portilla osumia toisiin portteihin ja siirtää portin jos on tarve
	void handleCollisions(LogicGate* gate){
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

    //ottaa kaksi porttia ja tarkistaa onko niillä osumia
	bool checkIfCollides(LogicGate* gate1, LogicGate* gate2){
		LogicGate* lower = gate1->y > gate2->y ? gate1 : gate2;	
		LogicGate* higher = gate1->y < gate2->y ? gate1 : gate2;	
		int yl = lower->y - lower->inputs.size()/2;
		int yh = higher->y + higher->inputs.size()/2;
		return yl-1 <= yh;
	}
};

#endif

