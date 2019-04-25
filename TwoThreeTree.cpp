//
//  TwoThreeTree.cpp
//  
//
//  Created by Johnathan Soto on 4/13/19.
//

#include "TwoThreeTree.h"
#include "time.h"
#include <iomanip>
#include <sstream>

//Constructor
TwoThreeTree::TwoThreeTree() {
	root = NULL;
}

//Returns true if there are no nodes in the tree
bool TwoThreeTree::isEmpty() {
	return root == NULL;
}

//Returns height of tree. If tree has only one node, height is 1
int TwoThreeTree::findHeight(node *t) {
	if (t == NULL)
		return 0;
	else
	{
		int leftHeight = findHeight(t->left), rightHeight = findHeight(t->right), middleHeight = findHeight(t->middle);

		if (leftHeight > rightHeight)
		{
			if (middleHeight > leftHeight)
				return(middleHeight + 1);
			else
				return(leftHeight + 1);
		}
		else
		{
			if (middleHeight > rightHeight)
				return(middleHeight + 1);
			else
				return(rightHeight + 1);
		}
	}
}

//Used to implement the search function in the main
//program.
void TwoThreeTree::contains() const
{
	string input;
	vector<int> foundList;
	cout << "Search word: ";
	cin >> input;
	if (containsHelper(input, root, foundList))
	{
		cout << "Line Numbers: " << foundList[0];
		for (int i = 1; i < foundList.size(); i++)
			cout << ", " << foundList[i];
		cout << '\n';
	}
	else
		cout << '\"' << input << "\" is not in the document\n";
}

//Prints the index to the supplied receiver, either
//cout or the output file
void TwoThreeTree::printTree(ostream & out) const {
	out << "Binary Search Tree Index:\n-------------------------\n";
	printTreeHelper(root, out);
}

//Receives the specified input file and constructs
//the actual tree. Prints a message when finished.
void TwoThreeTree::buildTree(ifstream & input) {
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof())
	{
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (int i = 0; i < tempLine.length(); i++)
		{
			//Insert valid chars into tempWord until a delimiter( newline or space) is found
			while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length())
			{
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
			}

			//Trim any punctuation off end of word. Will leave things like apostrophes
			//and decimal points
			while (tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
				tempWord.resize(tempWord.size() - 1);

			if (tempWord.length() > 0)
			{
				//Once word is formatted,call insert with the word, the line of the input
				//file it came from, the root of our tree, and the distinct word counter
				insertHelper(tempWord, line, root, distWords, root);
				//Increment our total number of words inserted
				numWords++;
				//Clear out tempWord so we can use it again
				tempWord.clear();
			}

		}
		line++;
	}
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
	treeHeight = findHeight(root);

	//Print output
	cout << setw(40) << std::left;
	cout << "Total number of words: " << numWords << endl;

	cout << setw(40) << std::left
		<< "Total number of distinct words: " << distWords << endl;

	cout << setw(40) << std::left
		<< "Total time spent building index: " << totalTime << endl;

	cout << setw(40) << std::left
		<< "Height of TwoThreeTree is : " << treeHeight << endl;

}

