#pragma once
#include <string>

#include "OperatorType.h"

using namespace std;

class TreeNode
{
private:
	TreeNode* childFirst = nullptr;
	TreeNode* childSecond = nullptr;

	string name;
	OperatorType operatorType;
	void deleteRec(TreeNode* node);
public:
	void setName(string s);
	void setOpeartorType(OperatorType type);
	void setChildFirst(TreeNode* node);
	void setChildSecond(TreeNode* node);
	TreeNode* getChildFirst() const;
	TreeNode* getChildSecond() const;
	string getName() const;
	OperatorType getOperatorType() const;
	~TreeNode();
}; 

