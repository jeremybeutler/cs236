#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

class Predicate
{
private:
	std::string _type;
	std::string _id;
	std::vector<Parameter> _list;
	std::vector<std::string> _listStr;
public:
	Predicate() {}
    Predicate(std::string _type, std::string _id, std::vector<Parameter> _list, std::vector<std::string> _listStr)
			: _type(_type), _id(_id), _list(_list), _listStr(_listStr) {}

    std::string type() const
	{
		return _type;
	}

	std::string id() const
	{
		return _id;
	}

	std::vector<Parameter> list() const
	{
		return _list;
	}

	std::vector<std::string> listStr() const
	{
		return _listStr;
	}	

	std::string toString() const
    {
        std::stringstream out;
		if (_type == "PREDICATE")
		{
			out << _id << "(";
			for (unsigned int i = 0; i < _list.size(); i++)
			{
				out << _list.at(i).toString();
				if (i < _list.size() - 1) out << ",";
			}
			out << ")";
		}
		else if (_type == "HEAD_PREDICATE")
		{
			out << _id << "(";
			for (unsigned int i = 0; i < _listStr.size(); i++)
			{
				out << _listStr.at(i);
				if (i < _listStr.size() - 1) out << ",";
			}
			out << ")";
		}

        return out.str();
    }

};

#endif // PREDICATE_H
