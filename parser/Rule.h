#ifndef RULE_H
#define RULE_H
#include "Predicate.h"

#include <string>
#include <sstream>
#include <vector>

class Rule
{
private:
		Predicate predicateHead;
    std::vector<Predicate> predicateList;
public:
    Rule(Predicate predicateHead, std::vector<Predicate> predicateList)
			: predicateHead(predicateHead), predicateList(predicateList) {}

	std::string toString()
  {
      std::stringstream out;
      return out.str();
  }
};

#endif // RULE_H
