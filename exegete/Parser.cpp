#include "Parser.h"

const string Parser::UNFINISHED_ERROR = "ERROR unfinished Fact declaration";
const string Parser::UNEXPECTED_FACT_SYMB_ERROR= "ERROR unexpected symbol in Fact name: ";
const string Parser::UNEXPECTED_FACT_SPACE_ERROR = "ERROR unexpected space in Fact name";
const string Parser::UNEXPECTED_SYMB_ERROR = "ERROR unexpected symbol: ";
const string Parser::FACT_EXPECTED_ERROR = "ERROR new Fact declaration's missing"; //after comma (,)";
const string Parser::RULE_EXPECTED_ERROR = "ERROR new Rule declaration's missing";
const string Parser::COMMA_EXPECTED_ERROR_LINE = "comma (,) is expected instead";
const string Parser::BLANK_FACT_ERROR = "ERROR blank Fact name isn't allowed";
const string Parser::BROKEN_OPERATOR_ERROR_LINE = "complex operator should be spelled together";

const string Parser::EOF_FLAG = "-1";

set<string> Parser::parseFacts(istream& is) {
	set<string> facts;
	char c;
	bool factGen = false;
	bool pendingFact = true;
	string newFact;
	while (is.get(c) && c != '\n') {
		if (!isspace(c) || factGen) { //skipping spaces
			if (c == '"') {
				factGen = !factGen;
				if (factGen) {
					if (!pendingFact) {
						cerr << UNEXPECTED_SYMB_ERROR << c << " ; " << COMMA_EXPECTED_ERROR_LINE;
						exit(EXIT_FAILURE);
					}
					pendingFact = false;
				}
				else {
					if (newFact.empty()) {
						cerr << BLANK_FACT_ERROR;
						exit(EXIT_FAILURE);
					}
					facts.insert(newFact);
					newFact.clear();
				}
			}
			else if (c == ',' && !factGen) {
				pendingFact = true;
			}
			else {
				if (factGen) {
					if (isCorrectFactChar(c)) {
						newFact.push_back(c);
					}
					else {
						if (isspace(c)) {
							cerr << UNEXPECTED_FACT_SPACE_ERROR;
							exit(EXIT_FAILURE);
						}
						else {
							cerr << UNEXPECTED_FACT_SYMB_ERROR << c;
							exit(EXIT_FAILURE);
						}
					}
				}
				else {
					cerr << UNEXPECTED_SYMB_ERROR << c;
					exit(EXIT_FAILURE);
				}
			}
		} 
	}
	if (factGen) {
		cerr << UNFINISHED_ERROR;
		exit(EXIT_FAILURE);
	}
	if (pendingFact && !facts.empty()) {
		cerr << FACT_EXPECTED_ERROR;
		exit(EXIT_FAILURE);
	}
	return facts;
}

list<string> Parser::parseNextRule(istream& is) {
	list<string> rule;
	char c;
	bool ruleGen = false;
	bool factProc = false;
	bool pendingFact = false;
	bool pendingRule = true;
	bool operProc = false;
	bool isEOF = true;
	string token;
	while (is.get(c) && c != '\n') {
		if (!isspace(c) || factProc || operProc) {
			if (c == '"') {
				ruleGen = !ruleGen;
				if (ruleGen) {
					if (!pendingRule) {
						cerr << UNEXPECTED_SYMB_ERROR << c << " ; " << COMMA_EXPECTED_ERROR_LINE;
						exit(EXIT_FAILURE);
					}
					pendingFact = true;
					pendingRule = false;
				}
				else {
					if (!token.empty()) {
						factProc = false;
						rule.push_back(token);
						token.clear();
					}
					else if (pendingFact && !rule.empty()) {
						cerr << FACT_EXPECTED_ERROR;
						exit(EXIT_FAILURE);
					}
				}
			}
			else if (c == ',' && !ruleGen) {
				if (pendingRule) {
					cerr << UNEXPECTED_SYMB_ERROR << c;
					exit(EXIT_FAILURE);
				}
				pendingRule = true;
				isEOF = false;
				break;
			}
			else {
				if (pendingFact) {
					if (isCorrectFactChar(c)) {
						token.push_back(c);
						pendingFact = false;
						factProc = true;
					}
					else {
						cerr << UNEXPECTED_FACT_SYMB_ERROR << c;
						exit(EXIT_FAILURE);
					}
				}
				else if (factProc) {
					if (isCorrectFactChar(c)) {
						token.push_back(c);
					}
					else if (isspace(c) || c == ',' || c == '|' || c == '-') {
						factProc = false;
						rule.push_back(token);
						token.clear();
						if (!isspace(c)) {
							token.push_back(c);
							if (c == '-') {
								operProc = true;
							}
							else {
								rule.push_back(token);
								token.clear();
								pendingFact = true;
							}
						}
					}
					else {
						cerr << UNEXPECTED_FACT_SYMB_ERROR << c;
						exit(EXIT_FAILURE);
					}					
				}
				else if (operProc) {
					if (c == '>') {
						token.push_back(c);
						rule.push_back(token);
						token.clear();
						pendingFact = true;
						operProc = false;
					} 
					else {
						cerr << UNEXPECTED_FACT_SYMB_ERROR << token.at(0) << " ; " << BROKEN_OPERATOR_ERROR_LINE;
						exit(EXIT_FAILURE);
					}
				}
				else if (c == ',' || c == '|' || c == '-') {
					token.push_back(c);
					if (c == '-') {
						operProc = true;
					}
					else {
						rule.push_back(token);
						token.clear();
						pendingFact = true;
					}
				}
				else {
					cerr << UNEXPECTED_SYMB_ERROR << c;
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	if (isEOF) {
		rule.push_back(EOF_FLAG);
	}
	return rule;
}

bool Parser::isCorrectFactChar(char c) {
	return c >= 'A' && c <= 'Z';
}