#ifndef COORDINATE_HANDLER
#define COORDINATE_HANDLER
#include "BaseHandler.h"
#include <vector>
#include <queue>

class CoordinateHandler : public BaseHandler{
public:
	void handle(LogicGate* logicGate) override;


private:
	const int WIRE_DIST = 9;
	const int SCALE = 12;

	int setX(LogicGate* gate, int d);

	void set0(LogicGate* gate, int x);

	void setBaseY(LogicGate* gate, int y);

	void moveGate(LogicGate* gate, int translateY);

	void handleCollisions(LogicGate* gate);

	bool checkIfCollides(LogicGate* gate1, LogicGate* gate2);

};
#endif

