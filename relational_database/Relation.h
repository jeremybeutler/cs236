#ifndef RELATION_H
#define RELATION_H

#include <string>
#include <sstream>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

class Relation
{
private:
    std::string _name;
    Scheme _scheme;
    std::set<Tuple> _tuples; 
    
public:
    Relation() : _scheme() {}
    Relation(std::string _name, Scheme _scheme, std::set<Tuple> _tuples)
			: _name(_name), _scheme(_scheme), _tuples(_tuples) {}

    std::string name()
    {
        return _name;
    }
    
    Scheme scheme()
    {
        return _scheme;
    }
    
    std::set<Tuple> tuples()
    {
        return _tuples;
    }

    void setName(std::string name)
    {
        this->_name = name;
    }

    void setScheme(Scheme scheme)
    {
        this->_scheme = scheme;
    }

    void setTuples(std::set<Tuple> tuples)
    {
        this->_tuples = tuples;
    }

    void addTuple(Tuple t)
    {
        _tuples.insert(t);
    }

    std::string toString()
    {
        std::stringstream out;
        if (_tuples.size())
        {
            out << "Yes(" << _tuples.size() << ")" << std::endl;
            for (Tuple tuple : _tuples) 
            {
                if (_scheme.size() == 0) break;
                out << "  ";
                for (unsigned int i = 0; i < _scheme.size(); ++i)
                {
                    out << _scheme.at(i) << "=" << tuple.at(i);
                    out << ((i == _scheme.size() - 1) ? "" : ", ");
                }
                out << std::endl;
            }
        }
        else 
            out << "No" << std::endl;
        
        return out.str();
    }
};

#endif // RELATION_H
