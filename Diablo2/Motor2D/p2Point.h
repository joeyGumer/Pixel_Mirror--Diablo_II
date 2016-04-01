// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __P2POINT_H__
#define __P2POINT_H__

#include "p2Defs.h"
#include <math.h>

#define RADTODEG 57.2957795

template<class TYPE>
class p2Point
{
public:

	TYPE x, y;

	p2Point()
	{}

	p2Point(const p2Point<TYPE>& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	p2Point(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;
	}

	p2Point& create(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;

		return(*this);
	}

	// Math ------------------------------------------------
	p2Point operator -(const p2Point &v) const
	{
		p2Point r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Point operator + (const p2Point &v) const
	{
		p2Point r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	p2Point operator / (const float& m) const
	{
		p2Point r;

		r.x = x / m;
		r.y = y / m;

		return (r);
	}

	p2Point operator * (const float& m) const
	{
		p2Point r;

		r.x = x * m;
		r.y = y * m;

		return (r);
	}

	const p2Point& operator -=(const p2Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const p2Point& operator +=(const p2Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	/*const p2Point& operator *=(const f& float)
	{
		x *= f;
		y *= f;

		return(*this);
	}

	const p2Point& operator /=(const f& float)
	{
		x /= f;
		y /= f;

		return(*this);
	}*/

	bool operator ==(const p2Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const p2Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0);
	}

	p2Point& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	p2Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	// Distances ---------------------------------------------
	TYPE DistanceTo(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return sqrtf((fx*fx) + (fy*fy));
	}

	TYPE DistanceNoSqrt(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (fx*fx) + (fy*fy);
	}

	TYPE DistanceManhattan(const p2Point& v) const
	{
		return abs(v.x - x) + abs(v.y - y);
	}

	//Vector methods

	void Normalize()
	{
		float module = GetModule();
		if (module != 0)
		{
			x /= module;
			y /= module;
		}
		else
		{
			x = 0;
			y = 0;
		}
	}

	p2Point GetNormal()
	{
		float module = GetModule();
		if (module != 0)
		{
			p2Point ret;
		
			ret.x = x / module;
			ret.y = y / module;

			return ret;
		}

		return{ 0, 0 };
	}

	float GetModule()
	{
		return DistanceTo({ 0, 0 });
	}

	void SetModule(const float& f)
	{
		Normalize();

		x *= f;
		y *= f;
	}

	float GetAngle()
	{
		return (atan2(y, x) * RADTODEG);
	}
};

typedef p2Point<int> iPoint;
typedef p2Point<float> fPoint;

#endif // __P2POINT_H__