/** 
 * Represents the Iterator class.
 * @see Collection  
 * @param E object-type to hold in set.
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-14
*/


public class Iterator<E>
{
	private E[][] buffer; // underlying buffer.
	private int idx; // location of iterator in buffer.
	private E last_element; // last element returned by this iterator.

	public Iterator(E[][] arr)
	{
		buffer = arr;
		idx = 0;
	}

	/** 
	 * Returns true if the iteration has more elements.
	 * @return true if iteration has more elements.
	*/
	public boolean hasNext()
	{
		return idx<buffer[0].length;
	}

	/**
	 * Returns the next element in the iteration and advances the
 	 * iterator.
 	 * @return E, the next element in the iteration.
 	*/
	public E next()
	{
		last_element = buffer[0][idx++];
		return last_element;
	}
	
	/**
	 * Removes from the underlying collection the last element returned
	 * by this iterator.
	*/
	public void remove()
	{
		@SuppressWarnings("unchecked")
		E[] newArr = (E[]) new Object[buffer[0].length -1];

		for(int i=0, k=0;i<newArr.length;++i)
		{

			if(last_element == buffer[0][i])
				continue;
			
			newArr[k++] = buffer[0][i];
		}

		//change the real reference to new array.
		buffer[0] = newArr; 
	}


}


