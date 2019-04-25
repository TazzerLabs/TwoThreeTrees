.PHONY : twoThreeTree
twoThreeTree:
	g++ -std=c++11 23tree.cpp bst.cpp TwoThreeTree.cpp -o twoThreeTree.o	

.PHONY : clean
clean:
	rm -rf search.txt twoThreeTree.o
