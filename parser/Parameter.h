#ifndef PARAMETER_H
#define PARAMETER_H
#include "../lexer/Token.h"
#include "Predicate.h"
#include "Rule.h"
#include "Facts.h"

#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>
#include <cctype>
#include <vector>

class Parameter
{
private:
    std::string type;
    std::string param;
	
public:
    Parameter(std::string type, std::string param) : type(type), param(param)  {}

	std::string toString()
    {
        std::stringstream out;
        return out.str();
    }
};

#endif // PARAMETER_H
