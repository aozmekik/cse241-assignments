/* Polyline.h
 *
 * Created on: Nov 18, 2018
 * Author : Ahmed Semih Özmekik
 * *******************************/
 

#include "Polyline.h"

namespace shape_ozmekik
{

	using std::endl;

	Polyline::Polyline(const Polygon& p):polygon(p), header(false)
	{/* intentionally left blank */ }

	Polyline::Polyline():header(false)
	{/*intentionally left blank*/}

	const Polygon::Point2D& Polyline::operator[](unsigned int idx)const
	{
		return polygon[idx];
	}

	Polygon::Point2D& Polyline::operator[](unsigned int idx)
	{
		return polygon[idx];
	} 

	bool Polyline::operator==(const Polyline& other)const
	{
		return polygon == other.getPolygon();
	}

	bool Polyline::operator!=(const Polyline& other)const
	{
		return polygon != other.getPolygon(); 
	}

	const Polyline Polyline::operator+(const Polyline& other)const
	{

		return Polyline(polygon + other.getPolygon());

	}

	/* Polyline differs from Polygon here */ 
	std::ostream& operator<<(std::ostream& outfile,const Polyline& polyline)
	{

		// default height and width, for printing singular polygons 
		if(polyline.getHeader()) 
		{
			outfile<<"<svg version=\"1.1\"" <<std::endl<< "baseProfile=\"full\"" <<std::endl
			<<"width=\""<<500<< "\" height=\""<<500<<"\""
			<<" xmlns=\"http://www.w3.org/2000/svg\">"<<std::endl;
		}

		outfile<<"<polyline points=\"";
		for(unsigned int i=0;i<polyline.getSize();i++)
			outfile<<polyline[i].getX()<<","<<polyline[i].getY()<<" ";

		outfile<<"\""<<" style=\"fill:none;stroke:black;\" />";

		if(polyline.getHeader())	outfile<<endl<<"</svg>";

		return outfile;
	}

	inline const Polygon& Polyline::getPolygon()const
	{
		return polygon;
	}

	inline unsigned int Polyline::getSize()const
	{
		return polygon.getSize();
	}

	inline bool Polyline::getHeader()const
	{
		return header;
	}

	void Polyline::setHeader(bool h)
	{
		header = h;
	}

	void Polyline::setPoint(const Polygon& p)
	{
		polygon = p;
	}

}