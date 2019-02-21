/* 
 * PolygonDyn.h
 * 
 * Created on: Dec 18, 2018
 * Author: Ahmed Semih Özmekik
 */



#ifndef POLYGONDYN_H
#define POLYGONDYN_H

#include <iostream>
#include <ostream>
#include "Polygon.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"


namespace shape_ozmekik
{

	class PolygonDyn : public Polygon
	{
		public:
			PolygonDyn(const Polygon::Point2D&) throw(std::bad_alloc);
			/* Constructor for automatic type conversion conventions. */
			PolygonDyn();
			
			PolygonDyn(const Rectangle&) throw(std::bad_alloc);
			PolygonDyn(const Circle&) throw(std::bad_alloc);
			PolygonDyn(const Triangle&) throw(std::bad_alloc);
			/* After all, shapes are combination of 2D points.	   *
			 * Constructors parse the given shapes into 2D points. */

			PolygonDyn(const PolygonDyn&) throw(std::bad_alloc); 
			~PolygonDyn();
			const PolygonDyn& operator=(const PolygonDyn&)throw(std::bad_alloc);
			/* Changing the behavior of Big Three due to Deep Copy allocations  *
		     * and deallocations. 												*/ 	


			const Polygon::Point2D& operator[](int idx)const throw(bad_index) override; /* rvalue */
			Polygon::Point2D& operator[](int idx) throw(bad_index) override; /* lvalue */

			PolygonDyn operator+(const PolygonDyn&)const throw(std::bad_alloc);
			/* Adds two PolygonDyns by concatenating the points, returns new object*/

			std::ostream& draw(std::ostream&)override; /* .svg output */

			PolygonDyn& operator++()override;
			PolygonDyn& operator++(int)override; /* Postfix */
			PolygonDyn& operator--()override;
			PolygonDyn& operator--(int)override; /* Postfix */

			void setPoint(const Rectangle&)throw(std::bad_alloc);
			void setPoint(const Circle&)throw(std::bad_alloc);
			void setPoint(const Triangle&)throw(std::bad_alloc);
			/* Pre-Condition:
			 * You should be aware of that setting a brand new object 
			 * to a PolygonDyn makes your old data being deallocated, therefore lost.
			 * Post-Condition:
			 * Creates a PolygonDyn with a new list of 2D points due 
			 * to given object.
			 */

		private:
			PolygonDyn::Point2D *point;
	};
}

#endif /* POLYGONDYN_H */