//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
void TwoThreeTree::insertHelper(const string &x, int line, node *& t, int &distWord, node* parentalUnit)
{
	if (!t)
	{
		string emp = "";
		t = new node(x, emp, emp, NULL, NULL, NULL, NULL, parentalUnit);
		t->Llines.push_back(line);
		root = t;
		distWord++;
	}
	else if (x.compare(t->lkey) == 0) // x is found in the left key
		t->Llines.push_back(line);
	else if (x.compare(t->mkey) == 0) // x is found in the middle key
		t->Rlines.push_back(line);
	else if (x.compare(t->rkey) == 0) // x is found in the right key
		t->Rlines.push_back(line);
	else if (!t->isLeaf()) // progress down the tree
	{
		if (t->isOneKey()) // single key node, check if we need to progress left or right
		{
			if (x.compare(t->lkey) < 0) // insert left
				insertHelper(x, line, t->left, distWord, parentalUnit);
			else // insert right
				insertHelper(x, line, t->right, distWord, parentalUnit);
		}
		else // two key node, check if we need to progress left, center, or right
		{
			if (x.compare(t->lkey) < 0) // insert left
				insertHelper(x, line, t->left, distWord, parentalUnit);
			else if (x.compare(t->lkey) > 0 && x.compare(t->rkey) < 0) // insert middle
				insertHelper(x, line, t->middle, distWord, parentalUnit);
			else // insert right
				insertHelper(x, line, t->right, distWord, parentalUnit);
		}
	}
	else if (t->isOneKey()) // we have 1 key inside our node, and it is a leaf
	{
		distWord++;
		if (x.compare(t->lkey) < 0)
		{
			t->setRightKey(t->lkey);
			t->Rlines = t->Llines;
			t->setLeftKey(x);
			t->Llines.resize(0);
			t->Llines.push_back(line);
		}
		else
		{
			t->setRightKey(x);
			t->Rlines.push_back(line);
		}

	}
	else // We have two keys inside our node, and it is a leaf
	{
		distWord++;
		if (x.compare(t->lkey) > 0 && x.compare(t->rkey) > 0)
		{
			t->setMiddleKey(t->rkey);
			t->setRightKey(x);
			t->Mlines = t->Rlines;
			t->Rlines.resize(0);
			t->Rlines.push_back(line);
			split(t);
		}
		else if (x.compare(t->lkey) > 0 && x.compare(t->rkey) < 0)
		{
			t->setMiddleKey(x);
			t->Mlines.push_back(line);
			split(t);
		}
		else if (x.compare(t->lkey) < 0 && x.compare(t->rkey) < 0)
		{
			t->setMiddleKey(t->lkey);
			t->Mlines = t->Llines;
			t->Llines.resize(0);
			t->setLeftKey(x);
			t->Llines.push_back(line);
			split(t);
		}


	}

}

void TwoThreeTree::split(node* t)
{

	if (!t) // there is no node. What happened?
		return;

	string emp = "";
	node* j = new node(t->rkey, emp, emp, NULL, NULL, NULL, NULL, NULL);
	j->Llines = t->Rlines;
	t->Rlines.resize(0);
	t->rkey = "";
	if (!t->isLeaf()) { // Assign pointers from previous split(s)
		j->setLChild(t->mid2);
		j->left->setParent(j);
		j->setRChild(t->right);
		j->right->setParent(j);
		t->setRChild(t->middle);
		t->setMChild(NULL);
		t->setM2Child(NULL);
	}
	if (!t->parent) { // t is the root
		node* k = new node(t->mkey, emp, emp, t, NULL, NULL, j, NULL);
		k->Llines = t->Mlines;
		t->Mlines.resize(0);
		t->mkey = "";
		j->setParent(k);
		t->setParent(k);
		root = k;
	}
	else { // else t is not the root, it has a parent
		j->setParent(t->parent);
		if (t->parent->isTwoNode()) { // no need to split parent
			if (j->lkey.compare(t->parent->lkey) < 0) { // t is parent's left child
				t->parent->setRightKey(t->parent->lkey);
				t->parent->Rlines = t->parent->Llines;
				t->parent->setLeftKey(t->mkey);
				t->parent->Llines = t->Mlines;
				t->mkey = "";
				t->Mlines.resize(0);
				t->parent->setMChild(j);
			}
			else if (t->lkey.compare(t->parent->rkey) > 0) { // t is parent's right child
				t->parent->setRightKey(t->mkey);
				t->parent->Rlines = t->Mlines;
				t->mkey = "";
				t->Mlines.resize(0);
				t->parent->setMChild(t);
				t->parent->setRChild(j);
			}
		}
		else if (t->parent->isThreeNode()) { // will need to split parent
			if (j->lkey.compare(t->parent->lkey) < 0) { // t is parent's left child
				t->parent->setM2Child(t->parent->middle);
				t->parent->setMChild(j);
				t->parent->setMiddleKey(t->parent->lkey);
				t->parent->Mlines = t->parent->Llines;
				t->parent->setLeftKey(t->mkey);
				t->parent->Llines = t->Mlines;
				t->mkey = "";
				t->Mlines.resize(0);
				split(t->parent);
			}
			else if (t->mkey.compare(t->parent->lkey) > 0 && t->mkey.compare(t->parent->rkey) < 0) { // t is parent's middle child
				t->parent->setM2Child(j);
				t->parent->setMiddleKey(t->mkey);
				t->parent->Mlines = t->Mlines;
				t->mkey = "";
				t->Mlines.resize(0);
				split(t->parent);
			}
			else if (t->lkey.compare(t->parent->rkey) > 0) { // t is parent's right child
				t->parent->setM2Child(t);
				t->parent->setRChild(j);
				t->parent->setMiddleKey(t->parent->rkey);
				t->parent->Mlines = t->parent->Rlines;
				t->parent->setRightKey(t->mkey);
				t->parent->Rlines = t->Mlines;
				t->mkey = "";
				t->Mlines.resize(0);
				split(t->parent);
			}
		}
	}
}

