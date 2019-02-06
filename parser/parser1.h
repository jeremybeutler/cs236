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
    DatalogProgram program;
    Predicate p;
    Rule r;
    Parameter pa;
    Token token;
    std::vector<Token> tokenList;
    std::ostream &outputFile;
    unsigned int counter;
public:

    Parser(Predicate p, Rule r, Parameter pa, std::vector<Token> tokenList, std::ostream &out) : p(p), r(r), pa(pa), token(tokenList.at(0)), tokenList(tokenList), outputFile(out), counter(0) {}

    void parse()
    {
        datalog_program();
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
        p = Predicate("scheme", id, list);
        program.addScheme(p);
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
        p = Predicate("fact", id, list);
        program.addFact(p);
    }

    void rule()
    {
        std::vector<Predicate> list;
        head_predicate();
        Predicate predicateHead = p;
        match(COLON_DASH);
        predicate();
        list.push_back(p);
        predicate_list(list);
        match(PERIOD);
        r = Rule(predicateHead, list);
        program.addRule(r);
    }

    void query()
    {
        predicate();
        match(Q_MARK);
        program.addQuery(p);
    }

    void head_predicate()
    {
        std::vector<std::string> list;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        list.push_back(token.getValue());
        match(ID);
        id_list(list);
        match(RIGHT_PAREN);
        p = Predicate("head_predicate", id, list);
    }

    void predicate()
    {
        std::vector<std::string> list;
        std::string id = token.getValue();
        match(ID);
        match(LEFT_PAREN);
        parameter(list);
        parameter_list(list);
        match(RIGHT_PAREN);
        p = Predicate("predicate", id, list);
    }

    void predicate_list(std::vector<Predicate> &list)
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            predicate();
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
