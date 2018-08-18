#ifndef _QTPOINT_H
#define _QTPOINT_H

#include "Common.h"

namespace Common
{
	//class representing a 2D Point
	class QTPoint
	{
	public:
		double x, y;
	
	public:
		QTPoint(double _x, double _y) { x = _x, y = _y; }
		QTPoint() { x = y = 0; }

		//overloading operator '+'.
		friend QTPoint operator+(QTPoint const &rhs1, QTPoint const &rhs2)
		{
			QTPoint p;
			p.x = rhs1.x + rhs2.x;
			p.y = rhs1.y + rhs2.y;
			return p;
		}
		
		//overloading operator '-'.
		friend QTPoint operator-(QTPoint const &rhs1, QTPoint const &rhs2)
		{
			QTPoint p;
			p.x = rhs1.x - rhs2.x;
			p.y = rhs1.y - rhs2.y;
			return p;
		}

		//overloading operator '*'.
		friend QTPoint operator*(QTPoint const &rhs1, QTPoint const &rhs2)
		{
			QTPoint p;
			p.x = rhs1.x * rhs2.x;
			p.y = rhs1.y * rhs2.y;
			return p;
		}

		//overloading operator '<'.
		friend bool operator<(const QTPoint &lhs, const QTPoint &rhs)
		{
			return (((lhs.x*lhs.x) + (lhs.y*lhs.y)) < ((rhs.x*rhs.x) + (rhs.y*rhs.y)));
		}

		//overloading operator '>'.
		friend bool operator>(const QTPoint &lhs, const QTPoint &rhs)
		{
			return (((lhs.x*lhs.x) + (lhs.y*lhs.y)) > ((rhs.x*rhs.x) + (rhs.y*rhs.y)));
		}

		//returns the L2 Norm of the vector.
		double Norm()
		{
			return sqrt(pow(this->x, 2) + pow(this->y, 2));
		}
	};

} // namespace Common

#endif