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

class Rectangle;
class Circle;

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
	inline double getLength() const 		{return length;}
	inline double getArea() const				{return length*length*sqrt(3)/4.0;}
	inline double getPerimeter()const 			{return 3.0*length;}
	inline double getX()const					{return x;}
	inline double getY()const					{return y;}
	inline bool getRotate()const				{return rotate;}
	inline bool getFill() const					{return fill;}
	inline void setPosition(double _x, double _y){x=_x; y=_y;}
	inline void setRotate(bool r)				{rotate = r;}
	inline void setFill(bool f)					{fill = f;}
	void setLength(double len);
	inline void setHeader(bool h)		{header = h;}
	/* Pre-Condition:
	 * If you set header, then it initializes the svg file for one certain 
	 * shape and after that ends (</svg>) the svg file. Simply, if you set
	 * this flag, that means you can only take the output of that certain shape
	 * If you want to concetanate two or more shapes, use composed shapes class.
	 * Post-Condition:
	 * Sets the flags for initialize the svg and then close it.    
	 */ 

	Triangle operator++();
	Triangle operator++(int); // Postfix.
	Triangle operator--();
	Triangle operator--(int);
	Triangle operator+(double size)const;
	Triangle operator-(double size)const;
	inline bool operator==(Triangle& other){return getArea()==other.getArea();}
	inline bool operator!=(Triangle& other){return getArea()!=other.getArea();} 

	friend ostream& operator<<(ostream&,const Triangle&); 

	friend bool operator==(const Triangle& t,const Rectangle& r);
	friend bool operator!=(const Triangle& t,const Rectangle& r);
	friend bool operator>=(const Triangle& t,const Rectangle& r);
	friend bool operator<=(const Triangle& t,const Rectangle& r);
	friend bool operator>(const Triangle& t,const Rectangle& r);
	friend bool operator<(const Triangle& t,const Rectangle& r);
	friend bool operator==(const Triangle& t,const Circle& c);
	friend bool operator!=(const Triangle& t,const Circle& c);
	friend bool operator>=(const Triangle& t,const Circle& c);
	friend bool operator<=(const Triangle& t,const Circle& c);
	friend bool operator>(const Triangle& t,const Circle& c);
	friend bool operator<(const Triangle& t,const Circle& c);

	inline static double getTotalArea(){return total_area;} 
	inline static double getTotalPerimeter(){return total_perim;}

private:
	double length;
	double x,y;
	bool rotate; // true for rotate around top corner of itself by 180 degrees	
	bool fill; // true for fill inside the shape with color.
	bool header; // svg header on or off
	static double total_area,total_perim;
	void testValidity();
};

#endif // TRIANGLE_H_