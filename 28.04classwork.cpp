#include <iostream>
#include <vector>
#include "Tree.h"
#include "Tree.cpp"
using namespace std;

int main() {
	vector<int> v{0,1,2,3,4,5,6,7,8,9};
	Tree<int> t;
	t.create(v);
	t.pre_order();
	cout<<"----"<<endl;
	t.in_order();
	return 0;
}
