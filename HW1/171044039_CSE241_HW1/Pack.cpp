#include <iostream>
#include <fstream>
#include <cmath>
#include "Pack.h"

bool isValid(char chosen_shape)
{	
	const char R = 'R', C = 'C', T = 'T';
	bool valid = false;

	if(chosen_shape == R || chosen_shape == C || chosen_shape == T)
		valid = true;
	return(valid);
}

char inputShape(bool is_main)
{
	char chosen_shape;
	string name_shape;

	if(is_main) name_shape = "main";
	else		name_shape = "small";

	cout<<"Please enter the " + name_shape + " container shape(R, C, T)"<<endl;

	while(!(cin>>chosen_shape )|| !isValid(chosen_shape)){
		cout<<"Invalid input, Try Again: ";
		cin.clear();
		cin.ignore(256,'\n'); // 256 byte ignored for to prevent infinite loop
	}

	
	

	return chosen_shape;
}

void setMainShape(Container& c, char chosen_shape)
{
	const char R = 'R', C = 'C', T = 'T';
	switch(chosen_shape)
	{
		case R: c.main_shape = Shape::rect;		break;
		case C: c.main_shape = Shape::cir;		break;
		case T: c.main_shape = Shape::tri;		break;
		default: cout << "Err!!"; 
	}

	switch(c.main_shape)
	{
		case Shape::rect: setRectangle(c.rect1);   break;
		case Shape::cir:  setCircle(c.cir1); 		break;
		case Shape::tri:  setTriangle(c.tri1); 	break;
	}

}
void setSmallShape(Container &c, char chosen_shape)
{
	const char R = 'R', C = 'C', T = 'T';

	switch(chosen_shape)
	{
		case R: c.small_shape = Shape::rect;	break;
		case C: c.small_shape = Shape::cir;		break;
		case T: c.small_shape = Shape::tri;		break;
		default: cout << "Err!!"; 
	}

	switch(c.small_shape)
	{
		case Shape::rect: setRectangle(c.rect2);    break;
		case Shape::cir:  setCircle(c.cir2); 		break;
		case Shape::tri:  setTriangle(c.tri2); 		break;
	}

	

}

void initContainer(Container& c)
{
	Shape shape_default = Shape::rect; // set rectangle as default 
	double len_default = 0.0; // set zero as default length  

	c.main_shape = shape_default;
	c.small_shape = shape_default;

	// default init
	c.tri1.len = len_default;
	c.rect1.len1= len_default; c.rect1.len2= len_default;
	c.cir1.rad = len_default; 

	c.tri2.len = len_default;
	c.rect2.len1= len_default; c.rect2.len2= len_default;
	c.cir2.rad = len_default; 

}

void printInvalid()
{
	// Info and functions for to prevent infinite loop while checking the validity
	cout << "Invalid input - try again: ";
	cin.clear();
	cin.ignore(256, '\n');
}

void setTriangle(Triangle& t)
{
	double len=0;
	cout<<"Please enter the length:"<<endl;
	while (!(cin >> len) || len < 0) 
		printInvalid();
	
	t.len = len;
}
void setRectangle(Rectangle& r)
{
	double len1=0, len2=0;
	cout<<"Please enter the width:"<<endl;
	while (!(cin >> len1) || len1 < 0) 
		printInvalid();
	cout<<"Please enter the height:"<<endl;
	while (!(cin >> len2) || len2 < 0) 
		printInvalid();

	r.len1 = len1; 
	r.len2=len2;

}
void setCircle(Circle& c)
{
	double rad=0;

	cout<<"Please enter the radius:"<<endl;
	while (!(cin >> rad) || rad < 0) 
		printInvalid();

	c.rad = rad;
}

void setContainer(Container& c)
{
	char chosen_shape;

	// main_shape
	chosen_shape = inputShape(true); 
	setMainShape(c,chosen_shape);

	// small_shape
	chosen_shape = inputShape(false); 
	setSmallShape(c,chosen_shape);


}

void findBoundingBox(const Container& c, double& box_w, double& box_h)
{	
	// doubled the box to prevent the worst case for triangle and circle
	switch(c.main_shape)
	{
		case Shape::rect:  box_w = c.rect1.len1; box_h = c.rect1.len2;   break;
		case Shape::cir:   box_w = c.cir1.rad*2; box_h = c.cir1.rad*2; 	 break; 
		case Shape::tri:   box_w = c.tri1.len; box_h = c.tri1.len; 		 break;
	}
}

