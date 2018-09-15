#ifndef _UTILS_H
#define _UTILS_H

#include <queue>
#include <vector>

#include "QTPoint.h"

namespace Common
{
//@Author				:	Ravi Teja Narra (kagami3287).
//@Description			:	This is a class that is essentially a STL::Priority_Queue, templated over QTPoint
//							This is templated with '<' operator of QTPoint which is overwritten to compare the norms
//							of Points.This is a very optimal Data Structure that can be used while searching.
//@Critical Inputs		:
//	@Input1				:	Request Size (m_sRequestSize).
//	@Property			:	This is the size of the list maintaiend by the class. If more elements are pushed,
//							the elements with higher norms are popped from the queue.
//@Usage :
//	@Step 1				:	Set the RequestSize before instantialting a class object. Altough this step is not 
//							necessary for this class in particualr , I believe it is a good practice.
//	@Step 2				:	Inistantiate a class object and use it like a queue of QTPoints, the class is 
//							configured to do the rest.

	class QTNNList
	{
	private:
		//Data structure to store the QTPoints.
		std::priority_queue<QTPoint, std::vector<QTPoint>, std::less<QTPoint>> QTPointQueue;
		//Critical Inputs : Input1.
		static unsigned int m_sRequestSize;
	public:
		QTNNList();
		~QTNNList();
	public:
		static void SetRequestSize(unsigned int nReq);
		static unsigned int GetRequestSize();
		void Push(QTPoint p);
		void Pop();
		const QTPoint Top();
		int Size();
		void DeepCopy(std::vector<QTPoint> &list);
	};
} // namespace Common
#endif