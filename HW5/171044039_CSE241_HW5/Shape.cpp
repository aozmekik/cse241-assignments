/* 
 * Shape.cpp
 * 
 * Created on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */


#include "Shape.h"
#include <iostream>
#include <vector>
#include <algorithm> // sort() func.

namespace shape_ozmekik
{

	std::ostream& operator<<(std::ostream& outfile, Shape& shape)
	{
		return shape.draw(outfile);
	}

	void printAll(std::ostream& outfile, std::vector<Shape*>shape)
	{
		// one svg header for to gather shapes in one file.  
		outfile<<"<svg version=\"1.1\"" <<std::endl<< "baseProfile=\"full\"" <<std::endl
			<<"width=\""<<800<< "\" height=\""<<800<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<std::endl;


		for(auto s:shape)
		{
			// no other headers will be printed other than the first header. 
			s->setHeader(false);   
			s->draw(outfile);
		}

		outfile<<std::endl<<"</svg>";
	}

	/* provided the helper function for not to compare the number of 
	 * addresses, instead compare the objects pointed by addresses. */
	bool comparePtrToShapes(Shape *a, Shape *b) {return *a<*b;}

	void sortShapes(std::vector<Shape*> &shape)
	{
		std::sort(shape.begin(), shape.end(), comparePtrToShapes); 
	}


	Shape::Shape():area(0),perim(0), header(false)
	{/* intentionally left blank */}

	double Shape::getArea() const {return area;}
	double Shape::getPerim() const {return perim;}

	void Shape::setHeader(bool h){header = h;}
	bool Shape::getHeader()const{return header;}


	bool Shape::operator!=(Shape &other)const {return area!=other.getArea();}
	bool Shape::operator==(Shape &other)const {return area==other.getArea();}
	bool Shape::operator>=(Shape &other)const {return area>=other.getArea();}
	bool Shape::operator>(Shape &other)const  {return area>other.getArea();}
	bool Shape::operator<=(Shape &other)const {return area<=other.getArea();}
	bool Shape::operator<(Shape &other)const  {return area<other.getArea();}
	
}