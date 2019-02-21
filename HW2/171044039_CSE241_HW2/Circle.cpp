/* 
 * Circle.cpp
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Circle.h"
#include <cstdlib> // for exit(1) func.

Circle::Circle(double r,double _x, double _y)
	: radius(r)
	, x(_x)
	, y(_y)
	, fill(false)
{
	testValidity(); // terminates if the input is invalid.
}
void Circle::draw(ofstream& outfile) const
{
	outfile <<   "<circle cx=\"" << x <<
					  "\" cy=\"" << y <<
				      "\" r=\""  << radius << "\" stroke=\"black\" stroke-width=\"1.6\"";

	if(getFill()) outfile << " fill=\"cornflowerblue\"/>"<<endl;
	else	 	  outfile << " fill=\"white\"/>"<<endl; 

}

void Circle::testValidity()
{
	if(radius<0)
	{
		cout<<"Unvalid length value!";
		exit(1);
	}
}
