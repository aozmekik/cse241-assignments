/** 
 * Represents the ComposedShape.
 * ComposedShape is specified class for to create composition 
 * between the shapes Rectangle, Triangle and Circle.
 * Composition specialized in fitting one shape into another
 * for all possible combinations. 
 *  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @see Shape, Rectangle, Triangle and Circle.
 * @since 2019-01-03
*/

import java.awt.Graphics;
import java.util.*;

public class ComposedShape implements Shape
{
	private enum shape_enum{tri, rect, cir}; 

	// Every shapes(optimized) will be kept in Array of Shape references.
	private Shape[] inner_shape;

	// Shape flags to determine which to use. 
	private ComposedShape.shape_enum main_shape,small_shape; 

	// Starting points for composition, set default(0,0).
	private double _x,_y; 

	private Shape main,small;


	/**
	 * Increments the Main Shape positions by 1.0 in both (x,y) plane.
	*/
	public void increment()
	{
		main.increment();
	}

	/** 
	 * Decrements the Main Shape by 1.0 in both (x,y) plane. 
	*/
	public void decrement()
	{
		main.decrement();
	}

	/** 
	 * Takes a Graphics object as parameter and draws the shape. 
	 * This method will be called from the paintComponent method of a 
	 * JPanel object.
	 * @param Graphics object to draw into.
	 * @see JPanel
	 * @see Graphics
	*/
	public void draw(Graphics g)
	{
		main.draw(g);
		for(Shape s : inner_shape)
			s.draw(g);
	}


	/** 
	 * Gets the area of the main shape.
     * @return Area of the main shape.
	*/ 
	public double area()
	{
		return main.area();
	}

	/** 
	 * Gets the Perimeter of the main shape.
     * @return Perimeter of the main shape.
	*/ 
	public double perimeter()
	{
		return main.perimeter();
	}

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
	 * Creates a composition with given two shapes and 
	 * fits as many as small shapes into the given main shape.
	 * @param m, main shape of the composition.
	 * @param s, small shape which will be fitted into main shape
	 * with optimization.
	 * Main container's coordinates is composed shape's coordinates.
	 * If your position's are not positive which is valid, then you may
	 * not have the full view of your composed shape.  
	*/   
	ComposedShape(Shape m,Shape s)
	{
		setMainShape(m);
		setSmallShape(s);
		setDefaultPosition();
	}

	private void fitRinR() throws CloneNotSupportedException
	{ 
		Rectangle r1 = (Rectangle)main;
		Rectangle r2 = (Rectangle)small;
		Rectangle r = (Rectangle)r2.clone(); // Temp small shape which we will work on.
		List<Shape> shape = new ArrayList<Shape>();  // Small shapes. 
		double x,y; // temp positions which we will find later on for small shapes.    



		r.setFill(true); // small shapes will have color.

		// We determine which filling(rotate or not) is better for optimization. 
		if(totalRinR(r1.getWidth(),r1.getHeight(), r2) < 
		   totalRinR(r1.getHeight(),r1.getWidth(), r2))
		{
			r.swapEdges(); 
		}

		// Starting to fill from(a,b) to (max,b) without rotating.
		// (_x,_y) counters represent position.
		r.setRotate(false);
		for(x=0.0; x<=r1.getWidth()-r.getWidth();x+=r.getWidth())
		{
			for(y=0.0; y<=r1.getHeight()-r.getHeight(); y+=r.getHeight())
			{
				// (x,y) determined due to (0,0). We must add  
				// container's coordinates to shift to exact position.   
				r.setPosition(_x+x,_y+y);
				shape.add((Rectangle)r.clone());
			}
		}

		// Keep filling from(a,max) to (max,max) with rotating.
		r.setRotate(true);
		boolean filled=false; // to check if we filled any with this try.
		for(y=0.0,
			x=r.getWidth()*(double)((int)r1.getWidth()/(int)r.getWidth())+r.getHeight();	
									  x<= r1.getWidth() && y<=r1.getHeight()-r.getWidth();
																		   y+=r.getWidth())
		{	
			r.setPosition(_x+x,_y+y);
			shape.add((Rectangle)r.clone());
			filled=true;
		}

		// Try to fill with rotating from different position.
		if(!filled)
		{
			for(y=r.getHeight()*(double)((int)r1.getHeight()/(int)r.getHeight());
										y<r1.getHeight()-r.getWidth(); y+=r.getWidth())
			{
				for(x=0;x<=r1.getWidth()-r.getHeight();x+=r.getHeight())
				{
					r.setPosition(_x+x,_y+y);
					shape.add((Rectangle)r.clone());
				}
				r.setPosition(_x+x,_y+y);
				shape.add((Rectangle)r.clone());
			}
		}

		inner_shape = new Shape[shape.size()];
		inner_shape = shape.toArray(inner_shape); 

	}