//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool TwoThreeTree::containsHelper(const string & x, node * t, vector<int> &result) const
{
	if (t == NULL)
		return false;
	if (t->lkey.compare(x) == 0)
	{
		result = t->Llines;
		return true;
	}
	else if (t->mkey.compare(x) == 0)
	{
		result = t->Mlines;
		return true;
	}
	else if (t->rkey.compare(x) == 0)
	{
		result = t->Rlines;
		return true;
	}
	else if (t->isTwoNode())
	{
		if (t->lkey.compare(x) < 0)
			return containsHelper(x, t->left, result);
		else
			return containsHelper(x, t->right, result);
	}
	else if (t->isThreeNode())
	{

		if (t->lkey.compare(x) < 0)
			return containsHelper(x, t->left, result);
		else if (t->rkey.compare(x) > 0)
			return containsHelper(x, t->right, result);
		else // t->lkey < x < t->rkey
			return containsHelper(x, t->middle, result);

	}

}

bool TwoThreeTree::contain(const string & x) const
{
    return contain(x, root);
}

// Just says wheter or not the string is in the tree, don't care about location
bool TwoThreeTree::contain(const string & x, node* t) const
{
    if (t == NULL)
        return false;
    if (t->lkey.compare(x) == 0)
    {
        return true;
    }
    else if (t->mkey.compare(x) == 0)
    {
        return true;
    }
    else if (t->rkey.compare(x) == 0)
    {
        return true;
    }
    else if (t->isTwoNode())
    {
        if (t->lkey.compare(x) < 0)
            return contain(x, t->left);
        else
            return contain(x, t->right);
    }
    else if (t->isThreeNode())
    {

        if (t->lkey.compare(x) < 0)
            return contain(x, t->left);
        else if (t->rkey.compare(x) > 0)
            return contain(x, t->right);
        else // t->lkey < x < t->rkey
            return contain(x, t->middle);

    }

}

void TwoThreeTree::index(ostream & out)
{
    return index(root, out);
}
//Called by index(), outputs the list of words in the tree, without duplicates
void TwoThreeTree::index(node *t, ostream & out) const
{
    if(t == NULL)
        return;
    else
    {
    
        // left, root left key, middle, root right key, right
        index(t->left, out);
        
        // Do the left key
        out << setw(30) << std::left;
        out << t->lkey << " ";
        
        index(t->middle, out);

        // Do the right key if it exists
        if (t->rkey.compare("") != 0)
        {
            out << setw(30) << std::left;
            out << t->rkey;
        }
    
        index(t->right, out);
    
    } // end of else
    
} // end of index


//Called by printTree(), does the actual formatted printing
void TwoThreeTree::printTreeHelper(node *t, ostream & out) const
{
	if (t == NULL)
		return;
	if (t->isLeaf())
	{
		out << setw(30) << std::left;
		out << t->lkey << " " << t->Llines[0];
		for (int i = 1; i < t->Llines.size(); i++)
			out << ", " << t->Llines[i];
		out << endl;
		if (t->rkey.length() != 0)
		{
			out << setw(30) << std::left;
			out << t->rkey << " " << t->Rlines[0];
			for (int i = 1; i < t->Rlines.size(); i++)
				out << ", " << t->Rlines[i];
			out << endl;
		}
	}
	else if (t->isTwoNode())
	{

		printTreeHelper(t->left, out);
		out << setw(30) << std::left;
		out << t->lkey << " " << t->Llines[0];
		for (int i = 1; i < t->Llines.size(); i++)
			out << ", " << t->Llines[i];
		out << endl;
		printTreeHelper(t->right, out);

	}
	else // node is a 3-node
	{

		printTreeHelper(t->left, out);

		out << setw(30) << std::left;
		out << t->lkey << " " << t->Llines[0];
		for (int i = 1; i < t->Llines.size(); i++)
			out << ", " << t->Llines[i];
		out << endl;

		printTreeHelper(t->middle, out);

		if (t->rkey.length() != 0)
		{
			out << setw(30) << std::left;
			out << t->rkey << " " << t->Rlines[0];
			for (int i = 1; i < t->Rlines.size(); i++)
				out << ", " << t->Rlines[i];
			out << endl;
		}

		printTreeHelper(t->right, out);

	}

}
