#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
#include <sstream>

class Parameter
{
private:
    std::string _type;
    std::string _value;

public:
    Parameter(std::string _type, std::string _value)
      : _type(_type), _value(_value)  {}

    std::string type()
    {
        return _type;
    }

    std::string value()
    {
        return _value;
    }

    std::string toString()
    {
        std::stringstream out;
        if (_type == "STRING") out << _value;
        else if (_type == "ID") out << _value;
        else if (_type == "EXPRESSION") out << _value;

        return out.str();
    }
};

#endif // PARAMETER_H
