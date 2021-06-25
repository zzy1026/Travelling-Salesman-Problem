#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <tchar.h>
#include "Node.h"


class TSP_BB
{
private:

	int **costMatrix;
	Node* endNode;


public:

	int numberOFcities;
	TSP_BB(std::string);

	void print();
	int getMinCost();
	int *getSolution();

	void BB();

	~TSP_BB();
};

