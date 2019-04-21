//
//  TwoThreeTree.h
//  
//
//  Created by Johnathan Soto on 4/13/19.
//

#ifndef TwoThreeTree_h
#define TwoThreeTree_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class TwoThreeTree
{

    public:
        TwoThreeTree();
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
    private:
    struct node{
        node() { left = middle = right = nullptr;}
        node(const string &lx, const &mx, const string &rx, node *l, node *m, node *r, node *p)
        : lkey(lx), mkey(mx), rkey(rx), left(l), middle(m), right(r), parent(p) {
                Llines.resize(0);
                Rlines.resize(0);
                Mlines.resize(0);
        }
        string lkey;
        string mkey;
        string rkey;
        node * left;
        node * middle;
        node * right;
        node * parent;
        vector<int> Llines;
        vector<int> Mlines;
        vector<int> Rlines;
        
    };
    node * root;
    void insertHelper(const string &X, int line, node *& t, int &distWords);
    node* split(node* t);
    bool containsHelper(const string & x, node * t, node* &result) const;
    void printTreeHelper(node *t, ostream & out) const;
    int findHeight(node *t);
    bool isLeaf() { return (left == nullptr && middle == nullptr && right == nullptr); }
    bool isTwoNode();
    bool isThreeNode();
    bool isOneKey();
    bool isTwoKey();
    bool isThreeKey();
    node* lchild() { return left; }
    node* rchild() { return right; }
    node* mchild() { return middle; }
    node* parent() { return parent;}
    string rkey() { return rkey; }
    string mkey() { return mkey;}
    string lkey() { return lkey; }
    void setLeftKey(const string X) { lkey = X;}
    void setMiddleKey(const string X) {middle = X;}
    void setRightKey(const string X) { rkey = X; }
    void setLeftChild(node* t) { left = t; }
    void setRightChild(node* t) { right = t; }
    void setMchild(node* t) { middle = t; }
    void setParent(node* t) {parent = t;}
    
    

};

#endif /* TwoThreeTree_h */
