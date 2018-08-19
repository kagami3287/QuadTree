#include "Quad.h"

namespace Common
{
	double Quad::m_sAtomSize = 1;
	int Quad::m_sCapacity = 1;

	Quad::Quad()
	{
		m_Points.resize(m_sCapacity);
		m_pRegion = QTRegion();
		m_nCurSize = 0;
		m_pTopLeft = NULL;
		m_pTopRight = NULL;
		m_pBottomLeft = NULL;
		m_pBottomRight = NULL;
	}

	Quad::Quad(QTRegion pRegion)
	{
		m_Points.resize(m_sCapacity);
		m_pRegion = pRegion;
		m_nCurSize = 0;
		m_pTopLeft = NULL;
		m_pTopRight = NULL;
		m_pBottomLeft = NULL;
		m_pBottomRight = NULL;
	}

	Quad::~Quad()
	{
		delete m_pTopLeft;
		delete m_pTopRight;
		delete m_pBottomLeft;
		delete m_pBottomRight;

		m_Points.clear();
	}

	void Quad::SetCapacity(int nCapacity)
	{
		m_sCapacity = nCapacity;
	}

	void Quad::SetAtomicSize(double dAtomicSize)
	{
		m_sAtomSize = dAtomicSize;
	}

	int Quad::GetCapacity()
	{
		return m_sCapacity;
	}

	double Quad::GetAtomicSize()
	{
		return m_sAtomSize;
	}

	void Quad::SetRegion(QTRegion pRegion)
	{
		this->m_pRegion = pRegion;
	}

	QTRegion Quad::GetRegion()
	{
		return m_pRegion;
	}

	int Quad::GetCurSize()
	{
		return this->m_nCurSize;
	}

	bool Quad::IsChildNull()
	{
		return (m_pTopLeft == NULL) || (m_pTopRight == NULL) || (m_pBottomLeft == NULL) || (m_pBottomRight == NULL);
	}

	bool Quad::IsRegionValid()
	{
		return this->m_pRegion.IsPointsInit();
	}

	bool Quad::IsInBoundary(QTPoint p)
	{
		if (IsRegionValid())
		{
			return this->m_pRegion.IsInRegion(p);
		}
		return false;
	}

	bool Quad::IsRegionClose(QTPoint p, double distance)
	{
		bool bIsRegionClose = this->m_pRegion.IsRegionClose(p, distance);
		bool bIsChildPointPresent = (this->m_nCurSize > 0);
		return bIsRegionClose && bIsChildPointPresent;
	}

	QTRegion Quad::GetTopLeftRegion()
	{
		return this->m_pRegion.GetTopLeftChild();;
	}

	QTRegion Quad::GetTopRightRegion()
	{
		return this->m_pRegion.GetTopRightChild();
	}

	QTRegion Quad::GetBottomLeftRegion()
	{
		return this->m_pRegion.GetBottomLeftChild();
	}

	QTRegion Quad::GetBottomRightRegion()
	{
		return this->m_pRegion.GetBottomRightChild();
	}

	Quad * Quad::GetTopLeftChild()
	{
		return this->m_pTopLeft;
	}

	Quad * Quad::GetTopRightChild()
	{
		return this->m_pTopRight;
	}

	Quad * Quad::GetBottomLeftChild()
	{
		return this->m_pBottomLeft;
	}

	Quad * Quad::GetBottomRightChild()
	{
		return this->m_pBottomRight;
	}

	bool Quad::CreateChildren()
	{
		if (IsRegionValid())
		{
			double minDim = m_pRegion.GetMinDimention();

			if ((minDim / 2) > m_sAtomSize)
			{
				this->m_pTopLeft = new Quad(this->GetTopLeftRegion());
				this->m_pTopRight = new Quad(this->GetTopRightRegion());
				this->m_pBottomLeft = new Quad(this->GetBottomLeftRegion());
				this->m_pBottomRight = new Quad(this->GetBottomRightRegion());
				return true;
			}
			return false;
		}

		return false;
	}