void fitContainer(const Container& c)
{
	ofstream outfile;
	double box_w = 0, box_h = 0;

	findBoundingBox(c,box_w,box_h);

	outfile.open(FILE_NAME, ios::out);

	outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
	<<"width=\""<<box_w+100<< "\" height=\""<<box_h+100<<"\""<<endl;

	// expanding our view to out of boundaries for the see center well 
	if(c.main_shape == Shape::cir) 
	{
		outfile<<" viewBox=\" " << -c.cir1.rad/3.0  << " "
			   					<< -c.cir1.rad/3.0  << " " 
			   					<< box_w+100 	<< " " 
			   					<< box_h+100 	<< "\"";
	}
	
	outfile<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;

	switch(c.main_shape)
	{
		case Shape::rect: 
			switch(c.small_shape)
			{
				case Shape::rect: fitRInR(c.rect1,c.rect2); break;
				case Shape::cir:  fitCInR(c.rect1,c.cir2); 	break;
				case Shape::tri:  fitTInR(c.rect1,c.tri2); 	break;
			}break;
		case Shape::cir:
			switch(c.small_shape)
			{
				case Shape::rect: fitRInC(c.cir1,c.rect2); break;
				case Shape::cir:  fitCInC(c.cir1,c.cir2); 	break;
				case Shape::tri:  fitTInC(c.cir1,c.tri2); 	break;
			}break;
		case Shape::tri:
			switch(c.small_shape)
			{
				case Shape::rect: fitRInT(c.tri1,c.rect2); break;
				case Shape::cir:  fitCInT(c.tri1,c.cir2); 	break;
				case Shape::tri:  fitTInT(c.tri1,c.tri2); 	break;
			}break;
		default: outfile<<"</svg>"<<endl;
	}

	outfile.close();
}

void fitRInR(Rectangle r1, Rectangle r2)
{
	double area; // empty area;
	int total_shape=0; //  fitted shapes in total 
	ofstream outfile;

	Position p = {0,0}; // init at point (0,0)

	outfile.open(FILE_NAME, ios::app);

	area = areaRect(r1);
	printRect(r1,p,false, false); // false flag for not to rotate nor fill
	outfile<<endl; 

	// if rotating the rectangle can make us win more rectangle, we will go with that one
	if(totalRinR(r1.len1,r1.len2,r2)> totalRinR(r1.len2,r1.len1,r2)) 
		total_shape = fillRinR(r1,r2,p,false);
	else
		total_shape = fillRinR(r1,r2,p,true);

	outfile<<" </svg>";
	outfile.close();

	area -= areaRect(r2)*total_shape; // remainder empty area 

	printRemainder(total_shape,area);
}

double areaRect(Rectangle r) { return r.len1*r.len2;}
double areaCir(Circle c) {return 3.14159*c.rad*c.rad;}
double areaTri(Triangle t) { return t.len*t.len*sqrt(3)/4.0;}

int totalRinR(double r1_w,double r1_h, Rectangle r2)
{
	int total_fitted = 0;

	total_fitted = ((int)r1_w/(int)r2.len1)*((int)r1_h/(int)r2.len2);

	if((int)(r1_w)%(int)(r2.len1)>=(int)(r2.len2)) // whether rotating 90 degrees makes us win some more shape 
		total_fitted += (int)(r1_h)/(int)(r2.len1);

	return total_fitted;
}

void printRect(Rectangle r, Position p, bool fill, bool rotate)
{
	ofstream outfile;
	outfile.open(FILE_NAME, ios::app);

	outfile<< "<rect width=\"" << r.len1 << "\" height=\"" << r.len2 <<  
					  "\" y=\"" << p.y <<
					  "\" x=\"" << p.x <<  
					  "\" stroke=\"black\" stroke-width=\"1.6\"" << " fill="; 

	if(fill)outfile<< "\"cornflowerblue\""; // colorize the smaller shape 
	else 	outfile<< "\"white\""; 

	if(rotate) outfile << " transform = \" rotate(90," << p.x << "," << p.y <<")\"";

	outfile << "/>" << endl;
	outfile.close();
}

void shiftForward(Position &p, Position shift)	{p.x+=shift.x; p.y+=shift.y;}
void shiftBackward(Position &p, Position shift)	{p.x-=shift.x; p.y-=shift.y;}

