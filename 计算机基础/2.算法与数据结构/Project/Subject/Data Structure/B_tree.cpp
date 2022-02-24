/*
BÊ÷
*/
#include<stdio.h>
#include<algorithm>
#include<random>
#include<time.h>
#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<fstream>
using namespace std;
template<typename T>
struct B_Tree_Node {
	vector<T> key;
	bool leaf = false;
	vector<B_Tree_Node<T>*> child;
	size_t n() { return key.size(); }
};

template<typename T>
class B_Tree {
	B_Tree_Node<T>* root;
	size_t t;
public:
	B_Tree(size_t t0 = 2) :t(t0) {
		root = new B_Tree_Node<T>;
		root->leaf = true;
	}
	void Insert(T k);
	void Delete(T k);
	void Delete(B_Tree_Node<T>* x, T k);
	void printTree();
	void printTree(B_Tree_Node<T>* x);
	pair<B_Tree_Node<T>*, int> Search(T k);
	pair<B_Tree_Node<T>*, int> Search(B_Tree_Node<T>* x, T k);

private:
	void SplitChild(B_Tree_Node<T>* x, size_t i);
	void insertNonFull(B_Tree_Node<T>* x, T k);
};


template<typename T>
void B_Tree<T>::Insert(T k){
	B_Tree_Node<T>* r = root;
	if (r->n() == 2*t - 1) {							//if key of root is too full to insert new value 
		B_Tree_Node<T>* s = new B_Tree_Node<T>;
		root = s;
		s->leaf = false;
		s->child.push_back(r);
		SplitChild(s, 0);
		insertNonFull(s, k);
	}
	else
		insertNonFull(r, k);
}

template<typename T>
void B_Tree<T>::Delete(T k){
	Delete(root, k);
}

template<typename T>
void B_Tree<T>::Delete(B_Tree_Node<T>* x, T k){
	int i = 0;
	while (i <= x->n() - 1 && k > x->key[i])
		i++;
	if (i < x->n()&&k == x->key[i])	{
		if (x->leaf) {									//case 1
			while (i <= x->n()-2) {//delete k
				x->key[i] = x->key[i + 1];
				i++;
			}
			x->key.pop_back();
			x->child.pop_back();
		}
		else {											//case 2
			B_Tree_Node<T>* y = x->child[i];//predecessor
			B_Tree_Node<T>* z = x->child[i + 1];//successor
			if (y->n() >= t) {							//case 2a
				x->key[i] = y->key.back();
				Delete(y, x->key[i]);
			}
			else if (z->n() >= t) {						//case 2b
				x->key[i] = z->key[0];
				Delete(z, x->key[i]);
			}
			else {										//case 2c
				y->key.push_back(k);
				for (int j = 0; j <= z->n() - 1; j++) {//copy k and z to back of y
					y->key.push_back(z->key[j]);
					y->child.push_back(z->child[j]);
				}
				y->child.push_back(z->child[z->n()]);
				while (i <= x->n() - 2) {//delete k,z
					x->key[i] = x->key[i + 1];
					x->child[i + 1] = x->child[i + 2];
					i++;
				}
				x->key.pop_back();
				x->child.pop_back();
				Delete(y, k);
			}
		}
	}
	else {												//case 3
		if (x->child[i]->n() >= t) {
			Delete(x->child[i], k);
		}
		else {
			B_Tree_Node<T>* y, *z;
			if(i - 1 >= 0)
				y = x->child[i - 1];//left-bro
			if(i + 1 < x->n())
				z = x->child[i + 1];//right-bro
			B_Tree_Node<T>* cur = x->child[i];
			if (i - 1 >= 0&& y->n() >= t) {				//case 3a
				cur->key.insert(cur->key.begin(), x->key[i - 1]);
				cur->child.insert(cur->child.begin(), y->child.back());
				x->key[i - 1] = y->key.back();
				y->key.pop_back();
				y->child.pop_back();
				Delete(cur, k);
			}
			else if (i + 1 < x->n() && z->n() >= t) {
				cur->key.push_back(x->key[i]);
				cur->child.push_back(z->child.front());
				x->key[i] = z->key.front();
				z->key.erase(z->key.begin());
				z->child.erase(z->child.begin());
				Delete(cur, k);
			}
			else {										//case 3b
				if (i - 1 >= 0) {
					y->key.push_back(x->key[i - 1]);
					for (int j = 0; j < cur->n(); j++) {
						y->key.push_back(cur->key[j]);
						y->child.push_back(cur->child[j]);
					}
					y->child.push_back(cur->child.back());
					while (i <= x->n() - 1) {
						x->key[i - 1] = x->key[i];
						x->child[i] = x->child[i + 1];
						i++;
					}
					x->key.pop_back();
					x->child.pop_back();
					if (root->n() == 0)
						root = root->child[0];
					Delete(y, k);
				}
				else if (i + 1 <= x->n()) {
					cur->key.push_back(x->key[i - 1]);
					for (int j = 0; j < z->n(); j++) {
						cur->key.push_back(z->key[j]);
						cur->child.push_back(z->child[j]);
					}
					cur->child.push_back(z->child.back());
					while (i <= x->n() - 2) {
						x->key[i] = x->key[i + 1];
						x->child[i + 1] = x->child[i + 2];
						i++;
					}
					x->key.pop_back();
					x->child.pop_back();
					if (root->n() == 0)
						root = root->child[0];
					Delete(cur, k);
				}
			}
		}
	}
}

