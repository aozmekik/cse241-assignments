/* Driver file.
 * 
 * Date: Nov 18, 2018
 * Author: Ahmed Semih Özmekik
 * No: 171044039
 */

/* Global functions defined in seperated headers 
 * for to keep them in their context, as following:
 * Shape.h :
 * 				operator<<()
 *				printAll()
 *				sortShapes()
 * Polygon.h:
 *				printPoly()
 * PolygonVect:
 *				convertAll()
 *
*/

#include "ComposedShape.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"
#include "PolygonDyn.h"
#include "PolygonVect.h"
#include "Polygon.h"
#include <iostream>
#include <ostream>
#include <vector>

using std::cout;
using std::endl;
using namespace shape_ozmekik; 

int main(int argc, char const *argv[])
{
	try
	{

		Rectangle rectangle[5];
		Circle circle[5];
		Triangle triangle[5];
		ComposedShape composed[5];
		PolygonDyn polygonDyn[5];
		PolygonVect polygonVect[5];
		std::vector<Shape*> shape;
		/* Arrajs of objects of each class */ 

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
		circle[4].setPosition(circle[4].getRadius(),circle[4].getRadius());

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

		polygonDyn[0].setPoint(rectangle[2]);
		polygonDyn[1].setPoint(triangle[3]);
		polygonDyn[2].setPoint(circle[0]);
		polygonDyn[3].setPoint(rectangle[2]);
		polygonDyn[4].setPoint(circle[4]);

		polygonVect[0].setPoint(triangle[2]);
		polygonVect[1].setPoint(rectangle[2]);
		polygonVect[2].setPoint(circle[3]);
		polygonVect[3].setPoint(rectangle[0]);
		polygonVect[4].setPoint(triangle[0]);


		shape.reserve(3);


		rectangle[2].setPosition(100,200);
		rectangle[2].setFill(true);
		circle[2].setPosition(600,600);
		circle[2].setFill(true);
		triangle[2].setPosition(400,400);
		triangle[2].setFill(true);
		shape.push_back(&(rectangle[2]++));
		shape.push_back(&(++triangle[2]));
		shape.push_back(&(circle[2]++));
		//shape.push_back(&(polygonDyn[0]));

		cout<<endl<<"[DEBUG] Test is starting.."<<endl;




		outfile.open("PrintAll_Shapes.svg");
		printAll(outfile,shape);
		outfile.close();
		/* Same shapes, but converted to polygons */
		outfile.open("ConvertAll_ConvertedShapes.svg");
		shape = convertAll(shape);
		printPoly(outfile,shape);
		outfile.close();


		cout<<"[DEBUG] Not sorted shape vector:"<<std::endl;
		for(auto s:shape)
				std::cout<<s->getArea()<<std::endl;

		sortShapes(shape);
		cout<<"[DEBUG] Sorted shape vector:"<<std::endl;
		for(auto s:shape)
				std::cout<<s->getArea()<<std::endl;


		for(unsigned short i=0;i<5;++i)
		{
			composed[i].optimalFit();
			file_name[9]=i+48;
			outfile.open(file_name);
			outfile<<composed[i];
			outfile.close();
		}

		cout<<"[DEBUG] Testing of comparison operators: "<<endl<<endl;
		cout<<"[Circle[0]->Area:"<<circle[0].getArea()<<"<-->Rectangle[0]->Area:"<<rectangle[0].getArea()<<"]";
		cout<<endl<<"{---->Circle[0] ";
		if(circle[0]==rectangle[0]) 			cout<<"(==)";
		if(circle[0]!=rectangle[0]) 			cout<<"(!=)";
		if(circle[0]>=rectangle[0]) 			cout<<"(>=)";
		if(circle[0]<=rectangle[0]) 			cout<<"(<=)";
		if(circle[0]>rectangle[0]) 				cout<<"(>)";
		if(circle[0]<rectangle[0]) 				cout<<"(<)";
		cout<<"Rectangle[0]<----}"<<endl<<endl;	

		cout<<"[Circle[0]->Area:"<<circle[0].getArea()<<"<-->Triangle[0]->Area:"<<triangle[0].getArea()<<"]";
		cout<<endl<<"{---->Circle[0] ";
		if(circle[0]==triangle[0]) 				cout<<"(==)";
		if(circle[0]!=triangle[0]) 				cout<<"(!=)";
		if(circle[0]>=triangle[0]) 				cout<<"(>=)";
		if(circle[0]<=triangle[0]) 				cout<<"(<=)";
		if(circle[0]>triangle[0]) 				cout<<"(>)";
		if(circle[0]<triangle[0]) 				cout<<"(<)";
		cout<<" Triangle[0]<----}"<<endl<<endl;	

		cout<<"[Rectangle[0]->Area:"<<rectangle[0].getArea()<<"<-->Triangle[0]->Area:"<<triangle[0].getArea()<<"]";
		cout<<endl<<"{---->Rectangle[0] ";
		if(rectangle[0]==triangle[0]) 			cout<<"(==)";
		if(rectangle[0]!=triangle[0])			cout<<"(!=)";
		if(rectangle[0]>=triangle[0]) 			cout<<"(>=)";
		if(rectangle[0]<=triangle[0]) 			cout<<"(<=)";
		if(rectangle[0]>triangle[0]) 			cout<<"(>)";
		if(rectangle[0]<triangle[0]) 			cout<<"(<)";
		cout<<" Triangle[0]<----}"<<endl<<endl;


		outfile.open("PolygonDyn00.svg");
		polygonDyn[4].setHeader(true);
		outfile<<polygonDyn[4];
		outfile.close();
		outfile.open("PolygonVect00.svg");
		polygonVect[1].setHeader(true);
		outfile<<polygonVect[1];
		outfile.close();
		

		cout<<"[DEBUG] Testing is done... "<<endl
		    << "[DEBUG] Check .svg files!"<<endl;

		// Uncomment this section to catch bad_size err.
		//Rectangle err_rect(-50); 

		//Uncomment this section to catch bad_index err.
		/*
		PolygonDyn p = polygonDyn[4];
		p[-5].setPoint(1,2);
		*/

	
	}

	catch(bad_size &e)
	{
		cout<<e.what();
	}

	catch(bad_index &e)
	{
		cout<<e.what();
	}

	
	return 0;
}
