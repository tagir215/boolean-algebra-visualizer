#ifndef RENDERER_IMPL
#define RENDERER_IMPL
#include "LogicGate.h"
#include "Signal.h"
#include <string>
#include <iostream>
#include "Renderer.h"
#include <vector>

class RendererImpl : public Renderer{
public:
	//renders the logic gatess
	void renderLogicGates(LogicGate* rootGate) override{
		std::string xString = "                                           ";
		std::string canvas[20];
		for(int i=0; i<20; i++){
			canvas[i] = xString;
		}
		fillCanvas(canvas, rootGate);
		renderCanvas(canvas);
	}
private:
	//fills canvas with somehting
	void fillCanvas(std::string (&canvas)[20], LogicGate* gate){
		canvas[gate->y][gate->x] = gate->getType();
		int middle = gate->inputs.size()/2;
		int startY = gate->y-middle;
		int endY = gate->y+middle;
		fillGate(canvas,startY,endY,gate->x-1);

		int i=0;
		for(Signal* s : gate->inputs){
			if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
				fillCanvas(canvas,g);
				int ioff = -middle+i;
				int o = gate->y - g->y;
				fillWire(canvas,g,3,o+ioff);
			}
			else{
				canvas[s->y][s->x] = s->getType();
				fillWire(canvas,s,3,0);
			}
			i++;
		}
	}
	//fills gates lefts side cells
	void fillGate(std::string (&canvas)[20], int y, int endY, int x){
		while(y<=endY){
			canvas[y][x]=']';
			canvas[y][x-1]='-';
			canvas[y][x-2]='-';
			canvas[y][x-3]='-';
			y++;
		}	
	}

	//fills wire from left element to parent element
	void fillWire(std::string (&canvas)[20], Signal*s, int l,int offset){
		for(int i=1; i<l; i++){
			canvas[s->y][s->x+i] = '-';
			if(i==2 && s->inverted){
				canvas[s->y][s->x+i] = '!';
			}
		}
		while(offset!=0){
			int y = s->y+offset;
			int x = s->x+l;
			canvas[y][x] = '|';
			if(offset>0) offset--; else offset++;
		}
	}
	//renders the canvas
	void renderCanvas(std::string (&canvas)[20]){
		for(std::string s : canvas){
			std::cout<<s<<std::endl;
		}
	}

};

#endif
