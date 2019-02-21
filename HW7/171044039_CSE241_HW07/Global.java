/** 
 * Represents the following static methods:
 * drawAll()
 * convertAll()
 * sortShapes()
 * @see Shape  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-02
*/

import java.awt.Graphics;
import java.util.*;

public class Global
{

	/**
	 * Takes an Shape references and draws all shapes to an JPanel
	 * This method will be called from the paintComponent method of a 
	 * JPanel object.
	 * @param g, Graphics object to draw into.
	 * @param shape, Shape[] is array of shape references 
	 * to draw all. 
	 * @see Graphics
	 */	
	public static void drawAll(Graphics g, Shape[] shape)
	{
		for(Shape s: shape)
			s.draw(g);
	}


	/**
	 * Takes an Shape references and convert all shapes to a Polygon and
	 * gets a Array of Polygon references.
	 * @param shape, Shape[] is array of shape references. 
	 * @see Polygon
	 * @return Shape[], Converted Polygon[].
	 */
	public static Shape[] convertAll(Shape[] shape)
	{
		Polygon[] polygon = new PolygonDyn[shape.length];

		for(int i=0;i<shape.length;++i) // converting.
			polygon[i] = new PolygonDyn(shape[i]);

		return polygon;
	}


	/**
	 * Takes an Shape references and sorts all shapes due to their areas.
	 * Shape[] shape is sorted after making call to this method. 
	 * @param shape, Shape[] is array of shape references. 
	 * @return Shape[], Converted Polygon[].
	 */
	public static void sortShape(Shape[] shape)
	{
		// Since Shape implements Comparable, this method will work.
		Collections.sort(Arrays.asList(shape));
	}
}