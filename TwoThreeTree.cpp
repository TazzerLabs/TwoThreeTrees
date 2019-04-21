//
//  TwoThreeTree.cpp
//  
//
//  Created by Johnathan Soto on 4/13/19.
//

#include "TwoThreeTree.h"

//Constructor
TwoThreeTree::TwoThreeTree(){
    root = NULL;
}

//Returns true if there are no nodes in the tree
bool TwoThreeTree::isEmpty(){
    return root == NULL;
}

//Used to implement the search function in the main
//program.
void TwoThreeTree::contains() const
{
    string input;
    node *foundNode = NULL;
    cout << "Search word: ";
    cin >> input;
    if(containsHelper(input, root, foundNode))
    {
        cout << "Line Numbers: " << foundNode->lines[0];
        for(int i = 1; i < foundNode->lines.size(); i++)
        cout << ", " <<foundNode->lines[i];
        cout << '\n';
    }
    else
        cout << '\"' << input <<"\" is not in the document\n";
}

//Prints the index to the supplied receiver, either
//cout or the output file
void TwoThreeTree::printTree(ostream & out) const {
    out << "Binary Search Tree Index:\n-------------------------\n";
    printTreeHelper(root, out);
}

//Receives the specified input file and constructs
//the actual tree. Prints a message when finished.
void TwoThreeTree::buildTree(ifstream & input){
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
            while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() )
            {
                tempWord.insert(tempWord.end(), tempLine[i]);
                i++;
            }
           
            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
                tempWord.resize(tempWord.size() -1);
            
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
    totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
    treeHeight = findHeight(root);

    //Print output
    cout << setw(40) << std::left;
    cout << "Total number of words: " << numWords<< endl;

    cout << setw(40) << std::left
    << "Total number of distinct words: " << distWords << endl;

    cout << setw(40) << std::left
    <<"Total time spent building index: " << totalTime << endl;

    cout << setw(40) << std::left
    <<"Height of TwoThreeTree is : " << treeHeight << endl;
 
}

