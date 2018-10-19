#ifndef _QTREGION_H
#define _QTREGION_H

#include <algorithm>
#include "QTPoint.h"

namespace Common
{
	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	This is a class to represent a region(rectangle). This is achieved using two points (m_pStart,m_pEnd).
	//							The Region encompasses [m_pStart,m_pEnd). i.e The Left and Top edge are incuded in the region and Right,
	//							Bottom Edges are excluded from the region.
	//							This class provides wide range if API to facilitate majority of the operations that can be done 
	//							with a region.
	//@Usage				:	The usage of this class is straigh forward, instantiate the class and Use the API where ever necessary.			

	class QTRegion
	{
	private:
		//Start of the region, this point is included in the region.
		QTPoint m_pStart;
		//End of the region, this point is not included in the region. 
		QTPoint m_pEnd;

	public:
		QTRegion();
		QTRegion(QTPoint start, QTPoint end);
		~QTRegion();

	public:
		void SetRegionStart(QTPoint p);
		void SetRegionEnd(QTPoint p);
		bool IsPointsInit();
		bool IsInRegion(QTPoint p);
		QTRegion GetTopLeftChild();
		QTRegion GetTopRightChild();
		QTRegion GetBottomLeftChild();
		QTRegion GetBottomRightChild();
		bool IsRegionClose(QTPoint p, double distance);
		double GetMinDimention();
		double GetDiagonalLength();
	private:
		bool IsStartInit();
		bool IsEndInit();
		void CreateValidRegion();
	};
} // namespace Common
#endif