#ifndef RULE_H
#define RULE_H
#include "Predicate.h"

#include <string>
#include <sstream>
#include <vector>

class Rule
{
private:
	Predicate _predicateHead;
    std::vector<Predicate> _predicateList;
public:
    Rule(Predicate _predicateHead, std::vector<Predicate> _predicateList)
		: _predicateHead(_predicateHead), _predicateList(_predicateList) {}

	Predicate predicateHead()
	{
		return _predicateHead;
	}

	std::vector<Predicate> predicateList()
	{
		return _predicateList;
	}

	std::string toString()
	{
		std::stringstream out;
		out << _predicateHead.toString() << " :- ";
		for (unsigned int i = 0; i < _predicateList.size(); i++)
		{
			out << _predicateList.at(i).toString();
			if (i == (_predicateList.size() - 1)) out << ".";
			else out << ",";
		}
		return out.str();
	}
};

#endif // RULE_H
