#include <iostream>
#include <string>
#include <set>

#include "Parser.h"

using namespace std;

static const string REQ_FACTS_STR = "Put down Facts";
static const string REQ_RULES_STR = "Put down Rules";

int main() {
	//cout << REQ_FACTS_STR << endl;
	//set<string> facts;
	//facts = Parser::parseFacts(cin);
	cout << REQ_RULES_STR << endl;
	list<string> rule;
	bool f = true;
	do {
		rule = Parser::parseNextRule(cin);
		if ((--(rule.end())).operator*().compare(Parser::EOF_FLAG) == 0) {
			rule.pop_back();
			f = false;
		}
		for (auto s : rule) {
			cout << s << '\'';
		}
		cout << endl;
	} while (f);
	return 0;
}