	bool Quad::InserttoChild(QTPoint p)
	{
		bool bRet = false;
		bool bIsChildNull = this->IsChildNull();
		if (bIsChildNull)
		{
			bRet = this->CreateChildren();
		}
		if (bRet || !bIsChildNull)
		{
			bRet = false;
			if (!bRet)
			{
				bRet = m_pTopLeft->InsertPoint(p);
			}

			if (!bRet)
			{
				bRet = m_pTopRight->InsertPoint(p);
			}

			if (!bRet)
			{
				bRet = m_pBottomLeft->InsertPoint(p);
			}

			if (!bRet)
			{
				bRet = m_pBottomRight->InsertPoint(p);
			}
		}
		return bRet;
	}

	//Inserts points to the Quad
	bool Quad::InsertPoint(QTPoint p)
	{
		bool bRet = false;
		if (p == QTPoint())
		{
			bRet = false;
		}
		else if (!IsRegionValid())
		{
			bRet = false;
		}
		else if (!IsInBoundary(p))
		{
			bRet = false;
		}
		else if (this->GetCurSize() < Quad::GetCapacity())
		{
			m_Points[this->GetCurSize()] = p;
			++this->m_nCurSize;
			bRet = true;
		}
		else
		{
			bRet = InserttoChild(p);
		}
		return bRet;
	}

	//Search for given number of nearest points to p.
	vector<QTPoint> Quad::Search(QTPoint p, int nNearestPoints)
	{
		QTNNList pointList = QTNNList();
		pointList.SetRequestSize(nNearestPoints);

		vector<Quad*> quadList;
		double maxDist = (m_pRegion.GetRegionStart() - m_pRegion.GetRegionEnd()).Norm();
		quadList.push_back(this);

		while (!quadList.empty())
		{
			ProcessCurrentList(p, pointList, quadList, maxDist);
			PopulateValidChildren(p, quadList, maxDist);
		}

		vector<QTPoint> list;
		pointList.DeepCopy(list);

		for (int i = 0; i < list.size(); ++i)
		{
			QTPoint curPoint = ((list[i]) + p);

			list[i].x = curPoint.x;
			list[i].y = curPoint.y;
		}

		return list;
	}

	void Quad::ProcessCurrentList(QTPoint p, QTNNList & pointList, vector<Quad*>& quadList, double & max)
	{
		for (auto itQuad = quadList.begin(); itQuad < quadList.end(); ++itQuad)
		{
			vector<QTPoint> curPoints = (*itQuad)->m_Points;

			for (auto itPoint = curPoints.begin(); itPoint < curPoints.begin() + (*itQuad)->GetCurSize(); ++itPoint)
			{
				QTPoint curP = *itPoint;

				if ((p - curP).Norm() < max)
				{
					pointList.Push(p - curP);
					max = ((QTPoint)pointList.top()).Norm();
				}
			}
		}
	}

	void Quad::PopulateValidChildren(QTPoint p, vector<Quad*>& quadList, double & max)
	{
		vector<Quad *> quadListChild;

		for (auto itQuad = quadList.begin(); itQuad < quadList.end(); ++itQuad)
		{
			Quad* curQuad = *itQuad;

			if (!curQuad->IsChildNull())
			{
				if (curQuad->GetTopLeftChild()->IsRegionClose(p, max))
				{
					quadListChild.push_back(curQuad->GetTopLeftChild());
				}

				if (curQuad->GetTopRightChild()->IsRegionClose(p, max))
				{
					quadListChild.push_back(curQuad->GetTopRightChild());
				}

				if (curQuad->GetBottomLeftChild()->IsRegionClose(p, max))
				{
					quadListChild.push_back(curQuad->GetBottomLeftChild());
				}

				if (curQuad->GetBottomRightChild()->IsRegionClose(p, max))
				{
					quadListChild.push_back(curQuad->GetBottomRightChild());
				}
			}
		}

		quadList.clear();
		quadList = quadListChild;
	}

} // namespace Common