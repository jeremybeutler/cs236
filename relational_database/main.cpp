// #ifdef _MSC_VER
// #define _CRTDBG_MAP_ALLOC
// #include <crtdbg.h>
// #define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// #else
// #define VS_MEM_CHECK
// #endif

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
#include "../parser/Parser.h"
#include "Interpreter.h"
#include "Database.h"
#include "Relation.h"
#include "Scheme.h"
#include "Scheme.h"
#include "Tuple.h"
using namespace std;

int main(int argc, char *argv[])
{
	// VS_MEM_CHECK
	//	Create input stream from argv[1] and output stream to argv[2]

	ifstream in(argv[1]);
    Lexer lexer = Lexer(in, cout);
    lexer.Tokenize();
    std::vector<Token> tokens = lexer.tokens();
    Parser parser = Parser(tokens, cout);
    DatalogProgram p;
    try {
        p = parser.parse();

    } catch (Token error) {
        cout << "Parser Failure!" << std::endl << "  " << error.toString();
    }

    Interpreter i = Interpreter(p);
    Database db = i.db();
    cout << i.EvaluateRules() << std::endl;
    cout << i.evaluateQueries();

	return 0;
}
