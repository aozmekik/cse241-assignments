/* 
 * Polygon.h
 * 
 * Created on: Dec 18, 2018
 * Author: Ahmed Semih Özmekik
 */



#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <ostream>
#include "Shape.h"


namespace shape_ozmekik
{

	class Polygon : public Shape
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

			Polygon(int _size=0)throw(bad_size);
 
			virtual ~Polygon() = default;
																
			virtual const Polygon::Point2D& operator[](int idx)const throw(bad_index) = 0; /* rvalue */
			virtual Polygon::Point2D& operator[](int idx) throw(bad_index) = 0; /* lvalue */

			virtual Shape& operator++() = 0;
			virtual Shape& operator++(int) = 0; /* Postfix */
			virtual Shape& operator--() = 0;
			virtual Shape& operator--(int) = 0; /* Postfix */

			virtual std::ostream& draw(std::ostream&) = 0; /* .svg output */

			int getSize()const;

		protected:
			void setSize(int _size);
		private:
			  int size;
			  
	};

	void printPoly(std::ostream& outfile, std::vector<Shape*>shape);


	

	
}

#endif