int fillRinR(Rectangle r1, Rectangle r2, Position p,bool rotate)
{
	ofstream outfile;
	Position shift = p;
	double temp=0.0; // for to swap w and h 
	outfile.open(FILE_NAME, ios::app);


	if(rotate)
	{
		temp=r2.len1;
		r2.len1=r2.len2;
		r2.len2=temp;
	}

	// starting to fill from(a,b) to (max,b) without rotating
	int total1=0;
	for(p.x=0; p.x<=r1.len1-r2.len1;p.x+=r2.len1)
	{
		for(p.y=0; p.y<=r1.len2-r2.len2;p.y+=r2.len2)
		{
			shiftForward(p,shift);
			printRect(r2,p,true,false);
			shiftBackward(p,shift);
			++total1;
		}
	}
	
	int total2=0;
	// keep filling from(a,max) to (max,max) with rotating
	for(p.y=0,p.x=r2.len1*(double)((int)r1.len1/(int)r2.len1)+r2.len2;	
								p.x<= r1.len1 && p.y<=r1.len2-r2.len1;
														p.y+=r2.len1)
	{	
		shiftForward(p,shift);
		printRect(r2,p,true,true);
		shiftBackward(p,shift);
		++total2;
	}

	if(total2==0)
	{
		for(p.y=r2.len2*(double)((int)r1.len2/(int)r2.len2);p.y<r1.len2-r2.len1; p.y+=r2.len1)
		{
			for(p.x=0;p.x<=r1.len1-r2.len2;p.x+=r2.len2)
			{
				shiftForward(p,shift);
				printRect(r2,p,true,true);
				shiftBackward(p,shift);
				++total2;
			}
			shiftForward(p,shift);
			printRect(r2,p,true,true);
			shiftBackward(p,shift);
			++total2;
		}
		
	}

	total1+=total2; // total rectangle 
	outfile.close();

	return total1;
}

void fitRInC(Circle c, Rectangle r)
{
	ofstream outfile;
	Position p={0,0}; 
	double area;
	int total_shape=0;
	outfile.open(FILE_NAME, ios::app);

	// start the circle on point(r^0.5,r^0.5) 
	p.x = c.rad/sqrt(2.0);
	p.y = p.x;

	area = areaCir(c);
	printCir(c,p,false);

	total_shape = fillRinC(c,r);

	outfile<<"</svg>";
	outfile.close();

	area -= areaRect(r)*total_shape;
	printRemainder(total_shape,area);


}

void printRemainder(int total_shape, double area)
{
	cout<<endl<<"I can fit at most "<< total_shape << " shapes into main container."
	<< " The empty area(white) in container is " << area <<endl;
}

void printCir(Circle c, Position p, bool fill)
{
	ofstream outfile;
	outfile.open(FILE_NAME, ios::app);

	outfile <<   "<circle cx=\"" << p.x <<
					  "\" cy=\"" << p.y <<
				      "\" r=\""  << c.rad << "\" stroke=\"black\" stroke-width=\"1.6\"";

	if(fill) outfile << " fill=\"cornflowerblue\"/>"<<endl;
	else	 outfile << " fill=\"white\"/>"<<endl; 

	outfile.close();

}

int fillRinC(Circle c, Rectangle r)
{
	
	Position p{0,0}, cc{0,0}; // p: rectangle, cc: circle's center 
	Rectangle inner_r;
	int total_shape=0;
	bool rotate;

	cc.x = c.rad/sqrt(2.0); //(r^0.5,r^0.5)
	cc.y = cc.x;

	p.y = cc.y+c.rad;

	if(r.len1<r.len2)
	{
		rotate = true;
		inner_r.len2 = r.len1;
	}
	else
	{
		rotate = false;
		inner_r.len2 = r.len2;
	}

	while(p.x<cc.x)
	{
		p.y -= inner_r.len2;
		p.x = circleFunc(p.y,c.rad,cc,true);

		inner_r.len1 = circleFunc(p.y,c.rad,cc,false) - p.x;

		while(!isInsideCircle(p.x,p.y+inner_r.len2,c.rad,cc))
		{
			p.y-=.3;
			p.x++;
			inner_r.len1-=2.0;
		}

		total_shape += fillRinR(inner_r,r,p,rotate);
		
	}

	return total_shape;
}

