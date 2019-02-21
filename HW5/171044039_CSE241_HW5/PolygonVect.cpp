/* 
 * PolygonVect.cpp
 * 
 * Created on: Dec 18, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "PolygonVect.h"
#include <cmath>

namespace shape_ozmekik
{
	using std::endl;


	std::vector<Shape*> convertAll(const std::vector<Shape*> shape) throw(std::bad_alloc)
	{	
		std::vector<PolygonVect> *polygon = new std::vector<PolygonVect>;
		/* PolygonVect picked for this implementation, since 
		 * polygons are mans in middle it does not matter
		 * which to use. And it must stored in the heap, because 
		 * we are going need the address of polygons to keep them in the 
		 * new vector shape* in order to make them remain. */   
		std::vector<Shape*> new_shape;

		polygon->reserve(shape.size()); // for to improve effiency. 
		new_shape.reserve(shape.size());

		for(unsigned int i=0;i<shape.size();++i)
		{
			polygon->push_back(shape[i]);
			new_shape.push_back(&polygon->at(i));
		}

		return new_shape;
	}

	/* Even though the polygons are also shapes,
	 * the converter constructor's idea being all about 
	 * converting from other shapes(Rectangle, Triangle, Circle)
	 * to polygons made polygons are not considered to bo converted,
	 * therefore not handled in this implementation. */  
	PolygonVect::PolygonVect(Shape* shape) throw(std::bad_cast, bad_shape)  
	{
		/* Possible downcast cases */
		Rectangle *r;
		Triangle  *t;
		Circle    *c;

		// downcast try.
		if((r = dynamic_cast<Rectangle*>(shape)))
			*this = PolygonVect(*r);
		else if((t = dynamic_cast<Triangle*>(shape)))
			*this = PolygonVect(*t);
		else if((c = dynamic_cast<Circle*>(shape)))
			*this = PolygonVect(*c);
		else throw bad_shape();

	}


	PolygonVect::PolygonVect(const Rectangle& rectangle)
	: Polygon(4)
	{
		point.reserve(getSize()); /* 4 points reserved in vector */
		area = rectangle.getArea();
		perim = rectangle.getPerim();

		const double x = rectangle.getX();
		const double y = rectangle.getY();

		// Drawing route: 
		/* (x,y) left-most corner-> go to right -> go down -> then go left */ 
		point.push_back(Polygon::Point2D(x,y));
		point.push_back(Polygon::Point2D(x+rectangle.getWidth(),y));
		point.push_back(Polygon::Point2D(x+rectangle.getWidth(),y+rectangle.getHeight()));
		point.push_back(Polygon::Point2D(x,y+rectangle.getHeight()));
	}

	PolygonVect::PolygonVect(const Circle& circle)
	: Polygon(100)
	  
	{
		point.reserve(getSize()); /* 100 equal interval reserved in vector for circle*/
		area = circle.getArea();
		perim = circle.getPerim();

		const double PI = 3.14159; //value of pi to determine circle's point.
		double x=0.0,y=0.0; // coord. 

		for(int i=0;i<getSize();++i)
		{

			x = circle.getX() + cos(2.0*i*PI/getSize())*circle.getRadius();
			y = circle.getY() + sin(2.0*i*PI/getSize())*circle.getRadius();
			point.push_back(Polygon::Point2D(x,y));
		}	

	}


	PolygonVect::PolygonVect(const Triangle& triangle)
	: Polygon(3)
	{
		point.reserve(getSize()); /* 3 points for 3 corners */
		area = triangle.getArea();
		perim = triangle.getPerim();

		const double x = triangle.getX();
		const double y = triangle.getY();

		//Drawing route:
		/* (x,y) top corner -> go to down and right -> go left */
		point.push_back(Polygon::Point2D(x,y));
		if(triangle.getRotate())
		{
			point.push_back(Polygon::Point2D(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*sqrt(3)/2.0)); 
			point.push_back(Polygon::Point2D(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*sqrt(3)/2.0));
		}
		else
		{
			point.push_back(Polygon::Point2D(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
								 y+triangle.getLength()*sqrt(3)/2.0)); 
			point.push_back(Polygon::Point2D(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y+triangle.getLength()*sqrt(3)/2.0));
		}
	}	




	PolygonVect::PolygonVect(): Polygon(0)
	{/* body left intentionally blank */}


	const Polygon::Point2D& PolygonVect::operator[](int idx)const throw(bad_index)
	{
		if(idx<0) throw bad_index();
		return point[idx];
	}

	Polygon::Point2D& PolygonVect::operator[](int idx) throw(bad_index)
	{
		if(idx<0) throw bad_index();
		return point[idx];
	}	


	std::ostream& PolygonVect::draw(std::ostream& outfile)
	{
		
		// default height and width, for printing singular PolygonVect. 
		
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

	
	void PolygonVect::setPoint(const Rectangle& rectangle)
	{

		*this = PolygonVect(rectangle); 
	}

	void PolygonVect::setPoint(const Circle& circle)
	{
		*this = PolygonVect(circle);
	}

	void PolygonVect::setPoint(const Triangle& triangle)
	{
		*this = PolygonVect(triangle);
	}

	PolygonVect& PolygonVect::operator++()
	{
		for(auto p : point)
			p.setPoint(p.getX()+1,p.getY()+1);

		return *this;
		
	}
	PolygonVect& PolygonVect::operator++(int ignore)
	{
		PolygonVect *poly_vect = new PolygonVect(*this);
		for(auto p : point)
			p.setPoint(p.getX()+1,p.getY()+1);

		return *poly_vect;

	} 
	PolygonVect& PolygonVect::PolygonVect::operator--()
	{
		for(auto p : point)
			p.setPoint(p.getX()-1,p.getY()-1);

		return *this;
	}
	PolygonVect& PolygonVect::operator--(int ignore)
	{
		PolygonVect *poly_vect = new PolygonVect(*this);
		for(auto p : point)
			p.setPoint(p.getX()-1,p.getY()-1);

		return *poly_vect;
	}

}