template<typename T>
void B_Tree<T>::printTree(){
	printTree(root);
}

template<typename T>
void B_Tree<T>::printTree(B_Tree_Node<T>* x) {//print tree of root x in level order
	queue<pair<B_Tree_Node<T>*,int>> q;
	q.push(make_pair(x,0));
	int ntag = 0;
	while (!q.empty()) {
		B_Tree_Node<T>* tmp = q.front().first;
		int tag = q.front().second;
		q.pop();
		if (tag > ntag) {
			cout << '\n';
			ntag = tag;
		}
		cout << "|";
		if (tmp) {
			if (!tmp->key.empty())
				for (auto c = tmp->key.begin(); c != tmp->key.end();) {
					cout << *c;
					if (++c != tmp->key.end())
						cout << ' ';
				}
			else
				cout << "-";
			if (!tmp->child.empty())
				for (auto c : tmp->child)
					q.push(make_pair(c, tag + 1));
		}
		cout << "| ";
	}
}

template<typename T>
pair<B_Tree_Node<T>*, int> B_Tree<T>::Search(T k){
	return Search(root, k);
}

template<typename T>
pair<B_Tree_Node<T>*,int> B_Tree<T>::Search(B_Tree_Node<T>* x, T k){
	int i = 0;
	while (i <= x->n() - 1 && k > x->key[i])
		i++;
	if (i <= x->n() - 1 && k == x->key[i])
		return make_pair(x, i);
	else if (x->leaf)
		return make_pair((B_Tree_Node<T>*)nullptr, 0);
	else
		return Search(x->child[i], k);
}

template<typename T>
void B_Tree<T>::SplitChild(B_Tree_Node<T>* x, size_t i){
	B_Tree_Node<T>* z = new B_Tree_Node<T>;
	B_Tree_Node<T>* y = x->child[i];
	z->leaf = y->leaf;
	for (int j = 0; j < t - 1; j++)					//move key(t~2t-2) of y to z
		z->key.push_back(y->key[j + t]);
	for (int j = 0; j < t; j++)					//move children(t~2t-1) of y to z
		z->child.push_back(y->child[j + t]);
	x->child.push_back((B_Tree_Node<T>*)nullptr);
	for (int j = x->n() + 1; j > i + 1; j--)		//move children(i+1~n) of x back 1 space
		x->child[j] = x->child[j - 1];
	x->child[i + 1] = z;
	T tmpk;
	x->key.push_back(tmpk);
	for (int j = x->n() - 1; j > i; j--)				//move key(i~n-1) of x back 1 space
		x->key[j] = x->key[j - 1];
	x->key[i] = y->key[t - 1];
	while (y->n() != t - 1) {						//shrink space of y to t-1
		y->key.pop_back();
		y->child.pop_back();
	}
}

template<typename T>
void B_Tree<T>::insertNonFull(B_Tree_Node<T>* x, T k){
	int i = x->n() - 1;
	if (x->leaf) {
		if(x->child.empty())
			x->child.push_back((B_Tree_Node<T>*)nullptr);
		x->child.push_back((B_Tree_Node<T>*)nullptr);
		x->key.push_back(k);
		while(i >= 0 && k < x->key[i]) {
			x->child[i + 2] = x->child[i + 1];
			x->key[i + 1] = x->key[i];
			i--;
		}
		x->key[i + 1] = k;
	}
	else {
		while (i >= 0 && k < x->key[i])
			i--;
		i++;
		if (x->child[i]->n() == 2*t - 1) {
			SplitChild(x, i);
			if (k > x->key[i])
				i++;
		}
		insertNonFull(x->child[i], k);
	}
}


int main() {
	B_Tree<int> btree;
	FILE* fp = fopen("ts.txt", "r");
	int k;
	cout << "Insert nums from File ts.txt\n";
	while(fscanf(fp, "%d", &k)==1) {
		btree.Insert(k);
	}
	btree.printTree();
	cout << "\nSearch 69:\n";
	auto tmpsearch = btree.Search(69);
	if (tmpsearch.first) {
		cout << tmpsearch.first->key[tmpsearch.second] << " in :";
		btree.printTree(tmpsearch.first);
	}
	else
		cout << "Fail to find it!";
	cout << "\nDelete \n";
	btree.Delete(6);
	btree.printTree();
	cout << "\n";
	fclose(fp);
	system("pause");
	return 0;
}