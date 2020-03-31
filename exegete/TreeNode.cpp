#include "TreeNode.h"

void TreeNode::setName(string name) {
	this->name = name;
}

void TreeNode::setOpeartorType(OperatorType type) {
	this->operatorType = type;
}

void TreeNode::setChildFirst(TreeNode* node) {
	this->childFirst = node;
}

void TreeNode::setChildSecond(TreeNode* node) {
	this->childSecond = node;
}

TreeNode* TreeNode::getChildFirst() const {
	return childFirst;
}

TreeNode* TreeNode::getChildSecond() const {
	return childSecond;
}

string TreeNode::getName() const {
	return name;
}

OperatorType TreeNode::getOperatorType() const {
	return operatorType;
}

TreeNode::~TreeNode() {
	deleteRec(this);
}

void TreeNode::deleteRec(TreeNode* node) {
	if (node) {
		deleteRec(node->getChildFirst());
		deleteRec(node->getChildSecond());
	}
}