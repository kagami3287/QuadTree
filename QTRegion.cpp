#include "QTRegion.h"

namespace Common
{
	QTRegion::QTRegion()
	{
		this->m_pStart = NULL;
		this->m_pEnd = NULL;
	}

	QTRegion::QTRegion(QTPoint *start, QTPoint *end)
	{
		this->m_pStart = start;
		this->m_pEnd = end;
	}

	QTRegion::~QTRegion()
	{
		delete m_pStart;
		delete m_pEnd;
	}

	//Returns the Start point of the region.
	QTPoint *QTRegion::GetRegionStart()
	{
		return this->m_pStart;
	}

	//Returns the End point of the region.
	QTPoint *QTRegion::GetRegionEnd()
	{
		return this->m_pEnd;
	}

	//Set the Start of the region.
	void QTRegion::SetRegionStart(QTPoint *p)
	{
		this->m_pStart = p;
		CreateValidRegion();
	}

	//Set the End of the region.
	void QTRegion::SetRegionEnd(QTPoint *p)
	{
		this->m_pEnd = p;
		CreateValidRegion();
	}

	//Checks if the Starting point is Null.
	bool QTRegion::IsStartNull()
	{
		return (this->m_pStart == NULL);
	}

	//Checks if the Ending point is Null.
	bool QTRegion::IsEndNull()
	{
		return (this->m_pEnd == NULL);
	}

	//Checks if any point is Null (Start | End).
	bool QTRegion::IsPointsNull()
	{
		return (IsStartNull() || IsEndNull());
	}

	//Checks if a point is in this region
	//the area that is considered inside the region is [Start, End)
	bool QTRegion::IsInRegion(QTPoint *p)
	{
		bool bRet;

		if (IsPointsNull())
		{
			bRet = false;
		}
		else
		{
			bool bXin = (this->m_pStart->x <= p->x) && (this->m_pEnd->x > p->x);
			bool bYin = (this->m_pStart->y <= p->y) && (this->m_pEnd->y > p->y);

			bRet = (bXin && bYin);
		}
		return bRet;
	}

	//Creates a valid region by oredering the x,y coordinates
	void QTRegion::CreateValidRegion()
	{
		if (!IsPointsNull())
		{
			if (m_pStart->x > m_pEnd->x)
			{
				swap(m_pStart->x, m_pEnd->x);
			}
			if (m_pStart->y > m_pEnd->y)
			{
				swap(m_pStart->y, m_pEnd->y);
			}
		}
	}

	// Returns Top Left Childs Region
	QTRegion *QTRegion::GetTopLeftChild()
	{
		QTRegion *pRegion = NULL;
		QTPoint *start, *end;

		if (!IsPointsNull())
		{
			start = new QTPoint(this->m_pStart->x, this->m_pStart->y);
			end = new QTPoint((this->m_pStart->x + this->m_pEnd->x) / 2, (this->m_pStart->y + this->m_pEnd->y) / 2);
			pRegion = new QTRegion(start, end);
		}

		return pRegion;
	}

	// Returns Top Right Childs Region
	QTRegion *QTRegion::GetTopRightChild()
	{
		QTRegion *pRegion = NULL;
		QTPoint *start, *end;

		if (!IsPointsNull())
		{
			start = new QTPoint((this->m_pStart->x + this->m_pEnd->x) / 2, this->m_pStart->y);
			end = new QTPoint(this->m_pEnd->x, (this->m_pStart->y + this->m_pEnd->y) / 2);
			pRegion = new QTRegion(start, end);
		}

		return pRegion;
	}

	// Returns Bottom Left Childs Region
	QTRegion *QTRegion::GetBottomLeftChild()
	{
		QTRegion *pRegion = NULL;
		QTPoint *start, *end;

		if (!IsPointsNull())
		{
			start = new QTPoint(this->m_pStart->x, (this->m_pStart->y + this->m_pEnd->y) / 2);
			end = new QTPoint((this->m_pStart->x + this->m_pEnd->x) / 2, this->m_pEnd->y);
			pRegion = new QTRegion(start, end);
		}

		return pRegion;
	}

	// Returns Bottom Right Childs Region
	QTRegion *QTRegion::GetBottomRightChild()
	{
		QTRegion *pRegion = NULL;
		QTPoint *start, *end;
		if (!IsPointsNull())
		{
			start = new QTPoint((this->m_pStart->x + this->m_pEnd->x) / 2, (this->m_pStart->y + this->m_pEnd->y) / 2);
			end = new QTPoint(this->m_pEnd->x, this->m_pEnd->y);
			pRegion = new QTRegion(start, end);
		}

		return pRegion;
	}

	//Checks if the region is close enough to the point p.
	//i.e distance(region , p)< distance;
	bool QTRegion::IsRegionClose(QTPoint * p, double distance)
	{
		bool bRet = false;
		if (!IsPointsNull())
		{
			if (!bRet)
			{
				bRet = ((*m_pStart - *p).Norm() < distance);
			}

			if (!bRet)
			{
				bRet = ((*m_pEnd - *p).Norm() < distance);
			}

			if (!bRet)
			{
				bRet = ((QTPoint((*m_pStart).x, (*m_pEnd).y) - *p).Norm() < distance);
			}

			if (!bRet)
			{
				bRet = ((QTPoint((*m_pEnd).x, (*m_pStart).y) - *p).Norm() < distance);
			}
		}
		return bRet;
	}

	//Returns the Size of minimum dimention
	double QTRegion::GetMinDimention()
	{
		double x = m_pEnd->x - m_pStart->x;
		double y = m_pEnd->y - m_pStart->y;
		return fmin(x,y);
	}

} // namespace Common