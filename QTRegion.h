#ifndef _QTREGION_H
#define _QTREGION_H

#include "Common.h"
#include "QTPoint.h"

namespace Common
{
	//Class representign a region(rectangle).
	//The region is represented using 2 Points i.e, Start Point, End Point.
	//This Class makes it feasible for the user to set the points Start , End in any order
	//i.e SetStart(end.x,end.y) and SetEnd(start.x,start.y) is still valid
	//This class is not templated. So, If you want to use it for any custom purpose, 
	//feel free to modify.
	class QTRegion
	{
	private:
		QTPoint * m_pStart;
		QTPoint * m_pEnd;

	public:
		QTRegion();
		QTRegion(QTPoint * start, QTPoint * end);
		~QTRegion();

	public:
		QTPoint * GetRegionStart();
		QTPoint * GetRegionEnd();
		void SetRegionStart(QTPoint * p);
		void SetRegionEnd(QTPoint * p);
		bool IsPointsNull();
		bool IsInRegion(QTPoint * p);
		QTRegion * GetTopLeftChild();
		QTRegion * GetTopRightChild();
		QTRegion * GetBottomLeftChild();
		QTRegion * GetBottomRightChild();
		bool IsRegionClose(QTPoint * p, double distance);
		double GetMinDimention();
	private:
		bool IsStartNull();
		bool IsEndNull();
		void CreateValidRegion();
	};
} // namespace Common
#endif