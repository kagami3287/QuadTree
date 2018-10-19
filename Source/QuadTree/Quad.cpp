#include "Quad.h"

namespace Common
{
	double Quad::m_sAtomSize = 1;
	unsigned int Quad::m_sCapacity = 1;

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Constructor.
	Quad::Quad()
	{
		m_Points.resize(m_sCapacity);
		m_pRegion = QTRegion();
		m_nCurSize = 0;
		m_pTopLeftQuad = NULL;
		m_pTopRightQuad = NULL;
		m_pBottomLeftQuad = NULL;
		m_pBottomRightQuad = NULL;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Constructor. Sets the region frmo input
	//@Input				:	region (QTRegion)
	Quad::Quad(QTRegion pRegion)
	{
		m_Points.resize(m_sCapacity);
		m_pRegion = pRegion;
		m_nCurSize = 0;
		m_pTopLeftQuad = NULL;
		m_pTopRightQuad = NULL;
		m_pBottomLeftQuad = NULL;
		m_pBottomRightQuad = NULL;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Destructor.
	Quad::~Quad()
	{
		delete m_pTopLeftQuad;
		delete m_pTopRightQuad;
		delete m_pBottomLeftQuad;
		delete m_pBottomRightQuad;

		m_Points.clear();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to set the Quad Capacity. This is a static method. This method should be 
	//							called before instantiaitng the class, if non default value of m_sCapacity is to be used.
	//@Input1				:	Capacity (unsigned int).
	//@Return				:	void.
	void Quad::SetCapacity(unsigned int nCapacity)
	{
		m_sCapacity = nCapacity;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to set the Atomic Size. This is a static method. This method should be 
	//							called before instantiaitng the class, if non default value of m_sAtomSize is to be used.
	//							This should be a positive value.
	//@Input1				:	Atomic Size (double).
	//@Return				:	void.
	void Quad::SetAtomicSize(double dAtomicSize)
	{
		m_sAtomSize = dAtomicSize;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Quad Capacity .
	//@Return				:	unsigned int.
	unsigned int Quad::GetCapacity()
	{
		return m_sCapacity;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Atomic Size.
	//@Return				:	double.
	double Quad::GetAtomicSize()
	{
		return m_sAtomSize;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to set Region of the Quad. Please make sure to set a valid Quad.
	//@Input1				:	region (QTRegion).
	//@Return				:	void.
	void Quad::SetRegion(QTRegion pRegion)
	{
		this->m_pRegion = pRegion;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get Region of the Quad.
	//@Return				:	QTRegion.
	QTRegion Quad::GetRegion()
	{
		return m_pRegion;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the number of points in the Quad.
	//@Return				:	int.
	int Quad::GetCurSize()
	{
		return this->m_nCurSize;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if all the children of the Quad are not NULL.
	//@Return				:	bool.
	bool Quad::IsChildNull()
	{
		return (m_pTopLeftQuad == NULL) || (m_pTopRightQuad == NULL) || (m_pBottomLeftQuad == NULL) || (m_pBottomRightQuad == NULL);
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if the region has valid start and end points.
	//@Return				:	bool.
	bool Quad::IsRegionValid()
	{
		return this->m_pRegion.IsPointsInit();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if a Point is inside the region corresponding to the current Quad.
	//@Input				:	Query Point (QTPoint)
	//@Return				:	bool.
	bool Quad::IsInBoundary(QTPoint p)
	{
		if (IsRegionValid())
		{
			return this->m_pRegion.IsInRegion(p);
		}
		return false;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to check if a Point close enough to the region corresponding to the Quad. The "close enough" is 
	//							determined by user input "distance"
	//@Input				:	Query Point (QTPoint)
	//@Return				:	bool.
	bool Quad::IsQuadClose(QTPoint p, double distance)
	{
		bool bIsRegionClose = this->m_pRegion.IsRegionClose(p, distance);
		bool bIsChildPointPresent = (this->m_nCurSize > 0);
		return bIsRegionClose && bIsChildPointPresent;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the top left Quadrant of the current Quad's Region.
	//@Return				:	QTRegion.
	QTRegion Quad::GetTopLeftRegion()
	{
		return this->m_pRegion.GetTopLeftChild();;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the top right Quadrant of the current Quad's Region.
	//@Return				:	QTRegion.
	QTRegion Quad::GetTopRightRegion()
	{
		return this->m_pRegion.GetTopRightChild();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the bottom left Quadrant of the current Quad's Region.
	//@Return				:	QTRegion.
	QTRegion Quad::GetBottomLeftRegion()
	{
		return this->m_pRegion.GetBottomLeftChild();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the bottom right Quadrant of the current Quad's Region.
	//@Return				:	QTRegion.
	QTRegion Quad::GetBottomRightRegion()
	{
		return this->m_pRegion.GetBottomRightChild();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Quad corresponding to top left region of current Quad.
	//@Return				:	Quad*.
	Quad * Quad::GetTopLeftChild()
	{
		return this->m_pTopLeftQuad;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Quad corresponding to top right region of current Quad.
	//@Return				:	Quad*.
	Quad * Quad::GetTopRightChild()
	{
		return this->m_pTopRightQuad;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Quad corresponding to bottom left region of current Quad.
	//@Return				:	Quad*.
	Quad * Quad::GetBottomLeftChild()
	{
		return this->m_pBottomLeftQuad;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Quad corresponding to bottom right region of current Quad.
	//@Return				:	Quad*.
	Quad * Quad::GetBottomRightChild()
	{
		return this->m_pBottomRightQuad;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Create children 4 children for the current Quad. This method is called whenever the
	//							current Quad has max possible number of points (m_nCapacity) and a new point is to be added.
	//@Return				:	bool.
	bool Quad::CreateChildren()
	{
		//Check if the region for this Quad is valid
		if (IsRegionValid())
		{
			double minDim = m_pRegion.GetMinDimention();

			//Check if the Region post split is still > Atomic Size
			if ((minDim / 2) >= m_sAtomSize)
			{
				//Populate the 4 Children of the current Quad
				this->m_pTopLeftQuad = new Quad(this->GetTopLeftRegion());
				this->m_pTopRightQuad = new Quad(this->GetTopRightRegion());
				this->m_pBottomLeftQuad = new Quad(this->GetBottomLeftRegion());
				this->m_pBottomRightQuad = new Quad(this->GetBottomRightRegion());
				return true;
			}
			return false;
		}

		return false;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Insert a point to the child. This is called when a new point is being added, and the
	//							current Quad has Points == Capacity.
	//@Input				:	Insert Point (QTPoint)
	//@Return				:	bool.
	bool Quad::InserttoChild(QTPoint p)
	{
		bool bRet = false;
		//Check of the Quad has valid Children
		bool bIsChildNull = this->IsChildNull();
		if (bIsChildNull)
		{
			//If no valid children, create children
			bRet = this->CreateChildren();
		}
		if (bRet || !bIsChildNull)
		{
			//Select the child that has the insert point
			//in its region and insert it.
			bRet = false;
			if (!bRet)
			{
				bRet = m_pTopLeftQuad->InsertPoint(p);
			}

			if (!bRet)
			{
				bRet = m_pTopRightQuad->InsertPoint(p);
			}

			if (!bRet)
			{
				bRet = m_pBottomLeftQuad->InsertPoint(p);
			}

			if (!bRet)
			{
				bRet = m_pBottomRightQuad->InsertPoint(p);
			}
		}
		return bRet;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Insert a point to the Quad.
	//@Input				:	Insert Point (QTPoint)
	//@Return				:	bool.
	bool Quad::InsertPoint(QTPoint p)
	{
		bool bRet = false;
		//Check if the point is valid.
		if (p == QTPoint())
		{
			bRet = false;
		}
		//Check if the region corresponding to current Quad is Valid
		else if (!IsRegionValid())
		{
			bRet = false;
		}
		//Check if the insert point is in the boundary of Quads Region
		else if (!IsInBoundary(p))
		{
			bRet = false;
		}
		//Check the Quads Capacity details, if insert possible 
		//insert in the current Quad.
		else if (this->GetCurSize() < Quad::GetCapacity())
		{
			m_Points[this->GetCurSize()] = p;
			++this->m_nCurSize;
			bRet = true;
		}
		//If insert not possible int he current Quad, 
		//insert to child.
		else
		{
			bRet = InserttoChild(p);
		}
		return bRet;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to Search k-Nearest Neighbors.
	//@Input1				:	Query Point (QTPoint)
	//@Input2				:	K  in KNN(int)
	//@Return				:	vector<QTPoint>.
	std::vector<QTPoint> Quad::Search(QTPoint p, int nNearestPoints)
	{
		//Create a Priority Queue of fixed max Size.
		QTNNList pointList = QTNNList();
		pointList.SetRequestSize(nNearestPoints);

		//Insert the Current Quad to a list
		std::vector<Quad*> quadList;
		double maxDist = m_pRegion.GetDiagonalLength();
		quadList.push_back(this);

		//Step 1 :	For the each Quad in the current list 'quadList', check if 
		//			a point in the Quad(m_Points) that is closer to 'p' than
		//			the farthest point in 'pointList'.
		//			If Such a Point Exists in the Quads m_Points, insert the 
		//			points satisfying the above properties to the 'pointList'.

		//Step 2 :	For each Quad in the current list 'quadList', check for
		//			each child of the Quad to see if it is closer to the point
		//			'p' than the farthest point in 'pointList'. If so 
		//			create a insert this Quad to a new 'QuadList'. 

		// Repeat Step 1 and 2 until 'quadList; is empty.
		// Note at every iteration the 'quadList' is fill with Quads in the
		// same level.

		while (!quadList.empty())
		{
			//Step 1
			ProcessCurrentList(p, pointList, quadList, maxDist);
			//Step2
			PopulateValidChildren(p, pointList, quadList, maxDist);
		}

		std::vector<QTPoint> list;
		//Copy the KNN to a vector
		pointList.DeepCopy(list);

		for (int i = 0; i < list.size(); ++i)
		{
			QTPoint curPoint = ((list[i]) + p);

			list[i].x = curPoint.x;
			list[i].y = curPoint.y;
		}

		return list;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the KNN points until this level in the Quad Tree
	//@Input1				:	Query Point (QTPoint)
	//@Input2				:	pointList (QTNNList, by Reference)
	//@Input3				:	quadList (vector<Quad*>, by Reference)
	//@Input4				:	max (double, by Reference)
	//@Return				:	void.
	void Quad::ProcessCurrentList(QTPoint p, QTNNList & pointList, std::vector<Quad*>& quadList, double & max)
	{
		// for each Quad in the current 'quadList'
		for (auto itQuad = quadList.begin(); itQuad < quadList.end(); ++itQuad)
		{
			std::vector<QTPoint> curPoints = (*itQuad)->m_Points;
			// for each point in the current Quad
			for (auto itPoint = curPoints.begin(); itPoint < curPoints.begin() + (*itQuad)->GetCurSize(); ++itPoint)
			{
				QTPoint curP = *itPoint;

				// If current point is closer to 'p' than the 
				// farthest point in 'pointList', insert current 
				// point to 'pointList'. This will automatically 
				// reomve the 'farthest point' from 'pointList'
				// (since this is the property of the data structure
				// QTNNList).
				if ((p - curP).Norm() < max || pointList.Size() < pointList.GetRequestSize())
				{
					pointList.Push(p - curP);
					max = ((QTPoint)pointList.Top()).Norm();
				}
			}
		}
		//by this point we have updated the 'pointList'
		//with the closest points from all the points in 
		//the elements of 'quadList'.
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Quads that are children to Quads in 'quadList' and are 
	//							closer to 'p' than the fartheset point in 'pointList' which is at a distance
	//							'max'.
	//@Input1				:	Query Point (QTPoint)
	//@Input2				:	pointList (QTNNList)
	//@Input3				:	quadList (vector<Quad*>, by Reference)
	//@Input4				:	max (double, by Reference)
	//@Return				:	void.
	void Quad::PopulateValidChildren(QTPoint p, QTNNList pointList, std::vector<Quad*>& quadList, double & max)
	{
		// list to store quads that are children 
		// closer of Quads in 'quadLisr' and are
		// closer to p than the fartheset point 
		// in 'pointList'(the distance of this 
		// farthest point is 'max' an input 
		//parameter).
		std::vector<Quad *> quadListChild;

		//for each Quad in the 'quadList'
		for (auto itQuad = quadList.begin(); itQuad < quadList.end(); ++itQuad)
		{
			Quad* curQuad = *itQuad;

			//for each child of the current Quad
			//If the point 'p' is closer to the child 
			//than the distance 'max', then isert the 
			//child to 'quadListChild'
			if (!curQuad->IsChildNull())
			{	
				if (curQuad->GetTopLeftChild()->IsQuadClose(p, max) || pointList.Size() < pointList.GetRequestSize())
				{
					quadListChild.push_back(curQuad->GetTopLeftChild());
				}

				if (curQuad->GetTopRightChild()->IsQuadClose(p, max) || pointList.Size() < pointList.GetRequestSize())
				{
					quadListChild.push_back(curQuad->GetTopRightChild());
				}

				if (curQuad->GetBottomLeftChild()->IsQuadClose(p, max) || pointList.Size() < pointList.GetRequestSize())
				{
					quadListChild.push_back(curQuad->GetBottomLeftChild());
				}

				if (curQuad->GetBottomRightChild()->IsQuadClose(p, max) || pointList.Size() < pointList.GetRequestSize())
				{
					quadListChild.push_back(curQuad->GetBottomRightChild());
				}
			}
		}

		quadList.clear();
		// update 'quadList' with 'quadListChild'
		// we are moving lower by one step in the 
		// Quad Tree by this step.
		quadList = quadListChild;
	}

} // namespace Common