#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

class Predicate
{
private:
		std::string type;
    std::string id;
    std::vector<Parameter> list;
		std::vector<std::string> listStr;
public:
    Predicate(std::string type, std::string id, std::vector<Parameter> list, std::vector<std::string> listStr)
			: type(type), id(id), list(list), listStr(listStr) {}

    std::string toString()
    {
        std::stringstream out;
				if (type == "PREDICATE")
				{
					out << id << "(";
					for (unsigned int i = 0; i < list.size(); i++)
					{
						out << list.at(i).toString();
						if (i < list.size() - 1) out << ",";
					}
					out << ")";
				}
				else if (type == "HEAD_PREDICATE")
				{
					out << id << "(";
					for (unsigned int i = 0; i < listStr.size(); i++)
					{
						out << listStr.at(i);
						if (i < listStr.size() - 1) out << ",";
					}
					out << ")";
				}

        return out.str();
    }

};

#endif // PREDICATE_H
