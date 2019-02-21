/* 
 * ComposedShape.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "ComposedShape.h"
#include <cmath>


ComposedShape::ComposedShape(const Rectangle& _r1,const Rectangle& _r2)
	: main_shape(Shape::rect)
	, small_shape(Shape::rect)
	, r1(_r1)
	, r2(_r2)
	, _x(r1.getX())
	, _y(r1.getY()) 
{
	r1.setHeader(false);
	r2.setHeader(false);
	findBoundingBox();
}

ComposedShape::ComposedShape(const Rectangle& _r1,const Circle& _c2)
	: main_shape(Shape::rect)
	, small_shape(Shape::cir)
	, r1(_r1)
	, c2(_c2)
	, _x(r1.getX())
	, _y(r1.getY()) 
{
	r1.setHeader(false);
	c2.setHeader(false);
	findBoundingBox();
}

ComposedShape::ComposedShape(const Rectangle& _r1,const Triangle& _t2)
	: main_shape(Shape::rect)
	, small_shape(Shape::tri)
	, r1(_r1)
	, t2(_t2)
	, _x(r1.getX())
	, _y(r1.getY())
{
	r1.setHeader(false);
	t2.setHeader(false);
	findBoundingBox();
}

ComposedShape::ComposedShape(const Circle& _c1,const Rectangle& _r2)
	: main_shape(Shape::cir)
	, small_shape(Shape::rect)
	, r2(_r2)
	, c1(_c1)
	, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
	, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
{
	r2.setHeader(false);
	c1.setHeader(false);
	findBoundingBox();
}

ComposedShape::ComposedShape(const Circle& _c1,const Circle& _c2)
	: main_shape(Shape::cir)
	, small_shape(Shape::cir)
	, c1(_c1)
	, c2(_c2)
	, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
	, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
{
	c1.setHeader(false);
	c2.setHeader(false);
	findBoundingBox();
}
ComposedShape::ComposedShape(const Circle& _c1,const Triangle& _t2)
	: main_shape(Shape::cir)
	, small_shape(Shape::tri)
	, c1(_c1)
	, t2(_t2)
	, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
	, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
{
	c1.setHeader(false);
	c2.setHeader(false);
	findBoundingBox();
}

ComposedShape::ComposedShape(const Triangle& _t1,const Rectangle& _r2)
	: main_shape(Shape::tri)
	, small_shape(Shape::rect)
	, r2(_r2)
	, t1(_t1)
	, _x(t1.getX()-t1.getLength()/2.0)
	, _y(t1.getY())
{
	r2.setHeader(false);
	t1.setHeader(false);
	findBoundingBox();
	

}

ComposedShape::ComposedShape(const Triangle& _t1,const Circle& _c2)
	: main_shape(Shape::tri)
	, small_shape(Shape::cir)
	, c2(_c2)
	, t1(_t1)
	, _x(t1.getX()-t1.getLength()/2.0)
	, _y(t1.getY())
{
	c2.setHeader(false);
	t1.setHeader(false);
	findBoundingBox();
}

ComposedShape::ComposedShape(const Triangle& _t1,const Triangle& _t2)
	: main_shape(Shape::tri)
	, small_shape(Shape::tri)
	, t1(_t1)
	, t2(_t2)
	, _x(t1.getX()-t1.getLength()/2.0)
	, _y(t1.getY())
{
	t1.setHeader(false);
	t2.setHeader(false);
	findBoundingBox();
}

// main and small shape set as default rectangle 
ComposedShape::ComposedShape() : ComposedShape(Rectangle(),Rectangle())
{/* Body intentionally left empty */}

void ComposedShape::setMainShape(const Rectangle& _r1)
{
	r1=_r1; 
	main_shape=Shape::rect; 
    _x=_r1.getX(); 
    _y=_r1.getY();
} 

void ComposedShape::setMainShape(const Circle& _c1)  		
{	
	c1=_c1; 
	main_shape=Shape::cir; 
	_x=_c1.getX()-_c1.getRadius()/sqrt(2.0);
 	_y=_c1.getY()-_c1.getRadius()/sqrt(2.0);

}
void ComposedShape::setMainShape(const Triangle& _t1)		
{	
	t1=_t1; 
	main_shape=Shape::tri;
	_x = _t1.getX()-_t1.getLength()/2.0;
	_y = _t1.getY();

}




