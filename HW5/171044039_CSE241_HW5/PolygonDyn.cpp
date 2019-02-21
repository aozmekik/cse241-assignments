/* 
 * PolygonDyn.cpp
 * 
 * Created on: Dec 18, 2018
 * Author: Ahmed Semih Özmekik
 */



#include "PolygonDyn.h"
#include <cmath>

namespace shape_ozmekik
{
	
	using std::endl;

	PolygonDyn::PolygonDyn(const PolygonDyn& other)throw(std::bad_alloc)
	{	
		setSize(other.getSize());
		point = new PolygonDyn::Point2D[getSize()]; /* allocating */
		header = other.getHeader();
		area = other.getArea();
		perim = other.getPerim();

		for(int i=0;i<getSize();++i)
			point[i] = other[i]; 
	}

	PolygonDyn::PolygonDyn():Polygon(0), point(nullptr)
	{/* intentionally left blank */}


	PolygonDyn::PolygonDyn(const PolygonDyn::Point2D& singlePoint)throw(std::bad_alloc)
	: Polygon(1)
	{

		point = new PolygonDyn::Point2D;
		point[0] = singlePoint; 
	}

	PolygonDyn::PolygonDyn(const Rectangle& rectangle)throw(std::bad_alloc)
	: Polygon(4)
	{
		point = new PolygonDyn::Point2D[getSize()]; /* 4 points for 4 corners */
		area = rectangle.getArea();
		perim = rectangle.getPerim();

		const double x = rectangle.getX();
		const double y = rectangle.getY();

		// Drawing route: 
		/* (x,y) left-most corner-> go to right -> go down -> then go left */ 
		point[0].setPoint(x,y);
		point[1].setPoint(x+rectangle.getWidth(),y);
		point[2].setPoint(x+rectangle.getWidth(),y+rectangle.getHeight());
		point[3].setPoint(x,y+rectangle.getHeight());
	}

	PolygonDyn::PolygonDyn(const Circle& circle)throw(std::bad_alloc)
	: Polygon(100)
	{
		point = new PolygonDyn::Point2D[getSize()]; /* 100 equal interval for circle*/
		area = circle.getArea();
		perim = circle.getPerim();

		const double PI = 3.14159; //value of pi to determine circle's point.
		double x=0.0,y=0.0; // coord. 

		for(int i=0;i<getSize();++i)
		{
			x = circle.getX() + cos(2.0*i*PI/getSize())*circle.getRadius();
			y = circle.getY() + sin(2.0*i*PI/getSize())*circle.getRadius();
			point[i].setPoint(x,y);
		}	

	}

	PolygonDyn::PolygonDyn(const Triangle& triangle)throw(std::bad_alloc)
	: Polygon(3)
	{
		point = new PolygonDyn::Point2D[getSize()]; /* 3 points for 3 corners */
		area = triangle.getArea();
		perim = triangle.getPerim();

		const double x = triangle.getX();
		const double y = triangle.getY();

		//Drawing route:
		/* (x,y) top corner -> go to down and right -> go left */
		point[0].setPoint(x,y);
		if(triangle.getRotate())
		{
			point[1].setPoint(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*sqrt(3)/2.0); 
			point[2].setPoint(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*sqrt(3)/2.0);
		}
		else
		{
			point[1].setPoint(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
								 y+triangle.getLength()*sqrt(3)/2.0); 
			point[2].setPoint(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y+triangle.getLength()*sqrt(3)/2.0);
		}
	}	



	const PolygonDyn::Point2D& PolygonDyn::operator[](int idx)const throw(bad_index)
	{
		if(idx<0) throw bad_index();
		return point[idx];
	}

	PolygonDyn::Point2D& PolygonDyn::operator[](int idx) throw(bad_index)
	{
		if(idx<0) throw bad_index();
		return point[idx];
	}	

	const PolygonDyn& PolygonDyn::operator=(const PolygonDyn& other)throw(std::bad_alloc)
	{
		if(other.getSize() == getSize()) // No need for allocation, just copy.
		{
			for(int i=0;i<getSize();i++)
				point[i] = other[i];
		}
		else
		{
			delete[] point;  

			setSize(other.getSize()); 
			point = new PolygonDyn::Point2D[getSize()];

			for(int i=0;i<getSize();++i)
				point[i] = other[i];
		}
		header = other.getHeader();

		return *this;
	}

	PolygonDyn PolygonDyn::operator+(const PolygonDyn& other)const throw(std::bad_alloc)
	{
		std::vector<PolygonDyn::Point2D> newPoint;
		newPoint.reserve(getSize()+other.getSize());

		/* Concatenating the points in newPoint vector. */
		for(int i=0;i<getSize();i++)
			newPoint.push_back(point[i]);
		for(int i=0;i<other.getSize();i++)
			newPoint.push_back(other[i]);

		return	*this;
	}

	PolygonDyn::~PolygonDyn()
	{
		delete[] point;
	}

	std::ostream& PolygonDyn::draw(std::ostream& outfile)
	{
		
		// default height and width, for printing singular PolygonDyns. 
		
		if(getHeader()) 
		{
			outfile<<"<svg version=\"1.1\"" <<std::endl<< "baseProfile=\"full\"" <<std::endl
			<<"width=\""<<500<< "\" height=\""<<500<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<std::endl;
		}

		outfile<<std::endl<<"<polygon points=\"";
		for(int i=0;i<getSize();++i)
			outfile<<point[i].getX()<<","<<point[i].getY()<<" ";

		outfile<<"\""<<" style=\"fill:cornflowerblue;";
		outfile<<"stroke:black;stroke-width:1.6\" />";


		if(getHeader())	outfile<<endl<<"</svg>";

		return outfile;
	}

	void PolygonDyn::setPoint(const Rectangle& rectangle)throw(std::bad_alloc)
	{

		*this = PolygonDyn(rectangle); 
	}

	void PolygonDyn::setPoint(const Circle& circle)throw(std::bad_alloc)
	{
		*this = PolygonDyn(circle);
	}

	void PolygonDyn::setPoint(const Triangle& triangle)throw(std::bad_alloc)
	{
		*this = PolygonDyn(triangle);
	}

	PolygonDyn& PolygonDyn::operator++()
	{
		for(int i=0;i<getSize();++i)
			point[i].setPoint(point[i].getX()+1,point[i].getY()+1);

		return *this;
		
	}
	PolygonDyn& PolygonDyn::operator++(int ignore)
	{
		PolygonDyn *poly_dyn = new PolygonDyn(*this);
		for(int i=0;i<getSize();++i)
			point[i].setPoint(point[i].getX()+1,point[i].getY()+1);

		return *poly_dyn;

	} 
	PolygonDyn& PolygonDyn::operator--()
	{
		for(int i=0;i<getSize();++i)
			point[i].setPoint(point[i].getX()-1,point[i].getY()-1);

		return *this;
	}
	PolygonDyn& PolygonDyn::operator--(int ignore)
	{
		PolygonDyn *poly_dyn = new PolygonDyn(*this);
		for(int i=0;i<getSize();++i)
			point[i].setPoint(point[i].getX()-1,point[i].getY()-1);

		return *poly_dyn;
	}

	

}
	