void fitRInT(Triangle t, Rectangle r)
{
	ofstream outfile;
	Position p[3]; // triangle's points
	double area;
	int total_shape;
	outfile.open(FILE_NAME, ios::app);

	area = areaTri(t);
	setTriPoints(t,p,t.len/2.0,0.0); // create main triangle in p(len,0) without rotating
	printTri(t,p,false, false);

	total_shape = fillRinT(t,r);

	outfile<<"</svg>";
	outfile.close();

	area -= areaRect(r)*total_shape;
	printRemainder(total_shape,area);

}

void printTri(Triangle t, Position p[], bool fill, bool rotate)
{
	ofstream outfile;
	outfile.open(FILE_NAME, ios::app);

	outfile << "<polygon points=\""<< p[0].x << "," << p[0].y
							<< " " << p[1].x << "," << p[1].y
							<< " " << p[2].x << "," << p[2].y
							<< "\" style=\"fill:";

	if(fill) outfile<<"cornflowerblue;";
	else 	 outfile<<"white;";

	outfile<< "stroke:black;stroke-width:1.6\" "<<endl;

	if(rotate) outfile << " transform = \" rotate(180," << p[0].x << "," << p[0].y <<")\"";

	outfile << "/>" << endl;

	outfile.close();
}

void setTriPoints(Triangle t, Position p[], double x, double y)
{
	// 2a is length: (x,y) (x-a,y+a*3^0.5) (x+a,y+a*3^0.5)
	p[0].x = x;		  p[0].y = y;
	p[1].x = x-t.len/2.0; p[1].y = y+(t.len/2.0)*sqrt(3.0);
	p[2].x = x+t.len/2.0; p[2].y = y+(t.len/2.0)*sqrt(3.0);

}

int fillRinT(Triangle t, Rectangle r)
{
	Rectangle inner_r;
	Position p; // position of inner rectangle
	int total_shape=0;
	bool rotate; 

	p.x = 0.0;
	p.y = t.len/2.0*sqrt(3.0);

	// short length of rect is the height of inner rect which we will fill in.   
	if(r.len1<r.len2)
	{
		rotate = true; // width is smaller than height, so swap them for better fit
		inner_r.len2 = r.len1;	
		inner_r.len1 = t.len;
	}
	else	
	{
		rotate = false;
		inner_r.len2 = r.len2;
		inner_r.len1 = t.len;	
	}
	
	while(p.x<=t.len/2.0)
	{
		
		// updates: 
		// rectangle width gets smaller by it's height
		// position of rectangle goes top right 
		// magic number 1.7 is calculated from eq.triangle
		// for to calculate inner rectangle's starter point and length

		p.y-=inner_r.len2;
		p.x+=inner_r.len2/1.7;
		inner_r.len1 -= 2*inner_r.len2/1.7; 
	
		total_shape += fillRinR(inner_r,r,p,rotate);
	} 

	return total_shape;
}


void fitCInR(Rectangle r, Circle c)
{
	ofstream outfile;
	Position p{0,0}; // rectangle top left corner
	double area; 
	int total_shape;

	outfile.open(FILE_NAME, ios::app);

	area = areaRect(r);
	printRect(r,p,false,false); // no rotate nor fill for main rectangle

	total_shape = fillCinR(r,c,p);

	outfile<<"</svg>";
	outfile.close();

	area -= areaCir(c)*total_shape;
	printRemainder(total_shape,area);
}
int fillCinR(Rectangle r, Circle c, Position p)
{
	Position p1; // for to count
	int total_shape = 0;

	// pretty straight forward filling with starting from (r,r) 
	for(p1.y=c.rad;p1.y<=r.len2-c.rad;p1.y+=2.0*c.rad)
	{
		for(p1.x=c.rad;p1.x<=r.len1-c.rad;p1.x+=2.0*c.rad)
		{
			shiftForward(p1,p); // p1 shifted with p
			printCir(c,p1,true); 
			shiftBackward(p1,p);
			++total_shape;
		}
	}

	return total_shape;
}

void fitCInC(Circle c1, Circle c2)
{
	ofstream outfile;
	Position p={0,0}; 
	double area;
	int total_shape;

	outfile.open(FILE_NAME, ios::app);

	// start the circle on point(r^0.5,r^0.5) 
	p.x = c1.rad/sqrt(2.0);
	p.y = p.x;

	area = areaCir(c1);
	printCir(c1,p,false);
	total_shape = fillCinC(c1,c2);

	outfile<<"</svg>";
	outfile.close();

	area -= areaCir(c2)*total_shape;
	printRemainder(total_shape,area);

}

