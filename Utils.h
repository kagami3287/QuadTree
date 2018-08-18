// Document for Utilities for the Quad Tree(2D only)

#ifndef _UTILS_H
#define _UTILS_H

#include "QTPoint.h"

namespace Common
{
	// This is a class that is essentially a STL::Priority_Queue, templated over QTPoint
	// This is templated with '<' operator of QTPoint which is overwritten to compare the norms 
	// of Points.
	// This class takes as Input 'Request Size', and makes sure to always keep the size of the 
	// Queue not greater than request Size. Whenever the size is grater than Request Size the Point 
	// with Highest L2 Norm is removed to meet this condition.
	// So, In essence this class is a Priority_Queue that stores points and orders them using their 
	// L2 Norms. It also makes sure that the Size of the Queue is not grater than a specified size. So, 
	// this is a very good Data Structure that can be used while searching. 

	//Usage :
	// Step 1 : set the RequestSize.
	// Step 2 : Initialize the class and use it like a queue of points and the magic will happen!!.
	class QTNNList
	{
	private:
		priority_queue<QTPoint, vector<QTPoint>, std::less<QTPoint>> QTPointQueue;
		static unsigned int m_sRequestSize;
	public:
		QTNNList();
		~QTNNList();
	public:
		void SetRequestSize(unsigned int nReq);
		void Push(QTPoint * p);
		void Pop();
		const QTPoint * top();
		int size();
		void DeepCopy(vector<QTPoint*> &list);
	};
} // namespace Common
#endif