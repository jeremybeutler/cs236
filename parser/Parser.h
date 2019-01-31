#ifndef PARSER_H
#define PARSER_H
#include "../lexer/Token.h"
#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>
#include <cctype>
#include <vector>

class Parser
{
private:
    int counter;
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
        token = tokenList.at(counter + 1);
    }

    void datalog_program()
    {
        match(SCHEMES);
        match(COLON);
        schemes();
        scheme_list();
        match(FACTS);
        match(COLON);
        fact_list();
        match(RULES);
        match(COLON);
        rule_list();
        match(QUERIES);
        match(COLON);
        query_list();
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

    void schemes()
    {

    }

    void scheme_list()
    {
    }

    void fact_list()
    {
    }

    void rule_list()
    {
    }

    void query_list()
    {
    }

    void scheme()
    {
    }

    void fact()
    {
    }

    void scheme()
    {
    }

    void fact()
    {
    }

    void rule()
    {
    }

    void query()
    {
    }

    void head_predicate()
    {
    }

    void predicate()
    {

    }

    void predicate_list()
    {

    }

    void parameter_list()
    {

    }

    void string_list()
    {

    }

    void id_list()
    {

    }
	
};

#endif // PARSER_H
