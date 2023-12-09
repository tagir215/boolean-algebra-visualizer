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
    //renderöi portit
	void renderLogicGates(LogicGate* rootGate) override{
		int top = 1000;
		int bottom = 0;
		int right = 0;
		findBorders(rootGate,&top,&bottom,&right);
		std::string xString(right+17,' ');
		xString += '~';
		const int canvasHeight = bottom-top+20;
		std::vector<std::string>canvas;
		for(int i=0; i<canvasHeight; i++){
		    canvas.push_back(xString);
		}

		fillCanvas(canvas, rootGate);
		fillEnd(canvas, rootGate);
		renderCanvas(canvas);
	}
private:
    const char invertedChar = '!';
    const int invertedDistance = 1;

    //etsii rajakohdat logiikkaportti struktuurista
    void findBorders(LogicGate* gate, int* top, int* bottom, int* right){
        for(Signal* s : gate->inputs){
	        if(s->y < *top){ 
		    *top = s->y;
		}
           	if(s->y > *bottom){
		    *bottom = s->y;
		}
		if(s->x > *right){
		    *right = s->x;
		}
            if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
                findBorders(g,top,bottom,right);
            }
        }
    }

    //laittaa canvas stringeihin sisältöä
	void fillCanvas(std::vector<std::string>& canvas, LogicGate* gate){
		canvas[gate->y][gate->x] = gate->getType();
        if(gate->inverted){
            canvas[gate->y][gate->x+invertedDistance] = invertedChar;
        }

		int i=0;
		for(Signal* s : gate->inputs){
			if(LogicGate* g = dynamic_cast<LogicGate*>(s)){
				fillCanvas(canvas,g);
				int o = gate->y - g->y;
                fillGateWire(canvas,g,gate);
                
			}
			else{
				canvas[s->y][s->x] = s->getType();
                if(s->inverted){
                    canvas[s->y][s->x+invertedDistance] = invertedChar;
                }
                fillGateWire(canvas,s,gate);
			}
			i++;
		}
	}


    //piirtää viivan portista tai signaalista vanhempi porttiin
    void fillGateWire(std::vector<std::string>& canvas, Signal* child, LogicGate* parent){
        int dist = parent->x - child->x;
        int middle = dist/2;
        if(dynamic_cast<LogicGate*>(child)){
	    middle = middle + 1;
        }
        for(int i=1; i<middle; i++){
            int x = child->x+i;
            int y = child->y;
            if(i==1){
                if(canvas[y][x] == ' ')
                    canvas[y][x] = '.';
            }else{
                if(canvas[y][x] == ' ')
                    canvas[y][x] = '_';
            }
        }
        int offsetY = parent->y - child->y;
        int childY = child->y;
        if(offsetY < 0){
            childY++;
        }
        while(offsetY!=0){
            canvas[childY+offsetY][child->x+middle]='|';
            offsetY += offsetY<0 ? 1 : -1;
        }

        for(int i=middle+1; i<dist; i++){
            int x = child->x+i;
            int y = parent->y;
            if(i==dist-1){
                canvas[y][x] = '.';
            }else{
                if(canvas[y][x] == ' ')
                    canvas[y][x] = '_';
            }
        }
    }


    //renderöi lopullisen tuotoksen
	void renderCanvas(std::vector<std::string>& canvas){
		for(std::string s : canvas){
			std::cout<<s<<std::endl;
		}
	}

    //piirtää vielä yhden viivan root porttiin koska viivat on yleensä piirretty lapsista 
    //vanhempiin
    void fillEnd(std::vector<std::string>& canvas, LogicGate* root){
        for(int i=1; i<10; i++){
	    char c = i == 1 ? '.' : '_';
            if(i==1) c = '.';
            canvas[root->y][root->x+i] = c;
        }
    }

};

#endif
