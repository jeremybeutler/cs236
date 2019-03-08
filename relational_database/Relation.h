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

};

#endif // RELATION_H
