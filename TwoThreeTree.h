//
//  TwoThreeTree.h
//  
//
//  Created by Johnathan Soto on 4/13/19.
//

#ifndef TwoThreeTree_h
#define TwoThreeTree_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class TwoThreeTree
{

public:
	TwoThreeTree();
	void contains() const;
	bool isEmpty();
	void printTree(ostream & out = cout) const;
	void buildTree(ifstream & input);
    void index(ostream & out);
    bool contain(const string & x) const;
private:
	struct node {
		node() { left = middle = right = nullptr; }
		node(const string &lx, const string &mx, const string &rx, node *l, node *m, node *m2, node *r, node *p)
			: lkey(lx), mkey(mx), rkey(rx), left(l), middle(m), mid2(m2), right(r), parent(p) {
			Llines.resize(0);
			Rlines.resize(0);
			Mlines.resize(0);
		}
		string lkey;
		string mkey;
		string rkey;
		node * left;
		node * middle;
		node * mid2;
		node * right;
		node * parent;
		vector<int> Llines;
		vector<int> Mlines;
		vector<int> Rlines;
		bool isLeaf() { return (left == nullptr && right == nullptr && middle == nullptr); }
		bool isTwoNode() { return (left != nullptr && right != nullptr && middle == nullptr); }
		bool isThreeNode() { return (left != nullptr && right != nullptr && middle != nullptr); }
		bool isOneKey() { return (lkey.compare("") != 0 && rkey.compare("") == 0 && mkey.compare("") == 0); }
		bool isTwoKey() { return (lkey.compare("") != 0 && rkey.compare("") != 0 && mkey.compare("") == 0); }
		bool isThreeKey() { return (lkey.compare("") != 0 && rkey.compare("") != 0 && mkey.compare("") != 0); }
		void setLeftKey(string x) { lkey = x; }
		void setMiddleKey(string x) { mkey = x; }
		void setRightKey(string x) { rkey = x; }
		void setLChild(node *t) { left = t; }
		void setMChild(node *t) { middle = t; }
		void setM2Child(node *t) { mid2 = t; }
		void setRChild(node *t) { right = t; }
		void setParent(node *t) { parent = t; }

	};
	node * root;
	void split(node* t);
	void insertHelper(const string &x, int line, node *& t, int &distWords, node* parentalUnit);
	bool containsHelper(const string & x, node * t, vector<int> &result) const;
    bool contain(const string & x, node * t) const;
	void printTreeHelper(node *t, ostream & out) const;
	int findHeight(node *t);
    void index(node *t, ostream & out) const;
};

#endif /* TwoThreeTree_h */
