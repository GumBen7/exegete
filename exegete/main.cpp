#include <iostream>
#include <string>
#include <set>

#include "Parser.h"
#include "Algorithms.h"

using namespace std;

static const string REQ_FACTS_STR = "Put down Facts";
static const string REQ_RULES_STR = "Put down Rules";

int main() {
	cout << REQ_FACTS_STR << endl;
	set<string> facts;
	facts = Parser::parseFacts(cin);
	
	cout << REQ_RULES_STR << endl;
	list<string> rule;
	bool f = true;
	bool firstFact = true;
	do {
		rule = Parser::parseNextRule(cin);
		if (!rule.empty() && (--(rule.end())).operator*().compare(Parser::EOF_FLAG) == 0) {
			rule.pop_back();
			f = false;
		}
		TreeNode* tree = Algorithms::getTreeFromRule(rule);
		if (Algorithms::calculateTree(tree, facts) == 0) {
			string newFact = tree->getChildSecond()->getName();
			facts.insert(newFact);
			if (!firstFact) {
				cout << ", ";
			}
			cout << newFact;
			firstFact = false;
		}
		delete tree;
	} while (f);
	return 0;
}