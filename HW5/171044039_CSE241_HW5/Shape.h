/* 
 * Shape.h
 * 
 * Created on: Dec 16, 2018
 * Author: Ahmed Semih Özmekik
 */



#ifndef SHAPE_H_
#define SHAPE_H_ 

#include <ostream>
#include <vector>
#include <exception>

namespace shape_ozmekik
{
	class Shape
	{
		public:
			Shape();

			virtual Shape& operator++() = 0;
			virtual Shape& operator++(int) = 0; /* Postfix */
			virtual Shape& operator--() = 0;
			virtual Shape& operator--(int) = 0; /* Postfix */


			virtual std::ostream& draw(std::ostream&) = 0;
 
			double getArea()const;
			double getPerim()const;
			bool getHeader()const;

			void setHeader(bool h);
			/* Pre-Condition:
			 * Set this true if you want to just print a single shape into
			 * single .svg file. Otherwise, you should disable header(which is
			 * the default) and mixed them in the same .svg file. But if you want
			 * to mixed them in the same .svg file you need to provide an .svg header
			 * by yourself. Yet, we provided the needed functions for to achive these kind
			 * of printing situations without dealing with .svg header. Meaning that,
			 * you can use printAll() etc. 
			 * Post-Condition:
			 * True: Prints .svg header and closes the svg file (</svg>)
			 * False: Doesn't print .svg header and does not close the svg file. 
			 */
			/* Mutator of members */



			bool operator!=(Shape& other)const;
			bool operator==(Shape& other)const;
			bool operator>=(Shape& other)const;
			bool operator>(Shape& other)const;
			bool operator<=(Shape& other)const;
			bool operator<(Shape& other)const;
			/* Overloaded comparison operators between two concrete 		  
			 * shapes(Rectangle, Circle, Triangle and so on.).				  
			 * Compares two shape's area.  */				  

			virtual ~Shape() = default;

		protected:
			double area; 
			double perim;
			bool header;

	}; 

	std::ostream& operator<<(std::ostream& outfile, Shape &shape);
	void printAll(std::ostream& outfile, std::vector<Shape*>shape);
	void sortShapes(std::vector<Shape*> &shape);


	class bad_size: public std::exception
	{
		public:
			virtual const char* what() const noexcept override
			{
				return "Negative or zero value was given for size!";
			}
	};

	class bad_index : public std::exception
	{
		public:
			virtual const char* what()const noexcept override
			{
				return "Negative value was given for index!";
			}
	}; 

	class bad_shape : public std::exception
	{
		public:
			virtual const char* what()const noexcept override
			{
				return "Shape is not convertable!";
			}
	};


}

#endif /* SHAPE_H */
