#include "TSP_BB.h"
#include "TSP_BF.h"
#include <Windows.h>
using namespace std;

LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}

int main()
{
	LARGE_INTEGER performanceCountStart, performanceCountEnd;
	unsigned _int64 freq;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&freq));

	string file_name = "input.txt";

	//Brute Force for TSP
	TSP_BF *T1;
	T1 = NULL;

	T1 = new TSP_BF(file_name);
	T1->print();

	performanceCountStart = startTimer();
	T1->BF();
	performanceCountEnd = endTimer();

	int n1 = T1->numberOFcities;
	int cost1 = T1->getMinCost();
	int *path1 = T1->getSolution();

	ofstream ofile1;
	ofile1.open("BF.txt");
	ofile1 << "Solution : " ;
	for (int i = 0; i < n1; i++)
	{
		ofile1 << path1[i] << " - ";
	}
	ofile1 << path1[n1] << endl;
	ofile1 << "Cost     : " << cost1 << endl;
	cout << "Cost     : " << cost1 << endl;
	double tm1 = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / (double)freq ;
	ofile1 << "Time     : " << tm1 << "s" << endl;
	cout << "Time     : " << tm1 << "s" << endl;
	cout << endl;
	//Branch and Bound for TSP
	TSP_BB *T2;
	T2 = NULL;

	T2 = new TSP_BB(file_name);
	T2->print();
	performanceCountStart = startTimer();
	T2->BB();
	performanceCountEnd = endTimer();

	int n2 = T2->numberOFcities;
	int cost2 = T2->getMinCost();
	int *path2 = T2->getSolution();

	ofstream ofile2;
	ofile2.open("BB.txt");
	ofile2 << "Solution : ";
	for (int i = 0; i < n2; i++)
	{
		ofile2 << path2[i] << " - ";
	}
	ofile2 << path2[n2] << endl;
	ofile2 << "Cost     : " << cost2 << endl;
	cout << "Cost     : " << cost2 << endl;
	double tm2 = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / (double)freq;
	ofile2 << "Time     : " << tm2 << "s" << endl;
	cout << "Time     : " << tm2 << "s" << endl;

	delete[] path1;
	delete[] path2;
	system("pause");
	return 0;
}

