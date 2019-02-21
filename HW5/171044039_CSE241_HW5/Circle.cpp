/* 
 * Circle.cpp
 * 
 * Created on: Oct 26, 2018
 * Edited on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Circle.h"
#include <cstdlib> // for exit(1) func.

namespace shape_ozmekik
{

	using std::endl;

	// Total area and perimeter.
	double Circle::total_area = 0.0;
	double Circle::total_perim = 0.0;

	Circle::Circle(double r,double _x, double _y)throw(bad_size)
		: Shape()
		, radius(r)
		, x(_x)
		, y(_y)
		, fill(false)
		
	{
		if(r<=0) throw bad_size();

		area = radius*radius*3.14159;
		perim = radius*2.0*3.14159;
		total_area+=getArea();
		total_perim+=getPerim();

	}

	inline double Circle::getRadius() const 		{return radius;}
	inline bool Circle::getFill() const				{return fill;}
	inline double Circle::getX()const				{return x;}
	inline double Circle::getY()const				{return y;}
	void Circle::setPosition(double _x, double _y) 	{x=_x; y=_y;}
	void Circle::setFill(bool f)					{fill = f;}
	
	std::ostream& Circle::draw(std::ostream& outfile)
	{
		if(getHeader())
		{
			outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
			<<"width=\""<<getRadius()*2.0<< "\" height=\""<<getRadius()*2.0<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
		}

		outfile <<   "<circle cx=\"" << getX() <<
						  "\" cy=\"" << getY() <<
					      "\" r=\""  << getRadius() << 
					      "\" stroke=\"black\" stroke-width=\"1.6\"" <<" fill=\""; 

	  	getFill()? outfile << "cornflowerblue\"/>" :  outfile << "white\"/>"; 
	  	outfile<<endl;

	  	if(getHeader()) outfile<<" </svg>";

	    return outfile;
	}

	void Circle::setRadius(double r)throw(bad_size)		
	{	
		if(r<=0) throw bad_size();
		total_area-=Shape::getArea();
		radius = r;
		total_area+=Shape::getArea();
	}

	Circle& Circle::operator++() 
	{
		setPosition(getX()+1,getY()+1); /* update this */


		return *this;

	}
	Circle& Circle::operator++(int ignore) 
	{

		Circle *circle = new Circle(*this); 

		setPosition(getX()+1,getY()+1); /* update this */

		return *circle;
	}
	
	Circle& Circle::operator--() 
	{
		setPosition(getX()-1,getY()-1); /* update this */

		return *this;

	}
	Circle& Circle::operator--(int ignore) 
	{

		Circle *circle = new Circle(*this); 

		setPosition(getX()-1,getY()-1); /* update this */
		
		return *circle;
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
}