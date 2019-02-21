/* 
 * Rectangle.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include <iostream>
#include <fstream>
using namespace std;

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

class Rectangle
{
public:
	Rectangle(double w=50.0,double h=50.0, double _x=0.0, double _y=0.0);
	/* Pre-Condition: 
	 * Default: width and height as  50.0 and position as (0,0).
	 * Default: Rotate flag set to false. 
	 * Default: Fill flag set to false.
	 * Position is the top left corner of rectangle.
	 * w and h values must be positive numbers. 
	 * Post-Condition:
	 * Initializes rectangle with safe parameters.
	 */  
	inline double getWidth()const		{return width;}
	inline double getHeight()const		{return height;}
	inline double getArea() const		{return width*height;}
	inline double getX()const			{return x;}
	inline double getY()const			{return y;}
	inline bool getRotate()const		{return rotate;}
	inline bool getFill() const			{return fill;}
	inline void setWidth(double w)		{width=w; testValidity();}
	inline void setHeight(double h)		{height=h; testValidity();}
	inline void setRotate(bool r)		{rotate=r;}
	inline void setFill(bool f)			{fill=f;}
	inline void setPosition(double _x, double _y) {x=_x; y=_y;}
	/* Getters and setters */

	void swapEdges();
	void draw(ofstream& outfile) const; 

private:
	double width,height;
	double x,y; // position
	bool rotate; // true for to rotate. (by 90 degress around position(x,y))
	bool fill; // true for fill inside the shape with color.
	void testValidity()const; 
};


#endif /* RECTANGLE_H_ */