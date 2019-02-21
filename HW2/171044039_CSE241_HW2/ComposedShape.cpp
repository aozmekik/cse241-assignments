/* 
 * ComposedShape.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "ComposedShape.h"
#include <cmath>


ComposedShape::ComposedShape(const Rectangle& r1,const Rectangle& r2)
	: main_shape(Shape::rect)
	, small_shape(Shape::rect)
	, r1(r1)
	, r2(r2)
	, total_shape(0)
	, empty_area(r1.getArea())
	, _x(r1.getX())
	, _y(r1.getY()) 
{
	findBoundingBox();
}

ComposedShape::ComposedShape(const Rectangle& r1,const Circle& c2)
	: main_shape(Shape::rect)
	, small_shape(Shape::cir)
	, r1(r1)
	, c2(c2)
	, total_shape(0)
	, empty_area(r1.getArea())
	, _x(r1.getX())
	, _y(r1.getY()) 
{
	findBoundingBox();
}

ComposedShape::ComposedShape(const Rectangle& r1,const Triangle& t2)
	: main_shape(Shape::rect)
	, small_shape(Shape::tri)
	, r1(r1)
	, t2(t2)
	, total_shape(0)
	, empty_area(r1.getArea())
	, _x(r1.getX())
	, _y(r1.getY())
{
	findBoundingBox();
}

ComposedShape::ComposedShape(const Circle& c1,const Rectangle& r2)
	: main_shape(Shape::cir)
	, small_shape(Shape::rect)
	, r2(r2)
	, c1(c1)
	, total_shape(0)
	, empty_area(c1.getArea())
	, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
	, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
{
	findBoundingBox();
}

ComposedShape::ComposedShape(const Circle& c1,const Circle& c2)
	: main_shape(Shape::cir)
	, small_shape(Shape::cir)
	, c1(c1)
	, c2(c2)
	, total_shape(0)
	, empty_area(c1.getArea())
	, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
	, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
{
	findBoundingBox();
}
ComposedShape::ComposedShape(const Circle& c1,const Triangle& t2)
	: main_shape(Shape::cir)
	, small_shape(Shape::tri)
	, c1(c1)
	, t2(t2)
	, total_shape(0)
	, empty_area(c1.getArea())
	, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
	, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
{
	findBoundingBox();
}

ComposedShape::ComposedShape(const Triangle& t1,const Rectangle& r2)
	: main_shape(Shape::tri)
	, small_shape(Shape::rect)
	, r2(r2)
	, t1(t1)
	, total_shape(0)
	, empty_area(t1.getArea())
	, _x(t1.getX()-t1.getLength()/2.0)
	, _y(t1.getY())
{
	findBoundingBox();
	

}

ComposedShape::ComposedShape(const Triangle& t1,const Circle& c2)
	: main_shape(Shape::tri)
	, small_shape(Shape::cir)
	, c2(c2)
	, t1(t1)
	, total_shape(0)
	, empty_area(t1.getArea())
	, _x(t1.getX()-t1.getLength()/2.0)
	, _y(t1.getY())
{
	findBoundingBox();
}

ComposedShape::ComposedShape(const Triangle& t1,const Triangle& t2)
	: main_shape(Shape::tri)
	, small_shape(Shape::tri)
	, t1(t1)
	, t2(t2)
	, total_shape(0)
	, empty_area(t1.getArea())
	, _x(t1.getX()-t1.getLength()/2.0)
	, _y(t1.getY())
{
	findBoundingBox();
}

// main and small shape set as default rectangle 
ComposedShape::ComposedShape() : ComposedShape(Rectangle(),Rectangle())
{/* Body intentionally left empty */}


