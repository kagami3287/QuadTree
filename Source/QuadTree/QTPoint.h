#ifndef _QTPOINT_H
#define _QTPOINT_H

#include "math.h"

namespace Common
{
	//@Author				:	Ravi Teja Narra (kagami3287).
	//@Description			:	Class for 2D Points. Many operators(=,+,-,*,<,>,==) were overwritten for this class 
	//							for ease of use.

	class QTPoint
	{
	public:
		double x, y;

	public:
		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	Class Constructor.
		//@Inputs				:	x,y coordinates of the point (double,double).
		QTPoint(double _x, double _y) { x = _x, y = _y; }

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	Class Constructor. Initializes object to (0,0).
		QTPoint() { x = y = 0; }

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '='.
		//@Inputs				:	point (QTPoint).
		//@Return				:	QTPoint
		QTPoint & operator=(QTPoint const &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;

			return *this;
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '+'.
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint).
		//@Return				:	QTPoint
		friend QTPoint operator+(QTPoint const &rhs1, QTPoint const &rhs2)
		{
			QTPoint p;
			p.x = rhs1.x + rhs2.x;
			p.y = rhs1.y + rhs2.y;
			return p;
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '-'.
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint).
		//@Return				:	QTPoint
		friend QTPoint operator-(QTPoint const &rhs1, QTPoint const &rhs2)
		{
			QTPoint p;
			p.x = rhs1.x - rhs2.x;
			p.y = rhs1.y - rhs2.y;
			return p;
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '*'.
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint).
		//@Return				:	QTPoint
		friend QTPoint operator*(QTPoint const &rhs1, QTPoint const &rhs2)
		{
			QTPoint p;
			p.x = rhs1.x * rhs2.x;
			p.y = rhs1.y * rhs2.y;
			return p;
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '<'.
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint)..
		//@Return				:	bool
		friend bool operator<(const QTPoint &lhs, const QTPoint &rhs)
		{
			return (((lhs.x*lhs.x) + (lhs.y*lhs.y)) < ((rhs.x*rhs.x) + (rhs.y*rhs.y)));
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '>'.
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint).
		//@Return				:	bool
		friend bool operator>(const QTPoint &lhs, const QTPoint &rhs)
		{
			return (((lhs.x*lhs.x) + (lhs.y*lhs.y)) > ((rhs.x*rhs.x) + (rhs.y*rhs.y)));
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '=='. 
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint).
		//@Return				:	bool
		friend bool operator==(const QTPoint &lhs, const QTPoint & rhs)
		{
			double norm = (lhs - rhs).Norm();

			return (norm == 0);
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '=='. 
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint).
		//@Return				:	bool
		friend bool operator<=(const QTPoint &lhs, const QTPoint & rhs)
		{
			bool bXCompare = (lhs.x <= rhs.x);
			bool bYCompare = (lhs.y<= rhs.y);

			return (bXCompare && bYCompare);
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	overwriting operator '=='. 
		//@Inputs				:	rhs1,rhs2 (QTPoint,QTPoint).
		//@Return				:	bool
		friend bool operator>=(const QTPoint &lhs, const QTPoint & rhs)
		{
			bool bXCompare = (lhs.x >= rhs.x);
			bool bYCompare = (lhs.y >= rhs.y);

			return (bXCompare && bYCompare);
		}

		//@Author				:	Ravi Teja Narra (kagami3287).
		//@Description			:	Method to measure the L2 norm of (x,y).
		//@Return				:	double
		double Norm()
		{
			return sqrt(pow(this->x, 2) + pow(this->y, 2));
		}
	};

} // namespace Common

#endif