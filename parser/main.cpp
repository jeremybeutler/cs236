#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream> 
#include <fstream>
#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
#include "Parser.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
using namespace std;

int main(int argc, char *argv[])
{
	VS_MEM_CHECK

	//	Create input stream from argv[1] and output stream to argv[2]

	ifstream in(argv[1]);

    Lexer lexer = Lexer(in, cout);
	lexer.Tokenize();
    vector<Token> tokens = lexer.tokens();
    Parser parser = Parser(tokens, cout);
    try {
        parser.parse();
    } catch (Token error) { 
        cout << "Failure! " << endl << error.toString();
    }
    

	return 0;
}
