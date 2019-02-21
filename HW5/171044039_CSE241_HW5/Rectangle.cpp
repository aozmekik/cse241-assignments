/*
 * Rectangle.cpp 
 * 
 * Created on: Oct 26, 2018
 * Edited on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Rectangle.h"
#include <cstdlib> // for exit(1) func.

namespace shape_ozmekik
{

	using std::endl;

	// Total area and perimeter.
	double Rectangle::total_area = 0.0;
	double Rectangle::total_perim = 0.0;

	Rectangle::Rectangle(double w, double h, double _x, double _y)throw(bad_size)
		: Shape()
		, width(w)
		, height(h)
		, x(_x)
		, y(_y)
		, rotate(false)
		, fill(false)
	{	
		if(h<=0 || w<=0) throw bad_size();

		area = width * height;
		perim = 2.0*(width+height);
		total_area+=getArea();
		total_perim+=getPerim();    	
	}

	inline double Rectangle::getWidth()const			{return width;}
	inline double Rectangle::getHeight()const			{return height;}
	inline double Rectangle::getX()const				{return x;}
	inline double Rectangle::getY()const				{return y;}
	inline bool Rectangle::getRotate()const			{return rotate;}
	inline bool Rectangle::getFill() const				{return fill;}
	void Rectangle::setRotate(bool r)					{rotate=r;}
	void Rectangle::setFill(bool f)					{fill=f;}
	void Rectangle::setPosition(double _x, double _y) 	{x=_x; y=_y;}




	void Rectangle::swapEdges()
	{
		// basic swaping operation
		double temp;
		temp = getWidth();
		setWidth(getHeight());
		setHeight(temp);
	}

	std::ostream& Rectangle::draw(std::ostream& outfile)
	{
		if(getHeader())
		{
			outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
			<<"width=\""<<getWidth()<< "\" height=\""<<getHeight()<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
		}

		outfile<< "<rect width=\"" << getWidth() 
		       <<   "\" height=\"" << getHeight() 
		       <<    "\" y=\"" << getY() 
		       <<	 "\" x=\"" << getX() 
		       <<    "\" stroke=\"black\" stroke-width=\"1.6\""
		       << " fill="; 

		getFill()? outfile << "\"cornflowerblue\"/>" :  outfile << "\"white\"/>"; 

		if(getRotate()) 
		{
				outfile << " transform = \" rotate(90," 
						   << getX() << "," 
						   << getY() <<")\"";
		}

		outfile << "/>" << endl;

		if(getHeader()) outfile<<" </svg>";

		return outfile;
	}


	void Rectangle::setWidth(double w)throw(bad_size)		
	{	
		if(w<=0) throw bad_size();
		total_area-=getArea();
		width=w;
		total_area+=getArea(); 
	}
	void Rectangle::setHeight(double h)	throw(bad_size)	
	{	
		if(h<=0) throw bad_size();
		total_area-=getArea();
		height=h;
		total_area+=getArea(); 
	}

	Rectangle& Rectangle::operator++() 
	{
		setPosition(getX()+1,getY()+1); /* update this */

		return *this;

	}
	Rectangle& Rectangle::operator++(int ignore) 
	{

		Rectangle *rectangle = new Rectangle(*this); 

		setPosition(getX()+1,getY()+1); /* update this */

		return *rectangle;
	}
	
	Rectangle& Rectangle::operator--() 
	{
		setPosition(getX()-1,getY()-1); /* update this */

		return *this;

	}

	Rectangle& Rectangle::operator--(int ignore)
	{

		Rectangle *rectangle = new Rectangle(*this); 

		setPosition(getX()-1,getY()-1); /* update this */
		
		return *rectangle;
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
}