int fillCinC(Circle c1, Circle c2)
{
	Rectangle inner_r;
	Position p{0,0}, c{0,0}; // p: rectangle, c: circle's center
	int total_shape = 0; 

	c.x = c1.rad/sqrt(2.0); //(r^0.5,r^0.5)
	c.y = c.x;

	p.y = c.y+c1.rad;
	inner_r.len2 = c2.rad*2.0;
 
	while(p.x<c.x)
	{
		p.y -= c2.rad*2.0;
		p.x = circleFunc(p.y,c1.rad,c,true);

		inner_r.len1 = circleFunc(p.y,c1.rad,c,false) - p.x;

		// the above half of the center requires some updates:
		// such as controlling overflow 
		if(p.y>=c.x)
		{
			p.x+=2.0*c2.rad;
			inner_r.len1 -= 3.5*c2.rad;

			while(!isInsideCircle(p.x,p.y+2.0*c2.rad,c1.rad,c))
			{
				p.y--;
				p.x++;
				inner_r.len1--;
			}
		}
		total_shape += fillCinR(inner_r,c2,p);	
	}

	return total_shape;

}

void fitCInT(Triangle t, Circle c)
{
	ofstream outfile;
	Position p[3]; // triangle's points
	double area;
	int total_shape;
	outfile.open(FILE_NAME, ios::app);

	setTriPoints(t,p,t.len/2.0,0.0); // create main triangle in p(len,0) without rotating

	area = areaTri(t);
	printTri(t,p,false,false);

	total_shape = fillCinT(t,c);

	outfile<<"</svg>";
	outfile.close();

	area -= areaCir(c)*total_shape;
	printRemainder(total_shape,area);

}

int fillCinT(Triangle t, Circle c)
{
	Rectangle inner_r;
	Position p; // position of inner rectangle
	int total_shape = 0; 

	p.x = 0.0;
	p.y = t.len/2.0*sqrt(3.0);

	// smallest square that circle can fit in 
	inner_r.len1=t.len;
	inner_r.len2=2*c.rad;

	// same algorithm which we used in fillRinT:
	// after we set our inner rectangle, we fill the rectangle with circle
	while(p.x<=t.len/2.0)
	{
		p.y-=inner_r.len2;
		p.x+=inner_r.len2/1.7;
		inner_r.len1 -= 2*inner_r.len2/1.7; 
	
		total_shape += fillCinR(inner_r,c,p); 
	} 

	return total_shape;

}

double circleFunc(double y, double r, Position c, bool small)
{
	double x;
	if(small)
		x = -sqrt(r*r-((y-c.y)*(y-c.y)))+c.x; 
	else
		x =  sqrt(r*r-((y-c.y)*(y-c.y)))+c.x;

	return x;
}

bool isInsideCircle(double x, double y, double r, Position c)
{
	bool inside;
	if(r*r  <  (x-c.x)*(x-c.x)+(y-c.y)*(y-c.y))
		inside = false;
	else
		inside = true;
	return inside;
}

void fitTInR(Rectangle r, Triangle t)
{
	ofstream outfile;
	Position p = {0,0}; // init at point (0,0)
	double area;
	int total_shape=0;

	outfile.open(FILE_NAME, ios::app);

	area = areaRect(r);
	printRect(r,p,false, false); 
	outfile<<endl; 

	total_shape = fillTinR(r, t, p); 

	outfile<<" </svg>";
	outfile.close();

	area -= areaTri(t)*total_shape;
	printRemainder(total_shape,area);

}

int fillTinR(Rectangle r, Triangle t, Position shift)
{
	Position p[3]; // points of rectangle 
	double tri_height = sqrt(3.0)*t.len/2.0;
	int total_shape = 0;

	// (a,width-a*sqrt(3)) init for fill inside without rotating  
	for(p[0].y = r.len2-tri_height;p[0].y>=0;p[0].y-=tri_height)
	{
		setTriPoints(t,p,t.len/2.0,p[0].y);
		while(p[0].x+t.len/2.0<=r.len1)
		{
			shiftTriForward(p,shift);
			printTri(t,p,true,false);
			++total_shape;
			shiftTriBackward(p,shift);
			setTriPoints(t,p,p[0].x+t.len,p[0].y);

		}	
	}
	
	// (2a,width)init for fill inside with rotating
	for(p[0].y = r.len2;p[0].y-tri_height>=0;p[0].y-=tri_height)
	{
		setTriPoints(t,p,t.len,p[0].y);
		while(p[0].x+t.len/2.0<=r.len1)
		{
			shiftTriForward(p,shift);
			printTri(t,p,true, true);
			++total_shape;
			shiftTriBackward(p,shift);
			setTriPoints(t,p,p[0].x+t.len,p[0].y);
		}
	}
	return total_shape;	
}

