#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
#include <sstream>

class Parameter
{
private:
    std::string type;
    std::string param;

public:
    Parameter(std::string type, std::string param)
      : type(type), param(param)  {}

	std::string toString()
  {
      std::stringstream out;
      if (type == "STRING") out << param;
      else if (type == "ID") out << param;
      else if (type == "EXPRESSION") out << param;

      return out.str();
  }
};

#endif // PARAMETER_H
