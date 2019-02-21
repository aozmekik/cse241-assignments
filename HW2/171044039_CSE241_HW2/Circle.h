/* 
 * Circle.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#ifndef CIRCLE_H_
#define CIRCLE_H_


class Circle
{
public:
	Circle(double r=50.0, double _x=0.0, double _y=0.0);
	/* Pre-Condition:
	 * Default: r=50, center at (0,0)
	 * r(radius) must be positive number.
	 * Position is at center.
	 * Post-Condition:
	 * Initializes circle with safe parameters.
	 */
	double getRadius() const 		{return radius;}
	double getArea()const			{return radius*radius*3.14159; }
	bool getFill() const			{return fill;}
	double getX()const				{return x;}
	double getY()const				{return y;}
	void setRadius(double r)		{radius = r; testValidity();}
	void setPosition(double _x, double _y) {x=_x; y=_y;}
	void setFill(bool f)			{fill = f;}

	void draw(ofstream& outfile) const;

private:
	double radius;
	double x,y;
	bool fill; // true for fill inside the shape with color. 
	void testValidity();
};

#endif /* CIRCLE_H_ */ 
