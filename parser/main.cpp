#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <vector>
#include <fstream>
#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
#include "Parser.h"
using namespace std;

int main(int argc, char *argv[])
{
	VS_MEM_CHECK

	//	Create input stream from argv[1] and output stream to argv[2]

	ifstream in(argv[1]);
    // std::string DEFAULT = "DEFAULT";
    // std::vector<std::string> DEFAULT_LIST;
    // std::vector<Predicate> DEFAULT_LIST_P;
		//
    // Predicate p = Predicate(DEFAULT, DEFAULT, DEFAULT_LIST);
    // Rule r = Rule(p, DEFAULT_LIST_P);
    // Parameter pa = Parameter(DEFAULT, DEFAULT);

    Lexer lexer = Lexer(in, cout);
    lexer.Tokenize();
    std::vector<Token> tokens = lexer.tokens();
    Parser parser = Parser(tokens, cout);
    try {
        DatalogProgram program = parser.parse();
        cout << "Success!" << std::endl << program.toString(); 
    } catch (Token error) {
        cout << "Failure!" << std::endl << "  " << error.toString();
    }
	return 0;
}
