#pragma once
#include <set>
#include <list>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Parser
{
private:
	static const string UNFINISHED_ERROR;
	static const string UNEXPECTED_FACT_SYMB_ERROR;
	static const string UNEXPECTED_FACT_SPACE_ERROR;
	static const string UNEXPECTED_SYMB_ERROR;
	static const string FACT_EXPECTED_ERROR;
	static const string RULE_EXPECTED_ERROR;
	static const string COMMA_EXPECTED_ERROR_LINE;
	static const string BLANK_FACT_ERROR;
	static const string BROKEN_OPERATOR_ERROR_LINE;
	static bool isCorrectFactChar(char c);
public:
	static const string EOF_FLAG;
	static set<string> parseFacts(istream& is);
	static list<string> parseNextRule(istream& is);
};

