#include <iostream>
#include "Input.h"
#include "SyntaxHandler.h"
#include "LogicGateSorter.h"
#include "CoordinateHandler.h"
#include "LogicGatePrinter.h"
#include "Renderer.h"

int main(){
	Input input;
	std::string thing = input.getInput();
	SyntaxHandler syntaxHandler;
	LogicGateSorter logicGateSorter;
	LogicGatePrinter printer;
	CoordinateHandler coordinateHandler;
	Renderer renderer;

	syntaxHandler.setNextHandler(&logicGateSorter);
	logicGateSorter.setNextHandler(&printer);
	printer.setNextHandler(&coordinateHandler);
	coordinateHandler.setNextHandler(&renderer);

	syntaxHandler.handle(thing);
}
