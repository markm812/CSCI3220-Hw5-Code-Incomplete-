#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
constexpr auto debugging = 0;

//TODO: 
//	1. assign function for putting value from distance matrix into the tree(s)
//	2. complete buildQuadTree function with assign function
//	3. single link function for picking smallest value outside -1
//
//	。　　　　•　 　ﾟ　　。 　　.			  
//										  
//	..。　   。 .                         
//
//	.。　　　•.• 　　　　•
//
//	ﾟ　　 Red was not An Impostor.ඞ。　.
//
//	'　　　 1 Impostor remains 　 　　。
//
//	ﾟ　　　.　　　. 　　　　.　 .

class quadTree {
public:
	// constructor & deconstructor
	quadTree(quadTree* ptr, int lv);
	~quadTree();

	// return functions
	quadTree* returnThisPtr();
	quadTree* returnAncestorPtr();
	int returnLevel();
	quadTree* returnChildPtr(int which);

	// assign funciton
	void assignChild(int which, quadTree* qt);
private:
	// personal privacy  
	int data = -1;
	int level;

	// an orphanage of size 4
	// 0 -> ChildNE
	// 1 -> ChildSE
	// 2 -> ChildSW
	// 3 -> ChildNW
	quadTree* orphanage[4] = {NULL,NULL,NULL,NULL}; // PS: Look at these pathetic pointers LMAO 
	quadTree* ancestor = NULL; // No mum -> u mum gay 
	quadTree* qtPtr = this; // pointer to the current tree
};

void assignValue(quadTree* qPtr, int** disMtx)
{

}

// build the quad tree
void buildQuadTree(quadTree* qPtr, int depth, int** disMtx)
{
	// Testing
	if (debugging) cout << "current tree depth: " << qPtr->returnLevel() << " target deepth: " << depth << endl;

	// (current depth < target depth) ? build deeper : assign value 
	if (qPtr->returnLevel() < depth)
	{
		for (int i = 0; i < 4; i++)
		{
			quadTree* newChild = new quadTree(qPtr, qPtr->returnLevel() + 1);
			qPtr->assignChild(i, newChild);
			// Testing
			if (debugging) cout << "Created " << i << "th child" << endl;
		}

		for (int i = 0; i < 4; i++)
		{
			buildQuadTree(qPtr->returnChildPtr(i), qPtr->returnChildPtr(i)->returnLevel());
		}
	}
	else
	{
		assignValue(qPtr,disMtx);
	}
}

// convert distance matrix from str to int arr
void strToArr(int** arrPtr, string input, int size, string delimiter, int row)
{
	string s = input, token;
	size_t pos = 0;
	int count = 0;
	while (count < size)
	{
		pos = s.find(delimiter);
		token = s.substr(0, pos);
		arrPtr[row][count++] = stoi(token);
		s.erase(0, pos + delimiter.length());
	}
}

// print out the lower triangle of the distance matrix 
void printArr(int size, int** arrPtr)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < i; j++)
			cout << arrPtr[i][j] << " ";
		cout << endl;
	}
}

int main() 
{
	// scan first line for data
	string firstInput;
	cin >> firstInput;

	// count total elements
	int totalElements = 1; // size of the distance matrix
	for (int i = 0; i < firstInput.length(); i++)
	{
		if (firstInput[i] == ',') totalElements++;
	}

	quadTree* qt = new quadTree(NULL, 0); // tree root

	// calculation for convenience
	int power = int(ceil(log2(totalElements))); // Number of quad tree in total
	int trueSize = int(pow(2, power));

	// building the distance matrix and invaliding useless entries
	int** xmasTree = new int* [trueSize]; // PS: its born on 12/25, its a Christmas tree
	for (int i = 0; i < trueSize; i++)
	{
		string input;
		xmasTree[i] = new int[trueSize];
		if (i == 0)
		{
			strToArr(xmasTree, firstInput, totalElements, ",", i);
			for (int j = i; j < trueSize; j++)
				xmasTree[i][j] = -1;
		}
		else if (i < totalElements)
		{
			cin >> input;
			strToArr(xmasTree, input, totalElements, ",", i);
			for (int j = i; j < trueSize; j++)
				xmasTree[i][j] = -1;
		}
		else
		{
			for (int j = 0; j < trueSize; j++)
				xmasTree[i][j] = -1;
		}
	}
	printArr(totalElements,xmasTree);

	buildQuadTree(qt, power,xmasTree);

	// Testing
	//cout << power << endl;
	//cout << qt->returnThisPtr() << endl;
	//cout << qt->returnAncestorPtr() << endl;
	//cout << qt->returnChildPtr(0);

	return 0;
}

// constructor for quadTree
quadTree::quadTree(quadTree* ptr, int lv)
{
	ancestor = ptr;
	level = lv;
}

// deconstructor
quadTree::~quadTree()
{
}

// return pointer of the current tree
quadTree* quadTree::returnThisPtr()
{
	return qtPtr;
}

// return ancestor pointer of the current tree
quadTree* quadTree::returnAncestorPtr()
{
	return ancestor;
}

// return depth of the current tree
int quadTree::returnLevel()
{
	return level;
}

// return child pointer of the current tree
quadTree* quadTree::returnChildPtr(int which)
{
	return orphanage[which];
}

// assign child for the current tree
void quadTree::assignChild(int which, quadTree* qt)
{
	orphanage[which] = qt;
}


