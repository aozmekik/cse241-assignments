/** 
 * Represents the Queue interface.
 * Queue order elements in a FIFO (first-in-first-out) manner. 
 * There is no random access with this collection. Some
 * functions throw bad_request exception; indicates 
 * request from queue is not valid.  
 * @param E object-type to hold in set.
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-14
*/

public interface Queue<E> extends Collection<E>
{


	/**
	 * Returns an iterator over the Queue
	 * @return Iterator, iterator over Queue.
	 * @see Iterator
	*/
	public Iterator<E> iterator();

	/**
	 * Ensures that this Queue contains the specified element.
	**/
	public void add(E e);

	/**
	 * Adds all of the elements in the specified Queue to this
     * Queue.
	**/
	public void addAll(Collection<E> c);

	/**
	 * Removes all of the elements from this Queue.
	**/
	public void clear();

	/**
	 * Returns true if this Queue contains the specified element.
	 * @return true if Queue contains specified element, false if
	 * Queue does not contain the specified element. 
	**/
	public boolean contains(E e);

	/**
	 * Returns true if this Queue contains all of the elements in the
 	 * specified Queue.
 	 * @return true if Queue contains the specified Queue's all
 	 * elements, false if the Queue does not contain at least one element 
 	 * from the specified Queue. 
	**/
	public boolean containsAll(Collection<E> c);

	/**
	 * Returns true if this Queue contains no elements.
	 * @return true if Queue is empty, false if it's not empty.
	**/
	public boolean isEmpty();

	/**
	 * Removes a single instance of the specified element from this
     * Queue, if it is present.
	**/
	public void remove(E e);

	/**
	 * Removes all of this Queue's elements that are also contained
  	 * in the specified Queue.
	**/
	public void removeAll(Collection<E> c);

	/**
	 * Retains only the elements in this Queue that are contained in
	 * the specified Queue.
	**/
	public void retainAll(Collection<E> c);

	/**
	 * Returns the number of elements in this Queue.
	 * @return size of the Queue.
	**/
	public int size();

	/**
	 * Retrieves, but does not remove, the head of this queue.
	 * @return E, head of this queue.
	 * @exception emptyQueue, throws if the queue is empty.
	**/
	public E element()throws emptyQueue;

	/**
	 * Inserts the specified element into this queue.
	 * @param E, element to insert to queue.
	**/
	public void offer(E e);

	/**
	 * Retrieves and removes the head of this queue, or throws if this
 	 * queue is empty.
	 * @return E, head of this queue.
 	 * @exception emptyQueue, throws if the queue is empty.
	**/
	public E poll()throws emptyQueue;

	public class emptyQueue extends Exception 
	{
		public String toString()
		{
			return "Empty Queue Error!";
		}
	}

}

