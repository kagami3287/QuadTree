#ifndef _QUAD_H
#define _QUAD_H

#include "Utils.h"
#include "QTRegion.h"

namespace Common
{
	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	This is a class representing the data structure Quad Tree. Please visit the references for more information.
	//@Critical Inputs		:
	//	@Input1				:	Atomic Size (m_sAtomSize).
	//	@Property			:	This is the minimum size of the minimum dimention with which a region can be created in this Quad.
	//	@Default Value		:	1.
	//	@Input2				:	Region Capacity (m_sCapacity).
	//	@Property			:	This is the maximum number of points that get inserted to a region before splitting it into 4  Quadrants.
	//	@Default Value		:	1.
	//@Usage :
	//	@Step 1				:	Set the Atomic Size. Based on the requirements this can change and have differnt values.
	//	@Step 2				:	Set the Capacity. Again this also depends on the application, and the performance is expected to vary depending on 
	//							factors like the dimention of the initial region of the Quad. Experiment with various values and use it accordingly.
	//	@Step 3				:	Instantiate the Quad object, insert the required points to the Quad.
	//	@Step 4				:	Search for K-Nearest Neighbors.
	//@References			:	1. http://homepage.divms.uiowa.edu/~kvaradar/sp2012/daa/ann.pdf
	//						:	2. https://en.wikipedia.org/wiki/Quadtree

	//@Note1				:	It is the users responsibility to insert unique points while creating the QuadTree. Altough the application 
	//							will not crash because of multiple insertions of the same point. The search results might give the repeated
	//							point, which beats the purpose of this structure to begin with(** in my opinion).
	//@Note2				:	If the number of points inserted are less than 'K'(K in KNN), then the result will also have less number of
	//							points.
	

	class Quad
	{
	private:
		// Atomic Size, minimum size of the minimum dimention with 
		// which a region can be created in this Quad.
		static double m_sAtomSize;
		// Capcacity, maximum number of points that get inserted to 
		// a region before splitting it into 4  Quadrants.
		static unsigned int m_sCapacity;
		// List of points in this Quad. There can be at max m_sCapacity
		// number of points in each Quad.
		std::vector<QTPoint> m_Points;
		// Region represented by the Quad.
		QTRegion m_pRegion;
		// number of points in the Quad.
		int m_nCurSize;
	private:
		//Links to children
		Quad *m_pTopLeftQuad;
		Quad *m_pTopRightQuad;
		Quad *m_pBottomLeftQuad;
		Quad *m_pBottomRightQuad;

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
		bool IsQuadClose(QTPoint p, double distance);
		QTRegion GetTopLeftRegion();
		QTRegion GetTopRightRegion();
		QTRegion GetBottomLeftRegion();
		QTRegion GetBottomRightRegion();
		bool CreateChildren();
		bool InserttoChild(QTPoint p);
		void ProcessCurrentList(QTPoint p, QTNNList& pointList, std::vector<Quad*> &quadList, double & max);
		void PopulateValidChildren(QTPoint p, QTNNList pointList, std::vector<Quad*> &quadList, double & max);
	public:
		static void SetCapacity(unsigned int nCapacity);
		static unsigned int GetCapacity();
		static void SetAtomicSize(double dAtomicSize);
		static double GetAtomicSize();
		void SetRegion(QTRegion pRegion);
		QTRegion GetRegion();
		Quad * GetTopLeftChild();
		Quad * GetTopRightChild();
		Quad * GetBottomLeftChild();
		Quad * GetBottomRightChild();
		bool InsertPoint(QTPoint p);
		std::vector<QTPoint> Search(QTPoint p, int nNearestPoints);
	};
} // namespace Common

#endif