void ComposedShape::optimalFit()
{
	switch(main_shape)
	{
		case Shape::rect: 
			switch(small_shape)
			{
				case Shape::rect: small_r = fitRinR(); 	
								  total_shape = small_r.size();
								  empty_area = r1.getArea()-r2.getArea()*total_shape;
								  break;
				case Shape::cir:  small_c = fitCinR();
								  total_shape = small_c.size();
								  empty_area = r1.getArea()-c2.getArea()*total_shape;
								  break;
				case Shape::tri:  small_t = fitTinR();
								  total_shape = small_t.size();
								  empty_area = r1.getArea()-t2.getArea()*total_shape;
								  break;
			}break;
		case Shape::cir:
			switch(small_shape)
			{
				case Shape::rect: small_r = fitRinC();
								  total_shape = small_r.size();
								  empty_area = c1.getArea()-r2.getArea()*total_shape;
								  break;
				case Shape::cir:  small_c = fitCinC();
								  total_shape = small_c.size();
								  empty_area = c1.getArea()-c2.getArea()*total_shape;
								  break;
				case Shape::tri:  small_t = fitTinC();
								  total_shape = small_t.size();
								  empty_area = c1.getArea()-t2.getArea()*total_shape;
								  break;
			}break;
		case Shape::tri:
			switch(small_shape)
			{
				case Shape::rect: small_r = fitRinT();
								  total_shape = small_r.size();
								  empty_area = t1.getArea()-r2.getArea()*total_shape;
								  break;
				case Shape::cir:  small_c = fitCinT();
								  total_shape = small_c.size();
								  empty_area = t1.getArea()-c2.getArea()*total_shape;
								  break;
				case Shape::tri:  small_t = fitTinT(); 
								  total_shape = small_t.size();
								  empty_area = t1.getArea()-t2.getArea()*total_shape;
								  break;
			}break;
	}
}

void ComposedShape::draw(ofstream& outfile)const
{
	// There will be such cases that we only want to fit small shape
	// into an imaginary main container shape to make this code reusable.   
	
	// header codes for svg format
	outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
	<<"width=\""<<box_w<< "\" height=\""<<box_h<<"\""
	<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;

	switch(main_shape)
	{	
		case Shape::rect: r1.draw(outfile); break;
		case Shape::cir:  c1.draw(outfile); break;
		case Shape::tri:  t1.draw(outfile); break;
	}
	

	switch(small_shape)
	{
		case Shape::rect: 

			for(auto r: small_r)
				r.draw(outfile); 
			break;

		case Shape::cir: 
			for(auto c: small_c)
				c.draw(outfile); 
			break;

		case Shape::tri: 
			for(auto t: small_t)
				t.draw(outfile); 
			break; 
	}

	outfile<<" </svg>"; // end of svg.

}
void ComposedShape::findBoundingBox()
{
	// doubled the box to prevent the worst case for circle
	switch(main_shape)
	{
		case Shape::rect:  
			setBoxWidth(r1.getWidth()); 
			setBoxHeight(r1.getHeight());   
			break;

		case Shape::cir:
			setBoxWidth(c1.getRadius()*2.0); // doubled for full view of circle
			setBoxHeight(c1.getRadius()*2.0);   
			break;  
		 
		case Shape::tri:   
			setBoxWidth(t1.getLength()); 
			setBoxHeight(t1.getLength());   
	}

	// expanding our box to see the strokes of border edges
	setBoxWidth(getBoxWidth()+100.0);
	setBoxHeight(getBoxHeight()+100.0);
}

int ComposedShape::totalRinR(double w, double h) const
{
	int total_fitted = 0;

	total_fitted = ((int)w/(int)r2.getWidth())*((int)h/(int)r2.getHeight());

	// Whether rotating the small shape by 90 degrees 
	// makes us win some more shape.
	// int casting because of getting exact numbers.  
	if((int)(w)%(int)(r2.getWidth())>=(int)(r2.getHeight())) 
		total_fitted = (int)(h)/(int)(r2.getWidth());

	return total_fitted;
}

