#ifndef RELATION_H
#define RELATION_H

#include <string>
#include <sstream>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

class Relation
{
private:
    std::string name;
    Scheme scheme;
    std::set<Tuple> tuples; 
    
public:
    Relation() : scheme() {}
    Relation(std::string name, Scheme scheme, std::set<Tuple> tuples)
			: name(name), scheme(scheme), tuples(tuples) {}

    void addTuple(Tuple t)
    {
        tuples.insert(t);
    }

    std::string toString()
    {
        std::stringstream out;
        for (Tuple tuple : tuples) 
        {
            for (unsigned int i = 0; i < scheme.size(); ++i)
            {
                out << scheme.at(i) << "=" << tuple.at(i);
                out << ((i == scheme.size() - 1) ? ", " : "");
            }
            out << std::endl;
        }
        return out.str();
    }
};

#endif // RELATION_H