//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
void TwoThreeTree::insertHelper(const string &x, int line, node *& t, int &distWord, node* parentalUnit)
{
    if(!t)
    {
        t = new node(x, "", "", NULL, NULL, NULL, parentalUnit);
        t->Llines.push_back(line);
        distWord++;
    }
    if (t->isOneKey()) // we have 1 key inside our node
    {
    
        if (x.compare(t->lkey) == 0)
            t->Llines.push_back(line);
        else if (x.compare(t->lkey) < 0 )
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
    else // We have two keys inside our node
    {
        if (x.compare(t->lkey) == 0)
            t->Llines.push_back(line);
        else if (x.compare(t->rkey) == 0 )
            t->Rlines.push_back(line);
        else if (x.compare(t->lkey) > 0 && x.compare(t->rkey) > 0)
        {
            t->setMiddleKey(t->rkey);
            t->setRightKey(x);
            t->Mlines = t->Rlines;
            t->Rlines.resize(0);
            t->Rlines.push_back(line);
            // Call split
        }
        else if (x.compare(t->lkey) > 0 && x.compare(t->rkey) < 0)
        {
            t->setMiddleKey(x);
            t->Mlines.push_back(line);
            // Call split
        }
        else if (x.compare(t->lkey) < 0 && x.compare(t->rkey) < 0)
        {
            t->setMiddleKey(t->lkey);
            t->Mlines = t->Llines;
            t->Llines.resize(0);
            t->setLeftKey(x);
            t->Llines.push_back(line);
            // Call Split
        }

        
    }

}

void TwoThreeTree::split(node* t)
{

    if (!t)
        return;
    
    node* j = new node(t->rkey, "", "", NULL, NULL, NULL, NULL);
    j->Llines = t->Rlines;
    t->Rlines.resize(0);
    t->rkey = "";
    
    if (!t->parent)
    {
        
        node* k = new node(t->mkey, "", "", t, NULL, j, NULL);
        j->setParent(k);
        k->Llines = t->Mlines;
        t->Mlines.resize(0);
        t->mkey = "";
        t->setParent(k);
    
    }
    else // else they have a parent
    {
    
        j->setParent(t->parent);
    
        if (t->parent->isOneKey())
        {
    
            if (t->parent->lkey.compare(t->mkey) < 0 )
            {
                t->parent->setRightKey(t->parent->lkey);
                t->parent->Rlines = t->parent->Llines;
                t->parent->setLeftKey(t->mkey);
                t->parent->Llines = t->Mlines;
                t->mkey = "";
                t->Mlines.resize(0);
                
            }
            else
            {
                t->parent->setRightKey(t->mkey);
                t->Rlines = t->Mlines;
                
            }
        }
        else // They have two keys
        {
        
            if (t->mkey.compare(t->parent->lkey) > 0 && t->mkey.compare(t->parent->rkey) > 0)
            {
                t->parent->setMiddleKey(t->parent->rkey);
                t->parent->setRightKey(t->mkey);
                t->parent->Mlines = t->parent->Rlines;
                t->parent->Rlines = t->Mlines;
                
            }
            else if (t->mkey.compare(t->parent->lkey) > 0 && t->mkey.compare(t->parent->rkey) < 0)
            {
                t->parent->setMiddleKey(t->mkey);
                t->parent->Mlines = t->Mlines;
                
            }
            else if (t->mkey.compare(t->parent->lkey) < 0 && t->mkey.compare(t->parent->rkey) < 0)
            {
                t->parent->setMiddleKey(t->parent->lkey);
                t->parent->Mlines = t->parent->Llines;
                t->parent->setLeftKey(t->mkey);
                t->parent->Llines = t->Mlines;
                
            }
            
            t->Mlines.resize(0);
            t->mkey = "";
            
            split(t->parent);
        
        } // end of else parent has 2 keys
            
    } // end of else they have a parent

}

//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool TwoThreeTree::containsHelper(const string & x, node * t, node * &result) const
{
    if (t == NULL)
        return false;
    if (t->lkey.compare(x) == 0 || t->rkey.compare(x) == 0)
    {
                result = t;
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

//Called by printTree(), does the actual formatted printing
void TwoThreeTree::printTreeHelper(node *t, ostream & out) const
{
    if(t == NULL)
        return;
    if (t.isLeaf())
        {
            out << setw(30) << std::left;
            out << t->lkey << " " << t->lines[0];
            for (int i = 1; i < t->lines.size(); i++)
                out << ", " << t->lines[i];
            out << endl;
            if (t->rkey.length() != 0)
            {
                out << setw(30) << std::left;
                out << t->rkey << " " << t->lines[0];
                for (int i = 1; i < t->lines.size(); i++)
                    out << ", " << t->lines[i];
                out << endl;
            }
        }
        else if (t.isTwoNode())
        {
            
            printTreeHelper(t->left, out);
            out << setw(30) << std::left;
            out << t->lkey << " " << t->lines[0];
            for (int i = 1; i < t->lines.size(); i++)
                out << ", " << t->lines[i];
            out << endl;
            if (t->rkey.length() != 0)
            {
                out << setw(30) << std::left;
                out << t->rkey << " " << t->lines[0];
                for (int i = 1; i < t->lines.size(); i++)
                    out << ", " << t->lines[i];
                out << endl;
            }
            printTreeHelper(t->right, out);
            
        }
        else // node is a 3-node
        {
        
            printTreeHelper(t->left, out);
            
            out << setw(30) << std::left;
            out << t->lkey << " " << t->lines[0];
            for (int i = 1; i < t->lines.size(); i++)
                out << ", " << t->lines[i];
            out << endl;
            
            printTreeHelper(t->middle, out);
            
            if (t->rkey.length() != 0)
            {
                out << setw(30) << std::left;
                out << t->rkey << " " << t->lines[0];
                for (int i = 1; i < t->lines.size(); i++)
                    out << ", " << t->lines[i];
                out << endl;
            }
            
            printTreeHelper(t->right, out);
        
        }
    
}

//Returns height of tree. If tree has only one node, height is 1
int TwoThreeTree::findHeight(node *t)
{
    if(t == NULL)
        return 0;
    else
    {
        int leftHeight = findHeight(t->left), rightHeight = findHeight(t->right), middleHeight = findHeight(t->middle);
        
        if(leftHeight > rightHeight)
        {
            if (middleHeight > leftHeight)
                return(middleHeight+1);
            else
                return(leftHeight+1);
        }
        else
        {
            if (middleHeight > rightHeight)
                return(middleHeight+1);
            else
                return(rightHeight+1);
        }
    }
}

bool TwoThreeTree::isOneKey()
{

    return (lkey.compare("") != 0)

}

bool TwoThreeTree::isTwoKey()
{

    return ((lkey.compare("") != 0 && rkey.compare("") != 0 && mkey.compare("") == 0) || (lkey.compare("") != 0 && rkey.compare("") == 0 && mkey.compare("") != 0) || (lkey.compare("") == 0 && rkey.compare("") != 0 && mkey.compare("") != 0));

}

bool TwoThreeTree::isThreeKey()
{

    return (lkey.compare("") != 0 && rkey.compare("") != 0 && mkey.compare("") != 0);

}

bool TwoThreeTree::isTwoNode()
{

    return ((lkey != nullptr && right != nullptr && middle == nullptr) || (left != nullptr && right == nullptr && middle != nullptr) || (left == nullptr && right != nullptr && middle != nullptr));

}

bool TwoThreeTree::isThreeNode()
{

    return (left != nullptr && right != nullptr && middle != nullptr);

}
