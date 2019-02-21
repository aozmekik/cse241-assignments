/* 
 * PolygonVect.h
 * 
 * Created on: Dec 18, 2018
 * Author: Ahmed Semih Özmekik
 */

#ifndef POLYGONVECT_H
#define POLYGONVECT_H

#include <vector>
#include <iostream>
#include <typeinfo> // bad_cast
#include "Polygon.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"


namespace shape_ozmekik
{
	class PolygonVect : public Polygon
	{
		public:
			PolygonVect(const Rectangle&);
			PolygonVect(const Circle&);
			PolygonVect(const Triangle&);

			PolygonVect(Shape* shape) throw(std::bad_cast, bad_shape);
			/* For a given shape, after downcasting to some particular
			 * shape, it converts this shape into a polygonVect object.
			 * This constructor is mainly used in global convertAll() func, 
			 * Since it returns vector of shapes(polygons), you may want to
			 * use it instead of directly dealing with this constructor 
			 * Bad_cast exception thrown because of dynamic_cast usage. */     

			/* Parsing constructors from shapes */
			PolygonVect();

			const Polygon::Point2D& operator[](int idx)const throw(bad_index) override; /* rvalue */
			Polygon::Point2D& operator[](int idx) throw(bad_index) override; /* lvalue */

			virtual std::ostream& draw(std::ostream&) override;

			void setPoint(const Rectangle&);
			void setPoint(const Circle&);
			void setPoint(const Triangle&);
			/* Pre-Condition:
			 * You should be aware of that setting a brand new object 
			 * to a Polygon makes your old data lost.
			 * Post-Condition:
			 * Creates a Polygon with a new list of 2D points due 
			 * to given object.
			 */

			PolygonVect& operator++() override;
			PolygonVect& operator++(int) override; /* Postfix */
			PolygonVect& operator--() override;
			PolygonVect& operator--(int) override; /* Postfix */


		private:
			std::vector<Polygon::Point2D> point;
	};

	

	std::vector<Shape*> convertAll(std::vector<Shape*> shape) throw(std::bad_alloc); 

}
#endif /*POLYGONVECT_H */