#include "Quad.h"

using namespace Common;

int main()
{
	
	Quad::SetAtomicSize(1);
	Quad::SetCapacity(4);
	
	QTRegion * pRegion = new QTRegion(new QTPoint(0,0),new QTPoint(1000,1000));
	Quad * pQuad = new Quad(pRegion);

	for (int i = 0; i < 1000; ++i)
	{
		double x = rand() % 1000;
		double y = rand() % 1000;

		QTPoint * pPoint = new QTPoint(x, y);
		pQuad->InsertPoint(pPoint);
	}

	double x = rand() % 1000;
	double y = rand() % 1000;

	QTPoint * pPoint = new QTPoint(x, y);
	vector<QTPoint*> nearestList = pQuad->Search(pPoint, 10);

	delete pQuad;

	return -1;
}
