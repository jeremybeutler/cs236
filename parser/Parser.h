#ifndef PARSER_H
#define PARSER_H
#include "../lexer/Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <vector>

class Parser
{
private:
    Token token;
    std::vector<Token> tokenList;
    std::ostream &outputFile;
    unsigned int counter;

    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
public:

    Parser(std::vector<Token> tokenList, std::ostream &out) : token(tokenList.at(0)), tokenList(tokenList), outputFile(out), counter(0), schemes(0), facts(0), rules(0), queries(0) {}

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
        std::vector<std::string> list;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        list.push_back(token.getValue());
        match(ID);
        id_list(list);
        match(RIGHT_PAREN);
        schemes.push_back(Predicate("scheme", id, list));
    }

    void fact()
    {
        std::vector<std::string> list;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        list.push_back(token.getValue());
        match(STRING);
        string_list(list);
        match(RIGHT_PAREN);
        match(PERIOD);
        facts.push_back(Predicate("fact", id, list));
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
        std::vector<std::string> list;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        list.push_back(token.getValue());
        match(ID);
        id_list(list);
        match(RIGHT_PAREN);
        return Predicate("head_predicate", id, list);
    }

    Predicate predicate()
    {
        std::vector<std::string> list;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        parameter(list);
        parameter_list(list);
        match(RIGHT_PAREN);
        return Predicate("predicate", id, list);
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

    void parameter_list(std::vector<std::string> &list)
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

    void parameter(std::vector<std::string> &list)
    {
        if (token.getType() == STRING)
        {
            list.push_back(token.getValue());
            match(STRING);
        }
        else if (token.getType() == ID)
        {
            list.push_back(token.getValue());
            match(ID);
        }
        else
        {
            expression(list);
        }

    }

    void expression(std::vector<std::string> &list)
    {
        list.push_back(token.getValue());
        match(LEFT_PAREN);
        parameter(list);
        operator_(list);
        parameter(list);
        list.push_back(token.getValue());
        match(RIGHT_PAREN);
    }

    void operator_(std::vector<std::string> &list)
    {
        if (token.getType() == ADD)
        {
            list.push_back(token.getValue());
            match(ADD);
        }
        else
        {
            list.push_back(token.getValue());
            match(MULTIPLY);
        }
    }

};

#endif // PARSER_H
