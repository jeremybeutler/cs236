#ifndef PREDICATE_H
#define PREDICATE_H
#include "../lexer/Token.h"
#include "Parameter.h"
#include "Rule.h"
#include "Facts.h"

#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>
#include <cctype>
#include <vector>

class Predicate
{
private:
	std::string type;
    std::string id;
    std::vector<std::string> list;
public:
    Predicate(std::string type, std::string id, std::vector<std::string> list) : type(type), id(id), list(list) {}
    
    std::string toString()
    {
        std::stringstream out;
        return out.str();
    }
	
};

#endif // PREDICATE_H
