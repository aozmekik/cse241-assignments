/* 
 * Circle.h
 * 
 * Created on: Oct 26, 2018
 * Revisited on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */


#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"
#include <fstream>

namespace shape_ozmekik
{

	class Circle: public Shape
	{
	public:
		Circle(double r=50.0, double _x=0.0, double _y=0.0)throw(bad_size);
		/* Pre-Condition:
		 * Default: r=50, center at (0,0)
		 * r(radius) must be positive number.
		 * Position is at center.
		 * Post-Condition:
		 * Initializes circle with safe parameters.
		 */
		double getRadius() const;
		bool getFill() const;
		double getX()const;
		double getY()const;
		void setRadius(double r)throw(bad_size);
		void setPosition(double _x, double _y);
		void setFill(bool f);
		

		/* Operator overloadings. */

		Circle& operator++() override ; 
		Circle& operator++(int) override ; // Postfix version. 
		Circle& operator--() override; 
		Circle& operator--(int) override; // Postfix version.
		/* Overloaded ++ operators(both pre and post) for incrementing 
		 * and decrementing the shape positions by 1.0 		*/
		
		Circle operator+(double size)const;
		Circle operator-(double size)const;

		// operator << overloading for output to ofstream
		std::ostream& draw(std::ostream& outfile)override;

		inline static double getTotalArea(){return total_area;} 
		inline static double getTotalPerimeter(){return total_perim;}


	private:
		double radius;
		double x,y;
		bool fill; // true for fill inside the shape with color. 
		static double total_area,total_perim; // total created object
	};
}


#endif /* CIRCLE_H_ */ 
