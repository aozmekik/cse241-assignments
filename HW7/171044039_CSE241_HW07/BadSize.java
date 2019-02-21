/** 
 * Represents the BadSize Exception.
 * BadSize is thrown when the expected is 
 * not in expected boundaries.
 * @see Shape  
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-05
*/

public class BadSize extends Exception
{
	public BadSize() { super(); }
	public BadSize(String msg) { super(msg); }

	/** 
	 * Returns an info about the exception BadSize
	 * @return String, exception info.
	 */    
	@Override
	public String toString() 
	{ 
		return new String("Negative value or zero was given for size!"); 
	}
}