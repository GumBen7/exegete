#pragma once
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Parser
{
private:
	static const string UNFINISHED_ERROR;
	static const string UNEXPECTED_FACT_SYMB_ERROR;
	static const string UNEXPECTED_FACT_SPACE_ERROR;
	static const string UNEXPECTED_SYMB_ERROR;
	static const string FACT_EXPECTED_ERROR;
	static const string COMMA_EXPECTED_ERROR_LINE;
	static const string BLANK_FACT_ERROR;
public:
	static set<string> parseFacts(istream& is);
};

