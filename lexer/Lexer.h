#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include <cctype>
//#include "LexerInterface.h"

class Lexer
{
private:
	std::ifstream &inputFile;
	std::ofstream &outputFile;
	int numTokens;
	int lineNum;

public:
	Lexer(std::ifstream &in, std::ofstream &out) : inputFile(in), outputFile(out), numTokens(0), lineNum(1) {}
	
	void Tokenize() 
	{
		Token token = Token(DEFAULT, "DEFAULT", -99);
		char c;
		bool readFile = true;
		while (readFile)
		{
			c = inputFile.get();
			if (isspace(c))
			{
				if (c == '\n') 
					lineNum++;
			}
			else
			{
				switch (c)
				{
					case EOF:
					{
						token = Token(ENDFILE, "", lineNum + 1);
						outputFile << token.toString() << std::endl;
						numTokens++;
						readFile = false;
						break;
					}
					case ',':
					{
						token = Token(COMMA, ",", lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}
					case '.':
					{
						token = Token(PERIOD, ".", lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}

					case '?':
					{
						token = Token(Q_MARK, "?", lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}
					case '(':
					{
						token = Token(LEFT_PAREN, "(", lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}
					case ')':
					{
						token = Token(RIGHT_PAREN, ")", lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}
					case ':':
					{
						if (inputFile.peek() == '-')
						{
							inputFile.get();
							token = Token(COLON_DASH, ":-", lineNum);
							outputFile << token.toString() << std::endl;
							numTokens++;
							break;
						}
						else
						{
							token = Token(COLON, ":", lineNum);
							outputFile << token.toString() << std::endl;
							numTokens++;
							break;
						}
					}
					case '*':
					{
						token = Token(MULTIPLY, "*", lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}
					case '+':
					{
						token = Token(ADD, "+", lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}
					case '\'':
					{
						readFile = !(ScanString(c, lineNum));
						break;
					}
					case '#':
					{
						readFile = !(ScanComment(c, lineNum));
						break;
					}
					default:
					{
						if (isalpha(c))
						{
							readFile = !(ScanIdentifier(c, lineNum));
						}
						else
						{
							token = Token(UNDEFINED, std::string(1, c), lineNum);
							outputFile << token.toString() << std::endl;
							numTokens++;
						}
						//check whether or not a valid identifier
						break;
					}
				}
			}
		}
		outputFile << "Total Tokens = " << numTokens;
	}
	
	/**
	 * Scans string token from input file
	 *
	 * @param c First char. Probably a single open quote.
	 * @param lineNum Current line number in scanned file.
	 * @return Boolean indicating whether or not EOF been reached.
	*/
	bool ScanString(char c, int lineStart)
	{
		Token token = Token(DEFAULT, "DEFAULT", -99);
		bool readString = true;
		bool isEOF = false;
		std::string str, undefStr;
		char peek;
		str += c;
		undefStr += c;
		/*if (inputFile.peek() == '\'')
		{
			c = inputFile.get();
			str += c;
			return false;
		}*/
		while (readString)
		{
			c = inputFile.get();
			switch (c)
			{
				//???what to do with multiline string??? for now will assume that multiline strings are invalid
				case EOF:
				{
					//create and print undefined unterminated string token
					//create and print EOF token
					isEOF = true;
					readString = false;
					token = Token(UNDEFINED, undefStr + '\n', lineStart);
					outputFile << token.toString() << std::endl;
					numTokens++;
					token = Token(ENDFILE, "", lineNum + 1);
					outputFile << token.toString() << std::endl;
					numTokens++;
					break;
				}
				case '\n':
				{
					str += c;
					undefStr += c;
					lineNum++;
					break;
				}
				case '\'':
				{
					str += c;
					undefStr += c;
					peek = inputFile.peek();
					if (peek == '\'')
					{
						c = inputFile.get();
						undefStr += c;
					}
					else
					{
						token = Token(STRING, str, lineStart);
						outputFile << token.toString() << std::endl;
						numTokens++;
						readString = false;
					}
					break;
				}
				default:
				{
					str += c;
					undefStr += c;
					break;
				}
			}
		}
		return isEOF;
	}

	bool ScanComment(char c, int lineStart)
	{
		Token token = Token(DEFAULT, "DEFAULT", -99);
		bool readComment = true;
		bool isEOF = false;
		char peek;
		std::string str;
		str += c;
		if (inputFile.peek() == '|')
		{
			c = inputFile.get();
			str += c;
			while (readComment)
			{
				c = inputFile.get();
				
				switch (c)
				{
					//???what to do with multiline string??? for now will assume that multiline strings are invalid
					case EOF:
					{
						//create and print undefined unterminated string token
						//create and print EOF token
						isEOF = true;
						readComment = false;
						token = Token(ENDFILE, "", lineNum + 1);
						outputFile << token.toString() << std::endl;
						numTokens++;
						break;
					}
					case '|':
					{
						str += c;
						if (inputFile.peek() == '#')
						{
							c = inputFile.get();
							str += c;
							readComment = false;
							token = Token(COMMENT, str, lineStart);
							outputFile << token.toString() << std::endl;
							numTokens++;
							break;
						}
					}
					case '\n':
					{
						str += c;
						lineNum++;
						break;
					}
					default:
					{
						str += c;
						break;
					}
				}
			}
				
		}
		else
		{
			while (readComment)
			{
				c = inputFile.get();
				if (isspace(c))
				{
					if (c == '\n')
					{
						readComment = false;
						token = Token(COMMENT, str, lineNum);
						outputFile << token.toString() << std::endl;
						numTokens++;
						lineNum++;
						break;
					}
					else
					{
						str += c;
					}
				}
				else
				{
					switch (c)
					{
						//???what to do with multiline string??? for now will assume that multiline strings are invalid
						case EOF:
						{
							//create and print undefined unterminated string token
							//create and print EOF token
							isEOF = true;
							readComment = false;
							token = Token(ENDFILE, "", lineNum + 1);
							outputFile << token.toString() << std::endl;
							numTokens++;
							break;
						}
						default:
						{
							str += c;
							break;
						}
					}
				}
				
			}
		}
		str += c;
		return isEOF;
	}
	
	bool ScanIdentifier(char c, int lineStart)
	{
		Token token = Token(DEFAULT, "DEFAULT", -99);
		bool readIdent = true;
		bool isEOF = false;
		char peek;
		std::string str;
		//str += c;
		while (isalpha(c) || isdigit(c))
		{
			switch (c)
			{
				//???what to do with multiline string??? for now will assume that multiline strings are invalid
				case EOF:
				{
					//create and print undefined unterminated string token
					//create and print EOF token
					isEOF = true;
					readIdent = false;
					token = Token(ENDFILE, "", lineNum + 1);
					outputFile << token.toString() << std::endl;
					numTokens++;
					break;
				}
				default:
				{
					str += c;
					break;
				}
			}
			//inputFile.get();
			peek = inputFile.peek();
			if (isalpha(peek) || isdigit(peek)) c = inputFile.get();
			else break;
		}
		if (!isEOF)
		{
			if (str == "Schemes") token = Token(SCHEMES, str, lineNum);
			else if (str == "Facts") token = Token(FACTS, str, lineNum);
			else if (str == "Rules") token = Token(RULES, str, lineNum);
			else if (str == "Queries") token = Token(QUERIES, str, lineNum);
			else token = Token(ID, str, lineNum);

			numTokens++;
			outputFile << token.toString() << std::endl;
		}
		return isEOF;
	}
};

#endif	// LEXER_H