void ComposedShape::optimalFit()
{
	switch(main_shape)
	{
		case Shape::rect: 
			switch(small_shape)
			{
				case Shape::rect: shape = fitRinR();break;
				case Shape::cir:  shape = fitCinR();break;
				case Shape::tri:  shape = fitTinR();break;
			}break;
		case Shape::cir:
			switch(small_shape)
			{
				case Shape::rect: shape = fitRinC();break;
				case Shape::cir:  shape = fitCinC();break;
				case Shape::tri:  shape = fitTinC();break;
			}break;
		case Shape::tri:
			switch(small_shape)
			{
				case Shape::rect: shape = fitRinT();break;
				case Shape::cir:  shape = fitCinT();break;
				case Shape::tri:  shape = fitTinT();break;
			}break;
	}
}

void ComposedShape::operator+=(const Rectangle& r){ shape.push_back(r);}
void ComposedShape::operator+=(const Circle& c){ shape.push_back(c);}
void ComposedShape::operator+=(const Triangle& t){ shape.push_back(t);}

const ComposedShape::ShapeElem ComposedShape::operator[](unsigned int idx)const{return shape[idx];} 


ostream& operator<<(ostream& outfile,const ComposedShape& c)
{	
	// header codes for svg format
	outfile<<"<svg version=\"1.1\"" <<endl<< "baseProfile=\"full\"" <<endl
	<<"width=\""<<c.box_w<< "\" height=\""<<c.box_h<<"\""
	<<" xmlns=\"http://www.w3.org/2000/svg\">"<<endl;

	switch(c.main_shape)
	{	
		case Shape::rect: outfile<<c.r1; break;
		case Shape::cir:  outfile<<c.c1; break;
		case Shape::tri:  outfile<<c.t1; break;
	}
	
	for(auto s: c.shape)
		outfile<<s;

	outfile<<" </svg>"; // end of svg.

	return outfile;
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

const vector<ComposedShape::ShapeElem> ComposedShape::fitRinR()const
{ 
	Rectangle r(r2); // Temp small shape which we will work on.
	vector<ComposedShape::ShapeElem> _shape; // Small shapes. 
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
			_shape.push_back(r);
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
		_shape.push_back(r);
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
				_shape.push_back(r);
			}
			r.setPosition(_x+x,_y+y);
			_shape.push_back(r);
		}
	}

	return _shape;

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


const vector<ComposedShape::ShapeElem> ComposedShape::fitRinC()const
{
	// We fill the imaginary inner rectangles which inside of circle with small rectangles.
	// To do this we must create a composition with rectangular main container.
	// We copy the circle object to shift the wanted area of cartesian coordinate
	// system for better use of circle functions. 
	Rectangle inner_r,r(r2);
	Circle c(c1); 
	ComposedShape inner_shape(inner_r,r);
	vector<ComposedShape::ShapeElem> _shape;
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
		appendComposition(inner_shape,inner_r,r,_shape);
		
	}

	return _shape;

}

const vector<ComposedShape::ShapeElem> ComposedShape::fitRinT()const
{
	// Yet another imaginary composition created. 
	// We again, find the optimal rectangles inside the triangle,
	// Then make them our container, so that we can use fitRinR func.
	Rectangle inner_r,r(r2);
	ComposedShape inner_shape(inner_r,r);
	vector<ComposedShape::ShapeElem> _shape;

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
		appendComposition(inner_shape,inner_r,r,_shape);

	} 
	return _shape;
}

const vector<ComposedShape::ShapeElem> ComposedShape::fitCinR()const
{
	vector<ComposedShape::ShapeElem> _shape;
	Circle c(c2);
	double x,y;

	// pretty straight forward filling with starting from (r,r) 
	c.setFill(true);
	for(y=c.getRadius();y<=r1.getHeight()-c.getRadius();y+=2.0*c.getRadius())
	{
		for(x=c.getRadius();x<=r1.getWidth()-c.getRadius();x+=2.0*c.getRadius())
		{
			c.setPosition(x+_x,y+_y);
			_shape.push_back(c);
		}
	}

	return _shape;
}

const vector<ComposedShape::ShapeElem> ComposedShape::fitCinC()const
{
	Rectangle inner_r;
	Circle main_c(c1),small_c(c2);
	ComposedShape inner_shape(inner_r,small_c);
	vector<ComposedShape::ShapeElem> _shape;
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
		appendComposition(inner_shape,inner_r,small_c,_shape);
	}

	return _shape;
}

const vector<ComposedShape::ShapeElem> ComposedShape::fitCinT()const
{
	Rectangle inner_r;
	Circle c(c2);
	ComposedShape inner_shape(inner_r,c);
	vector<ComposedShape::ShapeElem> _shape;
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
		appendComposition(inner_shape,inner_r,c,_shape);
	 
	} 

	return _shape;
}

