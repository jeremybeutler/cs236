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
#include "Token.h"
#include "Lexer.h"
using namespace std;

int main(int argc, char *argv[])
{
	VS_MEM_CHECK

	//	Create input stream from argv[1] and output stream to argv[2]

	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		system("PAUSE");
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		system("PAUSE");
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);

	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		system("PAUSE");
		return 3;
	}

	Lexer lexer = Lexer(in, out);
	lexer.Tokenize();
	/*Token token = Token(ENDFILE, "", 2);
	cout << token.toString() << std::endl;*/
	system("pause");
	return 0;
}