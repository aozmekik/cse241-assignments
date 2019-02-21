/* 
 * Circle.cpp
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Circle.h"
#include <cstdlib> // for exit(1) func.

// Total area and perimeter.
double Circle::total_area = 0.0;
double Circle::total_perim = 0.0;

Circle::Circle(double r,double _x, double _y)
	: radius(r)
	, x(_x)
	, y(_y)
	, fill(false)
	, header(false)
{
	testValidity(); // terminates if the input is invalid.
	total_area+=getArea();
	total_perim+=getPerimeter();

}

void Circle::testValidity()
{
	if(radius<0)
	{
		cout<<"Unvalid length value!";
		exit(1);
	}
}
ostream& operator <<(ostream& outfile, const Circle& c)
{
	if(c.header)
	{
		outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
		<<"width=\""<<c.getRadius()*2.0<< "\" height=\""<<c.getRadius()*2.0<<"\""
		<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
	}

	outfile <<   "<circle cx=\"" << c.getX() <<
					  "\" cy=\"" << c.getY() <<
				      "\" r=\""  << c.getRadius() << 
				      "\" stroke=\"black\" stroke-width=\"1.6\"" <<" fill=\""; 

  	c.getFill()? outfile << "cornflowerblue\"/>" :  outfile << "white\"/>"; 
  	outfile<<endl;

  	if(c.header) outfile<<" </svg>";

    return outfile;
}

void Circle::setRadius(double r)		
{	
	testValidity();
	total_area-=getArea();
	radius = r;
	total_area+=getArea();
}


Circle Circle::operator++()
{
	Circle temp(*this);
	++x; ++y;
	return temp;
}
Circle Circle::operator++(int ignore) 
{ 
	++x; ++y;
	return *this;
}
Circle Circle::operator--()
{
	Circle temp(*this);
	--x; --y;
	return temp;
}
Circle Circle::operator--(int ignore) 
{ 
	x--; y--;
	return *this;
}
Circle Circle::operator+(double size)const
{
	Circle temp(*this);
	temp.setRadius(radius+size);
	return temp;
}
Circle Circle::operator-(double size)const
{
	Circle temp(*this);
	temp.setRadius(radius+size);
	return temp;
} 