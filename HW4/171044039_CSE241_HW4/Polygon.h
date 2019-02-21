#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>
#include <ostream>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"


namespace shape_ozmekik
{

	class Polygon
	{
		public:
			
			class Point2D
			{
				public:
					Point2D(double px=0.0, double py=0.0);
					void setPoint(double px=0.0, double py=0.0);
					double getX()const;
					double getY()const;
					bool operator==(Point2D)const;
					bool operator!=(Point2D)const;

				private:
					double x,y;

			};/* Inner Point2D class, representing 2D points in coordinate system.*/

			Polygon();
			Polygon(const std::vector<Polygon::Point2D>&); 
			/* Point can be given as a vector of points.*/ 

			Polygon(const Polygon::Point2D&);
			/* Constructor for automatic type conversion conventions. */
			
			Polygon(const Rectangle&);
			Polygon(const Circle&);
			Polygon(const Triangle&);
			/* After all, shapes are combination of 2D points.	   *
			 * Constructors parse the given shapes into 2D points. */

			Polygon(const Polygon&); 
			~Polygon();
			const Polygon& operator=(const Polygon&);
			/* Changing the behavior of Big Three due to Deep Copy allocations  *
		     * and deallocations. 												*/ 	


			const Polygon::Point2D& operator[](unsigned int idx)const; /* rvalue */
			Polygon::Point2D& operator[](unsigned int idx); /* lvalue */

			bool operator==(const Polygon&)const; 
			bool operator!=(const Polygon&)const; 
			/* Polygon comparison operations.*/

			Polygon operator+(const Polygon&)const;
			/* Adds two polygons by concatenating the points, returns new object*/

			friend std::ostream& operator<<(std::ostream&,const Polygon&); /* .svg output */

			unsigned int getSize()const;
			bool getHeader()const;
			/* Accessor of members */

			void setPoint(const std::vector<Polygon::Point2D>&);
			void setPoint(const Rectangle&);
			void setPoint(const Circle&);
			void setPoint(const Triangle&);
			/* Pre-Condition:
			 * You should be aware of that setting a brand new object 
			 * to a polygon makes your old data being deallocated, therefore lost.
			 * Post-Condition:
			 * Creates a polygon with a new list of 2D points due 
			 * to given object.
			 */
			void setHeader(bool);
			/* Pre-Condition:
			 * Set this true if you want to just print a single .svg file
			 * Otherwise, you can draw into same file with composition. 
			 * Post-Condition:
			 * Prints .svg header and closes the svg file (</svg>) 
			 */
			/* Mutator of members */

		private:
			Polygon::Point2D *point;
			unsigned int size;
			bool header; /* .svg format header, false for default */ 

	};
}

#endif