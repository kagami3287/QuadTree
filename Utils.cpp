#include "Utils.h"

namespace Common
{
	unsigned int QTNNList::m_sRequestSize = 1;

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Constructor.
	QTNNList::QTNNList()
	{
		while (!QTPointQueue.empty())
		{
			QTPointQueue.pop();
		}
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class Destructor.
	QTNNList::~QTNNList()
	{
		while (!QTPointQueue.empty())
		{
			QTPointQueue.pop();
		}
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to set the Request Size. (static method)
	//@Input1				:	Request Size (Unsigned Int).
	//@Return				:	void.
	void QTNNList::SetRequestSize(unsigned int nReq)
	{
		m_sRequestSize = nReq;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to get the Request Size. (static method)
	//@Return				:	unsigned int.
	unsigned int QTNNList::GetRequestSize()
	{
		return m_sRequestSize;
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to push elements to the queue. The element with highest L2 Norm is always on top.
	//@Input1				:	Point (QTPoint).
	//@Return				:	void.
	void QTNNList::Push(QTPoint p)
	{
		this->QTPointQueue.push(p);
		if (this->QTPointQueue.size() > this->m_sRequestSize)
		{
			this->QTPointQueue.pop();
		}
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to pop the first element in the queue. This will essentially pop the element with 
	//							highest L2 Norm.
	//@Return				:	void.
	void QTNNList::Pop()
	{
		this->QTPointQueue.pop();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to return the first element in the queue. This will essentially pop the element with 
	//							highest L2 Norm.
	//@Return				:	const QTPoint.
	const QTPoint QTNNList::Top()
	{
		return QTPointQueue.top();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to return the Size of Queue. (size <= Request Size).
	//@Return				:	int.
	int QTNNList::Size()
	{
		return QTPointQueue.size();
	}

	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Method to copy the current queue data to input vector. The vector is fill in ascending order.
	//							norm(list[i]) <= norm(list(i+1))
	//@Input1				:	Point Vector (vecttor<QTPoint>).
	//@Return				:	void.
	void QTNNList::DeepCopy(std::vector<QTPoint> &list)
	{
		list.resize(QTPointQueue.size());

		for (int i = this->Size() -1; i >= 0; --i)
		{
			list[i] = QTPoint(QTPointQueue.top().x, QTPointQueue.top().y);
			QTPointQueue.pop();
		}
	}
}