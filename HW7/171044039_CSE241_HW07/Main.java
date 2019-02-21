/** 
 * Represents the Driver/Test Code.
 * Circle implements Shape interface.
 * @see Shape  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-02
*/

import javax.swing.JPanel;
import java.awt.Graphics;
import javax.swing.JFrame;

public class Main
{
	public static void main(String[] args) 
	{
		try
		{
			Rectangle r1 = new Rectangle(-200,-300);
		}
		catch(BadSize b)
		{
			System.out.println("Exception caught in Test>");
			System.out.println(b.toString());
		}

		try
		{
			Rectangle r1 = new Rectangle(634,732);
			Rectangle r2 = new Rectangle(56,72);
			Triangle t1 = new Triangle(500);
			Triangle t2 = new Triangle(46);
			Circle c2 = new Circle(33);
			Circle c1 = new Circle(300);
			PolygonVect p1 = new PolygonVect(new Triangle(70,300,400));
			PolygonDyn p2 = new PolygonDyn(new Rectangle(100,100,500,400));

			Shape[] shape = new Shape[5];
			shape[0] = r2;
			shape[1] = t2;
			shape[2] = c2;
			shape[3] = p1;
			shape[4] = p2;

			System.out.println("Unsorted Array>");
			for(Shape s: shape)
				System.out.println(s.area());

			Global.sortShape(shape);

			System.out.println("Sorted Array>");
			for(Shape s: shape)
				System.out.println(s.area());

		}
		catch(BadSize b)
		{
			System.out.println("Error in Test:" + b.toString());
		}

		try
		{
			DrawPanel panel = new DrawPanel();

			JFrame app = new JFrame();

			app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

			app.add(panel);
			app.setSize(1000,1000);
			app.setVisible(true);
		}
		
		

		finally
		{
			System.out.println("End of the Test!");
		}



	}

}