	private void fitRinC() throws CloneNotSupportedException
	{
		// We fill the imaginary inner rectangles which inside of circle with small rectangles.
		// To do this we must create a composition with rectangular main container.
		// We copy the circle object to shift the wanted area of cartesian coordinate
		// system for better use of circle functions.
		try
		{
			Circle c1 = (Circle)main;
			Rectangle r2 = (Rectangle)small;
			Rectangle r = (Rectangle)r2.clone(); 
			Rectangle inner_r = new Rectangle(1,1); // just default. 
			Circle c = (Circle)c1.clone(); 
			ComposedShape inner_shape = new ComposedShape(inner_r,r);
			List<Shape> shape = new ArrayList<Shape>();
			double x=0.0,y=0.0; 

			c.setPosition(c.getRadius()/Math.sqrt(2.0),c.getRadius()/Math.sqrt(2.0));

			y = c.getY()+c.getRadius();

			if(r.getWidth()>r.getHeight())
				r.swapEdges();
				
			
			inner_r.setHeight(r.getWidth());
			

			while(x<c.getX())
			{
				y -= inner_r.getHeight();
				x = circleFunc(y,c,true);

				inner_r.setWidth(circleFunc(y,c,false) - x);

				while(!isInsideCircle(x,y+inner_r.getHeight(),c))
				{
					y-=.3;
					x++;
					inner_r.setWidth(inner_r.getWidth()-2.0);
				}
				// Update the composition.
				r.setPosition(x+_x,y+_y);
				// Concatenate two vectors.
				appendComposition(inner_shape,inner_r,r,shape);

				this.inner_shape = new Shape[shape.size()];
				this.inner_shape = shape.toArray(this.inner_shape); 
				
			}
		}
		catch(BadSize b)
		{
			System.out.println("In optimal fit:"+ b.toString());
		}

	}

	/**
	 * Fits as many as small shapes into the main shape.
	 * Regarding to your created composition, this method
	 * optimally fits as many as small shapes into outer
	 * main shape. Before drawing your composition you certainly
	 * must call this method to create the composition.  
	 */  
	public void optimalFit()
	{

		try
		{
				switch(main_shape)
			{
				case rect: 
					switch(small_shape)
					{
						case rect: fitRinR();break;
						case cir:  fitCinR();break;
						case tri:  fitTinR();break;
					}break;

				case cir:
					switch(small_shape)
					{
						case rect: fitRinC();break;
						case cir:  fitCinC();break;
						case tri:  fitTinC();break;
					}break;

				case tri:
					switch(small_shape)
					{
						case rect: fitRinT();break;
						case cir:  fitCinT();break;
						case tri:  fitTinT();break;
					}break;
			}	
		}
		catch(CloneNotSupportedException c)
		{
			System.out.println("Err!, Get contact with dev:" +  c.toString());
		}

		
	}


	private void fitRinT() throws CloneNotSupportedException
	{
		try
		{
			// Yet another imaginary composition created. 
			// We again, find the optimal rectangles inside the triangle,
			// Then make them our container, so that we can use fitRinR func.
			Rectangle inner_r = new Rectangle(1,1); // default
			Rectangle r2 = (Rectangle)small;
			Triangle t1 = (Triangle)main;
			Rectangle r = (Rectangle)r2.clone();
			ComposedShape inner_shape = new ComposedShape(inner_r,r);
			List<Shape> shape = new ArrayList<Shape>();

			double x,y;

			x = 0.0;
			y = t1.getLength()/2.0*Math.sqrt(3.0);

			// short length of rect is the height of inner rect which we will fill in.   
			if(r.getWidth()>r.getHeight())
				r.swapEdges();
			
			
			inner_r.setHeight(r.getWidth());
			inner_r.setWidth (t1.getLength());

			while(x<=t1.getLength()/2.0 && inner_r.getWidth()- 2*inner_r.getHeight()/1.7 >0)
			{
				
				// Updates: 
				// Rctangle width gets smaller by it's height.
				// Position of rectangle goes top right 
				// magic number 1.7 is calculated from eq.triangle,
				// for to calculate inner rectangle's starter point and length

				y-=inner_r.getHeight();
				x+=inner_r.getHeight()/1.7;
				inner_r.setWidth(inner_r.getWidth()- 2*inner_r.getHeight()/1.7);

				r.setPosition(x+_x,y+_y);
				appendComposition(inner_shape,inner_r,r,shape);

				this.inner_shape = new Shape[shape.size()];
				this.inner_shape = shape.toArray(this.inner_shape);

			} 
		}
		catch(BadSize b)
		{
			System.out.println("In optimal fit:"+ b.toString());

		}
	}


