#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <tchar.h>
#include <vector>


class TSP_BF
{
private:

	int **costMatrix;
	int minCost;
	bool *visit;
	std::vector<int*> allPath;

public:

	int numberOFcities;

	TSP_BF(std::string);

	void print();
	int getMinCost();
	int *getSolution();
	void result(std::vector<int>seq);
	void dfs(std::vector<int>seq, int begin);
	void BF();

	~TSP_BF();
};


