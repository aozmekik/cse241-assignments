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

class Rectangle; // forward declaration for friend functions
class Triangle;

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
	inline double getRadius() const 		{return radius;}
	inline double getArea()const			{return radius*radius*3.14159; }
	inline double getPerimeter()const      {return radius*2.0*3.14159;}
	inline bool getFill() const			{return fill;}
	inline double getX()const				{return x;}
	inline double getY()const				{return y;}
	void setRadius(double r);
	inline void setPosition(double _x, double _y) {x=_x; y=_y;}
	inline void setFill(bool f)			{fill = f;}

	inline void setHeader(bool h)		{header = h;}
	/* Pre-Condition:
	 * If you set header, then it initializes the svg file for one certain 
	 * shape and after that ends (</svg>) the svg file. Simply, if you set
	 * this flag, that means you can only take the output of that certain shape
	 * If you want to concetanate two or more shapes, use composed shapes class.
	 * Post-Condition:
	 * Sets the flags for initialize the svg and then close it.    
	 */ 

	/* Operator overloadings. */

	Circle operator++(); 
	Circle operator++(int); // Postfix version. 
	Circle operator--(); 
	Circle operator--(int); // Postfix version.
	Circle operator+(double size)const;
	Circle operator-(double size)const;
	inline bool operator==(const Circle& other)const{return getArea()==other.getArea();}
	inline bool operator!=(const Circle& other)const{return getArea()!=other.getArea();}

	friend bool operator==(const Circle& c,const Rectangle& r);
	friend bool operator!=(const Circle& c,const Rectangle& r);
	friend bool operator>=(const Circle& c,const Rectangle& r);
	friend bool operator>(const Circle& c,const Rectangle& r);
	friend bool operator<=(const Circle& c,const Rectangle& r);
	friend bool operator<(const Circle& c,const Rectangle& r);
	friend bool operator==(const Circle& c,const Triangle& t);
	friend bool operator!=(const Circle& c,const Triangle& t);
	friend bool operator>=(const Circle& c,const Triangle& t);
	friend bool operator<=(const Circle& c,const Triangle& t);
	friend bool operator>(const Circle& c,const Triangle& t);
	friend bool operator<(const Circle& c,const Triangle& t);



	// operator << overloading for output to ofstream
	friend ostream& operator<<(ostream& outfile, const Circle& c);

	inline static double getTotalArea(){return total_area;} 
	inline static double getTotalPerimeter(){return total_perim;}


private:
	double radius;
	double x,y;
	bool fill; // true for fill inside the shape with color. 
	bool header; // svg header on or off
	static double total_area,total_perim; // total created object
	void testValidity();
};



#endif /* CIRCLE_H_ */ 
