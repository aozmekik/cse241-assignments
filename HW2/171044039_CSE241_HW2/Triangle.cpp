/* 
 * Triangle.cpp
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Triangle.h"
#include <cstdlib> // for exit(1) func.

Triangle::Triangle(double len, double _x, double _y)
	: length(len)
	, x(_x)
	, y(_y)
	, rotate(false)
	, fill(false)
{
	testValidity(); // terminates if the input is invalid.
}
void Triangle::draw(ofstream& outfile) const
{
	// as said, other two points are taken in below and if rotate is true:
	// they will be in above.
	outfile << "<polygon points=\""<< x << "," << y
							<< " " << x-length/2.0 << "," << y+(length/2.0)*sqrt(3.0)
							<< " " << x+length/2.0 << "," << y+(length/2.0)*sqrt(3.0)
							<< "\" fill=";

	if(getFill()) outfile<<"\"cornflowerblue\" ";
	else 	 	  outfile<<"\"white\" ";

	outfile<< " stroke=\"black\" stroke-width=\"1.6\" "<<endl;

	if(getRotate()) outfile << " transform = \" rotate(180," << x << "," << y <<")\"";

	outfile << "/>" << endl;
}

void Triangle::testValidity()
{
	if(length<=0)
	{
		cout<<length;
		cout<<"Unvalid length value!";
		exit(1);
	}
}