#include "Parser.h"

#include <iostream> //TODO delete

const string Parser::UNFINISHED_ERROR = "ERROR unfinished Fact declaration";
const string Parser::UNEXPECTED_FACT_SYMB_ERROR= "ERROR unexpected symbol in Fact name: ";
const string Parser::UNEXPECTED_FACT_SPACE_ERROR = "ERROR unexpected space in Fact name";
const string Parser::UNEXPECTED_SYMB_ERROR = "ERROR unexpected symbol: ";
const string Parser::FACT_EXPECTED_ERROR = "ERROR new Fact declaration's missing after ','";
const string Parser::COMMA_EXPECTED_ERROR_LINE = "comma expected instead";
const string Parser::BLANK_FACT_ERROR = "ERROR blank Fact name isn't allowed";

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
			else if (c == ',') {
				pendingFact = true;
			}
			else {
				if (factGen) {
					if (c >= 'A' && c <= 'Z') {
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