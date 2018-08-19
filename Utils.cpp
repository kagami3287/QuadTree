#include "Utils.h"

namespace Common
{
	unsigned int QTNNList::m_sRequestSize = 1;

	QTNNList::QTNNList()
	{
		while (!QTPointQueue.empty())
		{
			QTPointQueue.pop();
		}
	}

	QTNNList::~QTNNList()
	{
		while (!QTPointQueue.empty())
		{
			QTPointQueue.pop();
		}
	}

	void QTNNList::SetRequestSize(unsigned int nReq)
	{
		this->m_sRequestSize = nReq;
	}

	void QTNNList::Push(QTPoint p)
	{
		this->QTPointQueue.push(p);
		if (this->QTPointQueue.size() > this->m_sRequestSize)
		{
			this->QTPointQueue.pop();
		}
	}

	void QTNNList::Pop()
	{
		this->QTPointQueue.pop();
	}

	const QTPoint QTNNList::top()
	{
		return QTPointQueue.top();
	}

	int QTNNList::size()
	{
		return QTPointQueue.size();
	}
	void QTNNList::DeepCopy(vector<QTPoint> &list)
	{
		list.resize(QTPointQueue.size());
		for (int i = 0; !QTPointQueue.empty(); ++i)
		{
			list[i] = QTPoint(QTPointQueue.top().x, QTPointQueue.top().y);
			QTPointQueue.pop();
		}
	}
}