#pragma once 

#include <iostream>

class vect2 {
	public:
		int x, y;
		vect2(): x(0), y(0){}
		vect2(int _x, int _y): x(_x), y(_y){}
		vect2(const vect2 &oth)
		{
			x = oth.x;
			y = oth.y;
		}
		vect2 &operator=(const vect2 &oth)
		{
			if (this != &oth)
			{
				x = oth.x;
				y = oth.y;
			}
			return *this;
		}
		int &operator[](int index)
		{
			if (index == 0)
				return x;
			return y;
		}
		const int &operator[](int index) const
		{
			if (index == 0)
				return x;
			return y;
		}
		vect2 operator++()
		{
			x++;
			y++;
			return *this;
		}
		vect2 operator++(int)
		{
			vect2 tmp = *this;
			x++;
			y++;
			return tmp;
		}
		vect2 operator--(int)
		{
			vect2 tmp = *this;
			x--;
			y--;
			return tmp;
		}
		vect2 operator--()
		{
			x--;
			y--;
			return *this;
		}
		vect2 operator+=(const vect2 &v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		vect2 operator-=(const vect2 &v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		vect2 operator*(int s) const
		{
			return vect2(x * s, y * s);
		}
		vect2 operator+(const vect2 &v) const
		{
			return vect2(v.x + x, v.y + y);
		}
		vect2 operator-(const vect2 &v) const
		{
			return vect2(v.x - x, v.y - y);
		}
		vect2 operator*=(int s)
		{
			x *= s;
			y *= s;
			return *this;
		}
		vect2 operator-()
		{
			return vect2(-x, -y);
		}
		bool operator==(const vect2 &v)
		{
			if (x == v.x && y == v.y)
				return true;
			return false;
		}
		bool operator!=(const vect2 &v)
		{
			if (x != v.x || y != v.y)
				return true;
			return false;
		}
};
vect2 operator*(int s, const vect2 &v) 
{
	return vect2(v.x * s, v.y * s);
}

std::ostream &operator<<(std::ostream &s, const vect2 &v)
{
	s << "{" << v[0] << ", " << v[1] << "}";
	return s;
}