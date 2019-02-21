#ifndef POLYLINE_H
#define POLYLINE_H
#include "Polygon.h"

/* Polyline class gets all it's functionality from Polygon since they are almost 		*
 * identical. In most of the member functions, Polyline reaches all the points it       *
 * has, through Polygon. Since the constructor takes Polygon object, thanks to 		*
 * automatic type conversion, you can give any other shape(rectangle,circle,triangle)   *
 * and point vector to constructor. 													*/    

namespace shape_ozmekik
{

	class Polyline
	{
		public:
			Polyline(const Polygon&);
			Polyline();

			const Polygon::Point2D& operator[](unsigned int idx)const; /* rvalue */
			Polygon::Point2D& operator[](unsigned int idx); /* lvalue */

			bool operator==(const Polyline&)const; 
			bool operator!=(const Polyline&)const; 

			const Polyline operator+(const Polyline&)const;
			/* Adds two polyline by concatenating the points, returns new object*/		

			friend std::ostream& operator<<(std::ostream&,const Polyline&); /* .svg output */

			unsigned int getSize()const;
			bool getHeader()const;
			/* Accessor of members */

			void setHeader(bool); 
			/* Pre-Condition:
			 * Set this true if you want to just print a single .svg file
			 * Otherwise, you can draw into same file with composition. 
			 * Post-Condition:
			 * Prints .svg header and closes the svg file (</svg>) 
			 */
			void setPoint(const Polygon&);
			/* Mutators of members */

		private:
			Polygon polygon; /* points kept in polygon object*/
			const Polygon& getPolygon()const;
			bool header;

	};
}

#endif