void shiftTriForward(Position p[], Position shift)
{
	shiftForward(p[0],shift);
	shiftForward(p[1],shift);
	shiftForward(p[2],shift);
}

void shiftTriBackward(Position p[], Position shift)
{
	shiftBackward(p[0],shift);
	shiftBackward(p[1],shift);
	shiftBackward(p[2],shift);
}

void fitTInC(Circle c, Triangle t)
{
	ofstream outfile;
	Position p={0,0};
	double area;
	int total_shape = 0;

	outfile.open(FILE_NAME, ios::app);

	// start the circle on point(r^0.5,r^0.5) 
	p.x = c.rad/sqrt(2.0);
	p.y = p.x;

	area = areaCir(c);
	printCir(c,p,false);
	total_shape = fillTinC(c,t);

	outfile<<"</svg>";
	outfile.close();

	area -= areaTri(t)*total_shape;
	printRemainder(total_shape,area);
}


int fillTinC(Circle c, Triangle t)
{
	Position p{0,0}, cc{0,0}; // p: rectangle, cc: circle's center 
	int total_shape = 0;
	Rectangle inner_r;

	cc.x = c.rad/sqrt(2.0); //(r^0.5,r^0.5)
	cc.y = cc.x;

	inner_r.len2 = sqrt(3.0)*t.len/2.0;

	p.y = cc.y+c.rad;

	while(p.x<cc.x)
	{
		p.y -= inner_r.len2;
		p.x = circleFunc(p.y,c.rad,cc,true);

		inner_r.len1 = circleFunc(p.y,c.rad,cc,false) - p.x;

		while(!isInsideCircle(p.x,p.y+inner_r.len2,c.rad,cc))
		{
			p.y-=.3;
			p.x++;
			inner_r.len1-=1.8;
		}

		total_shape += fillTinR(inner_r,t,p);		
	}

	return total_shape;
}

void fitTInT(Triangle t1, Triangle t2)
{
	ofstream outfile;
	Position p[3]; // triangle's points
	double area;
	int total_shape;

	outfile.open(FILE_NAME, ios::app);

	setTriPoints(t1,p,t1.len/2.0,0.0); // create main triangle in p(len,0) without rotating
	area = areaTri(t1);
	printTri(t1,p,false, false);
	total_shape = fillTinT(t1,t2);

	outfile<<"</svg>";
	outfile.close();

	area -= areaTri(t2)*total_shape;
	printRemainder(total_shape,area);

}
int fillTinT(Triangle t1, Triangle t2)
{
	Position p[3]; // little triangle's points
	double main_h, small_h;  // h of big main triangle
	int total_shape = 0;

	main_h = sqrt(3.0)*t1.len/2.0;
	small_h = sqrt(3.0)*t2.len/2.0;

	setTriPoints(t2,p,0.0,main_h); // (0,H)

	int i=1;
	double width=t1.len;
	for(p[0].y = main_h-small_h; p[0].y>=0; p[0].y-= small_h)
	{
		setTriPoints(t2,p,i*t2.len/2.0,p[0].y);
		++i;
		while(p[0].x+t2.len/2.0<=width)
		{
			printTri(t2,p,true,false);
			++total_shape;
			setTriPoints(t2,p,p[0].x+t2.len,p[0].y);
		}

		width-=t2.len/2.0;
	
	}

	i=2;
	width=t1.len-t2.len/2.0;
	for(p[0].y = main_h; p[0].y-small_h>=0; p[0].y-= small_h)
	{
		setTriPoints(t2,p,i*t2.len/2.0,p[0].y);
		++i;
		while(p[0].x+t2.len/2.0<=width)
		{
			printTri(t2,p,true, true);
			++total_shape;
			setTriPoints(t2,p,p[0].x+t2.len,p[0].y);
		}

		width-=t2.len/2.0;
	}

	return total_shape;
}