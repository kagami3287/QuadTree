#include "Quad.h"
#include "Windows.h"
#include "ProfileCPU.h"
#include <iostream>

#define PROFILE_CPU

using namespace Common;

void UsageSample()
{
	Quad::SetAtomicSize(1);
	Quad::SetCapacity(4);

	QTRegion pRegion = QTRegion(QTPoint(0, 0), QTPoint(1000, 1000));
	Quad * pQuad = new Quad(pRegion);

	PROFILER_INIT("timer.txt");
	PROFILER_START;
	for (int i = 0; i < 100000; ++i)
	{
		double x = rand() % 1000;
		double y = rand() % 1000;

		QTPoint pPoint = QTPoint(x, y);
		pQuad->InsertPoint(pPoint);
	}
	PROFILER_STOP("Total InsertPoint time");
	double x = rand() % 1000;
	double y = rand() % 1000;

	QTPoint pPoint = QTPoint(x, y);
	PROFILER_START;
	std::vector<QTPoint> nearestList = pQuad->Search(pPoint, 10);
	PROFILER_STOP("Search 100 points time");
	PROFILER_DEINIT;
	delete pQuad;
}

void BenchmarkSample()
{
	auto GetNumPixels = [](int size, double atomicsize)
	{
		int ret = 1;
		double dSize = size;
		while (dSize / 2 >= atomicsize)
		{
			dSize = dSize / 2;
			ret = ret * 4;
		}
		return ret;
	};

	auto GetNearest2Power = [](int n)
	{
		int ret = 0;
		while (n / 2 > 0)
		{
			n = n / 2;
			++ret;
		}
		return ret;
	};

	auto GetGPSum = [](int n)
	{
		unsigned long long numerator = pow(4, n + 1) - 1;
		return numerator / 3;
	};

	char pInsertText[512];
	char pSearchText[512];
	char pOutputText[512];

	int nIterations = 20;
	std::vector<double> vAtomicSize = { 0.25,0.5,1,2,4 };
	std::vector<int> vCapacity = { 1,2,4,8,16 };
	std::vector<int> vGridSize = { 100,200,500,1000,2000 };
	std::vector<int> vInsertSize = { 100,200,500,1000,2000,5000,10000,20000,50000,100000 };
	std::vector<int> vSearchSize = { 10,50,100,200,500,1000,2000,5000 };

	Quad * pQuad;

	double dAtomicSize;
	int nCapacity;
	int nGridSize;
	int nInsertSize;
	int nSearchSize;

	//Iterate trough different values of each parameter, create grid , insert points, search.
	for (int nASIndex = 0; nASIndex < vAtomicSize.size(); ++nASIndex)
	{
		dAtomicSize = vAtomicSize[nASIndex];
		Quad::SetAtomicSize(dAtomicSize);

		for (int nCIndex = 0; nCIndex < vCapacity.size(); ++nCIndex)
		{
			nCapacity = vCapacity[nCIndex];
			Quad::SetCapacity(nCapacity);

			for (int nGSIndex = 0; nGSIndex < vGridSize.size(); ++nGSIndex)
			{
				nGridSize = vGridSize[nGSIndex];
				for (int nISIndex = 0; nISIndex < vInsertSize.size(); ++nISIndex)
				{
					nInsertSize = vInsertSize[nISIndex];
					for (int nSSIndex = 0; nSSIndex < vSearchSize.size(); ++nSSIndex)
					{
						nSearchSize = vSearchSize[nSSIndex];

						int nNumOfPixels = GetNumPixels(nGridSize, dAtomicSize);
						int nLargest2PowerLessthan = GetNearest2Power(nNumOfPixels);
						unsigned long long nNumInsertPointsPossible = GetGPSum(nLargest2PowerLessthan) * nCapacity;

						std::cout << nNumInsertPointsPossible << std::endl;

						if (nInsertSize <= nNumInsertPointsPossible && nSearchSize <= nInsertSize)
						{

							for (int iter = 0; iter < nIterations; ++iter) // iterating on each configuration for 20 times
							{
								PROFILER_INIT("timer.txt");
								pQuad = new Quad(QTRegion(QTPoint(0, 0), QTPoint(nGridSize, nGridSize)));

								//Output : Iter_id : AS : C : GS : IS : SS
								sprintf(pOutputText, "Output:%i:%f:%i:%i:%i:%i\n", iter, dAtomicSize,
									nCapacity, nGridSize, nInsertSize, nSearchSize);

								std::cout << pOutputText;

								//Insert : Iter_id : AS : C : GS : IS : SS
								sprintf(pInsertText, "Insert:%i:%f:%i:%i:%i:%i", iter, dAtomicSize,
									nCapacity, nGridSize, nInsertSize, nSearchSize);
								//Search : Iter_id : AS : C : GS : IS : SS
								sprintf(pSearchText, "Search:%i:%f:%i:%i:%i:%i", iter, dAtomicSize,
									nCapacity, nGridSize, nInsertSize, nSearchSize);

								PROFILER_START;
								for (int i = 0; i < nInsertSize; ++i)
								{
									double x = rand() % nGridSize;
									double y = rand() % nGridSize;

									QTPoint pPoint = QTPoint(x, y);
									pQuad->InsertPoint(pPoint);
								}

								PROFILER_STOP(pInsertText);
								double x = rand() % nGridSize;
								double y = rand() % nGridSize;

								QTPoint pPoint = QTPoint(x, y);
								PROFILER_START;
								std::vector<QTPoint> nearestList = pQuad->Search(pPoint, nSearchSize);
								PROFILER_STOP(pSearchText);
								PROFILER_DEINIT;
								delete pQuad;
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	BenchmarkSample();

	return 0;
}
