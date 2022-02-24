/*
¶þ²æËÑË÷Ê÷
*/
#include<stdio.h>
#include<algorithm>
#include<random>
#include<time.h>
#include<iostream>
#include<queue>
using namespace std;

template<typename T>
struct node {
	T data;
	node<T>* left;
	node<T>* right;
	node<T>* parent;
};

template<typename T>
class BINARY_SEARCH_TREE {
	node<T>* root;
	size_t size;
public:
	BINARY_SEARCH_TREE():root(nullptr) {}
	BINARY_SEARCH_TREE(T* Array, size_t s);
	node<T>* Search(T x);
	void Print_tree_inorder();
	void Print_tree_levelorder();
	void Inorder_tree_walk(node<T>* cur);
	void Insert(T x);
	void Delete(T x);
	void Transplant(node<T>* u, node<T>* v);
	node<T>* Minimum();
	node<T>* Minimum(node<T>* cur);
	node<T>* Maximum();
	node<T>* Maximum(node<T>* cur);
};
template<typename T>
BINARY_SEARCH_TREE<T>::BINARY_SEARCH_TREE(T* Array, size_t s) {
	size = s;
	if (s == 0)	
		return;
	bool* flag = new bool[s] {};
	default_random_engine e(time(0));
	uniform_int_distribution<unsigned> u(0, size - 1);
	size_t index;
	while (s--){
		while (flag[index = u(e)]);
		flag[index] = true;
		Insert(Array[index]);
	}
}

template<typename T>
node<T>* BINARY_SEARCH_TREE<T>::Search(T x) {
	node<T>* cur = root;
	while (cur != nullptr && cur->data != x) {
		if (x < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return cur;
}

template<typename T>
void BINARY_SEARCH_TREE<T>::Print_tree_inorder(){
	Inorder_tree_walk(root);
	cout << endl;
}

template<typename T>
void BINARY_SEARCH_TREE<T>::Print_tree_levelorder(){
	queue<node<T>*> q;
	q.push(root);
	while (!q.empty()) {
		node<T>* cur = q.front();
		q.pop();
		if (cur == nullptr) {
			cout << "- ";
		}
		else {
			cout << cur->data << " ";
			q.push(cur->left);
			q.push(cur->right);
		}
	}
	cout << endl;
}

template<typename T>
void BINARY_SEARCH_TREE<T>::Inorder_tree_walk(node<T>* cur){
	if (cur != nullptr) {
		Inorder_tree_walk(cur->left);
		cout << cur->data << ' ';
		Inorder_tree_walk(cur->right);
	}
}

template<typename T>
void BINARY_SEARCH_TREE<T>::Insert(T x){
	node<T>* elem = new node<T>;
	elem->data = x;
	elem->left = nullptr;
	elem->right = nullptr;
	node<T>* p = nullptr;
	node<T>* cur = root;
	while (cur != nullptr) {
		p = cur;
		if (x < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}
	elem->parent = p;
	if (p == nullptr)
		root = elem;
	else if (x < p->data)
		p->left = elem;
	else
		p->right = elem;
}

template<typename T>
void BINARY_SEARCH_TREE<T>::Delete(T x){
	node<T>* cur = Search(x);
	if (cur->left == nullptr)
		Transplant(cur, cur->right);
	else if (cur->right == nullptr)
		Transplant(cur, cur->left);
	else {
		node<T>* y = Minimum(cur->right);
		if (y->parent != cur) {
			Transplant(y, y->right);
			y->right = cur->right;
			y->right->parent = y;
		}
		Transplant(cur, y);
		y->left = cur->left;
		y->left->parent = y;
	}
	delete cur;
}

template<typename T>
void BINARY_SEARCH_TREE<T>::Transplant(node<T>* u, node<T>* v){
	if (u->parent == nullptr)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != nullptr)
		v->parent = u->parent;
}

template<typename T>
node<T>* BINARY_SEARCH_TREE<T>::Minimum(){
	return Minimum(root);
}

template<typename T>
node<T>* BINARY_SEARCH_TREE<T>::Minimum(node<T>* cur){
	while (cur->left != nullptr) {
		cur = cur->left;
	}
	return cur;
}

template<typename T>
node<T>* BINARY_SEARCH_TREE<T>::Maximum(){
	return Maximum(root);
}

template<typename T>
node<T>* BINARY_SEARCH_TREE<T>::Maximum(node<T>* cur){
	while (cur->right != nullptr) {
		cur = cur->right;
	}
	return cur;
}

int main() {
	int a[10] = { 3,0,1,4,8,10,2,5,11,6 };
	BINARY_SEARCH_TREE<int> Tree(a, 10);
	cout << "Initializing Tree:" << endl;
	Tree.Print_tree_inorder();
	cout << "Level Order:" << endl;
	Tree.Print_tree_levelorder();
	cout << "Minimum:" << endl;
	cout << Tree.Minimum()->data << endl;
	cout << "Maximum:" << endl;
	cout << Tree.Maximum()->data << endl;
	cout << "Search 8's minimum:" << endl;
	cout << Tree.Minimum(Tree.Search(8))->data << endl;
	cout << "Search 2's minimum:" << endl;
	cout << Tree.Maximum(Tree.Search(2))->data << endl;
	cout << "Delete 8:" << endl;
	Tree.Delete(8);
	Tree.Print_tree_levelorder();

	system("pause");
	return 0;
}