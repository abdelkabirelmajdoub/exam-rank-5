#pragma once 
#include <iostream>

class vect2
{

	public:
		int x, y;
		vect2();
		vect2(int a, int b);
		vect2(const vect2& copy);
		vect2 &operator=(const vect2 &copy);
		int &vect2::operator[](int index);
};

vect2::vect2():x(0), y(0) {}

vect2::vect2(int a, int b): x(a), y(b){}

vect2::vect2(const vect2& copy){
	this->x = copy.x;
	this->y = copy.y;
}
vect2 &vect2::operator=(const vect2 &copy){
	if (this != &copy)
	{
		this->x = copy.x;
		this->y = copy.y;
	}
	return *this;
}
int &vect2::operator[](int index)
{
	if (index == 0)
		return this->x;
	return this->y;
}






std::ostream &operator<<(std::ostream &s, const vect2 &v)
{
	s << "{" << v[0] << ", " << v[1] << "}" << std::endl;
	return s;
}

