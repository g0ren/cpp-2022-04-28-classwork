#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Node {
	T value;
	Node *leftChild;
	Node *rightChild;
public:
	Node();
	Node(T);
	void setLeft(T);
	void setRight(T);
	Node* getLeft();
	Node* getRight();
	void show();
};

template<class T>
class Tree {
	Node<T> *begin;
public:
	Tree();
	Node<T>*root();
	void create(vector<T>);
	void show();
	void pre_order();
	void in_order();
	void post_order(Node<T>*);
};
#endif /* TREE_H_ */
