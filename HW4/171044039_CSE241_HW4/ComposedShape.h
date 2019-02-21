/* 
 * ComposedShape.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */


#ifndef COMPOSEDSHAPE_H_
#define COMPOSEDSHAPE_H_

#include <vector>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Polygon.h"

namespace shape_ozmekik
{

	enum class Shape{tri, rect, cir};

	class ComposedShape
	{
	public:
		ComposedShape(const Rectangle& _r1,const Rectangle& _r2);
		ComposedShape(const Rectangle& _r1,const Circle& _c2);
		ComposedShape(const Rectangle& _r1,const Triangle& _t2);
		ComposedShape(const Circle& _c1,const Rectangle& _r2);
		ComposedShape(const Circle& _c1,const Circle& _c2);
		ComposedShape(const Circle& _c1,const Triangle& _t2);
		ComposedShape(const Triangle& _t1,const Rectangle& _r2);
		ComposedShape(const Triangle& _t1,const Circle& _c2);
		ComposedShape(const Triangle& _t1,const Triangle& _t2);
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
		
		void setMainShape(const Rectangle& _r1);
		void setMainShape(const Circle& _c1);
		void setMainShape(const Triangle& _t1);
		inline void setSmallShape(const Rectangle& _r2)		{r2=_r2; small_shape=Shape::rect;}	
		inline void setSmallShape(const Circle& _c2)		{c2=_c2; small_shape=Shape::cir;}
		inline void setSmallShape(const Triangle& _t2)		{t2=_t2; small_shape=Shape::tri;}
		 
		
		inline double getBoxWidth()const 	{ return box_w;}
		inline double getBoxHeight()const 	{ return box_h;}

		inline void setBoxWidth(double w) 	{box_w=w;}
		inline void setBoxHeight(double h) 	{box_h=h;}
		// BoundingBox set as default in constructor due to the main container's
		// sizes. With this setter you can change it arbitrarily. But the overflow 
		// is in the programmer's responsibility. 
			
		void optimalFit();
		// Fits as many as small shape into the main shape. 

		void draw(std::ofstream& outfile)const;
		
		friend std::ostream& operator<<(std::ostream& outfile,const ComposedShape& c);
		/* Pre-Condition:
		 * ofstream file must be empty.
		 * Post-Condition:
		 * Writes the svg code into file.
		 */ 

		void operator+=(const Rectangle& r);
		void operator+=(const Circle& c);
		void operator+=(const Triangle& t);

		const Polygon operator[](unsigned int idx)const; // rvalue.
		Polygon operator[](unsigned int idx); // lvalue.
		inline const std::vector<Polygon>getVector()const{return shape;}

	private:

		// Every shapes(optimized and main) will be kept in vector of polygon.
		std::vector<Polygon> shape;


		// Shape flags to determine which to use. 
		Shape main_shape,small_shape;
		
		// Possible objects for to keep data: 
		//*1s refers to main shape,  *2s refers to small shape.
		Rectangle r1,r2;
		Circle 	  c1,c2;
		Triangle  t1,t2;

		// BoundingBox width and height.
		double box_w,box_h;

		// Starting points for composition, set default(0,0).
		double _x,_y; 

		void findBoundingBox(); 
		const std::vector<Polygon> fitRinR()const;
		const std::vector<Polygon> fitRinC()const;
		const std::vector<Polygon> fitRinT()const;
		const std::vector<Polygon> fitCinR()const;
		const std::vector<Polygon> fitCinC()const;
		const std::vector<Polygon> fitCinT()const;
		const std::vector<Polygon> fitTinR()const;
		const std::vector<Polygon> fitTinC()const;
		const std::vector<Polygon> fitTinT()const;
		
		void appendComposition(ComposedShape& inner,const Rectangle& main,
							 const Rectangle& small,std::vector<Polygon>& v)const;
		void appendComposition(ComposedShape& inner,const Rectangle& main,
							   const Circle& small,std::vector<Polygon>& v)const;
		void appendComposition(ComposedShape& inner, const Rectangle& main,
							   const Triangle& small,std::vector<Polygon>& v)const;

		
		inline void setPosition(double x,double y) {_x=x; _y=y;}

	};

}
#endif /* COMPOSEDSHAPE_H_ */