/* 
 * Polygon.cpp
 * 
 * Created on: Dec 18, 2018
 * Author: Ahmed Semih Özmekik
 */



#include "Polygon.h" 

namespace shape_ozmekik
{
 
	using std::endl;

	void printPoly(std::ostream& outfile, std::vector<Shape*>shape)
	{
		// since they are doing the same thing. printPoly was not
		// needed for this design.
		printAll(outfile,shape); 
	}


	Polygon::Point2D::Point2D(double px, double py): x(px), y(py)
	{/* intentionally left blank */}


	void Polygon::Point2D::setPoint(double px, double py)
	{
		x = px;
		y = py;
	}

	double Polygon::Point2D::getX()const{return x;};
	double Polygon::Point2D::getY()const{return y;};

	bool Polygon::Point2D::operator==(Point2D other)const
	{	return ((x==other.getX())?y==other.getY():false);	}

	bool Polygon::Point2D::operator!=(Point2D other)const
	{   return !(*this==other);}

	Polygon::Polygon(int _size) throw(bad_size)
	: Shape(), 
	  size(_size) 
	{
		if(_size<0) throw bad_size();
	}


	int Polygon::getSize()const{return size;}

	void Polygon::setSize(int _size){size = _size;}

}

