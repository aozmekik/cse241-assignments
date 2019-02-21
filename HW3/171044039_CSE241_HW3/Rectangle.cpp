/*
 * Rectangle.cpp 
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Rectangle.h"
#include <cstdlib> // for exit(1) func.

// Total area and perimeter.
double Rectangle::total_area = 0.0;
double Rectangle::total_perim = 0.0;

Rectangle::Rectangle(double w, double h, double _x, double _y)
	: width(w)
	, height(h)
	, x(_x)
	, y(_y)
	, rotate(false)
	, fill(false)
	, header(false)
{	
	testValidity(); // terminates if the input is not valid.
	total_area+=getArea();
	total_perim+=getPerimeter();    	
}

void Rectangle::testValidity() const
{
	if(width<=0 || height<=0)
	{
		cout<<"Unvalid length value!";
		exit(1);
	}
}


void Rectangle::swapEdges()
{
	// basic swaping operation
	double temp;
	temp = getWidth();
	setWidth(getHeight());
	setHeight(temp);
}

ostream& operator<<(ostream& outfile,const Rectangle& r)
{
	if(r.header)
	{
		outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
		<<"width=\""<<r.getWidth()<< "\" height=\""<<r.getHeight()<<"\""
		<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
	}

	outfile<< "<rect width=\"" << r.getWidth() 
	       <<   "\" height=\"" << r.getHeight() 
	       <<    "\" y=\"" << r.getY() 
	       <<	 "\" x=\"" << r.getX() 
	       <<    "\" stroke=\"black\" stroke-width=\"1.6\""
	       << " fill="; 

	r.getFill()? outfile << "\"cornflowerblue\"/>" :  outfile << "\"white\"/>"; 

	if(r.getRotate()) 
	{
			outfile << " transform = \" rotate(90," 
					   << r.getX() << "," 
					   << r.getY() <<")\"";
	}

	outfile << "/>" << endl;

	if(r.header) outfile<<" </svg>";

	return outfile;
}


void Rectangle::setWidth(double w)		
{	
	testValidity();
	total_area-=getArea();
	width=w;
	total_area+=getArea(); 
}
void Rectangle::setHeight(double h)		
{	
	testValidity();
	total_area-=getArea();
	height=h;
	total_area+=getArea(); 
}


Rectangle Rectangle::operator++()
{
	Rectangle temp(*this);
	++x; ++y;
	return temp;
}
Rectangle Rectangle::operator++(int ignore) 
{ 
	++x; ++y;
	return *this;
}
Rectangle Rectangle::operator--()
{
	Rectangle temp(*this);
	--x; --y;
	return temp;
}
Rectangle Rectangle::operator--(int ignore) 
{ 
	x--; y--;
	return *this;
}
Rectangle Rectangle::operator+(double size)const
{
	Rectangle temp(*this);
	temp.setWidth(width+size);
	temp.setHeight(height+size);
	return temp;
}

Rectangle Rectangle::operator-(double size)const
{
	Rectangle temp(*this);
	temp.setWidth(width-size);
	temp.setHeight(height-size);
	return temp;
} 
