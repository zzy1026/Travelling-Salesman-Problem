#include "TSP_BB.h"
#include "Node.h"
#include <queue>
using namespace std;

TSP_BB::TSP_BB(string name)
{
	fstream inputfile;
	inputfile.open(name, ios::in);
	if (inputfile.good())
	{
		inputfile >> numberOFcities;
		costMatrix = new int*[numberOFcities];
		for (int i = 0; i < numberOFcities; i++)
		{
			costMatrix[i] = new int[numberOFcities];
			for (int j = 0; j < numberOFcities; j++)
				inputfile >> costMatrix[i][j];
		}
	}
	else
		cout << "can not find input.txt" << endl;
	inputfile.close();
}



TSP_BB::~TSP_BB()
{
	for (int i = 0; i < numberOFcities; i++)
		delete[] costMatrix[i];
	delete[] costMatrix;
}




void TSP_BB::print()
{
	cout << "The cost matrix for Branch and Bound :" << endl;
	for (int i = 0; i < numberOFcities; i++)
		cout << setw(3) << " " << i;
	cout << endl;
	for (int i = 0; i < numberOFcities; i++)
	{
		cout << i << " ";
		for (int j = 0; j < numberOFcities; j++)
			cout << setw(3) << costMatrix[i][j] << " ";
		cout << endl;
	}
}
class cmpLowerBound
{
public:
	bool operator() (const Node *node1, const Node *node2)
	{
		if (node1->lowerBound > node2->lowerBound) return true;
		else return false;
	}
};
void TSP_BB::BB()
{
	priority_queue <Node*, vector<Node*>, cmpLowerBound> pq;
	Node *n = new Node(costMatrix, numberOFcities, NULL, 0);
	pq.push(n);

	int minCost = INT_MAX;
	endNode = NULL;
	while (!pq.empty())
	{
		Node * n = pq.top();
		pq.pop();

		if (n->endPath())
		{
			if (minCost > n->lowerBound)
			{
				endNode = n;
				minCost = n->lowerBound;
			}
			continue;
		}
		if (n->lowerBound > minCost)
		{
			continue;
		}
		vector<Node*>* children = n->generateChildren();
		for (auto it = children->begin(); it != children->end(); it++)
		{
			pq.push(*it);
		}
		children->clear();
		children->shrink_to_fit();

	}
}

int TSP_BB::getMinCost()
{
	return endNode->lowerBound;
}

int *TSP_BB::getSolution()
{
	int* solution = new int[numberOFcities+1];
	int i = 0;
	for (auto it = endNode->path.begin(); it != endNode->path.end(); it++)
	{
		solution[i]= *it ;
		i++;
	}
	solution[i] = endNode->path.at(0);
	return solution;
}


