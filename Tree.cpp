#include "Tree.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template<typename T>
Node<T>::Node(T value) :
		Node() { //Наследование инициализируюшего конструктора от конструктора по умолчанию
	this->value = value;
}

template<typename T>
Node<T>::Node() {
	value = NULL;
	leftChild = NULL;
	rightChild = NULL;
}

template<typename T>
void Node<T>::show() {
	cout << value << endl;
}

//Создание левого потомка по значению
template<typename T>
void Node<T>::setLeft(T value) {
	this->leftChild = new Node<T>(value);
}

//Создание правого потомка по значению
template<typename T>
void Node<T>::setRight(T value) {
	this->rightChild = new Node<T>(value);
}

//Вернуть левого потомка
template<typename T>
Node<T>* Node<T>::getLeft() {
	return leftChild;
}

//Вернуть правого потомка
template<typename T>
Node<T>* Node<T>::getRight() {
	return rightChild;
}

template<typename T>
Tree<T>::Tree() {
	begin = NULL;
}

template<typename T>
vector<T> sort(vector<T> args) {
	T tmp;
	for (int i = 0; i < args.size(); ++i) {
		for (int j = i + 1; j < args.size(); ++j) {
			if (args[i] > args[j]) {
				tmp = args[i];
				args[i] = args[j];
				args[j] = tmp;
			}
		}
	}
	return args;
}

//template<typename T>
//void Tree<T>::create(vector<T> args) {
//	args = sort<T>(args);
//	struct LR {
//		Node<T>* root;
//		int left, right;
//		LR(Node<T>* root, int left, int right) {
//			this->root = root;
//			this->left = left;
//			this->right = right;
//		}
//	};
//	stack<LR> roots;
//	int middle;
//	middle = (args.size() - 1) / 2;
//	begin = new Node<T>(args[middle]);
//	roots.push(LR{ begin, 0, (int)(args.size() - 1) });
//
//	while (!roots.empty()) {
//		LR& top			= roots.top();
//		int left		= top.left;
//		int right		= top.right;
//		Node<T>* root	= top.root;
//		middle			= (left + right) / 2;
//		roots.pop();
//
//
//		if (left < middle) {
//			root->setLeft(args[(left + middle - 1) / 2]);
//
//				roots.push(LR(root->getLeft(), left, middle - 1));
//
//		}
//		if (right > middle) {
//			root->setRight(args[(right + middle + 1) / 2]);
//			roots.push(LR(root->getRight(), middle + 1, right));
//		}
//
//	}
//
//}

//template<typename T>
//void Tree<T>::show() {
//	stack<Node<T>*> roots;
//	roots.push(begin);
//	while(!roots.empty()){
//		Node<T>* top = roots.top();
//		top->show();  cout << endl;
//		roots.pop();
//		if (top->getLeft() != NULL) {
//			roots.push(top->getLeft());
//		}
//		if (top->getRight() != NULL) {
//			roots.push(top->getRight());
//		}
//
//	}
//}
//template<typename T>
//void f(Node<T>* begin, vector<T> args) {
//	vector<T> vL, vR;
//	int middle = args.size() / 2;
//	//assigned(A, B) - делает срез вектора, итетератора A, до итератора B
//	//begin - итератор на первый элемент
//	//at(A) - итератор на A'ный(по счёту) элемент
//	vL.assign(args.begin(), args.at(middle));
//	vR.assign(args.at(middle + 1), args.end());
//	if (vL.size() != 1) {
//		begin->setLeft(vL[vL.size() / 2]);
//		f(begin->getLeft, vL);
//	}
//	if (vR.size() != 1) {
//		begin->setRight(vR[vR.size() / 2]);
//		f(begin->getRight, vR);
//	}
//}
//
//template<typename T>
//void Tree<T>::create(vector<T> args) {
//	begin = new Node<T>(args[args.size() / 2]);
//	f(begin, args);
//}

template<typename T>
void Tree<T>::create(vector<T> args) {
	args = sort<T>(args);
	struct LR {
		Node<T> *root;
		int left, right;
		LR(Node<T> *begin, int left, int right) {
			this->root = begin;
			this->left = left;
			this->right = right;
		}
	};
	int left = 0;
	int right = args.size() - 1;
	int middle = (left + right) / 2;
	stack<LR*> roots;
	//СМ. в Tree.h, Это указатель на главный корень, с него начинаем, его первого добавляем в стек
	begin = new Node<T>(args[middle]);
	LR *tmp = new LR(begin, left, right);
	roots.push(tmp);
	while (!roots.empty()) {
		//roots[0] -если бы roots был бы вектором
		LR *tmp = roots.top();
		roots.pop();
		middle = (tmp->left + tmp->right) / 2;
		if (tmp->left < middle) {

			//Создание левого соседа.ребенка.корня
			//СМ. Tree.h, функция setLeft(T value)
			//value, вектор args<T>
			//tmp->left + middle - 1) / 2
			//[left, left + 1, left + 2 ..... middle - 1]
			//[left, left + 1, left + 2 ..... middle - 1, middle, ,middle + 1 ... right]
			//tmp->left + middle - 1) / 2 - Новая середина
			tmp->root->setLeft(args[(tmp->left + middle - 1) / 2]);
			LR *cat = new LR(tmp->root->getLeft(), tmp->left, middle - 1);
			roots.push(cat);
		}
		if (tmp->right > middle) {
			tmp->root->setRight(args[(tmp->right + middle + 1) / 2]);
			LR *dog = new LR(tmp->root->getRight(), middle + 1, tmp->right);
			roots.push(dog);
		}
	}
}

template<typename T>
void Tree<T>::show() {
	stack<Node<T>*> roots;
	roots.push(begin);
	do {
		Node<T> *tmp = roots.top();
		tmp->show();
		roots.pop();
		if (tmp->getRight() != NULL)
			roots.push(tmp->getRight());
		if (tmp->getLeft() != NULL)
			roots.push(tmp->getLeft());

	} while (!roots.empty());
}

//if (root->getChild() != NULL) X_order(root->getChild());
//Если есть потомок, то итерируемся - вызываем функию с потомством
template<typename T>
void Tree<T>::pre_order(/*Node<T>* root*/) {
	/*root->show();
	 if (root->getLeft() != NULL) pre_order(root->getLeft());
	 if (root->getRight() != NULL) pre_order(root->getRight());*/

	stack<Node<T>*> roots;	//Создание стека корней
	roots.push(begin);		//Добавление первого корня(главного корня)
	while (!roots.empty()) {	//пока в стеке что-то есть, то
		Node<T> *top = roots.top();		//Достаем первый элемент
		roots.pop();					//И сразу его удаляем
		top->show(); //pre-order -  означает сразу вывод
		if (top->getRight() != NULL)
			roots.push(top->getRight());		//Пополнение стека
		if (top->getLeft() != NULL)
			roots.push(top->getLeft());			//	следующими элементами
	}
}

template<typename T>
void Tree<T>::in_order() {
	stack<Node<T>*> roots;
	roots.push(begin);
	while (!roots.empty()) { //пока в стеке что-то есть, то
		Node<T> *top = roots.top(); //Достаем первый элемент
		if (top->getRight() != NULL)
			roots.push(top->getRight()); //Пополнение стека
		while (top->getLeft() != NULL) {
			roots.push(top->getLeft());
			top = top->getLeft();
		}
		top->show();
		roots.pop();
	}
}

template<typename T>
void Tree<T>::post_order(Node<T> *root) {
	if (root->getLeft() != NULL)
		post_order(root->getLeft());
	if (root->getRight() != NULL)
		post_order(root->getRight());
	root->show();
}
