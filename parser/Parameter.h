#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
#include <sstream>

class Parameter
{
private:
    bool _isConstant;
    std::string _value;

public:
    Parameter(bool _isConstant, std::string _value)
      : _isConstant(_isConstant), _value(_value)  {}

    bool isConstant()
    {
        return _isConstant;
    }

    std::string value()
    {
        return _value;
    }

    std::string toString()
    {
        std::stringstream out;
        out << _value;
        return out.str();
    }
};

#endif // PARAMETER_H
