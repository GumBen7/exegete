#pragma once
#include <string>
#include <set>
#include <list>
#include <stack>

#include "TreeNode.h"
#include "OperatorType.h"

using namespace std;

class Algorithms
{
public:
	static bool calculateTree(const TreeNode* node, const set<string>& facts);
	static TreeNode* getTreeFromRule(const list<string>& rule);
	static list<string> getRuleInRPN(const list<string>& rule); 
	static OperatorType getOperatorByName(string name);
	static TreeNode* getNode(list<string>& pN);
	static bool operate(OperatorType type, bool op1, bool op2);
};