const vector<Rectangle> ComposedShape::fitRinR()const
{ 
	Rectangle r(r2); // Temp small shape which we will work on.
	vector<Rectangle> shape; // Small shapes. 
	double x,y; // temp positions which we will find later on for small shapes.    

	r.setFill(true); // small shapes will have color.

	// We determine which filling(rotate or not) is better for optimization. 
	if(totalRinR(r1.getWidth(),r1.getHeight()) < 
	   totalRinR(r1.getHeight(),r1.getWidth()) )
	{
		r.swapEdges(); 
	}

	// Starting to fill from(a,b) to (max,b) without rotating.
	// (_x,_y) counters represent position.
	r.setRotate(false);
	for(x=0.0; x<=r1.getWidth()-r.getWidth();x+=r.getWidth())
	{
		for(y=0.0; y<=r1.getHeight()-r.getHeight(); y+=r.getHeight())
		{
			// (x,y) determined due to (0,0). We must add  
			// container's coordinates to shift to exact position.   
			r.setPosition(_x+x,_y+y);
			shape.push_back(r);
		}
	}

	// Keep filling from(a,max) to (max,max) with rotating.
	r.setRotate(true);
	bool filled=false; // to check if we filled any with this try.
	for(y=0.0,
		x=r.getWidth()*(double)((int)r1.getWidth()/(int)r.getWidth())+r.getHeight();	
								  x<= r1.getWidth() && y<=r1.getHeight()-r.getWidth();
																	   y+=r.getWidth())
	{	
		r.setPosition(_x+x,_y+y);
		shape.push_back(r);
		filled=true;
		cout<<"test";
	}

	// Try to fill with rotating from different position.
	if(!filled)
	{
		for(y=r.getHeight()*(double)((int)r1.getHeight()/(int)r.getHeight());
									y<r1.getHeight()-r.getWidth(); y+=r.getWidth())
		{
			for(x=0;x<=r1.getWidth()-r.getHeight();x+=r.getHeight())
			{
				r.setPosition(_x+x,_y+y);
				shape.push_back(r);
			}
			r.setPosition(_x+x,_y+y);
			shape.push_back(r);
		}
	}

	return shape;

}

double ComposedShape::circleFunc(double y, const Circle& c, bool small)
{
	double x;
	if(small)
		x = -sqrt(c.getRadius()*c.getRadius()-((y-c.getY())*(y-c.getY())))+c.getX(); 
	else
		x =  sqrt(c.getRadius()*c.getRadius()-((y-c.getY())*(y-c.getY())))+c.getX();

	return x;
}

bool ComposedShape::isInsideCircle(double x, double y, const Circle& c)
{
	bool inside;
	if(c.getRadius()*c.getRadius()  <  (x-c.getX())*(x-c.getX())+(y-c.getY())*(y-c.getY()))
		inside = false;
	else
		inside = true;
	return inside;
}


const vector<Rectangle> ComposedShape::fitRinC()const
{
	// We fill the imaginary inner rectangles which inside of circle with small rectangles.
	// To do this we must create a composition with rectangular main container.
	// We copy the circle object to shift the wanted area of cartesian coordinate
	// system for better use of circle functions. 
	Rectangle inner_r,r(r2);
	Circle c(c1); 
	ComposedShape inner_shape(inner_r,r);
	vector<Rectangle> shape;
	double x=0.0,y=0.0; 

	c.setPosition(c.getRadius()/sqrt(2.0),c.getRadius()/sqrt(2.0));

	y = c.getY()+c.getRadius();

	if(r.getWidth()>r.getHeight())
		r.swapEdges();
		
	
	inner_r.setHeight(r.getWidth());
	

	while(x<c.getX())
	{
		y -= inner_r.getHeight();
		x = circleFunc(y,c,true);

		inner_r.setWidth(circleFunc(y,c,false) - x);

		while(!isInsideCircle(x,y+inner_r.getHeight(),c))
		{
			y-=.3;
			x++;
			inner_r.setWidth(inner_r.getWidth()-2.0);
		}
		// Update the composition.
		r.setPosition(x+_x,y+_y);
		// Concatenate two vectors.
		appendComposition(inner_shape,inner_r,r,shape);
		
	}


	return shape;

}

