/* 
 * Triangle.h
 * 
 * Created on: Oct 26, 2018
 * Revisited on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */


#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Shape.h"
#include <iostream>
#include <fstream>
#include <cmath>

namespace shape_ozmekik
{

	class Triangle : public Shape
	{ 
	public:
		Triangle(double len=50.0, double _x=0.0, double _y=0.0) throw(bad_size);
		/* Pre-Condition:
		 * Default: a length of a equilateral triangle must be positive number.
		 * Otherwise, exceptions is thrown.
		 * Position is the top corner of triangle. Other two corners of the 
		 * triangle is either in below or above, depending on the rotate flag. 
		 * Post-Condition:
		 * Initializes the triangle with safe params. 
		 */

		Triangle& operator++() override;
		Triangle& operator++(int) override; // Postfix.
		Triangle& operator--() override;
		Triangle& operator--(int) override; // Postfix.
		/* Overloaded ++ operators(both pre and post) for incrementing 
		 * and decrementing the shape positions by 1.0 		*/

		double getLength() const;
		double getX()const;
		double getY()const;
		bool getRotate()const;
		bool getFill() const;

		void setPosition(double _x, double _y);
		void setRotate(bool r);
		void setFill(bool f);
		void setLength(double len) throw(bad_size); 

		
		Triangle operator+(double size)const;
		Triangle operator-(double size)const;

		std::ostream& draw(std::ostream&); 

		inline static double getTotalArea(){return total_area;} 
		inline static double getTotalPerimeter(){return total_perim;}

	private:
		double length;
		double x,y;
		bool rotate; // true for rotate around top corner of itself by 180 degrees	
		bool fill; // true for fill inside the shape with color.
		static double total_area,total_perim;
	};
}
#endif // TRIANGLE_H_