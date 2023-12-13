#ifndef SYNTAX_HELPER
#define SYNTAX_HELPER

#include <string>
#include <vector>
#include <iostream>
#include "BaseHandler.h"

class SyntaxHandler : public BaseHandler {
public:
    void handle(const std::string& input) override;

private:
    std::vector<char> acceptedStuff = {'+', '*', '\'', '(', ')'};

    bool checkSyntax(const std::string& input);

    bool checkCharacter(const char& ch);
};

#endif

