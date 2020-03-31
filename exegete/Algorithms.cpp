#include "Algorithms.h"


bool Algorithms::calculateTree(const TreeNode* node, const set<string>& facts) {
	OperatorType type;
	type = node->getOperatorType();
	if (type == OperatorType::NONE) {
		return facts.find(node->getName()) != facts.end();
	}
	else {
		bool firstChildsResult = calculateTree(node->getChildFirst(), facts);
		bool secondChildResult = calculateTree(node->getChildSecond(), facts);
		return operate(type, firstChildsResult, secondChildResult);
	}
}

TreeNode* Algorithms::getTreeFromRule(const list<string>& rule) { 
	TreeNode* root;
	list<string> ruleInRPN = getRuleInRPN(rule);
	ruleInRPN.reverse();
	root = getNode(ruleInRPN);
	return root;
}

TreeNode* Algorithms::getNode(list<string>& pN) {
	TreeNode* node = new TreeNode;
	string name = pN.front();
	node->setName(name);
	OperatorType type = getOperatorByName(name);
	node->setOpeartorType(type);
	pN.pop_front();
	if (type == OperatorType::NONE) {
		node->setChildSecond(nullptr);
		node->setChildFirst(nullptr);
	}
	else {
		node->setChildSecond(getNode(pN));
		node->setChildFirst(getNode(pN));
	}
	return node;
}

list<string> Algorithms::getRuleInRPN(const list<string>& rule) { //shunting-yard
	list<string> ruleInRPN;
	stack<string> opStack;
	for (auto s : rule) {
		OperatorType type = getOperatorByName(s);
		if (type == OperatorType::NONE) {
			ruleInRPN.push_back(s);
		}
		else {
			string opName;
			while (!opStack.empty() && getOperatorByName(opName = opStack.top()) <= type) {
				ruleInRPN.push_back(opName);
				opStack.pop();
			}
			opStack.push(s);
		}
	}
	while (!opStack.empty()) {
		ruleInRPN.push_back(opStack.top());
		opStack.pop();
	}
	return ruleInRPN;
}

OperatorType Algorithms::getOperatorByName(string name) {
	if (name.compare(",") == 0) {
		return OperatorType::LOGIC_AND;
	}
	if (name.compare("|") == 0) {
		return OperatorType::LOGIC_OR;
	}
	if (name.compare("->") == 0) {
		return OperatorType::LOGIC_IMPLY;
	}
	return OperatorType::NONE;
}

bool Algorithms::operate(OperatorType type, bool op1, bool op2) {
	if (type == OperatorType::LOGIC_AND) {
		return op1 & op2;
	}
	else if (type == OperatorType::LOGIC_OR) {
		return op1 | op2;
	}
	else {//if (type == OperatorType::LOGIC_IMPLY) {
		return (!op1) | op2;
	}
}