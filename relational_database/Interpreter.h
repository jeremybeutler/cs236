#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include "Database.h"
#include "../parser/DatalogProgram.h"

class Interpreter
{
private:
    DatalogProgram p;
    Database _db;
    
public:
    Interpreter() {}
    Interpreter(DatalogProgram& p)
			: p(p) 
    {
        createDatabase();
    }

    void createDatabase()
    {
        std::vector<Predicate> schemes = p.schemes();
        std::vector<Predicate> facts = p.facts();
        // std::vector<Rule> rules = p.rules();
        // std::vector<Predicate> queries = p.queries();
        // std::vector<std::string> domains = p.domain();

        // loop through each scheme Predicate
        for (unsigned int i = 0; i < schemes.size(); ++i)
        {
            Relation r;
            std::string name = schemes.at(i).id();
            Scheme s;
            std::set<Tuple> tuples;
            
            // loop through each Parameter in the vector of Parameters in the scheme Predicate 
            for (unsigned int j = 0; j < schemes.at(i).listStr().size(); ++j)
            {
                s.push_back(schemes.at(i).listStr().at(j));
            }
            // loop through each fact Predicate
            for (unsigned int j = 0; j < facts.size(); ++j)
            {
                if (facts.at(j).id() == name)
                {
                    Tuple t;
                    // loop through each Parameter in the vector of Parameters in the fact Predicate 
                    for (unsigned int k = 0; k < facts.at(j).listStr().size(); ++k)
                    {                            
                        t.push_back(facts.at(j).listStr().at(k));
                    }
                    tuples.insert(t);
                }
                
            }
            r = Relation(name, s, tuples);
            _db[name] = r;
        }
    }

    Database db()
    {
        return _db;
    }

    Relation selectA(Relation& r, std::string val, int pos)
    {
        std::set<Tuple> tuples_old = r.tuples();
        Relation relation_new = Relation(r.name(), r.scheme(), std::set<Tuple>());        
        for (Tuple tuple : tuples_old) 
        {
            if (tuple.at(pos) == val) 
                relation_new.addTuple(tuple);
        }
        return relation_new;
    }

    Relation selectB(Relation& r, int pos_1, int pos_2)
    {
        std::set<Tuple> tuples_old = r.tuples();
        Relation relation_new = Relation(r.name(), r.scheme(), std::set<Tuple>());
        for (Tuple tuple : tuples_old) 
        {
            if (tuple.at(pos_1) == tuple.at(pos_2)) 
                relation_new.addTuple(tuple);
        }
        return relation_new;
    }

    Relation project(Relation& r, std::vector<int> indexes, std::vector<std::string> new_order = std::vector<std::string>())
    {
        Scheme scheme_old = r.scheme();
        std::set<Tuple> tuples_old = r.tuples();
        Scheme scheme_new;

        for (unsigned int i = 0; i < indexes.size(); ++i)
            scheme_new.push_back(scheme_old.at(indexes.at(i)));

        Relation relation_new = Relation(r.name(), scheme_new, std::set<Tuple>());

        for (Tuple tuple : tuples_old) 
        {
            Tuple tuple_new;
            for (unsigned int i = 0; i < indexes.size(); ++i)
                tuple_new.push_back(tuple.at(indexes.at(i)));

            relation_new.addTuple(tuple_new);
        }
        return relation_new;
    }

    Relation rename(Relation& r, Scheme scheme_new)
    {
        Relation relation_new = Relation(r.name(), scheme_new, r.tuples());
        return relation_new;
    }

    Relation query(Predicate p)
    {
        std::string name = p.id();
        Relation r = db()[name];
        std::vector<Parameter> param_list = p.list();
        std::vector<std::string> query_vars;
        Scheme scheme_new;
        std::vector<int> kept_column_indexes;
        for (unsigned int i = 0; i < param_list.size(); ++i)
        {
            std::string param_val = param_list.at(i).value();
            if (param_list.at(i).isConstant())
                r = selectA(r, param_val, i);
            else if (count(query_vars.begin(), query_vars.end(), param_val))
            {
                auto it = std::find(query_vars.begin(), query_vars.end(), param_val);
                r = selectB(r, std::distance(query_vars.begin(), it), i);
            }
            else
            {
                query_vars.push_back(param_val);
                scheme_new.push_back(param_val);
                kept_column_indexes.push_back(i);
            }
        }
        r = project(r, kept_column_indexes);
        r = rename(r, scheme_new);
        return r;
    }

    std::string evaluateQueries()
    {
        std::stringstream out;
        std::vector<Predicate> queries = p.queries();
        for (unsigned int i = 0; i < queries.size(); ++i)
        {
            out << query(queries.at(i)).toString() << std::endl;
        }
        return out.str();
    }

};

#endif // INTERPRETER_H
