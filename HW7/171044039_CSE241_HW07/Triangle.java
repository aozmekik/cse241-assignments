/** 
 * Represents the T.
 * Triangle implements Shape interface.
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
import java.util.*;


public class Triangle implements Shape, Cloneable
{
	private double length; // size of equaliteral triangle's each edge. 
	private double x,y;
	private boolean rotate; // Flag for rotate by 90 degress around pos(x,y)
	private boolean fill; // Flag for fill 
	private static double total_area = 0;
	private static double total_perim = 0;
	private int[] xPoints;
	private int[] yPoints;



	/** 
	 * Constructs Equaliteral Triangle object with given size.
	 * Default Position of Triangle is (0,0).
	 * As Default Triangle will be filled. 
	 * As there is no rotating.  
	 * @param l is length.
	 * @exception BadSize is thrown, when zero or negative value is given 
	 * for size parameters.
	*/ 
	public Triangle(double l)throws BadSize
	{
	 	if(l<=0) 
	 		throw new BadSize();

		length = l;
		x = 0;
		y = 0;

		rotate = false;
		fill = true;
		total_area += area();
		total_perim += perimeter();

		// created point arrays for to use drawPolygon method of Graphics.  
		xPoints = new int[3];
		yPoints = new int[3];

		
	}

	public Triangle(Triangle triangle) {
		xPoints = new int[3];
		yPoints = new int[3];

        length = triangle.length;
        x = triangle.x;
        y = triangle.y;
        rotate = triangle.rotate;
        fill = triangle.fill;

        xPoints = xPoints != null ? Arrays.copyOf(xPoints, xPoints.length) : null;
        yPoints = yPoints != null ? Arrays.copyOf(yPoints, yPoints.length) : null;

        setPoint();

    }

	/** 
	 * Constructs Triangle object with given sizes.
	 * @param l is width.
	 * @param posx is x coordinate.
	 * @param posy is y coordinate.  
	 * @exception BadSize is thrown when zero or negative value is given 
	 * for size parameters.
	*/
	public Triangle(double l, double posx, double posy)throws BadSize
	{
		this(l);
		x = posx;
		y = posy;

		setPoint();

	}

	/** 
	 * Gets the area of the Triangle.
     * @return Area of the Triangle.
     * @see Shape.
	*/  

	@Override 
	public double area()
	{
		// length : 2a
		// area : (a^^2*sqrt(3))/4.
		return Math.sqrt(Math.pow(length/2.0,2.0)*Math.sqrt(3.0))/4.0;
	}


	/** 
	 * Gets the perimeter of the Triangle.
     * @return Perimeter of the Triangle.
     * @see Shape.
	*/  

	@Override 
	public double perimeter()
	{
		return 3.0*length;
	}


	/**
	 * Compares this Triangle with the specified Triangle
	 * with respect to their areas.
	 * @param The Shape to be compared.
	 * @return A negative integer, zero, or a positive integer
	 * as this Triangle's area is less than, equal to, or greater 
	 * than the specified Triangle. 
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
	 * Takes a Graphics object as parameter and draws the Triangle into it. 
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

		if(getRotate()) // rotate by 180 degrees.
		{
			// downcasting to Graphics2D for to use rotate() method.
			Graphics2D g2d = (Graphics2D) copy;
			g2d.rotate(Math.toRadians(180),x,y);
		}


		if(getFill())
			copy.fillPolygon(xPoints,yPoints,3);

		((Graphics2D)copy).setStroke(new BasicStroke(1));
		copy.setColor(Color.BLACK);
		copy.drawPolygon(xPoints,yPoints,3);

		copy.dispose(); // getting rid of from the copy.
	}


	/**
	 * Gets the width of Triangle.
	 * @return Length.
	*/

	public double getLength()
	{
		return length;
	}

	

	 /** 
	 * Gets the position of Triangle in x plane.
	 * @return position X.
	*/

	 public double getX()
	 {
	 	return x;
	 }

	 /** 
	 * Gets the position of Triangle in y plane.
	 * @return position Y.
	*/

	 public double getY()
	 {
	 	return y;
	 }

	 /** 
	 * Gets the Rotate flag of Triangle.
	 * @return Rotate flag.
	*/

	 public boolean getRotate()
	 {
	 	return rotate;
	 }


	 /** 
	 * Gets the Fill flag of Triangle.
	 * @return Fill flag.
	*/

	 public boolean getFill()
	 {
	 	return fill;
	 }

	 /** 
	 * Sets the width of Triangle.
	 * @param Width.
	 * @exception BadSize is thrown when zero or negative value is given 
	 * for size width.  
	*/

	 public void setLength(double l) throws BadSize
	 {
	 	if(l<=0) 
	 		throw new BadSize();

	 	length = l;
	 	setPoint();

	 }

	
	private void setPoint()
	{
		xPoints[0] = (int)getX();
		yPoints[0] = (int)getY();

		xPoints[1] = (int)getX()-(int)(getLength()/2.0);
		yPoints[1] = (int)getY()+(int)(Math.sqrt(3.0)*(getLength()/2.0));

		xPoints[2] = (int)getX()+(int)(getLength()/2.0);
		yPoints[2] = (int)getY()+(int)(Math.sqrt(3.0)*(getLength()/2.0));
	}	  

	 /** 
	 * Sets the rotate flag of Triangle.
	 * <br> Note: </br> It can only be rotated around 180 degrees.  
	 * @param Rotate, True for rotating this Triangle by 180
	 * degrees around (x,y).
	*/

	 public void setRotate(boolean r)
	 { 
	 	rotate = r;
	 }

	 /** 
	 * Sets the Fill flag of Triangle.
	 * @param Fill, if you set this True, inside of your shape will 
	 * be painted with color.     
	*/

	 public void setFill(boolean f) 
	 {
	 	fill = f;		 	
	 }

	 /** 
	 * Sets the positions of Triangle.
	 * @param posx, position of Triangle in x plane.
	 * @param posy, position of Triangle in y plane.
	*/

	 public void setPosition(double posx, double posy)
	 {
	 	x = posx;
	 	y = posy;
	 	setPoint();		 	
	 }


	 /**
	  * Gets the sum of the areas of all Triangles created.
	  * @return Total Areas of all Triangles created.
	 */ 
	 public static double getTotalArea()
	 {
	 	return total_area;
	 }

	 /**
	  * Gets the sum of the perimeters of all Triangles created.
	  * @return Total Areas of all Triangles created.
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

