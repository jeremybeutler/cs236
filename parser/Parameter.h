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

    bool isConstant() const
    {
        return _isConstant;
    }

    std::string value() const
    {
        return _value;
    }

    std::string toString() const
    {
        std::stringstream out;
        out << _value;
        return out.str();
    }
};

#endif // PARAMETER_H