const vector<ComposedShape::ShapeElem> ComposedShape::fitTinR()const
{
	Triangle t(t2); 
	vector<ComposedShape::ShapeElem> _shape;
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
			_shape.push_back(t);
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
			_shape.push_back(t);
			x += t.getLength();
		}
	}

	return _shape;

}

const vector<ComposedShape::ShapeElem> ComposedShape::fitTinC()const
{
	Rectangle inner_r;
	Triangle t(t2);
	Circle c(c1);
	ComposedShape inner_shape(inner_r,t);
	vector<ComposedShape::ShapeElem> _shape;
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
		appendComposition(inner_shape,inner_r,t,_shape);

	}

	return _shape;
}

const vector<ComposedShape::ShapeElem> ComposedShape::fitTinT()const
{
	Triangle main_t(t1),small_t(t2);
	double x,y;
	double main_h, small_h;  // h of big main triangle
	vector<ComposedShape::ShapeElem> _shape;

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
			_shape.push_back(small_t);
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
			_shape.push_back(small_t);
			x+= small_t.getLength();
			small_t.setPosition(x+_x,y+_y);
		}

		width-=small_t.getLength()/2.0;
	}

	return _shape;
}


void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
									  const Rectangle& small,vector<ComposedShape::ShapeElem>& v)const
{
	vector<ComposedShape::ShapeElem> temp;
	inner.setMainShape(main);
	inner.setSmallShape(small);
	inner.setPosition(small.getX(),small.getY());
	inner.optimalFit();
	temp = inner.getVector();
	v.insert(v.end(), temp.begin(),temp.end());
}
void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
									  const Circle& small,vector<ComposedShape::ShapeElem>& v)const
{
	vector<ComposedShape::ShapeElem> temp;
	inner.setMainShape(main);
	inner.setSmallShape(small);
	inner.setPosition(small.getX(),small.getY());
	inner.optimalFit();
	temp = inner.getVector();
	v.insert(v.end(), temp.begin(),temp.end());
}
void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
									  const Triangle& small,vector<ComposedShape::ShapeElem>& v)const
{
	vector<ComposedShape::ShapeElem> temp;
	inner.setMainShape(main);
	inner.setSmallShape(small);
	inner.setPosition(small.getX(),small.getY());
	inner.optimalFit();
	temp = inner.getVector();
	v.insert(v.end(), temp.begin(),temp.end());
}

/* Comparison Operators overloaded for all cases. */

bool operator==(const Circle& c,const Rectangle& r){return c.getArea()==r.getArea();}
bool operator!=(const Circle& c,const Rectangle& r){return c.getArea()!=r.getArea();}
bool operator>=(const Circle& c,const Rectangle& r){return c.getArea()>=r.getArea();}
bool operator<=(const Circle& c,const Rectangle& r){return c.getArea()<=r.getArea();}
bool operator>(const Circle& c,const Rectangle& r){return c.getArea()>r.getArea();}
bool operator<(const Circle& c,const Rectangle& r){return c.getArea()<r.getArea();}

bool operator==(const Circle& c,const Triangle& t){return c.getArea()==t.getArea();}
bool operator!=(const Circle& c,const Triangle& t){return c.getArea()!=t.getArea();}
bool operator>=(const Circle& c,const Triangle& t){return c.getArea()>=t.getArea();}
bool operator<=(const Circle& c,const Triangle& t){return c.getArea()<=t.getArea();}
bool operator>(const Circle& c,const Triangle& t){return c.getArea()>t.getArea();}
bool operator<(const Circle& c,const Triangle& t){return c.getArea()<t.getArea();}

bool operator==(const Rectangle& r,const Triangle& t){return r.getArea()==t.getArea();}
bool operator!=(const Rectangle& r,const Triangle& t){return r.getArea()!=t.getArea();}
bool operator>=(const Rectangle& r,const Triangle& t){return r.getArea()>=t.getArea();}
bool operator<=(const Rectangle& r,const Triangle& t){return r.getArea()<=t.getArea();}
bool operator>(const Rectangle& r,const Triangle& t){return r.getArea()>t.getArea();}
bool operator<(const Rectangle& r,const Triangle& t){return r.getArea()<t.getArea();}

bool operator==(const Rectangle& r,const Circle& c){return r.getArea()==c.getArea();}
bool operator!=(const Rectangle& r,const Circle& c){return r.getArea()!=c.getArea();}
bool operator>=(const Rectangle& r,const Circle& c){return r.getArea()>=c.getArea();}
bool operator<=(const Rectangle& r,const Circle& c){return r.getArea()<=c.getArea();}
bool operator>(const Rectangle& r,const Circle& c){return r.getArea()>c.getArea();}
bool operator<(const Rectangle& r,const Circle& c){return r.getArea()<c.getArea();}


