/* 
 * Triangle.cpp
 * 
 * Created on: Oct 26, 2018
 * Edited on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Triangle.h"


namespace shape_ozmekik
{
	using std::endl;

	// Total area and perimeter.
	double Triangle::total_area = 0.0;
	double Triangle::total_perim = 0.0;


	inline double Triangle::getLength() const 					{return length;}
	inline double Triangle::getX()const							{return x;}
	inline double Triangle::getY()const							{return y;}
	inline bool Triangle::getRotate()const						{return rotate;}
	inline bool Triangle::getFill() const						{return fill;}
	void Triangle::setPosition(double _x, double _y)			{x=_x; y=_y;}
	void Triangle::setRotate(bool r)							{rotate = r;}
	void Triangle::setFill(bool f)								{fill = f;}

	Triangle::Triangle(double len, double _x, double _y) throw(bad_size)
		: Shape()
		, length(len)
		, x(_x)
		, y(_y)
		, rotate(false)
		, fill(false)
	{
		if(len<=0) throw bad_size();

		area = length*length*sqrt(3)/4.0;
		perim = 3.0*length;
		total_area+=getArea();
		total_perim+=getPerim();  
	}

	

	std::ostream& Triangle::draw(std::ostream& outfile)
	{
		if(getHeader())
		{
			outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
			<<"width=\""<<getLength()<< "\" height=\""<<getLength()<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;
		}


		// as said, other two points are taken in below and if rotate is true:
		// they will be in above.
		outfile << "<polygon points=\""<< getX() << "," << getY()
								<< " " << getX()-getLength()/2.0 
								<< "," << getY()+(getLength()/2.0)*sqrt(3.0)
								<< " " << getX()+getLength()/2.0 
								<< "," << getY()+(getLength()/2.0)*sqrt(3.0)
								<< "\" fill=";


		getFill()? outfile << "\"cornflowerblue\"" :  outfile << "\"white\""; 

		outfile<< " stroke=\"black\" stroke-width=\"1.6\" "<<endl;

		if(getRotate()) outfile << " transform = \" rotate(180," << getX() << "," << getY() <<")\"";

		outfile << "/>" << endl;

		if(getHeader()) outfile<<" </svg>";

		return outfile;
	}

	void Triangle::setLength(double len) throw(bad_size)
	{
		if(len<=0) throw bad_size();

		total_area-=Shape::getArea();
		length=len;
		total_area+=Shape::getArea();
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


	Triangle& Triangle::operator++() 
	{
		setPosition(getX()+1,getY()+1); /* update this */

		return *this;

	}
	Triangle& Triangle::operator++(int ignore) 
	{

		Triangle *triangle = new Triangle(*this); 

		setPosition(getX()+1,getY()+1); 

		return *triangle;
	}
	
	Triangle& Triangle::operator--() 
	{
		setPosition(getX()-1,getY()-1); 

		return *this;

	}
	Triangle& Triangle::operator--(int ignore) 
	{

		Triangle *triangle = new Triangle(*this); 

		setPosition(getX()-1,getY()-1); 
		
		return *triangle;
	}

}