	private void fitCinR() throws CloneNotSupportedException
	{
		Rectangle r1 = (Rectangle)main;
		Circle c2 = (Circle)small; 
		Circle c = (Circle)c2.clone();
		List<Shape> shape = new ArrayList<Shape>();
		double x,y;

		// pretty straight forward filling with starting from (r,r) 
		c.setFill(true);
		for(y=c.getRadius();y<=r1.getHeight()-c.getRadius();y+=2.0*c.getRadius())
		{
			for(x=c.getRadius();x<=r1.getWidth()-c.getRadius();x+=2.0*c.getRadius())
			{
				c.setPosition(x+_x,y+_y);
				shape.add((Circle)c.clone());
			}
		}

		inner_shape = new Shape[shape.size()];
		inner_shape = shape.toArray(inner_shape);

	}

	private void fitCinC() throws CloneNotSupportedException
	{
		try
		{
			Rectangle inner_r = new Rectangle(1,1); // default.
			Circle c1 = (Circle)main;
			Circle c2 = (Circle)small;
			Circle main_c = (Circle)c1.clone();
			Circle small_c = (Circle)c2.clone(); 
			ComposedShape inner_shape = new ComposedShape(inner_r,small_c);
			List<Shape> shape = new ArrayList<Shape>();
			double x=-1,y;

			main_c.setPosition(c1.getRadius()/Math.sqrt(2.0),c1.getRadius()/Math.sqrt(2.0));

			y = main_c.getY() + main_c.getRadius();
			inner_r.setHeight(small_c.getRadius()*2.0);
		 
			while(x<main_c.getX())
			{
				y -= small_c.getRadius()*2.0;
				x = circleFunc(y,main_c,true);

				inner_r.setWidth(circleFunc(y,main_c,false) - x);

				// the above half of the center requires some updates:
				// such as controlling overflow 
				if(y>=main_c.getX())
				{
					x+=2.0*small_c.getRadius();
					inner_r.setWidth(inner_r.getWidth()- 3.5*small_c.getRadius());

					while(!isInsideCircle(x,y+2.0*c2.getRadius(),main_c))
					{
						y--;
						x++;
						inner_r.setWidth(inner_r.getWidth()-1);
					}
				}

				small_c.setPosition(x+_x,y+_y);
				appendComposition(inner_shape,inner_r,small_c,shape);

				this.inner_shape = new Shape[shape.size()];
				this.inner_shape = shape.toArray(this.inner_shape);

			}
		}
		catch(BadSize b)
		{
			System.out.println("In optimal fit:"+b.toString());
		}

	}

