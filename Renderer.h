#ifndef RENDERER
#define RENDERER
#include "LogicGate.h"
#include "BaseHandler.h"
#include "Signal.h"
#include <string>
#include <iostream>
#include "GarbageCollector.h"
#include <vector>


class Renderer : public BaseHandler{

public:
	void handle(LogicGate* logicGate) override;
private:
	const char invertedChar = '!';
	const int invertedDistance = 1;

	
	void render(LogicGate* rootGate);

	void findBorders(LogicGate* gate, int* top, int* bottom, int* right);

	void fillCanvas(std::vector<std::string>& canvas, LogicGate* gate);


	void fillGateWire(std::vector<std::string>& canvas, Signal* child, LogicGate* parent);

	void renderCanvas(std::vector<std::string>& canvas);

	void fillEnd(std::vector<std::string>& canvas, LogicGate* root);

};

#endif
