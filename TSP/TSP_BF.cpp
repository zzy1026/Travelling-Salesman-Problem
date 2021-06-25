#include "TSP_BF.h"
using namespace std;



TSP_BF::TSP_BF(string name)
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

	minCost = INT_MAX;
    visit = new bool[numberOFcities];
	for (int i = 0; i < numberOFcities; i++)
		visit[i] = 0;
	visit[0] = 1;
	int index = 0;
}


TSP_BF::~TSP_BF()
{
	for (int i = 0; i < numberOFcities; i++)
		delete[] costMatrix[i];
	delete[] costMatrix;
	delete[] visit;
}

void TSP_BF::print()
{
	cout << "The cost matrix for Brute force:" << endl;
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

void TSP_BF::result(vector<int>seq)
{
	int temp = 0;
	int pre = -1;
	int i = 1;
	int *path = new int[numberOFcities+1];
	for (int ele : seq) {
		if (pre != -1) {
			temp += costMatrix[pre][ele];
		}
		pre = ele;
		path[i] = ele;
		i++;
	}
	//cout << seq.front() + 1;
	temp += costMatrix[seq.back()][seq.front()];
	path[0] = temp;
	if (temp < minCost) {
		minCost = temp;
	}
	allPath.push_back(path);
}


void TSP_BF::dfs(vector<int>seq, int begin) 
{
	for (int i = 0; i < numberOFcities; i++) {
		if (i == begin)
			continue;
		else {
			if (!visit[i]) {
				visit[i] = 1;
				seq.push_back(i);
				dfs(seq, begin);
				seq.erase(find(seq.begin(), seq.end(), i));
				visit[i] = false;
			}
		}
	}
	if (seq.size() == numberOFcities) {
		result(seq);
	}
	return;
}

void TSP_BF::BF()
{

	vector<int> seq;
	seq.push_back(0);
	dfs(seq, 0);
	for (int i = 0; i < numberOFcities; i++) {
		visit[i] = 0;
	}
	seq.clear();

}

int TSP_BF::getMinCost()
{
	return minCost;
}

int *TSP_BF::getSolution()
{
	int* solution = new int[numberOFcities + 1];
	int k = 0;
	for (int i = 0; i < allPath.size(); i++) {
		if (allPath[i][0] == minCost) {
			for (int j = 0; j < numberOFcities; j++) {
				solution[k] = allPath[i][j + 1];
				k++;
			}
			solution[k] = allPath[i][1];
		}
	}
	return solution;
}