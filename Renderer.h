#ifndef RENDERER
#define RENDERER
#include "LogicGate.h"
#include "BaseHandler.h"

class Renderer : public BaseHandler{
public:
	void handle(LogicGate* logicGate) override{
		renderLogicGates(logicGate);
	}
	virtual void renderLogicGates(LogicGate* rootGate) = 0;
};

#endif
