#include "SyntaxHandler.h"

void SyntaxHandler::handle(const std::string& input) {
    if (checkSyntax(input)) {
        handleNext(input);
    } else {
        std::cout << "error" << std::endl;
    }
}

bool SyntaxHandler::checkSyntax(const std::string& input) {
    int braceBalance = 0;

    for (const char& c : input) {
        if (!checkCharacter(c)) {
            return false;
        }
        if (c == '(') {
            braceBalance++;
        } else if (c == ')') {
            braceBalance--;
        }
    }
    return braceBalance == 0;
}

bool SyntaxHandler::checkCharacter(const char& ch) {
    if (isalpha(ch)) {
        return true;
    } else {
        for (const char& c : acceptedStuff) {
            if (ch == c)
                return true;
        }
        return false;
    }
}

