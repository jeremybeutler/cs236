#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sstream>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"

class Database
{
private:
    DatalogProgram p;
    
public:
    Database(DatalogProgram p)
			: p(p) {}

};

#endif // DATABASE_H
