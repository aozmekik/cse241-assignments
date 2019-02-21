/** 
 * Represents the DrawPanel.
 * Circle implements Shape interface.
 * @see Shape  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-02
*/

import java.awt.Graphics;
import java.awt.Color;
import javax.swing.JPanel;

public class DrawPanel extends JPanel
{
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.setColor(Color.GRAY);


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


			r1.setPosition(150,100);
			c1.setPosition(150,100);
			c2.setPosition(200,200);
			r2.setPosition(300,600);

			t2.setPosition(300,150);
			t1.setPosition(300,100);
			c1.setPosition(300,300);

			
			Global.drawAll(g,shape);
			shape = Global.convertAll(shape); // convert the polygons.

			/* Try for ComposedShape Block.
			ComposedShape c = new ComposedShape(r1,r2);
			c.optimalFit();
			c.draw(g);
			*/
			
		}
		catch(BadSize b)
		{
			System.out.println(b.toString());
		}
		

	}
}