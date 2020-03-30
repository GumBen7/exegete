#include <iostream>
#include <string>
#include <set>

#include "Parser.h"

using namespace std;

static const string REQ_FACTS_STR = "Put down Facts";
static const string REQ_RULES_STR = "Put down Rules";

int main() {
	cout << REQ_FACTS_STR << endl;
	set<string> facts;
	facts = Parser::parseFacts(cin);
	for (auto f : facts) {
		cout << '~' << f << "~ ";
	}
	return 0;
}