	private void fitCinT() throws CloneNotSupportedException
	{

		try
		{
			Rectangle inner_r = new Rectangle(1,1);
			Circle c2 = (Circle)small;
			Circle c = (Circle)c2.clone();
			Triangle t1 = (Triangle)main;
			ComposedShape inner_shape = new ComposedShape(inner_r,c);
			List<Shape> shape = new ArrayList<Shape>();
			double x,y; // position of inner rectangle 

			x = 0.0;
			y = t1.getLength()/2.0*Math.sqrt(3.0);

			// smallest square that circle can fit in 
			inner_r.setWidth(t1.getLength());
			inner_r.setHeight(2*c.getRadius());

			// same algorithm which we used in fitRinT:
			// after we set our inner rectangle, we fill the rectangle with circle
			while(x<=t1.getLength()/2.0 && inner_r.getWidth()-2*inner_r.getHeight()/1.7>0)
			{
				y-=inner_r.getHeight();
				x+=inner_r.getHeight()/1.7;
				inner_r.setWidth(inner_r.getWidth()-2*inner_r.getHeight()/1.7); 

				c.setPosition(x+_x,y+_y);
				appendComposition(inner_shape,inner_r,c,shape);
			 
			} 

			this.inner_shape = new Shape[shape.size()];
			this.inner_shape = shape.toArray(this.inner_shape);

		}
		catch(BadSize b)
		{
			System.out.println("In optimal fit:" + b.toString());
		}
	}

	
	private void fitTinR() throws CloneNotSupportedException
	{
		Rectangle r1 = (Rectangle)main;
		Triangle t2 = (Triangle)small;
		Triangle t = new Triangle(t2);
		List<Shape> shape = new ArrayList<Shape>();
		double x,y;
		double tri_height = (Math.sqrt(3.0)*t.getLength())/2.0;
		int size=0;

		t.setFill(true);

		// (a,width-a*sqrt(3)) init for fill inside without rotating  
		for(y = r1.getHeight()-tri_height;y>=0;y-=tri_height)
		{
			x=t.getLength()/2.0;
			while(x+t.getLength()/2.0<=r1.getWidth())
			{
				t.setPosition(x+_x,y+_y);
				shape.add(new Triangle(t));
				x+=t.getLength();
			}
	
		}

		
		// (2a,width)init for fill inside with rotating
		t.setRotate(true);
		for(y = r1.getHeight();y-tri_height>=0;y-=tri_height)
		{
			x = t.getLength();
			while(x+t.getLength()/2.0<=r1.getWidth())
			{
				
				t.setPosition(x+_x,y+_y);
				shape.add(new Triangle(t));
				x += t.getLength();
			}
		}

		inner_shape = new Shape[shape.size()];
		inner_shape = shape.toArray(inner_shape);
	}

	private void fitTinC() throws CloneNotSupportedException
	{
		try
		{
			Rectangle inner_r = new Rectangle(1,1); // default.
			Circle c1 = (Circle)main;
			Triangle t2 = (Triangle)small;
			Triangle t = (Triangle)t2.clone();
			Circle c = (Circle)c1.clone();
			ComposedShape inner_shape = new ComposedShape(inner_r,t);
			List<Shape> shape = new ArrayList<Shape>();
			double x,y;

			c.setPosition(c.getRadius()/Math.sqrt(2.0),c.getRadius()/Math.sqrt(2.0));

			inner_r.setHeight(Math.sqrt(3.0)*t.getLength()/2.0);

			x=0.0;
			y=c.getY()+c.getRadius();

			while(x<c.getX())
			{
				y -= inner_r.getHeight();
				x = circleFunc(y,c,true);

				inner_r.setWidth(circleFunc(y,c,false)-x);

				while(!isInsideCircle(x,y+inner_r.getHeight(),c))
				{
					y-=.3;
					x++;
					inner_r.setWidth(inner_r.getWidth()-1.8);
				}

				t.setPosition(x+_x,y+_y);
				appendComposition(inner_shape,inner_r,t,shape);

			}

			this.inner_shape = new Shape[shape.size()];
			this.inner_shape = shape.toArray(this.inner_shape);

		}
		catch(BadSize b)
		{
			System.out.println("In optimalfit:" + b.toString());
		}

	}

	private void fitTinT() throws CloneNotSupportedException
	{
		Triangle t1 = (Triangle)main;
		Triangle t2 = (Triangle)small;

		Triangle main_t = new Triangle(t1);
		Triangle small_t = new Triangle(t2);

		double x,y;
		double main_h, small_h;  // h of big main triangle
		List<Shape> shape = new ArrayList<Shape>();

		main_h = Math.sqrt(3.0)*main_t.getLength()/2.0;
		small_h = Math.sqrt(3.0)*small_t.getLength()/2.0;

		small_t.setFill(true);

		x=0.0;
		y=main_h;

		int i=1;
		double width=main_t.getLength();
		for(y = main_h-small_h; y>=0; y-= small_h)
		{
			x = i*small_t.getLength()/2.0;
			small_t.setPosition(x+_x,y+_y);
			++i;
			while(x+small_t.getLength()/2.0<=width)
			{
				shape.add(new Triangle(small_t));
				x += small_t.getLength(); 
				small_t.setPosition(x+_x,y+_y);
			}

			width-=small_t.getLength()/2.0;
		
		}

		small_t.setRotate(true);
		i=2;
		width=main_t.getLength()-small_t.getLength()/2.0;
		for(y = main_h; y-small_h>=0; y-= small_h)
		{
			x = i*small_t.getLength()/2.0;
			small_t.setPosition(x+_x,y+_y);
			++i;
			while(x+small_t.getLength()/2.0<=width)
			{
				shape.add(new Triangle(small_t));
				x+= small_t.getLength();
				small_t.setPosition(x+_x,y+_y);
			}

			width-=small_t.getLength()/2.0;
		}

		inner_shape = new Shape[shape.size()];
		inner_shape = shape.toArray(inner_shape);
		
	}


