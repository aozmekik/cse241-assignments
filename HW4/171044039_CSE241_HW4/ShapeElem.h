#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

enum class Shape{tri, rect, cir};

class ShapeElem
{
	public:
		ShapeElem(const Rectangle& r); 
		ShapeElem(const Triangle& t);
		ShapeElem(const Circle& c);
		ShapeElem(const ShapeElem&); // copy constructor for to avoid copying shapes to different pointers.
		ShapeElem();
		~ShapeElem(); // avoiding memory leak.

		void setShape(const Rectangle& r);
		void setShape(const Circle& c);
		void setShape(const Triangle& t);

		double getArea()const;
		double getPerimeter()const;
		inline Shape getType()const {return type;}
		inline void* getObject()const{return object;}

		ShapeElem operator=(const ShapeElem&);

		friend ostream& operator<<(ostream&, const ShapeElem&);

	private:
		Shape type; 
		void* object;

};