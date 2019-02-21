
/** 
 * Represents the Shape interface.
 *  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-02
*/

import java.awt.Graphics;

public interface Shape extends Comparable<Shape>
{

	/** 
	 * Gets the area of the shape.
     * @return Area of the shape.
	*/ 
	public double area();


	/** 
	 * Gets the perimeter of the shape.
	 * @return Perimeter of the shape.
	*/
	public double perimeter();	


	/**
	 * Compares this shape with the specified object with respect
	 * to their areas.
	 * @param The shape to be compared.
	 * @return A negative integer, zero, or a positive integer
	 * as this object's area is less than, equal to, 
	 * or greater than the specified object. 
	*/ 
	public int compareTo(Shape other);


	/**
	 * Increments the shape positions by 1.0 in both (x,y) plane.
	*/
	public void increment();

	/** 
	 * Decrements the shape positions by 1.0 in both (x,y) plane. 
	*/
	public void decrement();

	/** 
	 * Takes a Graphics object as parameter and draws the shape. 
	 * This method will be called from the paintComponent method of a 
	 * JPanel object.
	 * @param Graphics object to draw into.
	 * @see JPanel
	 * @see Graphics
	*/
	public void draw(Graphics g);


}