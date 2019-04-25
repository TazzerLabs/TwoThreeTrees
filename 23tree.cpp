//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST 

#include <iostream>
#include <fstream>
#include <iomanip>
#include "bst.h"
#include "TwoThreeTree.h"
using namespace std;

int main(int argc, char* argv[])
{

	char MainMenu;
	int choice;
	BST myTree;
	TwoThreeTree ourTree;

	if (argc != 2)
	{
		cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if (input.is_open())
	{

		cout << "Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree\nOption: ";
		cin >> MainMenu;

		switch (MainMenu)
		{
		case 'a':


			myTree.buildTree(input);
			input.close();

			while (1)
			{
				choice = 0;
				cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\nOption: ";
				cin >> choice;
                cout << endl;

				//Print index
				if (choice == 1)
					myTree.printTree(cout);
				//Search index for a word
				else if (choice == 2)
					myTree.contains();
				//Save index
				else if (choice == 3)
				{
					string outputFile;
					cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
					cin >> outputFile;
					ofstream output(outputFile.c_str());
					myTree.printTree(output);
					output.close();
					cout << "Saved\n";
				}
				//Quit
				else
					break;
			} // end of while
			break;

		case 'b':

			ourTree.buildTree(input);
			input.close();

			while (1)
			{
				choice = 0;
				cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
				cin >> choice;

				//Print index
				if (choice == 1)
					ourTree.printTree(cout);
				//Search index for a word
				else if (choice == 2)
					ourTree.contains();
				//Save index
				else if (choice == 3)
				{
					string outputFile;
					cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
					cin >> outputFile;
					ofstream output(outputFile.c_str());
					ourTree.printTree(output);
					output.close();
					cout << "Saved\n";
				}
				//Quit
				else
					break;

			} // end of while


			break;

		case 'c':
            {
            
                double Btime, Ttime, start, end;
                
                Btime = Ttime = 0.0;
                
                
                cout << "\n------------------------------\n";
                cout << "Construction of BST";
                cout << "\n------------------------------\n";
                
                BST Btree;
                Btree.buildTree(input);
                
                input.clear();
                input.seekg(0, ios::beg);
                
                cout << "\n------------------------------\n";
                cout << "Construction of Two Three Tree";
                cout << "\n------------------------------\n";
                TwoThreeTree Ttree;
                Ttree.buildTree(input);
                
                input.close();
                
                // Create Search txt file to compare times
                ofstream output("search.txt");
                Ttree.index(output);
                
                output.close();
                
                input.open("search.txt");
                
                // Code from buildTree for reference
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
                            // 23 tree search time
                            start = clock();
                            Ttree.contain(tempWord);
                            end = clock();
                            Ttime += (end-start)/CLOCKS_PER_SEC;
                     
                            // BST search time
                            start = clock();
                            Btree.contain(tempWord);
                            end = clock();
                            Btime += (end-start)/CLOCKS_PER_SEC;
                            tempWord.clear();
                        }

                    } // end of for loop
                    
                } // end of while
                
                cout << "\n------------------------------\n";
                cout << "Total Search Times";
                cout << "\n------------------------------\n";
                cout << setw(40) << std::left << "Binary Search Tree Time: " << Btime << endl;
                cout << setw(40) << std::left << "Two Three Tree Time: " << Ttime << endl << endl;
                
                
                break;
       
            } // end of case c

		default:
			break;

		} // end of switch

	} // end of if
	else
	{
		cout << "Invalid File Name. Restart Program.\n";
		return 2;
	}

	return 0;

}