bool operator==(const Triangle& t,const Rectangle& r){return t.getArea()==r.getArea();}
bool operator!=(const Triangle& t,const Rectangle& r){return t.getArea()!=r.getArea();}
bool operator>=(const Triangle& t,const Rectangle& r){return t.getArea()>=r.getArea();}
bool operator<=(const Triangle& t,const Rectangle& r){return t.getArea()<=r.getArea();}
bool operator>(const Triangle& t,const Rectangle& r){return t.getArea()>r.getArea();}
bool operator<(const Triangle& t,const Rectangle& r){return t.getArea()<r.getArea();}


bool operator==(const Triangle& t,const Circle& c){return t.getArea()==c.getArea();}
bool operator!=(const Triangle& t,const Circle& c){return t.getArea()!=c.getArea();}
bool operator>=(const Triangle& t,const Circle& c){return t.getArea()>=c.getArea();}
bool operator<=(const Triangle& t,const Circle& c){return t.getArea()<=c.getArea();}
bool operator>(const Triangle& t,const Circle& c){return t.getArea()>c.getArea();}
bool operator<(const Triangle& t,const Circle& c){return t.getArea()<c.getArea();}



ComposedShape::ShapeElem::ShapeElem(const Rectangle& r): type(Shape::rect), object(new Rectangle(r))
{/* Body left intentionally blank */}
ComposedShape::ShapeElem::ShapeElem(const Circle& c): type(Shape::cir), object(new Circle(c))
{/* Body left intentionally blank */}
ComposedShape::ShapeElem::ShapeElem(const Triangle& t): type(Shape::tri), object(new Triangle(t))
{/* Body left intentionally blank */}
ComposedShape::ShapeElem::ShapeElem(): type(Shape::rect), object(new Rectangle())
{/* Body left intentionally blank */}

ComposedShape::ShapeElem::ShapeElem(const ShapeElem& other)
{
	type = other.type;
	switch(type)
	{
		case Shape::rect : object = new Rectangle(*(Rectangle*)other.object); break;
		case Shape::cir  : object = new Circle(*(Circle*)other.object); 	  break;
		case Shape::tri  : object = new Triangle(*(Triangle*)other.object);   break;
	}

}  
    
ComposedShape::ShapeElem::~ShapeElem()
{	
	switch(type)
	{
		case Shape::rect : delete[] (Rectangle*)object;	 break;
		case Shape::cir  : delete[] (Circle*)object;  break;
		case Shape::tri  : delete[] (Triangle*)object;  break;
	}
}

ostream& operator<<(ostream& outfile, const ComposedShape::ShapeElem& shape)
{
	switch(shape.type)
	{
		case Shape::rect : outfile<<*(Rectangle*)(shape.object); break;
		case Shape::cir  : outfile<<*(Circle*)(shape.object);    break;
		case Shape::tri  : outfile<<*(Triangle*)(shape.object);  break;
	}
	
	return outfile;
}


double ComposedShape::ShapeElem::getArea()const
{
	double area=0.0;
	switch(type)
	{
		case Shape::rect : area = (*(Rectangle*)object).getArea(); break;
		case Shape::cir  : area = (*(Circle*)object).getArea();	   break;
		case Shape::tri  : area = (*(Triangle*)object).getArea();  break;
	}

	return area;
}
double ComposedShape::ShapeElem::getPerimeter()const
{
	double perim=0.0;
	switch(type)
	{
		case Shape::rect : perim = (*(Rectangle*)object).getPerimeter(); break;
		case Shape::cir  : perim = (*(Circle*)object).getPerimeter();	 break;
		case Shape::tri  : perim = (*(Triangle*)object).getPerimeter();  break;
	}

	return perim;	
}

ComposedShape::ShapeElem ComposedShape::ShapeElem::operator=(const ComposedShape::ShapeElem& other)
{
	type = other.type;
	switch(type)
	{
		case Shape::rect : object = new Rectangle(*(Rectangle*)other.object); break;
		case Shape::cir  : object = new Circle(*(Circle*)other.object); 	  break;
		case Shape::tri  : object = new Triangle(*(Triangle*)other.object);   break;
	}

	return *this;
}

void ComposedShape::ShapeElem::setShape(const Rectangle& r)
{
	type = Shape::rect;
	object = new Rectangle(r);
}

void ComposedShape::ShapeElem::setShape(const Circle& c)
{
	type = Shape::cir;
	object = new Circle(c);

}


void ComposedShape::ShapeElem::setShape(const Triangle& t)
{
	type = Shape::tri;
	object = new Triangle(t);
}
