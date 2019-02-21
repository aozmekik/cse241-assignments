#include "ComposedShape.h"
#include <iostream>
#include <ostream>



int main(int argc, char const *argv[])
{
	Circle circle[3];
	Triangle triangle[3];
	Rectangle rectangle[3];
	ComposedShape::ShapeElem shape[2];
	ComposedShape composed[9];
	ofstream outfile;
	char str_result[]="ComposedShape00.svg";

	circle[0].setRadius(500);
	circle[0].setPosition(500,500);
	circle[1].setRadius(100);
	circle[1].setPosition(100,100);
	circle[2].setRadius(50);
	circle[2].setPosition(50,50);

	cout<<"Testing each member function for Circle Class:"<<endl
	    <<"Radius: "<<circle[0].getRadius()<<endl
		<<"Addition:(+50) "<<(circle[0]+50.0).getRadius()<<endl
		<<"Substraction:(-50) "<<(circle[0]-50.0).getRadius()<<endl
	    <<"Position-> X: "<<circle[0].getX()<<endl
	    <<"Position-> Y: "<<circle[0].getY()<<endl
		<<"Pre-Increment-> X:"<<(++circle[0]).getX()<<endl
		<<"Post-Increment-> X: "<<(circle[0]++).getX()<<endl
		<<"Position-> X: "<<circle[0].getX()<<endl
		<<"Position-> Y: "<<circle[0].getY()<<endl
		<<"Pre-Decrement-> X:"<<(--circle[0]).getX()<<endl
		<<"Post-Decrement-> x: "<<(circle[0]--).getX()<<endl
		<<"Position-> X: "<<circle[0].getX()<<endl
		<<"Position-> Y: "<<circle[0].getY()<<endl
		<<"Comparing(==): ";circle[0]==circle[1]?cout<<"True!"<<endl:cout<<"False!"<<endl
		<<"Comparing(!=): ";circle[0]!=circle[1]?cout<<"True!"<<endl:cout<<"False!"<<endl;
	cout<<"Area: "  <<circle[0].getArea()<<endl
	    <<"Perimeter: "<<circle[0].getPerimeter()<<endl
	    <<"(Static)Total Area: "<<Circle::getTotalArea()<<endl
	    <<"(Static)Total Perimeter "<<Circle::getTotalPerimeter()<<endl;



	rectangle[0].setWidth(800);
	rectangle[0].setHeight(600);
	rectangle[1].setWidth(80);
	rectangle[1].setHeight(20);
	rectangle[2].setWidth(47);
	rectangle[2].setHeight(38);

	cout<<endl<<"Testing each member function for Rectangle Class:"<<endl
	    <<"Width: "<<rectangle[0].getWidth()<<endl
		<<"Addition:(+50) "<<(rectangle[0]+50.0).getWidth()<<endl
		<<"Substraction:(-50) "<<(rectangle[0]-50.0).getWidth()<<endl
		<<"Position-> X: "<<rectangle[0].getX()<<endl
		<<"Position-> Y: "<<rectangle[0].getY()<<endl
		<<"Pre-Increment-> X:"<<(++rectangle[0]).getX()<<endl
		<<"Post-Increment-> X: "<<(rectangle[0]++).getX()<<endl
		<<"Position-> X: "<<rectangle[0].getX()<<endl
		<<"Position-> Y: "<<rectangle[0].getY()<<endl
		<<"Pre-Decrement-> X:"<<(--rectangle[0]).getX()<<endl
		<<"Post-Decrement-> X: "<<(rectangle[0]--).getX()<<endl
		<<"Position-> X: "<<rectangle[0].getX()<<endl
		<<"Position-> Y: "<<rectangle[0].getY()<<endl
		<<"Comparing(==): ";rectangle[0]==rectangle[1]?cout<<"True!"<<endl:cout<<"False!"<<endl
		<<"Comparing(!=): ";rectangle[0]!=rectangle[1]?cout<<"True!"<<endl:cout<<"False!"<<endl;
	cout<<"Area: "  <<rectangle[0].getArea()<<endl
	    <<"Perimeter: "<<rectangle[0].getPerimeter()<<endl
	    <<"(Static)Total Area: "<<Rectangle::getTotalArea()<<endl
	    <<"(Static)Total Perimeter "<<Rectangle::getTotalPerimeter()<<endl;


	triangle[0].setLength(600);
	triangle[0].setPosition(300,0);
	triangle[1].setLength(100);
	triangle[1].setPosition(50,0);
	triangle[2].setLength(37);
	triangle[2].setPosition(20,0);

	cout<<endl<<"Testing each member function for Triangle Class:"<<endl
	    <<"Length: "<<triangle[0].getLength()<<endl
		<<"Addition:(+50) "<<(triangle[0]+50.0).getLength()<<endl
		<<"Substraction:(-50) "<<(triangle[0]-50.0).getLength()<<endl
		<<"Position-> X: "<<triangle[0].getX()<<endl
		<<"Position-> Y: "<<triangle[0].getY()<<endl
		<<"Pre-Increment-> X:"<<(++triangle[0]).getX()<<endl
		<<"Post-Increment-> X: "<<(triangle[0]++).getX()<<endl
		<<"Position-> X: "<<triangle[0].getX()<<endl
		<<"Position-> Y: "<<triangle[0].getY()<<endl
		<<"Pre-Decrement-> X:"<<(--triangle[0]).getX()<<endl
		<<"Post-Decrement-> X: "<<(triangle[0]--).getX()<<endl
		<<"Position-> X: "<<triangle[0].getX()<<endl
		<<"Position-> Y: "<<triangle[0].getY()<<endl
		<<"Comparing(==): ";triangle[0]==triangle[1]?cout<<"True!"<<endl:cout<<"False!"<<endl
		<<"Comparing(!=): ";triangle[0]!=triangle[1]?cout<<"True!"<<endl:cout<<"False!"<<endl;
	cout<<"Area: "  <<triangle[0].getArea()<<endl
	    <<"Perimeter: "<<triangle[0].getPerimeter()<<endl
	    <<"(Static)Total Area: "<<Triangle::getTotalArea()<<endl
	    <<"(Static)Total Perimeter "<<Triangle::getTotalPerimeter()<<endl;


	shape[0].setShape(rectangle[0]);
	shape[1].setShape(triangle[1]);

	cout<<endl<<"Testing each member function for ShapeElem Class:"<<endl
	    <<"Area: "<<shape[0].getArea()<<endl
	    <<"Perimeter: "<<shape[0].getPerimeter()<<endl;
	shape[0]=shape[1];
	cout<<"Area: "<<shape[0].getArea()<<endl
	    <<"Perimeter: "<<shape[0].getPerimeter();


	composed[0].setMainShape(circle[0]);
	composed[0].setSmallShape(circle[2]);
	composed[0].setBoxWidth(circle[0].getRadius()*2+100);
	composed[0].setBoxHeight(circle[0].getRadius()*2+100);
	composed[1].setMainShape(rectangle[0]);
	composed[1].setSmallShape(circle[2]);
	composed[1].setBoxWidth(rectangle[0].getWidth()+100);
	composed[1].setBoxHeight(rectangle[0].getHeight()+100);
	composed[2].setMainShape(rectangle[0]);
	composed[2].setSmallShape(triangle[2]);
	composed[2].setBoxWidth(rectangle[0].getWidth()+100);
	composed[2].setBoxHeight(rectangle[0].getHeight()+100);
	composed[3].setMainShape(circle[0]);
	composed[3].setSmallShape(rectangle[2]);
	composed[3].setBoxWidth(circle[0].getRadius()*2+100);
	composed[3].setBoxHeight(circle[0].getRadius()*2+100);
	composed[4].setMainShape(circle[0]);
	composed[4].setSmallShape(triangle[2]);
	composed[4].setBoxWidth(circle[0].getRadius()*2+100);
	composed[4].setBoxHeight(circle[0].getRadius()*2+100);
	composed[5].setMainShape(rectangle[0]);
	composed[5].setSmallShape(rectangle[2]);
	composed[5].setBoxWidth(rectangle[0].getWidth()+100);
	composed[5].setBoxHeight(rectangle[0].getHeight()+100);
	composed[6].setMainShape(triangle[0]);
	composed[6].setSmallShape(triangle[2]);
	composed[6].setBoxWidth(triangle[0].getLength()+100);
	composed[6].setBoxHeight(triangle[0].getLength()+100);
	composed[7].setMainShape(triangle[0]);
	composed[7].setSmallShape(rectangle[2]);
	composed[7].setBoxWidth(triangle[0].getLength()+100);
	composed[7].setBoxHeight(triangle[0].getLength()+100);
	composed[8].setMainShape(triangle[0]);
	composed[8].setSmallShape(circle[2]);
	composed[8].setBoxWidth(triangle[0].getLength()+100);
	composed[8].setBoxHeight(triangle[0].getLength()+100);

	
	for(int i=0;i<9;i++)
	{
		str_result[14]=i+48; // 48 for to integer to char
		outfile.open(str_result);
		composed[i].optimalFit();
		outfile<<composed[i];
		outfile.close();
	}
	

	circle[2].setFill(true);
	composed[8]+=circle[2]; // += usage adds shape to vector 
	outfile.open("ComposedShape+=10.svg");
	outfile<<composed[8];
	// [] usage returns corresponding vector ShapElem object
	// =  usage ShapeElem object. 
	shape[0]=composed[8][1]; 


	// Shape draw tests.
	outfile.open("Circle.svg");
	circle[0].setHeader(true);
	circle[0].setFill(true);
	outfile<<circle[0];
	outfile.close();
	outfile.open("Rectangle.svg");
	rectangle[0].setHeader(true);
	rectangle[0].setFill(true);
	outfile<<rectangle[0];
	outfile.close();
	outfile.open("Triangle.svg");
	triangle[0].setHeader(true);
	triangle[0].setFill(true);
	outfile<<triangle[0];
	outfile.close();

	
	cout<<endl<<endl<<"Comparing two shapes test section:"<<endl;

	cout<<"Circle's Area:"<<circle[0].getArea()<<"   Rectangle's area:"<<rectangle[0].getArea();
	cout<<endl<<"Circle's Area is "<<endl;
	if(circle[0]==rectangle[0]) 			cout<<"EQUAL TO"<<endl;
	if(circle[0]!=rectangle[0]) 			cout<<"NOT EQUAL TO"<<endl;
	if(circle[0]>=rectangle[0]) 			cout<<"BIGGER THAN OR EQUAL TO"<<endl;
	if(circle[0]<=rectangle[0]) 			cout<<"SMALLER THAN OR EQUAL TO"<<endl;
	if(circle[0]>rectangle[0]) 				cout<<"BIGGER THAN"<<endl;
	if(circle[0]<rectangle[0]) 				cout<<"SMALLER THAN"<<endl;
	cout<<" Rectangle's Area."<<endl;	

	cout<<"Circle's Area:"<<circle[0].getArea()<<"   Triangle's area:"<<triangle[0].getArea();
	cout<<endl<<"Circle's Area is "<<endl;
	if(circle[0]==triangle[0]) 				cout<<"EQUAL TO"<<endl;
	if(circle[0]!=triangle[0]) 				cout<<"NOT EQUAL TO"<<endl;
	if(circle[0]>=triangle[0]) 				cout<<"BIGGER THAN OR EQUAL TO"<<endl;
	if(circle[0]<=triangle[0]) 				cout<<"SMALLER THAN OR EQUAL TO"<<endl;
	if(circle[0]>triangle[0]) 				cout<<"BIGGER THAN"<<endl;
	if(circle[0]<triangle[0]) 				cout<<"SMALLER THAN"<<endl;
	cout<<" Triangle's Area."<<endl;	

	cout<<"Rectangle's Area:"<<rectangle[0].getArea()<<"   Triangle's area:"<<triangle[0].getArea();
	cout<<endl<<"Rectangle's Area is "<<endl;
	if(rectangle[0]==triangle[0]) 					cout<<"EQUAL TO"<<endl;
	if(rectangle[0]!=triangle[0]) 				cout<<"NOT EQUAL TO"<<endl;
	if(rectangle[0]>=triangle[0]) 				cout<<"BIGGER THAN OR EQUAL TO"<<endl;
	if(rectangle[0]<=triangle[0]) 				cout<<"SMALLER THAN OR EQUAL TO"<<endl;
	if(rectangle[0]>triangle[0]) 				cout<<"BIGGER THAN"<<endl;
	if(rectangle[0]<triangle[0]) 				cout<<"SMALLER THAN"<<endl;
	cout<<" Triangle's Area."<<endl;


	cout<<"Rectangle's Area:"<<rectangle[0].getArea()<<"   Triangle's area:"<<circle[2].getArea();
	cout<<"Rectangle's Area is "<<endl;
	if(rectangle[0]==circle[2]) 					cout<<"EQUAL TO"<<endl;
	if(rectangle[0]!=circle[2]) 				cout<<"NOT EQUAL TO"<<endl;
	if(rectangle[0]>=circle[2]) 				cout<<"BIGGER THAN OR EQUAL TO"<<endl;
	if(rectangle[0]<=circle[2]) 				cout<<"SMALLER THAN OR EQUAL TO"<<endl;
	if(rectangle[0]>circle[2]) 				cout<<"BIGGER THAN"<<endl;
	if(rectangle[0]<circle[2]) 				cout<<"SMALLER THAN"<<endl;
	cout<<" Circle's Area."<<endl;

	cout<<"Rectangle's Area:"<<rectangle[0].getArea()<<"   Triangle's area:"<<circle[2].getArea();
	cout<<endl<<"Rectangle's Area is "<<endl;
	if(rectangle[0]==circle[2]) 					cout<<"EQUAL TO"<<endl;
	if(rectangle[0]!=circle[2]) 				cout<<"NOT EQUAL TO"<<endl;
	if(rectangle[0]>=circle[2]) 				cout<<"BIGGER THAN OR EQUAL TO"<<endl;
	if(rectangle[0]<=circle[2]) 				cout<<"SMALLER THAN OR EQUAL TO"<<endl;
	if(rectangle[0]>circle[2]) 				cout<<"BIGGER THAN"<<endl;
	if(rectangle[0]>circle[2]) 				cout<<"SMALLER THAN"<<endl;
	cout<<" Circle's Area."<<endl;

	cout<<"Triangle's Area:"<<triangle[1].getArea()<<"   Rectangle's area:"<<rectangle[2].getArea();
	cout<<endl<<"Triangle's Area is "<<endl;
	if(triangle[1]==rectangle[2]) 				cout<<"EQUAL TO"<<endl;
	if(triangle[1]!=rectangle[2]) 			cout<<"NOT EQUAL TO"<<endl;
	if(triangle[1]>=rectangle[2]) 			cout<<"BIGGER THAN OR EQUAL TO"<<endl;
	if(triangle[1]<=rectangle[2]) 			cout<<"SMALLER THAN OR EQUAL TO"<<endl;
	if(triangle[1]>rectangle[2]) 			cout<<"BIGGER THAN"<<endl;
	if(triangle[1]<rectangle[2]) 			cout<<"SMALLER THAN"<<endl;
	cout<<" Rectangle's Area."<<endl;

	cout<<"Triangle's Area:"<<triangle[1].getArea()<<"   Circle's area:"<<circle[2].getArea();
	cout<<endl<<"Triangle's Area is "<<endl;
	if(triangle[1]==circle[2]) 					cout<<"EQUAL TO"<<endl;
	if(triangle[1]!=circle[2]) 			cout<<"NOT EQUAL TO"<<endl;
	if(triangle[1]>=circle[2]) 			cout<<"BIGGER THAN OR EQUAL TO"<<endl;
	if(triangle[1]<=circle[2]) 			cout<<"SMALLER THAN OR EQUAL TO"<<endl;
	if(triangle[1]>circle[2]) 				cout<<"BIGGER THAN"<<endl;
	if(triangle[1]<circle[2]) 				cout<<"SMALLER THAN"<<endl;
	cout<<" Circle's Area."<<endl;




	cout<<endl<<"Test is done!!..."<<endl;
	cout<<"You can check .svg files in the working directory!..."<<endl;

	return 0;
}




