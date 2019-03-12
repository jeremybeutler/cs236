#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sstream>
#include <map>
#include "../parser/DatalogProgram.h"
#include "../parser/Predicate.h"
#include "../parser/Rule.h"
#include "Relation.h"


class Database : public std::map<std::string, Relation>
{
public:
    Database() {}
};

#endif // DATABASE_H
