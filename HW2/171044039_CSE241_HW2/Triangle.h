/* 
 * Triangle.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

class Triangle
{
public:
	Triangle(double len=50.0, double _x=0.0, double _y=0.0);
	/* Pre-Condition:
	 * Default: a length of a equilateral triangle must be positive number.
	 * Position is the top corner of triangle. Other two corners of the 
	 * triangle is either in below or above, depending on the rotate flag. 
	 * Post-Condition:
	 * Initializes the triangle with safe params. 
	 */
	inline double getLength() const 	{return length;}
	double getArea() const				{return length*length*sqrt(3)/4.0;}
	double getX()const					{return x;}
	double getY()const					{return y;}
	bool getRotate()const				{return rotate;}
	bool getFill() const				{return fill;}
	void setLength(double len)			{length = len; testValidity();}
	void setPosition(double _x, double _y)	{x=_x; y=_y;}
	void setRotate(bool r)				{rotate = r;}
	void setFill(bool f)				{fill = f;}
	void draw(ofstream& outfile) const;

private:
	double length;
	double x,y;
	bool rotate; // true for rotate around top corner of itself by 180 degrees	
	bool fill; // true for fill inside the shape with color.
	void testValidity();
};

#endif // TRIANGLE_H_