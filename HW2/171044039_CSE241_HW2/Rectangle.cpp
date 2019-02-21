/*
 * Rectangle.cpp 
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Rectangle.h"
#include <cstdlib> // for exit(1) func.

Rectangle::Rectangle(double w, double h, double _x, double _y)
	: width(w)
	, height(h)
	, x(_x)
	, y(_y)
	, rotate(false)
	, fill(false)
{	
	testValidity(); // terminates if the input is not valid.    	
}

void Rectangle::draw(ofstream& outfile) const
{
	outfile<< "<rect width=\"" << getWidth() 
	       <<   "\" height=\"" << getHeight() 
	       <<    "\" y=\"" << getY() 
	       <<	 "\" x=\"" << getX() 
	       <<    "\" stroke=\"black\" stroke-width=\"1.6\""
	       << " fill="; 

	if(getFill())outfile<< "\"cornflowerblue\""; // colorize inside the shape  
	else 	outfile<< "\"white\""; 

	if(getRotate()) 
	{
			outfile << " transform = \" rotate(90," 
					   << getX() << "," 
					   << getY() <<")\"";
	}

	outfile << "/>" << endl;
}

void Rectangle::testValidity() const
{
	if(width<=0 || height<=0)
	{
		cout<<"Unvalid length value!";
		exit(1);
	}
}


void Rectangle::swapEdges()
{
	// basic swaping operation
	double temp;
	temp = getWidth();
	setWidth(getHeight());
	setHeight(temp);
}