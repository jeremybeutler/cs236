#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sstream>
#include <map>
#include "../parser/DatalogProgram.h"
#include "../parser/Predicate.h"
#include "../parser/Rule.h"
#include "Relation.h"


class Database
{
private:
    std::map<std::string, Relation> relationMap;
    
public:
    Database() {}
    Database(DatalogProgram& p)
    {
        create(p);
    }

    void create(DatalogProgram p)
    {
        std::vector<Predicate> schemes = p.schemes();
        std::vector<Predicate> facts = p.facts();
        std::vector<Rule> rules = p.rules();
        std::vector<Predicate> queries = p.queries();
        std::vector<std::string> domains = p.domain();

        // loop through each scheme Predicate
        for (unsigned int i = 0; i < schemes.size(); ++i)
        {
            Relation r;
            std::string name = schemes.at(i).id();
            Scheme s;
            std::set<Tuple> tuples;
            
            // loop through each Parameter in the vector of Parameters in the scheme Predicate 
            for (unsigned int j = 0; j < schemes.at(i).listStr().size(); ++j)
            {
                s.push_back(schemes.at(i).listStr().at(j));
            }
            // loop through each fact Predicate
            for (unsigned int j = 0; j < facts.size(); ++j)
            {
                if (facts.at(j).id() == name)
                {
                    Tuple t;
                    // loop through each Parameter in the vector of Parameters in the fact Predicate 
                    for (unsigned int k = 0; k < facts.at(j).listStr().size(); ++k)
                    {                            
                        t.push_back(facts.at(j).listStr().at(k));
                    }
                    tuples.insert(t);
                }
                
            }
            r = Relation(name, s, tuples);
            relationMap[name] = r;
        }
    }
};

#endif // DATABASE_H
