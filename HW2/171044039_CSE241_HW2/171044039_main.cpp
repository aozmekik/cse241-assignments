#include "ComposedShape.h"
#include <fstream>
#include <vector>

int main()
{
	vector<Rectangle> r;
	vector<Circle> c;
	vector<Triangle> t;
	char result[]="Output0.svg";
	ofstream outfile;

	vector<ComposedShape> my_shape;

	// Create objects.
	r.push_back(Rectangle(500,600));
	r.push_back(Rectangle(100,20));
	r.push_back(Rectangle());

	c.push_back(Circle(600));
	c.push_back(Circle(100,140,140));
	c.push_back(Circle(500));

	t.push_back(Triangle(800));
	t.push_back(Triangle(87,50,0));
	t.push_back(Triangle(50));

	// Testing functions of Objects

	c[0].setPosition(700,700);
	t[0].setPosition(400,0);
	r[2].setWidth(50);
	r[2].setHeight(33);
	c[2].setRadius(43);
	t[2].setLength(30); 

	// Create composed shape with combination of objects.
	my_shape.push_back(ComposedShape());
	my_shape.push_back(ComposedShape(r[0],c[1]));
	my_shape.push_back(ComposedShape(r[0],t[2]));
	my_shape.push_back(ComposedShape(c[0],r[1]));
	my_shape.push_back(ComposedShape(c[0],c[2]));
	my_shape.push_back(ComposedShape(c[0],t[2]));
	my_shape.push_back(ComposedShape(t[0],r[2]));
	my_shape.push_back(ComposedShape(t[0],c[2]));
	my_shape.push_back(ComposedShape(t[0],t[1]));

	// testing functions of ComposedShape class.
	my_shape[0].setMainShape(r[0]);
	my_shape[0].setSmallShape(r[2]);
	my_shape[0].setBoxWidth(r[0].getWidth()+200.0);
	my_shape[0].setBoxHeight(r[0].getHeight()+200.0); 
	r = my_shape[0].getVectorR();
	c = my_shape[1].getVectorC();
	t = my_shape[2].getVectorT();


	for(unsigned int i=0;i<9;i++)
	{
		result[6] = i+48; // output[i].svg, (output1.svg, output2.svg...)
		outfile.open(result);
		my_shape[i].optimalFit();
		my_shape[i].draw(outfile);
		cout<<"In "<<result<<":"<<endl
			<<"Total Fitted Shape: "<<my_shape[i].getTotalShape()<<endl
		    <<"Remainder Area: "<<my_shape[i].getRemainderArea()<<endl
			<<endl;
		outfile.close();
	}



	return 0;
}