const vector<Rectangle> ComposedShape::fitRinT()const
{
	// Yet another imaginary composition created. 
	// We again, find the optimal rectangles inside the triangle,
	// Then make them our container, so that we can use fitRinR func.
	Rectangle inner_r,r(r2);
	ComposedShape inner_shape(inner_r,r);
	vector<Rectangle> shape,temp;

	double x,y;

	x = 0.0;
	y = t1.getLength()/2.0*sqrt(3.0);

	// short length of rect is the height of inner rect which we will fill in.   
	if(r.getWidth()>r.getHeight())
		r.swapEdges();
	
	
	inner_r.setHeight(r.getWidth());
	inner_r.setWidth (t1.getLength());

	while(x<=t1.getLength()/2.0 && inner_r.getWidth()- 2*inner_r.getHeight()/1.7 >0)
	{
		
		// Updates: 
		// Rctangle width gets smaller by it's height.
		// Position of rectangle goes top right 
		// magic number 1.7 is calculated from eq.triangle,
		// for to calculate inner rectangle's starter point and length

		y-=inner_r.getHeight();
		x+=inner_r.getHeight()/1.7;
		inner_r.setWidth(inner_r.getWidth()- 2*inner_r.getHeight()/1.7);

		r.setPosition(x+_x,y+_y);
		appendComposition(inner_shape,inner_r,r,shape);

	} 
	return shape;
}

const vector<Circle> ComposedShape::fitCinR()const
{
	vector<Circle> shape;
	Circle c(c2);
	double x,y;

	// pretty straight forward filling with starting from (r,r) 
	c.setFill(true);
	for(y=c.getRadius();y<=r1.getHeight()-c.getRadius();y+=2.0*c.getRadius())
	{
		for(x=c.getRadius();x<=r1.getWidth()-c.getRadius();x+=2.0*c.getRadius())
		{
			c.setPosition(x+_x,y+_y);
			shape.push_back(c);
		}
	}

	return shape;
}

const vector<Circle> ComposedShape::fitCinC()const
{
	Rectangle inner_r;
	Circle main_c(c1),small_c(c2);
	ComposedShape inner_shape(inner_r,small_c);
	vector<Circle> shape,temp;
	double x,y;

	main_c.setPosition(c1.getRadius()/sqrt(2.0),c1.getRadius()/sqrt(2.0));

	y = main_c.getY() + main_c.getRadius();
	inner_r.setHeight(small_c.getRadius()*2.0);
 
	while(x<main_c.getX())
	{
		y -= small_c.getRadius()*2.0;
		x = circleFunc(y,main_c,true);

		inner_r.setWidth(circleFunc(y,main_c,false) - x);

		// the above half of the center requires some updates:
		// such as controlling overflow 
		if(y>=main_c.getX())
		{
			x+=2.0*small_c.getRadius();
			inner_r.setWidth(inner_r.getWidth()- 3.5*small_c.getRadius());

			while(!isInsideCircle(x,y+2.0*c2.getRadius(),main_c))
			{
				y--;
				x++;
				inner_r.setWidth(inner_r.getWidth()-1);
			}
		}

		small_c.setPosition(x+_x,y+_y);
		appendComposition(inner_shape,inner_r,small_c,shape);
	}

	return shape;
}

const vector<Circle> ComposedShape::fitCinT()const
{
	Rectangle inner_r;
	Circle c(c2);
	ComposedShape inner_shape(inner_r,c);
	vector<Circle> shape,temp;
	double x,y; // position of inner rectangle 

	x = 0.0;
	y = t1.getLength()/2.0*sqrt(3.0);

	// smallest square that circle can fit in 
	inner_r.setWidth(t1.getLength());
	inner_r.setHeight(2*c.getRadius());

	// same algorithm which we used in fitRinT:
	// after we set our inner rectangle, we fill the rectangle with circle
	while(x<=t1.getLength()/2.0 && inner_r.getWidth()-2*inner_r.getHeight()/1.7>0)
	{
		y-=inner_r.getHeight();
		x+=inner_r.getHeight()/1.7;
		inner_r.setWidth(inner_r.getWidth()-2*inner_r.getHeight()/1.7); 

		c.setPosition(x+_x,y+_y);
		appendComposition(inner_shape,inner_r,c,shape);
	 
	} 

	return shape;
}

