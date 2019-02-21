/* Driver file.
 * 
 * Date: Nov 18, 2018
 * Author: Ahmed Semih Özmekik
 * No: 171044039
 */


#include "Polyline.h"
#include "Polygon.h"
#include "ComposedShape.h"
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using namespace shape_ozmekik; 

int main(int argc, char const *argv[])
{
	Rectangle rectangle[5];
	Circle circle[5];
	Triangle triangle[5];
	ComposedShape composed[5];
	Polygon polygon[5];
	Polyline polyline[5];
	/* Arrajs of objects of each class */ 


	std::vector<Polygon::Point2D> vectorPoint;
	/* Point2D vector for to test polygon */

	std::ofstream outfile;
	char file_name[] = "Composed00.svg"; // file to create



	rectangle[0].setWidth(600);
	rectangle[0].setHeight(500);
	rectangle[1].setWidth(456);
	rectangle[1].setHeight(745);
	rectangle[2].setWidth(50);
	rectangle[2].setHeight(100);
	rectangle[3].setWidth(200);
	rectangle[3].setHeight(800);
	rectangle[4].setWidth(934);
	rectangle[4].setHeight(823);


	circle[0].setRadius(450);
	circle[1].setRadius(560);
	circle[2].setRadius(34);
	circle[3].setRadius(78);
	circle[4].setRadius(213);

	triangle[0].setLength(623);
	triangle[1].setLength(132);
	triangle[2].setLength(71);
	triangle[3].setLength(32);
	triangle[4].setLength(345);

	triangle[0].setPosition(triangle[0].getLength()/2,0);
	circle[1].setPosition(circle[1].getRadius(),circle[1].getRadius());
	circle[0].setPosition(circle[0].getRadius(),circle[0].getRadius());

	composed[0].setMainShape(rectangle[0]);
	composed[0].setSmallShape(circle[2]);
	composed[0].setBoxWidth(rectangle[0].getWidth());
	composed[0].setBoxHeight(rectangle[0].getHeight());
	composed[1].setMainShape(triangle[0]);
	composed[1].setSmallShape(circle[2]);
	composed[1].setBoxWidth(triangle[0].getLength());
	composed[1].setBoxHeight(triangle[0].getLength());
	composed[2].setMainShape(circle[1]);
	composed[2].setSmallShape(triangle[3]);
	composed[2].setBoxWidth(circle[1].getRadius()*2);
	composed[2].setBoxHeight(circle[1].getRadius()*2);
	composed[3].setMainShape(triangle[0]);
	composed[3].setSmallShape(rectangle[2]);
	composed[3].setBoxWidth(triangle[0].getLength());
	composed[3].setBoxHeight(triangle[0].getLength());
	composed[4].setMainShape(rectangle[1]);
	composed[4].setSmallShape(rectangle[2]);
	composed[4].setBoxWidth(circle[1].getRadius()*2);
	composed[4].setBoxHeight(circle[1].getRadius()*2);

	polygon[0].setPoint(rectangle[0]);
	polygon[1].setPoint(triangle[3]);
	polygon[2].setPoint(circle[0]);
	polygon[3].setPoint(rectangle[2]);
	polygon[4].setPoint(triangle[2]);


	/* 5 objects of composed shape and polygon, testing... */
	ComposedShape c1(rectangle[4],triangle[3]);
	ComposedShape c2(circle[1],circle[2]);
	ComposedShape c3(circle[1],triangle[3]);
	ComposedShape c4(triangle[0],circle[2]);
	ComposedShape c5(triangle[0],rectangle[2]);
	c1.optimalFit();	

	/* points generating.. */
	vectorPoint.reserve(20);
	for(unsigned short i = 0;i<10;++i)
		vectorPoint.push_back(Polygon::Point2D(i*10,i*20));
	for(unsigned short i = 10;i<20;++i)
		vectorPoint.push_back(Polygon::Point2D(i*10,i*20));

	Polygon p1(rectangle[3]);
	p1.setHeader(true);
	triangle[2].setPosition(triangle[2].getLength(),triangle[2].getLength());
	Polygon p2(triangle[2]);
	Polygon p3(vectorPoint);
	Polygon p4(p2);
	Polygon p5 = p3 + vectorPoint[5];
	 // automatic type conversion, copy constructor, operator+ tested in one line.
	p4 = p1; 
	// assignment operator testing.


	polyline[0].setPoint(rectangle[2]);
	polyline[0].setHeader(true);
	polyline[1].setPoint(triangle[4]);
	polyline[2].setPoint(vectorPoint);
	polyline[3].setPoint(circle[2]);
	polyline[4] = polyline[0];

	cout<<endl<<"[DEBUG] Test is starting.."<<endl;


	if(polyline[4] == polyline[0])
		cout<<"[DEBUG] Polyline[4] Equals Polyline[0]"<<endl;
	if(polyline[4] != polyline[1])
		cout<<"[DEBUG] Polyline[4] Not Equals Polyline[0]"<<endl;
	if(p2 == p1)
		cout<<"[DEBUG] p1 equals p2 "<<endl;
	if(p2 != polygon[0])
		cout<<"[DEBUG] p2 not equal Polygon[0]"<<endl;


	cout<<"[DEBUG] Printing .svg code of polygon-> p2:"<<endl<<p2<<endl;
	cout<<"[DEBUG] Printing .svg code of polyline-> polyline[1]:"<<endl<<polyline[1]<<endl;
	cout<<"[DEBUG] 2th point of p2->[x]="<<p2[2].getX()<<" p2->[y]="<<p2[2].getY()<<endl; // rvalue

	p2[2].setPoint(5.0,6.0); // lvalue

	cout<<"[DEBUG] Changed 2th point of p2->[x]="<<p2[2].getX()<<" p2->[y]="<<p2[2].getY()<<endl;

	for(unsigned short i=0;i<5;++i)
	{
		composed[i].optimalFit();
		file_name[9]=i+48;
		outfile.open(file_name);
		outfile<<composed[i];
		outfile.close();
	}

	
	outfile.open("Polygon00.svg");
	outfile<<p1;
	outfile.close();
	outfile.open("Polyline00.svg");
	polyline[0][0].setPoint(200,200);
	outfile<<polyline[0];
	outfile.close();
	outfile.open(file_name);
	outfile<<c1;
	outfile.close();
	outfile.open("Polygon01.svg"); // drawed with vector. 
	p3.setHeader(true);
	outfile<<p3;
	outfile.close();


	cout<<"[DEBUG] Testing is done... "<<endl
	    <<"Check .svg files!"<<endl;
	
	return 0;
}