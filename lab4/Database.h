#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sstream>
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Relation.h"


class Database : public std::map<std::string, Relation>
{
public:
    Database() {}
};

#endif // DATABASE_H
