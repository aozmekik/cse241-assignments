/* 
 * Rectangle.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include <iostream>
#include <fstream>
using namespace std;

class Circle;
class Triangle;

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
	inline double getPerimeter() const {return 2.0*(width+height);}
	inline double getX()const			{return x;}
	inline double getY()const			{return y;}
	inline bool getRotate()const		{return rotate;}
	inline bool getFill() const			{return fill;}
	void setWidth(double w);
	void setHeight(double h);
	inline void setRotate(bool r)		{rotate=r;}
	inline void setFill(bool f)			{fill=f;}
	inline void setPosition(double _x, double _y) {x=_x; y=_y;}
	/* Getters and setters */
	inline void setHeader(bool h)		{header = h;}
	/* Pre-Condition:
	 * If you set header, then it initializes the svg file for one certain 
	 * shape and after that ends (</svg>) the svg file. Simply, if you set
	 * this flag, that means you can only take the output of that certain shape
	 * If you want to concetanate two or more shapes, use composed shapes class.
	 * Post-Condition:
	 * Sets the flags for initialize the svg and then close it.    
	 */ 

	void swapEdges();

	Rectangle operator++();
	Rectangle operator++(int); // Postfix version.
	Rectangle operator--();
	Rectangle operator--(int); // Postfix version.
	Rectangle operator+(double size)const;
	Rectangle operator-(double size)const;
	inline bool operator==(const Rectangle& other)const{return getArea()==other.getArea();}
	inline bool operator!=(const Rectangle& other)const{return getArea()!=other.getArea();} 

	friend ostream& operator<<(ostream&,const Rectangle&); 


	friend bool operator==(const Rectangle& r,const Triangle& t);
	friend bool operator!=(const Rectangle& r,const Triangle& t);
	friend bool operator>=(const Rectangle& r,const Triangle& t);
	friend bool operator<=(const Rectangle& r,const Triangle& t);
	friend bool operator>(const Rectangle& r,const Triangle& t);
	friend bool operator<(const Rectangle& r,const Triangle& t);
	friend bool operator==(const Rectangle& r,const Circle& c);
	friend bool operator!=(const Rectangle& r,const Circle& c);
	friend bool operator>=(const Rectangle& r,const Circle& c);
	friend bool operator<=(const Rectangle& r,const Circle& c);
	friend bool operator>(const Rectangle& r,const Circle& c);
	friend bool operator<(const Rectangle& r,const Circle& c);



	inline static double getTotalArea(){return total_area;} 
	inline static double getTotalPerimeter(){return total_perim;}

private:
	double width,height;
	double x,y; // position
	bool rotate; // true for to rotate. (by 90 degress around position(x,y))
	bool fill; // true for fill inside the shape with color.
	bool header; // svg header on or off
	static double total_area,total_perim;
	void testValidity()const; 
};


#endif /* RECTANGLE_H_ */