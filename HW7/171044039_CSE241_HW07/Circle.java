/** 
 * Represents the Circle.
 * Circle implements Shape interface.
 * @see Shape  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-02
*/

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.lang.Math;
import java.awt.Color;
import java.awt.*;


public class Circle implements Shape, Cloneable
{
	private double radius;  
	private double x,y; // center of circle.
	private boolean fill; // Flag for fill 
	private static double total_area = 0;
	private static double total_perim = 0;



	/** 
	 * Constructs Equaliteral Circle object with given size.
	 * Default Position of Circle is (0,0).
	 * As Default Circle will be filled. 
	 * As there is no rotating.  
	 * @param l is length.
	 * @exception BadSize is thrown, when zero or negative value is given 
	 * for size parameters.
	*/ 
	public Circle(double r)throws BadSize
	{
	 	if(r<=0) 
	 		throw new BadSize();

		radius = r;
		x = 0;
		y = 0;

		fill = true;
		total_area += area();
		total_perim += perimeter();		
	}

	/** 
	 * Constructs Circle object with given sizes.
	 * @param l is width.
	 * @param posx is x coordinate.
	 * @param posy is y coordinate.  
	 * @exception BadSize is thrown when zero or negative value is given 
	 * for size parameters.
	*/
	public Circle(double l, double posx, double posy)throws BadSize
	{
		this(l);
		x = posx;
		y = posy;

	}

	/** 
	 * Gets the area of the Circle.
     * @return Area of the Circle.
     * @see Shape.
	*/  

	@Override 
	public double area()
	{
		return Math.PI*radius*radius;
	}


	/** 
	 * Gets the perimeter of the Circle.
     * @return Perimeter of the Circle.
     * @see Shape.
	*/  

	@Override 
	public double perimeter()
	{
		return 2.0*Math.PI*radius;
	}


	/**
	 * Compares this Circle with the specified Circle
	 * with respect to their areas.
	 * @param The Shape to be compared.
	 * @return A negative integer, zero, or a positive integer
	 * as this Circle's area is less than, equal to, or greater 
	 * than the specified Circle. 
	*/ 
	@Override
	public int compareTo(Shape other)
	{
		
		return Double.compare(area(),other.area()); 

	}

	/**
	 * Increments the shape positions by 1.0 in both (x,y) plane.
	*/
	@Override
	public void increment()	
	{
		setPosition(getX()+1,getY()+1);
	}

	/**
	 * Decrements the shape positions by 1.0 in both (x,y) plane.
	*/
	@Override
	public void decrement()	
	{
		setPosition(getX()-1,getY()-1);
	}

	/** 
	 * Takes a Graphics object as parameter and draws the Circle into it. 
	 * This method will be called from the paintComponent method of a 
	 * JPanel object.
	 * @param Graphics object to draw into.
	 * @see JPanel
	 * @see Graphics
	*/
	public void draw(Graphics g)
	{
		// copy the Graphics object so that changes in this context
		// will not effect outside.
		Graphics copy = g.create();

		if(getFill())
		{
			copy.fillOval((int)(getX()-getRadius()),(int)(getY()-getRadius()),
			(int)(getRadius()*2.0),(int)(getRadius()*2.0));
		}

		((Graphics2D)copy).setStroke(new BasicStroke(1));
		copy.setColor(Color.BLACK);
		copy.drawOval((int)(getX()-getRadius()),(int)(getY()-getRadius()),
			(int)(getRadius()*2.0),(int)(getRadius()*2.0));

		copy.dispose(); // getting rid of from the copy.
	}


	/**
	 * Gets the width of Circle.
	 * @return Length.
	*/

	public double getRadius()
	{
		return radius;
	}

	

	 /** 
	 * Gets the position of Circle in x plane.
	 * @return position X.
	*/

	 public double getX()
	 {
	 	return x;
	 }

	 /** 
	 * Gets the position of Circle in y plane.
	 * @return position Y.
	*/

	 public double getY()
	 {
	 	return y;
	 }


	 /** 
	 * Gets the Fill flag of Circle.
	 * @return Fill flag.
	*/

	 public boolean getFill()
	 {
	 	return fill;
	 }

	 /** 
	 * Sets the width of Circle.
	 * @param Width.
	 * @exception BadSize is thrown when zero or negative value is given 
	 * for size width.  
	*/

	 public void setRadius(double r) throws BadSize
	 {
	 	if(r<=0) 
	 		throw new BadSize();

	 	radius = r;
	 }  

	 /** 
	 * Sets the Fill flag of Circle.
	 * @param Fill, if you set this True, inside of your shape will 
	 * be painted with color.     
	*/

	 public void setFill(boolean f) 
	 {
	 	fill = f;		 	
	 }

	 /** 
	 * Sets the positions of Circle.
	 * @param posx, position of Circle in x plane.
	 * @param posy, position of Circle in y plane.
	*/

	 public void setPosition(double posx, double posy)
	 {
	 	x = posx;
	 	y = posy;		 	
	 }


	 /**
	  * Gets the sum of the areas of all Circles created.
	  * @return Total Areas of all Circles created.
	 */ 
	 public static double getTotalArea()
	 {
	 	return total_area;
	 }

	 /**
	  * Gets the sum of the perimeters of all Circles created.
	  * @return Total Areas of all Circles created.
	  */
	 public static double getTotalPerim()
	 {
	 	return total_perim;
	 }

	@Override
    protected void finalize() throws Throwable
    {
    	total_area -= area();
    	total_perim -= perimeter();

    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
    	return super.clone();
    }
}

