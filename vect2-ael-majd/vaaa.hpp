#pragma once

#include <iostream>

class vect2{
	public:
		int x, y;
		vect2(): x(0), y(0){}
		vect2(int _x, int _y): x(_x), y(_y){}

		vect2(const vect2 &oth){
			this->x = oth.x;
			this->y = oth.y;
		}
		vect2 &operator=(const vect2 &oth){
			if (this != &oth)
			{
				this->x = oth.x;
				this->y = oth.y;
			}
			return *this;
		}
		int &operator[](int index)
		{
			if (index == 0)
				return this->x;
			return this->y;
		}
		const int &operator[](int index) const
		{
			if (index == 0)
				return this->x;
			return this->y;
		}
		vect2 operator++(int)
		{
			vect2 tmp = *this;
			this->x++;
			this->y++;
			return tmp;
		}
		vect2 operator++()
		{
			this->x++;
			this->y++;
			return *this;
		}
		vect2 operator--(int)
		{
			vect2 tmp = *this;
			this->x--;
			this->y--;
			return tmp;
		}
		vect2 operator--()
		{
			this->x--;
			this->y--;
			return *this;
		}
		vect2 operator+=(const vect2 &oth)
		{
			this->x += oth.x;
			this->y += oth.y;
			return *this;
		}
		vect2 operator-=(const vect2 &oth)
		{
			this->x -= oth.x;
			this->y -= oth.y;
			return *this;
		}
		vect2 operator*(int scalar) const
		{
			return vect2(x * scalar, y * scalar);
		}
		vect2 operator*=(int s)
		{
			x *= s;
			y *= s;
			return *this;
		}

		vect2 operator+(const vect2 &oth) const
		{
			return vect2(x + oth.x, y + oth.y);
		}
		vect2 operator-(const vect2 &oth) const
		{
			return vect2(x - oth.x, y - oth.y);
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

vect2 operator*(int s, const vect2 &oth)
{
	return vect2(oth.x * s, oth.y * s);
}


std::ostream &operator<<(std::ostream &os, const vect2 &v)
{
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}
