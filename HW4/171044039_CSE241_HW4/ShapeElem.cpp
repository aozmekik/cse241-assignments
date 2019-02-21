#include "ShapeElem.h"

ShapeElem::ShapeElem(const Rectangle& r): type(Shape::rect), object(new Rectangle(r))
{/* Body left intentionally blank */}
ShapeElem::ShapeElem(const Circle& c): type(Shape::cir), object(new Circle(c))
{/* Body left intentionally blank */}
ShapeElem::ShapeElem(const Triangle& t): type(Shape::tri), object(new Triangle(t))
{/* Body left intentionally blank */}
ShapeElem::ShapeElem(): type(Shape::rect), object(new Rectangle())
{/* Body left intentionally blank */}

ShapeElem::ShapeElem(const ShapeElem& other)
{
	type = other.type;
	switch(type)
	{
		case Shape::rect : object = new Rectangle(*(Rectangle*)other.object); break;
		case Shape::cir  : object = new Circle(*(Circle*)other.object); 	  break;
		case Shape::tri  : object = new Triangle(*(Triangle*)other.object);   break;
	}

}  

/* I know we did not cover destructor in lectures but TA said that if you overload one of the things 
 * in Big Three, you must implement the two others too. So I added this one for both: 
 * Having a leak in memory and not deallocating it made me feel uncomfortable.
 * And TA's suggestions was nice.
 */      
ShapeElem::~ShapeElem()
{	
	switch(type)
	{
		case Shape::rect : delete[] (Rectangle*)object;	 break;
		case Shape::cir  : delete[] (Circle*)object;  break;
		case Shape::tri  : delete[] (Triangle*)object;  break;
	}
}

ostream& operator<<(ostream& outfile, const ShapeElem& shape)
{
	switch(shape.type)
	{
		case Shape::rect : outfile<<*(Rectangle*)(shape.object); break;
		case Shape::cir  : outfile<<*(Circle*)(shape.object);    break;
		case Shape::tri  : outfile<<*(Triangle*)(shape.object);  break;
	}
	
	return outfile;
}


double ShapeElem::getArea()const
{
	double area=0.0;
	switch(type)
	{
		case Shape::rect : area = (*(Rectangle*)object).getArea(); break;
		case Shape::cir  : area = (*(Circle*)object).getArea();	   break;
		case Shape::tri  : area = (*(Triangle*)object).getArea();  break;
	}

	return area;
}
double ShapeElem::getPerimeter()const
{
	double perim=0.0;
	switch(type)
	{
		case Shape::rect : perim = (*(Rectangle*)object).getPerimeter(); break;
		case Shape::cir  : perim = (*(Circle*)object).getPerimeter();	 break;
		case Shape::tri  : perim = (*(Triangle*)object).getPerimeter();  break;
	}

	return perim;	
}

ShapeElem ShapeElem::operator=(const ShapeElem& other)
{
	type = other.type;
	switch(type)
	{
		case Shape::rect : object = new Rectangle(*(Rectangle*)other.object); break;
		case Shape::cir  : object = new Circle(*(Circle*)other.object); 	  break;
		case Shape::tri  : object = new Triangle(*(Triangle*)other.object);   break;
	}

	return *this;
}

void ShapeElem::setShape(const Rectangle& r)
{
	type = Shape::rect;
	object = new Rectangle(r);
}

void ShapeElem::setShape(const Circle& c)
{
	type = Shape::cir;
	object = new Circle(c);

}


void ShapeElem::setShape(const Triangle& t)
{
	type = Shape::tri;
	object = new Triangle(t);
}
			