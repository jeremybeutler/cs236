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
    DatalogProgram() : schemes(0), facts(0), rules(0), queries(0) {}

    void addScheme(Predicate scheme)
    {
        schemes.push_back(scheme);
    }

    void addFact(Predicate fact)
    {
        facts.push_back(fact);
    }

    void addRule(Rule rule)
    {
        rules.push_back(rule);
    }

    void addQuery(Predicate query)
    {
        queries.push_back(query);
    }

};

#endif // DATALOG_PROGRAM_H
