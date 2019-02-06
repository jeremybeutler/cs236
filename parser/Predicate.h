#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <sstream>
#include <vector>

class Predicate
{
private:
		std::string type;
    std::string id;
    std::vector<std::string> list;
public:
    Predicate(std::string type, std::string id, std::vector<std::string> list)
			: type(type), id(id), list(list) {}

    std::string toString()
    {
        std::stringstream out;
        return out.str();
    }

};

#endif // PREDICATE_H
