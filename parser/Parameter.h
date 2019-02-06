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
      return out.str();
  }
};

#endif // PARAMETER_H
