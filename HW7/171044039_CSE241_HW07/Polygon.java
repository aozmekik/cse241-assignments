/** 
 * Represents the Abstract Polygon Class.
 *  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-05
 * @see Shape
*/

import java.awt.Graphics;

public abstract class Polygon implements Shape
{
	private int size; 

	/** 
	 * Gets the area of the Polygon.
     * @return Area of the Polygon.
	*/ 
	abstract public double area();


	/** 
	 * Gets the perimeter of the Polygon.
	 * @return Perimeter of the Polygon.
	*/
	abstract public double perimeter();	


	/**
	 * Compares this Polygon with the specified shape with respect
	 * to their areas.
	 * @param The Shape to be compared.
	 * @return A negative integer, zero, or a positive integer
	 * as this object's area is less than, equal to, 
	 * or greater than the specified object. 
	*/ 
	public int compareTo(Shape other)
	{
		return Double.compare(area(),other.area()); 
	}


	/**
	 * Increments the Polygon positions by 1.0 in both (x,y) plane.
	*/
	abstract public void increment();

	/** 
	 * Decrements the Polygon positions by 1.0 in both (x,y) plane. 
	*/
	abstract public void decrement();

	/** 
	 * Takes a Graphics object as parameter and draws the Polygon. 
	 * This method will be called from the paintComponent method of a 
	 * JPanel object.
	 * @param Graphics object to draw into.
	 * @see JPanel
	 * @see Graphics
	*/
	abstract public void draw(Graphics g);

	/**
	 * Sets size.
	 * Proper SubClass must use the constructor of the 
	 * Polygon to set size.
	 * @param s is size.
	*/
	Polygon(int s)
	{

		size = s;  
	}

	/**
	 * Inner Point2D class represents the 2D point in
	 * coordinate system.
	*/ 
	public class Point2D
	{
		private double x;
		private double y;

		/**
		 * Create 2D point with given x and y value.
		 * @param px is x coordinate.
		 * @param py is y coordinate.
		*/ 
		public Point2D(double px, double py)
		{
			x = px;
			y = py;
		}

		/**
		 * Sets 2D point with given x and y value.
		 * @param px is x coordinate.
		 * @param py is y coordinate.
		*/ 
		public void setPoint(double px, double py)
		{
			x = px;
			y = py;
		}

		/**
		 * Gets X coordinate of 2D point
		 * @return x
		 */
		public double getX()
		{
			return x;
		}

		/**
		 * Gets Y coordinate of 2D point
		 * @return y
		 */
		public double getY()
		{
			return y;
		}

	}


	/**
	 * Sets size of a polygon. 
	 * @param s is size
	 * @exception BadSize thrown, when size is less then zero.
	 */
	protected void setSize(int s)
	{
		size = s;
	}

	/**
	 * Gets the size of Polygon.
	 * Size represents how many 2D points does a polygon have.
	 * @return Total 2D Point in Polygon.
	 */  
	public int getSize()
	{
		return size;
	} 


}