/* 
 * Triangle.cpp
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Triangle.h"
#include <cstdlib> // for exit(1) func.

// Total area and perimeter.
double Triangle::total_area = 0.0;
double Triangle::total_perim = 0.0;


Triangle::Triangle(double len, double _x, double _y)
	: length(len)
	, x(_x)
	, y(_y)
	, rotate(false)
	, fill(false)
	, header(false)
{
	testValidity(); // terminates if the input is invalid.
	total_area+=getArea();
	total_perim+=getPerimeter();  
}

void Triangle::testValidity()
{
	if(length<=0)
	{
		cout<<length;
		cout<<"Unvalid length value!";
		exit(1);
	}
}

ostream& operator<<(ostream& outfile,const Triangle& t)
{
	if(t.header)
	{
		outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
		<<"width=\""<<t.getLength()<< "\" height=\""<<t.getLength()<<"\""
		<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
	}


	// as said, other two points are taken in below and if rotate is true:
	// they will be in above.
	outfile << "<polygon points=\""<< t.getX() << "," << t.getY()
							<< " " << t.getX()-t.getLength()/2.0 
							<< "," << t.getY()+(t.getLength()/2.0)*sqrt(3.0)
							<< " " << t.getX()+t.getLength()/2.0 
							<< "," << t.getY()+(t.getLength()/2.0)*sqrt(3.0)
							<< "\" fill=";


	t.getFill()? outfile << "\"cornflowerblue\"" :  outfile << "\"white\""; 

	outfile<< " stroke=\"black\" stroke-width=\"1.6\" "<<endl;

	if(t.getRotate()) outfile << " transform = \" rotate(180," << t.getX() << "," << t.getY() <<")\"";

	outfile << "/>" << endl;

	if(t.header) outfile<<" </svg>";

	return outfile;
}

void Triangle::setLength(double len)
{
	testValidity();
	total_area-=getArea();
	length=len;
	total_area+=getArea();
}			


Triangle Triangle::operator++()
{
	Triangle temp(*this);
	++x; ++y;
	return temp;
}
Triangle Triangle::operator++(int ignore) 
{ 
	++x; ++y;
	return *this;
}
Triangle Triangle::operator--()
{
	Triangle temp(*this);
	--x; --y;
	return temp;
}
Triangle Triangle::operator--(int ignore) 
{ 
	x--; y--;
	return *this;
}
Triangle Triangle::operator+(double size)const
{
	Triangle temp(*this);
	temp.setLength(length+size);
	return temp;
}

Triangle Triangle::operator-(double size)const
{
	Triangle temp(*this);
	temp.setLength(length+size);
	return temp;
} 