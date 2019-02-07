#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <sstream>

#include <vector>

class DatalogProgram
{
private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
public:
    DatalogProgram(std::vector<Predicate> schemes, std::vector<Predicate> facts, std::vector<Rule> rules, std::vector<Predicate> queries)
        : schemes(schemes), facts(facts), rules(rules), queries(queries) {}

    std::string schemesToString()
    {
        std::stringstream out;
        out << "Schemes(" << schemes.size() << "):" << std::endl;
        for (unsigned int i = 0; i < schemes.size(); i++)
        {
          out << "\t" << schemes.at(i).toString() << std::endl;
        }
        return out.str();
    }

    std::string factsToString()
    {
        std::stringstream out;
        out << "Facts(" << facts.size() << "):" << std::endl;
        for (unsigned int i = 0; i < facts.size(); i++)
        {
          out << "\t" << facts.at(i).toString() << std::endl;
        }
        return out.str();
    }

    std::string rulesToString()
    {
        std::stringstream out;
        out << "Rules(" << rules.size() << "):" << std::endl;
        for (unsigned int i = 0; i < rules.size(); i++)
        {
          out << "\t" << rules.at(i).toString() << std::endl;
        }
        return out.str();
    }

    std::string queriesToString()
    {
        std::stringstream out;
        out << "Queries(" << queries.size() << "):" << std::endl;
        for (unsigned int i = 0; i < queries.size(); i++)
        {
          out << "\t" << queries.at(i).toString() << "?" << std::endl;
        }
        return out.str();
    }

    std::string toString()
    {
        std::stringstream out;
        out << schemesToString() << factsToString() << rulesToString() << queriesToString();
        return out.str();
    }

};

#endif // DATALOG_PROGRAM_H
