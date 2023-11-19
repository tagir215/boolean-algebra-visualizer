#ifndef COORDINATE_HANDLER
#define COORDINATE_HANDLER
#include "BaseHandler.h"
#include <vector>

class CoordinateHandler : public BaseHandler{
public:
	void handle(LogicGate* logicGate) override{
		int maxD = setX(logicGate, 0);
		set0(logicGate,(maxD+1)*SCALE);
		int xy[100][100] = {};
		setY(logicGate,xy);
		next->handle(logicGate);
	}


private:
	const int WIRE_DIST = 7;
	const int SCALE = 9;

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

	int nextAvailableY(int x,int (&xy)[100][100]){
		for(int i=0; i<100; i++){
			int point = xy[x][i];
			if(point == 0){
				return i;
			}

		}
		return 0;
	}
	void fillMap(int x, int width, int y, int (&xy)[100][100]){
		x = x-100;
		width += 50;
		if(x<0) x =0;
		while(x<=width){
			xy[x][y] = 1;
			x++;
		}
	}

	int setY(LogicGate* gate, int (&xy)[100][100]){
		int topY=0;
		int bottomY=0;
		int nextY = nextAvailableY(gate->x,xy);

		int middleI = -1;
		if(gate->inputs.size()%2==0){
			middleI = gate->inputs.size()/2;
		}

		int i=0;
		for(Signal* s : gate->inputs){
			int y = 0;		
			if(i==middleI){
				int middle = nextAvailableY(s->x,xy);
				fillMap(s->x,SCALE,middle,xy);
			}
			if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
				y = setY(g,xy);
				fillMap(s->x,SCALE,s->y,xy);
			}
			else{
				y = nextAvailableY(s->x,xy);
				s->y = y;
				fillMap(s->x,2,s->y,xy);
			}

			if(i==0){
				topY = y;
			}
			else if(i==gate->inputs.size()-1){
				bottomY = y;
				fillMap(s->x,2,s->y+1,xy);
			}
			i++;
		}

		int height = bottomY-topY;
		if(height>0){
			int newY = topY + height/2;
			gate->y = newY;
		}else{
			gate->y = nextY;
		}
		fillMap(gate->x,SCALE,gate->y,xy);

		return gate->y;
	}


};

#endif

