/* 
 * ComposedShape.h
 * 
 * Created on: Oct 26, 2018
 * Author: Ahmed Semih Özmekik
 */


#ifndef COMPOSEDSHAPE_H_
#define COMPOSEDSHAPE_H_

#include <vector>
#include <typeinfo>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Shape.h"

namespace shape_ozmekik
{

	enum class shape_enum{tri, rect, cir};

	/* Composed Shape class inherits from Shape class, since 
	 * main container shape is shape. And programmer must be aware of 
	 * whatever he or she does to the ComposedShape object with 
	 * polymorphic features, main container shape will get effected.
	 * (i.e ++, --, getArea() or comparisons and so on.)
	 * Composed Shape class has composition with Shape class.
	 * All small shapes kept in main shape, are obviously shapes. */   

	class ComposedShape: public Shape
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
		~ComposedShape();
		ComposedShape(ComposedShape&) throw(std::bad_cast, bad_shape);
		ComposedShape operator=(ComposedShape&)throw(std::bad_cast, bad_shape);
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
		 * Creates a shape composition.
		 */  
		
		void setMainShape(const Rectangle& _r1);
		void setMainShape(const Circle& _c1);
		void setMainShape(const Triangle& _t1);
		void setSmallShape(const Rectangle& _r2);	
		void setSmallShape(const Circle& _c2);
		void setSmallShape(const Triangle& _t2);
		double getBoxWidth()const;
		double getBoxHeight()const;
		void setBoxWidth(double w)throw(bad_size);
		void setBoxHeight(double h)throw(bad_size);
		// BoundingBox set as default in constructor due to the main container's
		// sizes. With this setter you can change it arbitrarily. But the overflowing 
		// of main container in svg screen is in the programmer's responsibility. 
			
		void optimalFit()throw(std::bad_alloc);
		// Fits as many as small shape into the main shape. 
		
		std::ostream& draw(std::ostream& outfile);
		/* Pre-Condition:
		 * ofstream file must be empty.
		 * Post-Condition:
		 * Writes the svg code into file.
		 */ 


		ComposedShape& operator++() override;
		ComposedShape& operator++(int) override; // Postfix.
		ComposedShape& operator--() override;
		ComposedShape& operator--(int) override; // Postfix.
		/* Overloaded ++ operators(both pre and post) for incrementing 
		 * and decrementing the main shape positions by 1.0 		*/

		void operator+=(Shape* _shape);

		const Shape* operator[](int idx)const throw(bad_index); // rvalue.
		Shape* operator[](int idx)throw(bad_index); // lvalue.
		inline const std::vector<Shape*>getVector()const{return shape;}

	private:

		// Every shapes(optimized) will be kept in vector of Shape*.
		std::vector<Shape*> shape;

		// Shape flags to determine which to use. 
		shape_enum main_shape,small_shape;

		// BoundingBox width and height.
		double box_w,box_h;

		// Starting points for composition, set default(0,0).
		double _x,_y; 

		void findBoundingBox(); 
		const std::vector<Shape*> fitRinR()const;
		const std::vector<Shape*> fitRinC()const;
		const std::vector<Shape*> fitRinT()const;
		const std::vector<Shape*> fitCinR()const;
		const std::vector<Shape*> fitCinC()const;
		const std::vector<Shape*> fitCinT()const;
		const std::vector<Shape*> fitTinR()const;
		const std::vector<Shape*> fitTinC()const;
		const std::vector<Shape*> fitTinT()const;
		
		void appendComposition(ComposedShape& inner,const Rectangle& main,
							 const Rectangle& small,std::vector<Shape*>& v)const;
		void appendComposition(ComposedShape& inner,const Rectangle& main,
							   const Circle& small,std::vector<Shape*>& v)const;
		void appendComposition(ComposedShape& inner, const Rectangle& main,
							   const Triangle& small,std::vector<Shape*>& v)const;

		
		inline void setPosition(double x,double y) {_x=x; _y=y;}

		Rectangle r1,r2;
		Circle 	  c1,c2;
		Triangle  t1,t2;
		/* Possible objects for to keep data: 
		 * *1s refers to main shape,  *2s refers to small shape.
		 * All those datas used for the main algoritm of this 
		 * class which is optimalfit(). *1s or *2s
		 * is not actually a reference to real main shape or 
		 * small shapes given in contructor. Again, they are used 
		 * for better traitment in optimalFit() since almost everything 
		 * about the shape is needed in optimalFit() and being spesific 
		 * for each kind of shape must needed to implement the optimalFit(). 
		 * Real main shape actually is the ComposedShape and real small shapes
		 * are kept in Shape* vector; treat them in that way. */

	};

}
#endif /* COMPOSEDSHAPE_H_ */
