/* 
 * ComposedShape.h
 * 
 * Created on: Oct 26, 2018
 * Edited on: Nov 18, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "ComposedShape.h"
#include <cmath>



namespace 
{
	int totalRinR(double w, double h, shape_ozmekik::Rectangle r2)
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

	double circleFunc(double y, const shape_ozmekik::Circle& c, bool small)
	{
		double x;
		if(small)
			x = -sqrt(c.getRadius()*c.getRadius()-((y-c.getY())*(y-c.getY())))+c.getX(); 
		else
			x =  sqrt(c.getRadius()*c.getRadius()-((y-c.getY())*(y-c.getY())))+c.getX();

		return x;
	}

	bool isInsideCircle(double x, double y, const shape_ozmekik::Circle& c)
	{
		bool inside;
		if(c.getRadius()*c.getRadius()  <  (x-c.getX())*(x-c.getX())+(y-c.getY())*(y-c.getY()))
			inside = false;
		else
			inside = true;
		return inside;
	}

}

namespace shape_ozmekik
{


	ComposedShape::ComposedShape(const Rectangle& _r1,const Rectangle& _r2)
		: Shape(_r1)
		, main_shape(shape_enum::rect)
		, small_shape(shape_enum::rect)
		, _x(r1.getX())
		, _y(r1.getY()) 
		, r1(_r1)
		, r2(_r2)
	{
		r1.setHeader(false);
		r2.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}

	ComposedShape::ComposedShape(const Rectangle& _r1,const Circle& _c2)
		: Shape(_r1)
		, main_shape(shape_enum::rect)
		, small_shape(shape_enum::cir)
		, _x(r1.getX())
		, _y(r1.getY()) 
		, r1(_r1)
		, c2(_c2)
	{
		r1.setHeader(false);
		c2.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}

	ComposedShape::ComposedShape(const Rectangle& _r1,const Triangle& _t2)
		: Shape(_r1)
		, main_shape(shape_enum::rect)
		, small_shape(shape_enum::tri)
		, _x(r1.getX())
		, _y(r1.getY())
		, r1(_r1)
		, t2(_t2)
	{
		r1.setHeader(false);
		t2.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}

	ComposedShape::ComposedShape(const Circle& _c1,const Rectangle& _r2)
		: Shape(_c1)
		, main_shape(shape_enum::cir)
		, small_shape(shape_enum::rect)
		, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
		, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
		, r2(_r2)
		, c1(_c1)
	{
		r2.setHeader(false);
		c1.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}

	ComposedShape::ComposedShape(const Circle& _c1,const Circle& _c2)
		: Shape(_c1)
		, main_shape(shape_enum::cir)
		, small_shape(shape_enum::cir)
		, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
		, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
		, c1(_c1)
		, c2(_c2)
	{
		c1.setHeader(false);
		c2.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}
	ComposedShape::ComposedShape(const Circle& _c1,const Triangle& _t2)
		: Shape(_c1)
		, main_shape(shape_enum::cir)
		, small_shape(shape_enum::tri)
		, _x(c1.getX()-c1.getRadius()/sqrt(2.0))
		, _y(c1.getY()-c1.getRadius()/sqrt(2.0))
		, c1(_c1)
		, t2(_t2)
	{
		c1.setHeader(false);
		c2.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}

	ComposedShape::ComposedShape(const Triangle& _t1,const Rectangle& _r2)
		: Shape(_t1)
		, main_shape(shape_enum::tri)
		, small_shape(shape_enum::rect)
		, _x(t1.getX()-t1.getLength()/2.0)
		, _y(t1.getY())
		, r2(_r2)
		, t1(_t1)
	{
		r2.setHeader(false);
		t1.setHeader(false);
		setHeader(true);
		findBoundingBox();
		

	}

	ComposedShape::ComposedShape(const Triangle& _t1,const Circle& _c2)
		: Shape(_t1)
		, main_shape(shape_enum::tri)
		, small_shape(shape_enum::cir)
		, _x(t1.getX()-t1.getLength()/2.0)
		, _y(t1.getY())
		, c2(_c2)
		, t1(_t1)
	{
		c2.setHeader(false);
		t1.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}

	ComposedShape::ComposedShape(const Triangle& _t1,const Triangle& _t2)
		: Shape(_t1)
		, main_shape(shape_enum::tri)
		, small_shape(shape_enum::tri)
		, _x(t1.getX()-t1.getLength()/2.0)
		, _y(t1.getY())
		, t1(_t1)
		, t2(_t2)
	{
		t1.setHeader(false);
		t2.setHeader(false);
		setHeader(true);
		findBoundingBox();
	}

	// main and small shape set as default rectangle 
	ComposedShape::ComposedShape() : ComposedShape(Rectangle(),Rectangle())
	{/* Body intentionally left empty */}

	
	ComposedShape::~ComposedShape()
	{
		for(auto &s:shape)
			delete s;
	};

	ComposedShape::ComposedShape(ComposedShape& other) throw(std::bad_cast, bad_shape): Shape(*this)
	{
		Rectangle *r;
		Circle *c;
		Triangle *t;


		main_shape = other.main_shape;
		small_shape = other.small_shape;
		box_w = other.box_w;
		box_h = other.box_h;
		_x = other._x;
		_y = other._y;
		r1 = other.r1;
		r2 = other.r2;
		c1 = other.c1;
		c2 = other.c2;
		t1 = other.t1;
		t2 = other.t2;
		/* shallow copies */


		shape.reserve(other.shape.size()); // place reserved for optimization. 
		for(auto &s: other.shape) 
		{	// addresses are pushed due to taxonomy.  

			if((r = dynamic_cast<Rectangle*>(s)))
				shape.push_back(new Rectangle(*r));
			else if((c = dynamic_cast<Circle*>(s)))
				shape.push_back(new Circle(*c));
			else if((t = dynamic_cast<Triangle*>(s)))
				shape.push_back(new Triangle(*t));
			else // invalid shape.
				throw bad_shape();
		}
		/* deep copy of whole vector of shape*  */
	}

	ComposedShape ComposedShape::operator=(ComposedShape& other)throw(std::bad_cast, bad_shape)
	{
		Rectangle *r;
		Circle *c;
		Triangle *t;


		main_shape = other.main_shape;
		small_shape = other.small_shape;
		box_w = other.box_w;
		box_h = other.box_h;
		_x = other._x;
		_y = other._y;
		r1 = other.r1;
		r2 = other.r2;
		c1 = other.c1;
		c2 = other.c2;
		t1 = other.t1;
		t2 = other.t2;
		other.perim = perim;

		for(auto &s : other.shape)// cleaning old stuff 
		{	
			delete s;
			shape.pop_back();
		}

		shape.reserve(other.shape.size());  
		for(auto &s: shape) 
		{	  
			if((r = dynamic_cast<Rectangle*>(s)))
				shape.push_back(new Rectangle(*r));
			else if((c = dynamic_cast<Circle*>(s)))
				shape.push_back(new Circle(*c));
			else if((t = dynamic_cast<Triangle*>(s)))
				shape.push_back(new Triangle(*t));
			else // invalid shape.
				throw bad_shape();
		}

		return *this;
	}



	void ComposedShape::setSmallShape(const Rectangle& _r2)			{r2=_r2; small_shape=shape_enum::rect;}	
	void ComposedShape::setSmallShape(const Circle& _c2)			{c2=_c2; small_shape=shape_enum::cir;}
	void ComposedShape::setSmallShape(const Triangle& _t2)			{t2=_t2; small_shape=shape_enum::tri;}
	inline double ComposedShape::getBoxWidth()const 				{ return box_w;}
	inline double ComposedShape::getBoxHeight()const 				{ return box_h;}
	void ComposedShape::setBoxWidth(double w) throw(bad_size)						
	{	
		if(w<=0) throw bad_size();
		box_w=w;
	}

	void ComposedShape::setBoxHeight(double h) throw(bad_size)
	 {
	 	if(h<=0) throw bad_size();
	 	box_h=h;
	 }

	void ComposedShape::setMainShape(const Rectangle& _r1)
	{
		r1=_r1; 
		main_shape=shape_enum::rect; 
	    _x=_r1.getX(); 
	    _y=_r1.getY();
	} 

	void ComposedShape::setMainShape(const Circle& _c1)  		
	{	
		c1=_c1; 
		main_shape=shape_enum::cir; 
		_x=_c1.getX()-_c1.getRadius()/sqrt(2.0);
	 	_y=_c1.getY()-_c1.getRadius()/sqrt(2.0);

	}
	void ComposedShape::setMainShape(const Triangle& _t1)		
	{	
		t1=_t1; 
		main_shape=shape_enum::tri;
		_x = _t1.getX()-_t1.getLength()/2.0;
		_y = _t1.getY();

	}


	void ComposedShape::optimalFit() throw(std::bad_alloc)
	{
		switch(main_shape)
		{
			case shape_enum::rect: 
				switch(small_shape)
				{
					case shape_enum::rect: shape = fitRinR();break;
					case shape_enum::cir:  shape = fitCinR();break;
					case shape_enum::tri:  shape = fitTinR();break;
				}break;

			case shape_enum::cir:
				switch(small_shape)
				{
					case shape_enum::rect: shape = fitRinC();break;
					case shape_enum::cir:  shape = fitCinC();break;
					case shape_enum::tri:  shape = fitTinC();break;
				}break;

			case shape_enum::tri:
				switch(small_shape)
				{
					case shape_enum::rect: shape = fitRinT();break;
					case shape_enum::cir:  shape = fitCinT();break;
					case shape_enum::tri:  shape = fitTinT();break;
				}break;
		}
	}

	void ComposedShape::operator+=(Shape* _shape){ shape.push_back(_shape);}

	const Shape* ComposedShape::operator[](int idx)const throw(bad_index)
	{
		if(idx<0) throw bad_index();
		return shape[idx];
	} 

	Shape* ComposedShape::operator[](int idx)throw(bad_index)
	{
		if(idx<0) throw bad_index();
		return shape[idx];
	}


	std::ostream& ComposedShape::draw(std::ostream& outfile)
	{	
		// header codes for svg format

		if(getHeader())
		{
			outfile<<"<svg version=\"1.1\"" <<std::endl<< "baseProfile=\"full\"" <<std::endl
			<<"width=\""<<box_w<< "\" height=\""<<box_h<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<std::endl;
		}
		
		switch(main_shape)
		{
			case shape_enum::rect: r1.draw(outfile); break;
			case shape_enum::cir:  c1.draw(outfile); break;
			case shape_enum::tri:  t1.draw(outfile); break;
		}

		for(unsigned int i=0;i<shape.size();++i)
			outfile<<*shape[i];

		if(getHeader()) outfile<<" </svg>"; // end of svg.

		return outfile;
	}

	void ComposedShape::findBoundingBox()
	{
		// doubled the box to prevent the worst case for circle
		switch(main_shape)
		{
			case shape_enum::rect:  
				setBoxWidth(r1.getWidth()); 
				setBoxHeight(r1.getHeight());   
				break;

			case shape_enum::cir:
				setBoxWidth(c1.getRadius()*2.0); // doubled for full view of circle
				setBoxHeight(c1.getRadius()*2.0);   
				break;  
			 
			case shape_enum::tri:   
				setBoxWidth(t1.getLength()); 
				setBoxHeight(t1.getLength());   
		}

		// expanding our box to see the strokes of border edges
		setBoxWidth(getBoxWidth()+100.0);
		setBoxHeight(getBoxHeight()+100.0);
	}

	

	const std::vector<Shape*> ComposedShape::fitRinR()const
	{ 
		Rectangle r(r2); // Temp small shape which we will work on.
		std::vector<Shape*> _shape; // Small shapes. 
		double x,y; // temp positions which we will find later on for small shapes.    

		r.setFill(true); // small shapes will have color.

		// We determine which filling(rotate or not) is better for optimization. 
		if(totalRinR(r1.getWidth(),r1.getHeight(), r2) < 
		   totalRinR(r1.getHeight(),r1.getWidth(), r2))
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
				_shape.push_back(new Rectangle(r));
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
			_shape.push_back(new Rectangle(r));
			filled=true;
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
					_shape.push_back(new Rectangle(r));
				}
				r.setPosition(_x+x,_y+y);
				_shape.push_back(new Rectangle(r));
			}
		}

		return _shape;

	}



	const std::vector<Shape*> ComposedShape::fitRinC()const
	{
		// We fill the imaginary inner rectangles which inside of circle with small rectangles.
		// To do this we must create a composition with rectangular main container.
		// We copy the circle object to shift the wanted area of cartesian coordinate
		// system for better use of circle functions. 
		Rectangle inner_r,r(r2);
		Circle c(c1); 
		ComposedShape inner_shape(inner_r,r);
		std::vector<Shape*> _shape;
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

	const std::vector<Shape*> ComposedShape::fitRinT()const
	{
		// Yet another imaginary composition created. 
		// We again, find the optimal rectangles inside the triangle,
		// Then make them our container, so that we can use fitRinR func.
		Rectangle inner_r,r(r2);
		ComposedShape inner_shape(inner_r,r);
		std::vector<Shape*> _shape;

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

	const std::vector<Shape*> ComposedShape::fitCinR()const
	{
		std::vector<Shape*> _shape;
		Circle c(c2);
		double x,y;

		// pretty straight forward filling with starting from (r,r) 
		c.setFill(true);
		for(y=c.getRadius();y<=r1.getHeight()-c.getRadius();y+=2.0*c.getRadius())
		{
			for(x=c.getRadius();x<=r1.getWidth()-c.getRadius();x+=2.0*c.getRadius())
			{
				c.setPosition(x+_x,y+_y);
				_shape.push_back(new Circle(c));
			}
		}

		return _shape;
	}

	const std::vector<Shape*> ComposedShape::fitCinC()const
	{
		Rectangle inner_r;
		Circle main_c(c1),small_c(c2);
		ComposedShape inner_shape(inner_r,small_c);
		std::vector<Shape*> _shape;
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

	const std::vector<Shape*> ComposedShape::fitCinT()const
	{
		Rectangle inner_r;
		Circle c(c2);
		ComposedShape inner_shape(inner_r,c);
		std::vector<Shape*> _shape;
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

	const std::vector<Shape*> ComposedShape::fitTinR()const
	{
		Triangle t(t2); 
		std::vector<Shape*> _shape;
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
				_shape.push_back(new Triangle(t));
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
				_shape.push_back(new Triangle(t));
				x += t.getLength();
			}
		}

		return _shape;

	}

	const std::vector<Shape*> ComposedShape::fitTinC()const
	{
		Rectangle inner_r;
		Triangle t(t2);
		Circle c(c1);
		ComposedShape inner_shape(inner_r,t);
		std::vector<Shape*> _shape;
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

	const std::vector<Shape*> ComposedShape::fitTinT()const
	{
		Triangle main_t(t1),small_t(t2);
		double x,y;
		double main_h, small_h;  // h of big main triangle
		std::vector<Shape*> _shape;

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
				_shape.push_back(new Triangle(small_t));
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
				_shape.push_back(new Triangle(small_t));
				x+= small_t.getLength();
				small_t.setPosition(x+_x,y+_y);
			}

			width-=small_t.getLength()/2.0;
		}

		return _shape;
	}


	void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
										  const Rectangle& small,std::vector<Shape*>& v)const
	{
		std::vector<Shape*> temp;
		inner.setMainShape(main);
		inner.setSmallShape(small);
		inner.setPosition(small.getX(),small.getY());
		inner.optimalFit();
		temp = inner.getVector();
		v.insert(v.end(), temp.begin(),temp.end());
	}
	void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
										  const Circle& small,std::vector<Shape*>& v)const
	{
		std::vector<Shape*> temp;
		inner.setMainShape(main);
		inner.setSmallShape(small);
		inner.setPosition(small.getX(),small.getY());
		inner.optimalFit();
		temp = inner.getVector();
		v.insert(v.end(), temp.begin(),temp.end());
	}
	void ComposedShape::appendComposition(ComposedShape& inner, const Rectangle& main,
										  const Triangle& small,std::vector<Shape*>& v)const
	{
		std::vector<Shape*> temp;
		inner.setMainShape(main);
		inner.setSmallShape(small);
		inner.setPosition(small.getX(),small.getY());
		inner.optimalFit();
		temp = inner.getVector();
		v.insert(v.end(), temp.begin(),temp.end());
	}


	ComposedShape& ComposedShape::operator++() 
	{
		setPosition(_x+1,_y+1); /* update this */

		return *this;

	}
	ComposedShape& ComposedShape::operator++(int ignore) 
	{

		ComposedShape *composed = new ComposedShape(*this); 

		setPosition(_x+1,_y+1); 

		return *composed;
	}
	
	ComposedShape& ComposedShape::operator--() 
	{
		setPosition(_x-1,_y-1); /* update this */

		return *this;

	}
	ComposedShape& ComposedShape::operator--(int ignore) 
	{

		ComposedShape *composed = new ComposedShape(*this); 

		setPosition(_x-1,_y-1); /* update this */
		
		return *composed;
	}

}
