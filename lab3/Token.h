#ifndef TOKEN_H
#define TOKEN_H

enum TokenType { DEFAULT, COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDFILE };

class Token
{
private:
	TokenType type;
	std::string value;
	int lineNum;

public:
	Token(TokenType type, std::string value, int lineNum) : type(type), value(value), lineNum(lineNum) {}

	TokenType getType()
	{
		return type;
	}

	std::string getValue()
	{
		return value;
	}

	int getLineNum()
	{
		return lineNum;
	}

	std::string toString() {
		switch (type)
		{
		case COMMA: return ("(COMMA,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case PERIOD: return ("(PERIOD,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case Q_MARK: return ("(Q_MARK,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case LEFT_PAREN: return ("(LEFT_PAREN,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case RIGHT_PAREN: return ("(RIGHT_PAREN,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case COLON: return ("(COLON,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case COLON_DASH: return ("(COLON_DASH,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case MULTIPLY: return ("(MULTIPLY,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case ADD: return ("(ADD,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case SCHEMES: return ("(SCHEMES,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case FACTS: return ("(FACTS,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case RULES: return ("(RULES,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case QUERIES: return ("(QUERIES,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case ID: return ("(ID,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case STRING: return ("(STRING,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case COMMENT: return ("(COMMENT,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case UNDEFINED: return ("(UNDEFINED,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case ENDFILE: return ("(EOF,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		case DEFAULT: return ("(DEFAULT,\"" + value + "\"," + std::to_string(lineNum) + ")"); break;
		}
		return "ERROR"; // a string MUST be returned by the end
	}

};

#endif	// TOKEN_H