	private void appendComposition(ComposedShape inner, Rectangle main,
										  Shape small,List<Shape> v)
	{



		List<Shape> temp;
		inner.setMainShape(main);
		inner.setSmallShape(small);
		if(small instanceof Rectangle)
			inner.setPosition(((Rectangle)small).getX(),((Rectangle)small).getY());
		else if(small instanceof Circle)
			inner.setPosition(((Circle)small).getX(),((Circle)small).getY());
		else
			inner.setPosition(((Triangle)small).getX(),((Triangle)small).getY());	
		
		inner.optimalFit();
		temp = new ArrayList<Shape>(Arrays.asList(inner.inner_shape));
		v.addAll(temp); 
	}


	/** 
	 * Gets the inner shapes.
	 * @return Reference of Shape Array.
	**/
	public Shape[] getInnerShape()
	{
		return inner_shape;
	}

	/** 
	 * Sets the main shape of composition.
	 * Main shape is the outer shape and small 
	 * shapes will be fitted into this shape
	 * @param m, Main Shape.
	*/
	public void setMainShape(Shape m)
	{
		main = m;

		if(m instanceof Rectangle)
		{
			main_shape = shape_enum.rect; 
			((Rectangle)main).setFill(false);
		}
		else if(m instanceof Circle)
		{
			main_shape = shape_enum.cir;
			((Circle)main).setFill(false);
		}
		else 
		{
			main_shape = shape_enum.tri; 
			((Triangle)main).setFill(false);
		}	
	}

	/** 
	 * Sets the small shape of composition.
	 * Small shape is the inner shape and 
	 * will be fitted into the given main shape
	 * @param s, Small Shape.
	*/
	public void setSmallShape(Shape s)
	{
		small = s;

		if(s instanceof Rectangle)
			small_shape = shape_enum.rect;
		else if(s instanceof Circle)
			small_shape = shape_enum.cir;
		else 
			small_shape = shape_enum.tri;
	}

	private void setPosition(double x, double y)
	{
		_x = x;
		_y = y;
	}

	private void setDefaultPosition()
	{
		switch(main_shape)
		{
			case rect:
				Rectangle r = (Rectangle) main;
				_x = r.getX();
				_y = r.getY();
				break;

			case cir:
				Circle c = (Circle) main;
				_x = c.getX()-c.getRadius()/Math.sqrt(2.0);
				_y = c.getY()-c.getRadius()/Math.sqrt(2.0);
				break;

			case tri:
				Triangle t = (Triangle)main;
				_x = t.getX()-t.getLength()/2.0;
				_y = t.getY();
				break;
		}
	}



	private int totalRinR(double w, double h, Rectangle r2)
	{
		int total_fitted = 0;

		total_fitted = ((int)w/(int)r2.getWidth())*((int)h/(int)r2.getHeight());

		// Whether rotating the small shape by 90 degrees 
		// makes us win some more shape.
		// int casting because of getting exact numbers.  
		if((int)(w)%(int)(r2.getWidth())>=(int)(r2.getHeight())) 
			total_fitted = (int)(h)/(int)(r2.getWidth());

		return total_fitted;
	}

	private boolean isInsideCircle(double x, double y, Circle c)
	{
		boolean inside;
		if(c.getRadius()*c.getRadius()  <  (x-c.getX())*(x-c.getX())+(y-c.getY())*(y-c.getY()))
			inside = false;
		else
			inside = true;
		return inside;
	}

	private double circleFunc(double y, Circle c, boolean small)
	{
		double x;
		if(small)
			x = -Math.sqrt(c.getRadius()*c.getRadius()-((y-c.getY())*(y-c.getY())))+c.getX(); 
		else
			x =  Math.sqrt(c.getRadius()*c.getRadius()-((y-c.getY())*(y-c.getY())))+c.getX();

		return x;
	}

}
