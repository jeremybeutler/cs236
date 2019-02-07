#ifndef PARSER_H
#define PARSER_H
#include "../lexer/Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
#include <string>
#include <vector>

class Parser
{
private:
    Token token;
    std::vector<Token> tokenList;
    unsigned int counter = 0;

    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
public:

    Parser(std::vector<Token> tokenList, std::ostream &out)
        : token(tokenList.at(0)), tokenList(tokenList) {}

    DatalogProgram parse()
    {
        datalog_program();
        return DatalogProgram(schemes, facts, rules, queries);
    }

    void getToken()
    {
        counter++;
        token = tokenList.at(counter);
    }

    void datalog_program()
    {
        match(SCHEMES);
        match(COLON);
        scheme();
        scheme_list();
        match(FACTS);
        match(COLON);
        fact_list();
        match(RULES);
        match(COLON);
        rule_list();
        match(QUERIES);
        match(COLON);
        query();
        query_list();
        if (tokenList.size() - 1 !=  counter)
        {
            error();
        }

    }

    void match(TokenType t)
    {
        if (token.getType() == t)
			     getToken();
    		else
    			error();
    }

    void error()
    {
        throw token;
    }

    void scheme_list()
    {
        if (token.getType() == ID)
        {
            scheme();
            scheme_list();
        }
    }

    void fact_list()
    {
        if (token.getType() == ID)
        {
            fact();
            fact_list();
        }
    }

    void rule_list()
    {
        if (token.getType() == ID)
        {
            rule();
            rule_list();
        }
    }

    void query_list()
    {
        if (token.getType() == ID)
        {
            query();
            query_list();
        }
    }

    void scheme()
    {
        std::vector<Parameter> list;
        std::vector<std::string> listStr;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        listStr.push_back(token.getValue());
        match(ID);
        id_list(listStr);
        match(RIGHT_PAREN);
        schemes.push_back(Predicate("HEAD_PREDICATE", id, list, listStr));
    }

    void fact()
    {
        std::vector<Parameter> list;
        std::vector<std::string> listStr;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        listStr.push_back(token.getValue());
        match(STRING);
        string_list(listStr);
        match(RIGHT_PAREN);
        match(PERIOD);
        facts.push_back(Predicate("HEAD_PREDICATE", id, list, listStr));
    }

    void rule()
    {
        std::vector<Predicate> list;
        Predicate predicateHead = head_predicate();
        match(COLON_DASH);
        Predicate p = predicate();
        list.push_back(p);
        predicate_list(list);
        match(PERIOD);
        rules.push_back(Rule(predicateHead, list));
    }

    void query()
    {
        Predicate p = predicate();
        match(Q_MARK);
        queries.push_back(p);
    }

    Predicate head_predicate()
    {
        std::vector<Parameter> list;
        std::vector<std::string> listStr;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        listStr.push_back(token.getValue());
        match(ID);
        id_list(listStr);
        match(RIGHT_PAREN);
        return Predicate("HEAD_PREDICATE", id, list, listStr);
    }

    Predicate predicate()
    {
        std::vector<Parameter> list;
        std::vector<std::string> listStr;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        parameter(list);
        parameter_list(list);
        match(RIGHT_PAREN);
        return Predicate("PREDICATE", id, list, listStr);
    }

    void predicate_list(std::vector<Predicate> &list)
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            Predicate p = predicate();
            list.push_back(p);
            predicate_list(list);
        }
    }

    void parameter_list(std::vector<Parameter> &list)
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            parameter(list);
            parameter_list(list);
        }
    }

    void string_list(std::vector<std::string> &list)
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            list.push_back(token.getValue());
            match(STRING);
            string_list(list);
        }
    }

    void id_list(std::vector<std::string> &list)
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            list.push_back(token.getValue());
            match(ID);
            id_list(list);
        }
    }

    std::string parameter(std::vector<Parameter> &list, bool pushParam = true)
    {
        std::string paramVal = token.getValue();
        if (token.getType() == STRING)
        {
            if (pushParam)
            {
                Parameter p = Parameter("STRING", paramVal);
                list.push_back(p);
            }
            match(STRING);
        }
        else if (token.getType() == ID)
        {
            if (pushParam)
            {
                Parameter p = Parameter("ID", paramVal);
                list.push_back(p);
            }
            match(ID);
        }
        else
        {
            paramVal = expression(list);
            if (pushParam)
            {
                Parameter p = Parameter("EXPRESSION", paramVal);
                list.push_back(p);
            }

        }
        return paramVal;

    }

    std::string expression(std::vector<Parameter> &list)
    {
        std::stringstream out;
        std::string paramVal;
        //list.push_back(token.getValue());
        out << token.getValue();
        match(LEFT_PAREN);
        paramVal = parameter(list, false);
        //Parameter p = Parameter("STRING", paramVal);
        //list.push_back(p);
        out << paramVal;
        out << operator_();
        paramVal = parameter(list, false);
        //p = Parameter("STRING", paramVal);
        //list.push_back(p);
        out << paramVal;
        out << token.getValue();
        //list.push_back(token.getValue());
        match(RIGHT_PAREN);
        return out.str();
    }

    std::string operator_()
    {
        std::string opVal = token.getValue();
        if (token.getType() == ADD)
        {
            //list.push_back(opVal);
            match(ADD);
        }
        else
        {
            //list.push_back(opVal);
            match(MULTIPLY);
        }
        return opVal;
    }

};

#endif // PARSER_H

//
//
//
//
//
//
//
//
//
// snap(D,Y,B,(E+C))
//
// D Y B ( E + C )
//
// D Y B ( E + ( A * B
//
//
