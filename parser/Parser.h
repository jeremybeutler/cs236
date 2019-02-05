#ifndef PARSER_H
#define PARSER_H
#include "../lexer/Token.h"
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
    unsigned int counter;
    Token token;
    std::vector<Token> tokenList;
    std::ostream &outputFile;
public:

    Parser(std::vector<Token> tokenList, std::ostream &out) : counter(0), token(tokenList.at(0)), tokenList(tokenList), outputFile(out) {}

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
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        id_list();
        match(RIGHT_PAREN);
    }

    void fact()
    {
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        string_list();
        match(RIGHT_PAREN);
        match(PERIOD);
    }

    void rule()
    {
        head_predicate();
        match(COLON_DASH);
        predicate();
        predicate_list();
        match(PERIOD);
    }

    void query()
    {
        predicate();
        match(Q_MARK);
    }

    void head_predicate()
    {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        id_list();
        match(RIGHT_PAREN);
    }

    void predicate()
    {
        Predicate predicate = Predicate();
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameter_list();
        match(RIGHT_PAREN);
    }

    void predicate_list()
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            predicate();
            predicate_list();
        }
    }

    void parameter_list()
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            parameter();
            parameter_list();
        }
    }

    void string_list()
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            match(STRING);
            string_list();
        }
    }

    void id_list()
    {
        if (token.getType() == COMMA)
        {
            match(COMMA);
            match(ID);
            id_list();
        }
    }

    void parameter()
    {
        if (token.getType() == STRING)
        {
            match(STRING);
        }
        else if (token.getType() == ID)
        {
            match(ID);
        }
        else
        {
            expression();
        }

    }

    void expression()
    {
        match(LEFT_PAREN);
        parameter();
        operator_();
        parameter();
        match(RIGHT_PAREN);
    }

    void operator_()
    {
        if (token.getType() == ADD)
        {
            match(ADD);
        }
        else
        {
            match(MULTIPLY);
        }
    }
	
};

#endif // PARSER_H
