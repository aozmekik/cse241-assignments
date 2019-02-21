/* 
 * ComposedShape.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */

#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include <vector>

using namespace std;

enum class Shape{tri, rect, cir};

#ifndef COMPOSEDSHAPE_H_
#define COMPOSEDSHAPE_H_

class ComposedShape
{
public:
	ComposedShape(const Rectangle& r1,const Rectangle& r2);
	ComposedShape(const Rectangle& r1,const Circle& c2);
	ComposedShape(const Rectangle& r1,const Triangle& t2);
	ComposedShape(const Circle& c1,const Rectangle& r2);
	ComposedShape(const Circle& c1,const Circle& c2);
	ComposedShape(const Circle& c1,const Triangle& t2);
	ComposedShape(const Triangle& t1,const Rectangle& r2);
	ComposedShape(const Triangle& t1,const Circle& c2);
	ComposedShape(const Triangle& t1,const Triangle& t2);
	ComposedShape();
	/* Pre-Condition:
	 * First param is the main shape and the second is small shape.
	 * Default: Visibility of main shape set as true.
	 * User must know that in svg coordinate system -y = y(due to cartesian
	 * coordinate system.) And (_x,_y) are the coordinates of composed shape
	 * which set as the main container shape's positions. 
	 * Simply: main container's coordinates is composed shape's coordinates.
	 * If your position's are not positive which is valid, then you may
	 * not have the full view of your composed shape.
	 * Use the setBox*() funcs to gain a full view if necessary. 
	 * Post-Condition:
	 * Creates a shape composition
	 */  
	
	inline void setMainShape(const Rectangle& _r1) 		{r1=_r1; main_shape=Shape::rect;}
	inline void setMainShape(const Circle& _c1)  		{c1=_c1; main_shape=Shape::cir;}
	inline void setMainShape(const Triangle& _t1)		{t1=_t1; main_shape=Shape::tri;}
	inline void setSmallShape(const Rectangle& _r2)		{r2=_r2; small_shape=Shape::rect;}	
	inline void setSmallShape(const Circle& _c2)		{c2=_c2; small_shape=Shape::cir;}
	inline void setSmallShape(const Triangle& _t2)		{t2=_t2; small_shape=Shape::tri;}
	 
	
	inline double getBoxWidth()const 	{ return box_w;}
	inline double getBoxHeight()const 	{ return box_h;}

	inline const vector<Rectangle> getVectorR()const 
	{ if(small_shape != Shape::rect) {cout<<"Wrong Vector!!"; exit(1);}
		return small_r;
	}
	inline const vector<Circle> getVectorC()const
	{ if(small_shape != Shape::cir) {cout<<"Wrong Vector!!"; exit(1);}
		return small_c;
	}
	inline const vector<Triangle> getVectorT()const
	{ if(small_shape != Shape::tri) {cout<<"Wrong Vector!!"; exit(1);}
		return small_t;
	}
	// Pre-Condition:
	// You need to call the function with certain
	// type which is your smaller shape type.
	// Post-Condition:
	// Returns the packed list of small shape.   

	inline int getTotalShape()const {return total_shape;}
	inline double getRemainderArea()const {return empty_area;}

	inline void setBoxWidth(double w) 	{box_w=w;}
	inline void setBoxHeight(double h) 	{box_h=h;}
	// BoundingBox set as default in constructor due to the main container's
	// sizes. With this setter you can change it arbitrarily. But the overflow 
	// is in the programmer's responsibility. 
		
	void optimalFit();
	// Fits as many as small shape into the main shape. 

	void draw(ofstream& outfile)const;
	/* Pre-Condition:
	 * ofstream file must be empty.
	 * Post-Condition:
	 * Writes the svg code into file.
	 */ 
private:
	// Shape flags to determine which to use. 
	Shape main_shape,small_shape;

	// optimized small shapes will be kept in vector.
	vector<Rectangle> small_r;
	vector<Circle> 	  small_c;
	vector<Triangle>  small_t; 

	// Possible objects: 
	//*1s refers to main shape,  *2s refers to small shape.
	Rectangle r1,r2;
	Circle 	  c1,c2;
	Triangle  t1,t2;

	// BoundingBox width and height.
	double box_w,box_h;

	unsigned int total_shape; // Total fitted shape into main shape.
	double empty_area; 

	double _x,_y; // Starting points for composition, set default(0,0).

	void findBoundingBox(); 
	const vector<Rectangle> fitRinR()const;
	const vector<Rectangle> fitRinC()const;
	const vector<Rectangle> fitRinT()const;
	const vector<Circle> fitCinR()const;
	const vector<Circle> fitCinC()const;
	const vector<Circle> fitCinT()const;
	const vector<Triangle> fitTinR()const;
	const vector<Triangle> fitTinC()const;
	const vector<Triangle> fitTinT()const;


	int totalRinR(double w, double h)const;
	// Returns sum of packed r2 in the r1 before calculating anything

	static double circleFunc(double y, const Circle& c, bool small);
	static bool isInsideCircle(double x, double y, const Circle& c);

	
	void appendComposition(ComposedShape& inner,const Rectangle& main,
						 const Rectangle& small,vector<Rectangle>& v)const;
	void appendComposition(ComposedShape& inner,const Rectangle& main,
						   const Circle& small,vector<Circle>& v)const;
	void appendComposition(ComposedShape& inner, const Rectangle& main,
						   const Triangle& small,vector<Triangle>& v)const;

	
	inline void setPosition(double x,double y) {_x=x; _y=y;}


		
};


#endif /* COMPOSEDSHAPE_H_ */