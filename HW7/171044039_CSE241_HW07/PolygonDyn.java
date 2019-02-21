/** 
 * Represents the PolygonDyn.
 * SubClass of Polygon class.
 * PolygonVect uses Array to keep 2D points of Polygon.  
 *  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-05
 * @see Polygon
*/

import java.lang.Math;
import java.awt.*;
import java.util.*;

public class PolygonDyn extends Polygon
{
	private Polygon.Point2D[] point;

	private double _area;
	private double _perim; 


	/**
	 * Constructs a Polygon from given shape.
	 * Since a polygon is representation of 2D points,
	 * constructor will parse your shape into 2D points
	 * which is Polygon.
	 * @param Shape, will be converted to Polygon
	 */ 
	public PolygonDyn(Shape shape)
	{
		super(1); // init size with 1.
		if(shape instanceof Rectangle)		
			setPolygon((Rectangle)shape);
		else if(shape instanceof Circle)
			setPolygon((Circle)shape);
		else if(shape instanceof Triangle)
			setPolygon((Triangle)shape);
		
	}


	/** 
	 * Gets the area of the PolygonDyn.
     * @return Area of the PolygonDyn.
	*/
	@Override 
	public double area()
	{
		return _area;
	}


	/** 
	 * Gets the perimeter of the PolygonDyn.
	 * @return Perimeter of the PolygonDyn.
	*/
	@Override
	public double perimeter()
	{
		return _perim;
	}	

	/**
	 * Increments the Polygon positions by 1.0 in both (x,y) plane.
	*/
	@Override
	public void increment()
	{
		for(Polygon.Point2D p : point)
			p.setPoint(p.getX()+1,p.getY()+1);

	}

	/** 
	 * Decrements the Polygon positions by 1.0 in both (x,y) plane. 
	*/
	@Override
	public void decrement()
	{
		for(Polygon.Point2D p : point)
			p.setPoint(p.getX()-1,p.getY()-1);
	}

	/** 
	 * Takes a Graphics object as parameter and draws the Polygon. 
	 * This method will be called from the paintComponent method of a 
	 * JPanel object.
	 * @param Graphics object to draw into.
	 * @see JPanel
	 * @see Graphics
	*/
	@Override
	public void draw(Graphics g)
	{
		// copy the Graphics object so that changes in this context
		// will not effect outside.
		Graphics copy = g.create();

		int[] xPoints = new int[getSize()];
		int[] yPoints = new int[getSize()];

		// parsing the point2D for to use methods in Graphics.
		for(int i=0;i<getSize();++i) 
		{
			xPoints[i] = (int)point[i].getX();
			yPoints[i] = (int)point[i].getY();
		}

		copy.fillPolygon(xPoints,yPoints,getSize());

		((Graphics2D)copy).setStroke(new BasicStroke(1));
		copy.setColor(Color.BLACK);
		copy.drawPolygon(xPoints,yPoints,getSize());

		copy.dispose(); // getting rid of from the copy.
	}

	private void setPolygon(Rectangle rectangle)
	{
		setSize(4);
		point = new Polygon.Point2D[getSize()];


		_area = rectangle.area();
		_perim = rectangle.perimeter();

		final double x = rectangle.getX();
		final double y = rectangle.getY();

		// Drawing route: 
		/* (x,y) left-most corner-> go to right -> go down -> then go left */ 
		point[0] = new Polygon.Point2D(x,y);
		point[1] = new Polygon.Point2D(x+rectangle.getWidth(),y);
		point[2] = new Polygon.Point2D(x+rectangle.getWidth(),y+rectangle.getHeight());
		point[3] = new Polygon.Point2D(x,y+rectangle.getHeight());
	}

	private void setPolygon(Circle circle)
	{
		setSize(100);
		point = new Polygon.Point2D[getSize()];

		_area = circle.area();
		_perim = circle.perimeter();

		double x=0.0,y=0.0; // coord. 

		for(int i=0;i<getSize();++i)
		{

			x = circle.getX() + Math.cos(2.0*i*Math.PI/getSize())*circle.getRadius();
			y = circle.getY() + Math.sin(2.0*i*Math.PI/getSize())*circle.getRadius();
			point[i] = new Polygon.Point2D(x,y);
		}	
	}	

	private void setPolygon(Triangle triangle)
	{
		setSize(3);
		point = new Polygon.Point2D[getSize()];


		_area = triangle.area();
		_perim = triangle.perimeter();

		final double x = triangle.getX();
		final double y = triangle.getY();

		//Drawing route:
		/* (x,y) top corner -> go to down and right -> go left */
		point[0] = new Polygon.Point2D(x,y);
		if(triangle.getRotate())
		{
			point[1] = new Polygon.Point2D(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*Math.sqrt(3)/2.0); 
			point[2] = new Polygon.Point2D(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y-triangle.getLength()*Math.sqrt(3)/2.0);
		}
		else
		{
			point[1] = new Polygon.Point2D(x+triangle.getLength()/2.0, // (x+len/2,y+(3^1/2)*len/2)
								 y+triangle.getLength()*Math.sqrt(3)/2.0); 
			point[2] = new Polygon.Point2D(x-triangle.getLength()/2.0, // (x-len/2,y+(3^1/2)*len/2)
							 y+triangle.getLength()*Math.sqrt(3)/2.0);
		}
	} 


}