const vector<Triangle> ComposedShape::fitTinR()const
{
	Triangle t(t2); 
	vector<Triangle> shape;
	double x,y;
	double tri_height = sqrt(3.0)*t.getLength()/2.0;

	t.setFill(true);

	// (a,width-a*sqrt(3)) init for fill inside without rotating  
	for(y = r1.getHeight()-tri_height;y>=0;y-=tri_height)
	{
		x=t.getLength()/2.0;
		while(x+t.getLength()/2.0<=r1.getWidth())
		{
			t.setPosition(x+_x,y+_y);
			shape.push_back(t);
			x+=t.getLength();
		}	
	}
	
	// (2a,width)init for fill inside with rotating
	t.setRotate(true);
	for(y = r1.getHeight();y-tri_height>=0;y-=tri_height)
	{
		x = t.getLength();
		while(x+t.getLength()/2.0<=r1.getWidth())
		{
			
			t.setPosition(x+_x,y+_y);
			shape.push_back(t);
			x += t.getLength();
		}
	}

	return shape;

}

const vector<Triangle> ComposedShape::fitTinC()const
{
	Rectangle inner_r;
	Triangle t(t2);
	Circle c(c1);
	ComposedShape inner_shape(inner_r,t);
	vector<Triangle> shape;
	double x,y;

	c.setPosition(c.getRadius()/sqrt(2.0),c.getRadius()/sqrt(2.0));

	inner_r.setHeight(sqrt(3.0)*t.getLength()/2.0);

	x=0.0;
	y=c.getY()+c.getRadius();

	while(x<c.getX())
	{
		y -= inner_r.getHeight();
		x = circleFunc(y,c,true);

		inner_r.setWidth(circleFunc(y,c,false)-x);

		while(!isInsideCircle(x,y+inner_r.getHeight(),c))
		{
			y-=.3;
			x++;
			inner_r.setWidth(inner_r.getWidth()-1.8);
		}

		t.setPosition(x+_x,y+_y);
		appendComposition(inner_shape,inner_r,t,shape);

	}

	return shape;
}

const vector<Triangle> ComposedShape::fitTinT()const
{
	Triangle main_t(t1),small_t(t2);
	double x,y;
	double main_h, small_h;  // h of big main triangle
	vector<Triangle> shape;

	main_h = sqrt(3.0)*main_t.getLength()/2.0;
	small_h = sqrt(3.0)*small_t.getLength()/2.0;

	small_t.setFill(true);

	x=0.0;
	y=main_h;

	int i=1;
	double width=main_t.getLength();
	for(y = main_h-small_h; y>=0; y-= small_h)
	{
		x = i*small_t.getLength()/2.0;
		small_t.setPosition(x+_x,y+_y);
		++i;
		while(x+small_t.getLength()/2.0<=width)
		{
			shape.push_back(small_t);
			x += small_t.getLength(); 
			small_t.setPosition(x+_x,y+_y);
		}

		width-=small_t.getLength()/2.0;
	
	}

	small_t.setRotate(true);
	i=2;
	width=main_t.getLength()-small_t.getLength()/2.0;
	for(y = main_h; y-small_h>=0; y-= small_h)
	{
		x = i*small_t.getLength()/2.0;
		small_t.setPosition(x+_x,y+_y);
		++i;
		while(x+small_t.getLength()/2.0<=width)
		{
			shape.push_back(small_t);
			x+= small_t.getLength();
			small_t.setPosition(x+_x,y+_y);
		}

		width-=small_t.getLength()/2.0;
	}

	return shape;
}


void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
									  const Rectangle& small,vector<Rectangle>& v)const
{
	vector<Rectangle> temp;
	inner.setPosition(small.getX(),small.getY());
	inner.setMainShape(main);
	inner.setSmallShape(small);
	inner.optimalFit();
	temp = inner.getVectorR();
	v.insert(v.end(), temp.begin(),temp.end());
}
void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
									  const Circle& small,vector<Circle>& v)const
{
	vector<Circle> temp;
	inner.setPosition(small.getX(),small.getY());
	inner.setMainShape(main);
	inner.setSmallShape(small);
	inner.optimalFit();
	temp = inner.getVectorC();
	v.insert(v.end(), temp.begin(),temp.end());
}
void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
									  const Triangle& small,vector<Triangle>& v)const
{
	vector<Triangle> temp;
	inner.setPosition(small.getX(),small.getY());
	inner.setMainShape(main);
	inner.setSmallShape(small);
	inner.optimalFit();
	temp = inner.getVectorT();
	v.insert(v.end(), temp.begin(),temp.end());
}