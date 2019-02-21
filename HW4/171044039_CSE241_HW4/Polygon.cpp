#include "Polygon.h"
#include <cmath> // sqrt 
#include <cmath> // sin and cos funcs.

namespace shape_ozmekik
{
 
	using std::endl;


	Polygon::Point2D::Point2D(double px, double py): x(px), y(py)
	{/* intentionally left blank */}


	void Polygon::Point2D::setPoint(double px, double py)
	{
		x = px;
		y = py;
	}

	inline double Polygon::Point2D::getX()const{return x;};
	inline double Polygon::Point2D::getY()const{return y;};

	inline bool Polygon::Point2D::operator==(Point2D other)const
	{	return ((x==other.getX())?y==other.getY():false);	}

	inline bool Polygon::Point2D::operator!=(Point2D other)const
	{   return !(*this==other);}



	Polygon::Polygon(const std::vector<Polygon::Point2D>& vectorPoint)
	: size(vectorPoint.size()),
	  header(false)
	{
		point = new Polygon::Point2D[size];
		for(unsigned int i=0;i<size;++i)
			point[i] = vectorPoint[i];
	}

	Polygon::Polygon(): point(nullptr), size(0), header(false) // No parameter constructor.
	{/* intentionally left blank */}

	Polygon::Polygon(const Polygon& other)
	{	
		size = other.getSize();
		point = new Polygon::Point2D[size]; /* allocating */
		header = other.getHeader();

		for(unsigned int i=0;i<size;++i)
			point[i] = other[i]; 
	}


	Polygon::~Polygon(){ delete[] point; } /* free the whole dynamic array */

	Polygon::Polygon(const Polygon::Point2D& singlePoint)
	: size(1),
	  header(false)
	{
		point = new Polygon::Point2D;
		point[0] = singlePoint; 
	}

	Polygon::Polygon(const Rectangle& rectangle)
	: size(4),
	  header(false)
	{
		point = new Polygon::Point2D[size]; /* 4 points for 4 corners */

		const double x = rectangle.getX();
		const double y = rectangle.getY();

		// Drawing route: 
		/* (x,y) left-most corner-> go to right -> go down -> then go left */ 
		point[0].setPoint(x,y);
		point[1].setPoint(x+rectangle.getWidth(),y);
		point[2].setPoint(x+rectangle.getWidth(),y+rectangle.getHeight());
		point[3].setPoint(x,y+rectangle.getHeight());
	}

	Polygon::Polygon(const Circle& circle)
	: size(100),
	  header(false)
	{
		point = new Polygon::Point2D[size]; /* 100 equal interval for circle*/

		const double PI = 3.14159; //value of pi to determine circle's point.
		double x=0.0,y=0.0; // coord. 

		for(unsigned int i=0;i<size;++i)
		{
			x = circle.getX() + cos(2.0*i*PI/size)*circle.getRadius();
			y = circle.getY() + sin(2.0*i*PI/size)*circle.getRadius();
			point[i].setPoint(x,y);
		}	

	}

	Polygon::Polygon(const Triangle& triangle)
	: size(3),
	  header(false)
	{
		point = new Polygon::Point2D[size]; /* 3 points for 3 corners */

		const double x = triangle.getX();
		const double y = triangle.getY();

		//Drawing route:
		/* (x,y) top corner -> go to down and right -> go left */
		point[0].setPoint(x,y);
		if(triangle.getRotate())
		{
			point[1].setPoint(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*sqrt(3)/2.0); 
			point[2].setPoint(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*sqrt(3)/2.0);
		}
		else
		{
			point[1].setPoint(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
								 y+triangle.getLength()*sqrt(3)/2.0); 
			point[2].setPoint(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y+triangle.getLength()*sqrt(3)/2.0);
		}
	}	

	const Polygon& Polygon::operator=(const Polygon& other)
	{
		if(*this == other)
			return *this;
		if(other.getSize() == size) // No need for allocation, just copy.
		{
			for(unsigned int i=0;i<size;i++)
				point[i] = other[i];
		}
		else
		{
			delete[] point;  

			size = other.getSize(); 
			point = new Polygon::Point2D[size];

			for(unsigned int i=0;i<size;++i)
				point[i] = other[i];
		}
		header = other.getHeader();

		return *this;
	}	

	const Polygon::Point2D& Polygon::operator[](unsigned int idx)const
	{
		return point[idx];
	}

	Polygon::Point2D& Polygon::operator[](unsigned int idx)
	{
		return point[idx];
	}	

	bool Polygon::operator==(const Polygon& other)const
	{
		
		bool equal = true;
		if(size!=other.getSize())
			equal = false;
		else
		{
			for(unsigned int i=0;i<size && equal;i++)
				equal = point[i] == other[i];
		}	 

		return equal;
	}

	bool Polygon::operator!=(const Polygon& other)const
	{
		return !(*this == other);
	}


	Polygon Polygon::operator+(const Polygon& other)const
	{
		std::vector<Polygon::Point2D> newPoint;
		newPoint.reserve(size+other.getSize());

		/* Concatenating the points in newPoint vector. */
		for(unsigned int i=0;i<size;i++)
			newPoint.push_back(point[i]);
		for(unsigned int i=0;i<other.getSize();i++)
			newPoint.push_back(other[i]);

		return	Polygon(newPoint);
	}

	std::ostream& operator<<(std::ostream& outfile,const Polygon& polygon)
	{
		
		// default height and width, for printing singular polygons. 
		
		if(polygon.getHeader()) 
		{
			outfile<<"<svg version=\"1.1\"" <<std::endl<< "baseProfile=\"full\"" <<std::endl
			<<"width=\""<<500<< "\" height=\""<<500<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<std::endl;
		}

		outfile<<std::endl<<"<polygon points=\"";
		for(unsigned int i=0;i<polygon.getSize();++i)
			outfile<<polygon[i].getX()<<","<<polygon[i].getY()<<" ";

		outfile<<"\""<<" style=\"fill:cornflowerblue;";
		outfile<<"stroke:black;stroke-width:1.6\" />";


		if(polygon.getHeader())	outfile<<endl<<"</svg>";

		return outfile;
	}

	inline unsigned int Polygon::getSize()const
	{
		return size;
	}

	
	inline bool Polygon::getHeader()const
	{
		return header;
	}

	void Polygon::setHeader(bool h)
	{
		header = h;
	}

	void Polygon::setPoint(const std::vector<Polygon::Point2D>& vectorPoint)
	{
		/* deallocating is handled in operator= func. */
		*this = Polygon(vectorPoint);

	}

	void Polygon::setPoint(const Rectangle& rectangle)
	{

		*this = Polygon(rectangle); 
	}

	void Polygon::setPoint(const Circle& circle)
	{
		*this = Polygon(circle);
	}

	void Polygon::setPoint(const Triangle& triangle)
	{
		*this = Polygon(triangle);
	}

}

