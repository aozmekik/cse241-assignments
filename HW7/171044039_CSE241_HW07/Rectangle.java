/** 
 * Represents the Rectangle.
 * Rectangle implements Shape interface.
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



public class Rectangle implements Shape, Cloneable
{
	private double width;
	private double height;
	private double x,y;
	private boolean rotate; // Flag for rotate by 90 degress around pos(x,y)
	private boolean fill; // Flag for fill 
	private static double total_area = 0;
	private static double total_perim = 0;


	/** 
	 * Constructs Rectangle object with given sizes.
	 * Default Position of rectangle is (0,0).
	 * As Default rectangle will be filled. 
	 * As there is no rotating.  
	 * @param w is width.
	 * @param h is height. 
	 * @exception BadSize is thrown, when zero or negative value is given 
	 * for size parameters.
	*/ 
	public Rectangle(double w, double h)throws BadSize
	{
	 	if(w<=0) 
	 		throw new BadSize();

		width = w;
		height = h;
		x = 0;
		y = 0;
		rotate = false;
		fill = true;
		total_area += area();
		total_perim += perimeter();
	}

	/** 
	 * Constructs Rectangle object with given sizes.
	 * @param w is width.
	 * @param h is height.
	 * @param posx is x coordinate.
	 * @param posy is y coordinate.  
	 * @exception BadSize is thrown when zero or negative value is given 
	 * for size parameters.
	*/
	public Rectangle(double w, double h, double posx, double posy)throws BadSize
	{
		this(w,h);
		x = posx;
		y = posy;
	}

	/** 
	 * Gets the area of the rectangle.
     * @return Area of the rectangle.
     * @see Shape.
	*/  

	@Override 
	public double area()
	{
		return (width*height);
	}


	/** 
	 * Gets the perimeter of the rectangle.
     * @return Perimeter of the rectangle.
     * @see Shape.
	*/  

	@Override 
	public double perimeter()
	{
		return (width+height)*2.0;
	}


	/**
	 * Compares this rectangle with the specified rectangle
	 * with respect to their areas.
	 * @param The rectangle to be compared.
	 * @return A negative integer, zero, or a positive integer
	 * as this rectangle's area is less than, equal to, or greater 
	 * than the specified rectangle. 
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
	 * Takes a Graphics object as parameter and draws the rectangle into it. 
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
		double x = getX();
		double y = getY();


		if(getRotate()) // rotate by 90 degrees.
		{
			// downcasting to Graphics2D for to use rotate() method.
			Graphics2D g2d = (Graphics2D) copy;
			g2d.rotate(Math.toRadians(-90),x,y);
			x -= getWidth(); // for exact fit.
			y -= getHeight();
		}


		if(getFill())
			copy.fillRect((int)x,(int)y,(int)getWidth(),(int)getHeight());

		((Graphics2D)copy).setStroke(new BasicStroke(1));
		copy.setColor(Color.BLACK);
		copy.drawRect((int)x,(int)y,(int)getWidth(),(int)getHeight());

		copy.dispose(); // getting rid of from the copy.
	}


	/**
	 * Gets the width of rectangle.
	 * @return Width.
	*/

	public double getWidth()
	{
		return width;
	}

	/**
	 * Gets the height of rectangle.
	 * @return Height.
	*/
	public double getHeight()
	 {
	 	return height;
	 }

	 /** 
	 * Gets the position of rectangle in x plane.
	 * @return position X.
	*/

	 public double getX()
	 {
	 	return x;
	 }

	 /** 
	 * Gets the position of rectangle in y plane.
	 * @return position Y.
	*/

	 public double getY()
	 {
	 	return y;
	 }

	 /** 
	 * Gets the Rotate flag of rectangle.
	 * @return Rotate flag.
	*/

	 public boolean getRotate()
	 {
	 	return rotate;
	 }


	 /** 
	 * Gets the Fill flag of rectangle.
	 * @return Fill flag.
	*/

	 public boolean getFill()
	 {
	 	return fill;
	 }

	 /** 
	 * Sets the width of rectangle.
	 * @param Width.
	 * @exception BadSize is thrown when zero or negative value is given 
	 * for size width.  
	*/

	 public void setWidth(double w) throws BadSize
	 {
	 	if(w<=0) 
	 		throw new BadSize();

	 	width = w;
	 }

	  /** 
	 * Sets the height of rectangle.
	 * @param Height.
	 * @exception BadSize is thrown when zero or negative value is given 
	 * for size height.  
	*/

	 public void setHeight(double h) throws BadSize
	 {
	 	if(h<=0) 
	 		throw new BadSize();
	 	
	 	height = h;
	 }


	 /** 
	 * Sets the rotate flag of rectangle.
	 * <br> Note: </br> It can only be rotated around 90 degrees.  
	 * @param Rotate, True for rotating this rectangle by 90
	 * degrees around (x,y).
	*/

	 public void setRotate(boolean r)
	 { 
	 	rotate = r;
	 }

	 /** 
	 * Sets the Fill flag of rectangle.
	 * @param Fill, if you set this True, inside of your shape will 
	 * be painted with color.     
	*/

	 public void setFill(boolean f) 
	 {
	 	fill = f;		 	
	 }

	 /** 
	 * Sets the positions of rectangle.
	 * @param posx, position of rectangle in x plane.
	 * @param posy, position of rectangle in y plane.
	*/

	 public void setPosition(double posx, double posy)
	 {
	 	x = posx;
	 	y = posy;		 	
	 }


	 /** 
	 * Swaps the sizes edges of rectangle. 
	*/
	 public void swapEdges() 
	 {
	 	// basic swaping operation
	 	try
	 	{
	 		double temp;
			temp = getWidth();
			setWidth(getHeight());
			setHeight(temp);
	 	}
	 	catch(BadSize b)
	 	{/* intentionally left blank*/}
		
	 }

	 /**
	  * Gets the sum of the areas of all rectangles created.
	  * @return Total Areas of all rectangles created.
	 */ 
	 public static double getTotalArea()
	 {
	 	return total_area;
	 }

	 /**
	  * Gets the sum of the perimeters of all rectangles created.
	  * @return Total Areas of all rectangles created.
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

