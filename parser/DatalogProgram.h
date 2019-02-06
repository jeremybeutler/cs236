#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include "../lexer/Token.h"
#include "Parser.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <vector>

class DatalogProgram
{
private:
		std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
public:
    DatalogProgram(std::vector<Predicate> schemes, std::vector<Predicate> facts, std::vector<Rule> rules, std::vector<Predicate> queries) : schemes(schemes), facts(facts), rules(rules), queries(queries) {}

};

#endif // DATALOG_PROGRAM_H
