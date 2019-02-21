/* 
 * Rectangle.h
 * 
 * Created on: Oct 26, 2018
 * Revisited on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */


#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <iostream>
#include <fstream>
#include "Shape.h"


namespace shape_ozmekik
{
	class Rectangle: public Shape
	{
	public:
		Rectangle(double w=50.0,double h=50.0, double _x=0.0, double _y=0.0)throw(bad_size);
		/* Pre-Condition: 
		 * Default: width and height as  50.0 and position as (0,0).
		 * Default: Rotate flag set to false. 
		 * Default: Fill flag set to false.
		 * Position is the top left corner of rectangle.
		 * w and h values must be positive numbers. 
		 * Post-Condition:
		 * Initializes rectangle with safe parameters.
		 */  
		


		double getWidth()const;
		double getHeight()const;
		double getX()const;
		double getY()const;
		bool getRotate()const;
		bool getFill() const;
		void setWidth(double w)throw(bad_size);
		void setHeight(double h)throw(bad_size);
		void setRotate(bool r);
		void setFill(bool f);
		void setPosition(double _x, double _y);
		/* Getters and setters */
		
		void swapEdges();

		Rectangle& operator++() override;
		Rectangle& operator++(int) override; // Postfix version.
		Rectangle& operator--() override;
		Rectangle& operator--(int) override; // Postfix version.
		/* Overloaded ++ operators(both pre and post) for incrementing 
		 * and decrementing the shape positions by 1.0 		*/

		Rectangle operator+(double size)const;
		Rectangle operator-(double size)const;
 

		std::ostream& draw(std::ostream&); 

		inline static double getTotalArea(){return total_area;} 
		inline static double getTotalPerimeter(){return total_perim;}

	private:
		double width,height;
		double x,y; // position
		bool rotate; // true for to rotate. (by 90 degress around position(x,y))
		bool fill; // true for fill inside the shape with color.
		static double total_area,total_perim; 
	};

}
#endif /* RECTANGLE_H_ */