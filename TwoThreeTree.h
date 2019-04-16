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
        node(const string &lx, const string &rx, node *l, node *m, node *r, )
        :lkey(lx), rkey(rx), left(l), middle(m), right(r){
                Llines.resize(0);
                Rlines.resize(0);
        }
        string lkey;
        string rkey;
        node * left;
        node * middle;
        node * right;
        vector<int> Llines;
        vector<int> Rlines;
    };
    node * root;
    void insertHelper(const string &X, int line, node *& t, int &distWords);
    node* splitLeaf(node* t, string& X);
    node* splitNode(node* t, node* join, string& X);
    bool containsHelper(const string & x, node * t, node* &result) const;
    void printTreeHelper(node *t, ostream & out) const;
    int findHeight(node *t);
    bool isLeaf() { return left == nullptr; }
    bool isTwoNode();
    bool isThreeNode();
    node* lchild() { return left; }
    node* rchild() { return right; }
    node* mchild() { return middle; }
    string rkey() { return rkey; }
    string lkey() { return lkey; }
    void setLeft(const string X) { lkey = X;}
    void setRight(const string X) { rkey = X; }
    void setLeftChild(node* t) { left = t; }
    void setRightChild(node* t) { right = t; }
    void setMchild(node* t) { middle = t; }
    

};

#endif /* TwoThreeTree_h */
