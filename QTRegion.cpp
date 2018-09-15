#include "QTRegion.h"

namespace Common
{
	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Constructor. Instantiates the region to (negative infinity,negative infinity) or 
	//							simply put invalid region.
	QTRegion::QTRegion()
	{
		this->m_pStart = QTPoint(-DBL_MAX, -DBL_MAX);
		this->m_pEnd = QTPoint(-DBL_MAX, -DBL_MAX);
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Constructor. Instantiates the object as per inputs. This function facilitates the user 
	//							to give inputs in any order. combinations like cotr(end,start) , ctor((start.x,end.y),(end.x,start.y))
	//							are also valid inputs and the correct results, i.e results same as that of ctor(start,end). So, the user
	//							need not order the points in his code.
	//							need not sort the inputs before sending.
	//@Input1				:	start point (QTPoint).
	//@Input2				:	end point (QTPoint).
	QTRegion::QTRegion(QTPoint start, QTPoint end)
	{
		this->m_pStart = start;
		this->m_pEnd = end;
		CreateValidRegion();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Destructor.
	QTRegion::~QTRegion()
	{
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to set the Start Point of the region. It is valid if the user gives 'end' as input, given
	//							the input to SetRegionEnd() method is 'start'.
	//@Input1				:	start (QTPoint).
	//@Return				:	void.
	void QTRegion::SetRegionStart(QTPoint p)
	{
		this->m_pStart = p;
		CreateValidRegion();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to set the End Point of the region. It is valid if the user gives 'start' as input, given
	//							the input to SetRegionStart() method is 'end'.
	//@Input1				:	start (QTPoint).
	//@Return				:	void.
	void QTRegion::SetRegionEnd(QTPoint p)
	{
		this->m_pEnd = p;
		CreateValidRegion();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if the Start point is initialized.
	//@Return				:	bool.
	bool QTRegion::IsStartInit()
	{
		return !(this->m_pStart == QTPoint(-DBL_MAX, -DBL_MAX));
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if the End point is initialized.
	//@Return				:	bool.
	bool QTRegion::IsEndInit()
	{
		return !(this->m_pEnd == QTPoint(-DBL_MAX, -DBL_MAX));
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if the End and Start points are initialized.
	//@Return				:	bool.
	bool QTRegion::IsPointsInit()
	{
		return (IsStartInit() && IsEndInit());
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if a point is in this region. The inside part of the region is [start,end)
	//@Input				:	query point (QTPoint)
	//@Return				:	bool.
	bool QTRegion::IsInRegion(QTPoint p)
	{
		bool bRet;

		if (!IsPointsInit())
		{
			bRet = false;
		}
		else
		{
			bRet = (m_pStart <= p) && (p < m_pEnd);
		}
		return bRet;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Create a valid region by oredering the x,y coordinates of m_pStart, m_pEnd.
	//@Return				:	void.
	void QTRegion::CreateValidRegion()
	{
		if (IsPointsInit())
		{
			if (m_pStart.x > m_pEnd.x)
			{
				std::swap(m_pStart.x, m_pEnd.x);
			}
			if (m_pStart.y > m_pEnd.y)
			{
				std::swap(m_pStart.y, m_pEnd.y);
			}
		}
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Create top left child. This method will split the rectangle region into 4 symmetric about 
	//							the center Quardrent and returns the top left Quardrent.
	//@Return				:	QTRegion.
	QTRegion QTRegion::GetTopLeftChild()
	{
		if (IsPointsInit())
		{
			QTPoint start, end;
			start = QTPoint(this->m_pStart.x, this->m_pStart.y);
			end = QTPoint((this->m_pStart.x + this->m_pEnd.x) / 2, (this->m_pStart.y + this->m_pEnd.y) / 2);
			return QTRegion(start, end);
		}

		return QTRegion();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Create top right child. This method will split the rectangle region into 4 symmetric about 
	//							the center Quardrent and returns the top right Quardrent.
	//@Return				:	QTRegion.
	QTRegion QTRegion::GetTopRightChild()
	{
		if (IsPointsInit())
		{
			QTPoint start, end;
			start = QTPoint((this->m_pStart.x + this->m_pEnd.x) / 2, this->m_pStart.y);
			end = QTPoint(this->m_pEnd.x, (this->m_pStart.y + this->m_pEnd.y) / 2);
			return QTRegion(start, end);
		}

		return QTRegion();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Create bottom left child. This method will split the rectangle region into 4 symmetric about 
	//							the center Quardrent and returns the bottom left Quardrent.
	//@Return				:	QTRegion.
	QTRegion QTRegion::GetBottomLeftChild()
	{
		if (IsPointsInit())
		{
			QTPoint start, end;
			start = QTPoint(this->m_pStart.x, (this->m_pStart.y + this->m_pEnd.y) / 2);
			end = QTPoint((this->m_pStart.x + this->m_pEnd.x) / 2, this->m_pEnd.y);
			return QTRegion(start, end);
		}

		return QTRegion();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Create bottom right child. This method will split the rectangle region into 4 symmetric about 
	//							the center Quardrent and returns the bottom right Quardrent.
	//@Return				:	QTRegion.
	QTRegion QTRegion::GetBottomRightChild()
	{
		if (IsPointsInit())
		{
			QTPoint start, end;
			start = QTPoint((this->m_pStart.x + this->m_pEnd.x) / 2, (this->m_pStart.y + this->m_pEnd.y) / 2);
			end = QTPoint(this->m_pEnd.x, this->m_pEnd.y);
			return QTRegion(start, end);
		}

		return QTRegion();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Checks if the region is close enough to the point p. The "close enough" is determined by the user 
	//							by a input parameter (distance).
	//@Input1				:	query point (QTPoint)
	//@Input2				:	distance (double)
	//@Return				:	bool.
	bool QTRegion::IsRegionClose(QTPoint p, double distance)
	{
		bool bRet = false;
		if (IsPointsInit())
		{
			// Check if any of the four corners are closer to 
			// the point p ((corner-p).Norm < distance ). If
			// such point exists return True, else false.
			if (!bRet)
			{
				bRet = ((m_pStart - p).Norm() < distance);
			}

			if (!bRet)
			{
				bRet = ((m_pEnd - p).Norm() < distance);
			}

			if (!bRet)
			{
				bRet = ((QTPoint((m_pStart).x, (m_pEnd).y) - p).Norm() < distance);
			}

			if (!bRet)
			{
				bRet = ((QTPoint((m_pEnd).x, (m_pStart).y) - p).Norm() < distance);
			}
		}
		return bRet;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the size of minimum dimention. return min(width,height).
	//@Return				:	double.
	double QTRegion::GetMinDimention()
	{
		double x = m_pEnd.x - m_pStart.x;
		double y = m_pEnd.y - m_pStart.y;
		return fmin(x,y);
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the length of regions diagonal.
	//@Return				:	double.
	double QTRegion::GetDiagonalLength()
	{
		return (m_pStart - m_pEnd).Norm();
	}

} // namespace Common