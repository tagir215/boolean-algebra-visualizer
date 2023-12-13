#ifndef LOGIC_GATE_SORTER
#define LOGIC_GATE_SORTER

#include "BaseHandler.h"
#include <string>
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include "LogicGate.h"
#include "Wire.h"

class LogicGateSorter : public BaseHandler {
public:
    LogicGateSorter() {}

    void handle(const std::string& input) override;

private:
    LogicGate* syntaxToGate(const std::string& input, int& i);

    Signal* defineSignal(std::queue<Signal*>& signalQueue);

    LogicGate* andGate(std::queue<Signal*>& signalQueue);

    LogicGate* defineFinalGate(std::queue<Signal*>& signalQueue);
};

#endif

