#ifndef _QUAD_H
#define _QUAD_H

#include "Common.h"
#include "Utils.h"
#include "QTRegion.h"



namespace Common
{
	//Class for the Quad Tree
	//This class stores all the inserted points. This class has 2 Parameters that are to be set 
	//before calling the constructor. 
	//1. Atomic Size - The Min(Dimentions) allowed for the Region. All region with Min(Dimentions) smaller
	//than this Size is ont created. For all practical purposes use '1.0' as atomic Size.
	//2. Max Capacity - The number of points that can be stored in each Quad object. The optimal value
	// for this parameter is yet to be found. but a value in the range of (4-16) should give descent results.
	
	//Note : It is the users responsibility to insert unique points while creating the QuadTree. Altough the application will not crash 
	// because of multiple insertions of the same point. The search results might give the repeated point, which beats the purpose of 
	// this structure to begin with(** in my opinion).

	//Usage :
	//Step 1 : Set the Atomic Size.
	//Step 2 : Set the Max Capacity per Quad Node.
	//Step 3 : Initialize the tree using the required Region.
	//Step 4 : Insert Points and Search your heart out for the nearest neighbors.
	class Quad
	{
	private:
		static double m_sAtomSize;
		static int m_sCapacity;

		vector<QTPoint> m_Points;
		QTRegion m_pRegion;
		int m_nCurSize;
		//Links to children
	private:
		Quad * m_pTopLeft;
		Quad *m_pTopRight;
		Quad *m_pBottomLeft;
		Quad *m_pBottomRight;

	public:
		Quad();
		Quad(QTRegion pRegion);
		~Quad();
		//Methods
	private:
		bool IsChildNull();
		bool IsRegionValid();
		int GetCurSize();
		bool IsInBoundary(QTPoint p);
		bool IsRegionClose(QTPoint p, double distance);
		QTRegion GetTopLeftRegion();
		QTRegion GetTopRightRegion();
		QTRegion GetBottomLeftRegion();
		QTRegion GetBottomRightRegion();
		bool CreateChildren();
		bool InserttoChild(QTPoint p);
		void ProcessCurrentList(QTPoint p, QTNNList& pointList, vector<Quad*> &quadList, double & max);
		void PopulateValidChildren(QTPoint p, vector<Quad*> &quadList, double & max);
	public:
		static void SetCapacity(int nCapacity);
		static int GetCapacity();
		static void SetAtomicSize(double dAtomicSize);
		static double GetAtomicSize();
		void SetRegion(QTRegion pRegion);
		QTRegion GetRegion();
		Quad * GetTopLeftChild();
		Quad * GetTopRightChild();
		Quad * GetBottomLeftChild();
		Quad * GetBottomRightChild();
		bool InsertPoint(QTPoint p);
		vector<QTPoint> Search(QTPoint p, int nNearestPoints);
	};
} // namespace Common

#endif