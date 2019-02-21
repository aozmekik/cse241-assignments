/** 
 * Represents the LinkedList class.
 * LinkedList implement both Set and Queue interface.
 * @see Set  
 * @param E object-type to hold in set.
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-14
*/

public class LinkedList<E> implements Set<E>, Queue<E>
{
	private E[] buffer; // underlying container.
	private int buf_size;

	/** No paramater constructor. Initial size is zero, and 
	 *  underlying container created. 
	 */
	public LinkedList()
	{
		buf_size = 0;
	}

	/**
	 * Returns an Iterator over LinkedList. 
	 * Since List is an ordered collection, you have a precise
	 * control over where in the list each is element is inserted
	 * due to insertion order. 
	 * @see Iterator
	 * @return Iterator over a LinkedList.
	 */
	@Override
	public Iterator<E> iterator()
	{
		@SuppressWarnings("unchecked")
		E[][] temp = (E[][]) new Object[1][buf_size];
		temp[0] = buffer;

		return new Iterator<E>(temp);
	}


	/**
	 * Inserts the specified element into this LinkedList
	 * You can have duplicates of an element and insertion  
	 * order specifies your sequence's order.
	 * @param E, Element to insert.
	**/
	@Override
	public void add(E e)
	{
		if(isEmpty())
		{
			@SuppressWarnings("unchecked")
			E[] temp = (E[]) new Object[1];
			buffer = temp;
			buffer[0] = e;
			setSize(size()+1);
		}
		else
		{
			setSize(size()+1); // grow the size.
			@SuppressWarnings("unchecked")
			E[] temp = (E[]) new Object[size()]; 

			for(int i=1;i<size();++i) // copy the previous.
				temp[i] = buffer[i-1];

			temp[0] = e; // add the new.
			buffer = temp;

		}
	}

	
	/** 
	 * Ensures that LinkedList contains all of the elements in the 
	 * specified collection. Duplicates are permitted. 
	 * @param c, collection to insert. 
	**/
	@Override
	public void addAll(Collection<E> c)
	{
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			add(begin.next());
	}

	/**
	 * Removes all of the elements from LinkedList 
	**/
	@Override
	public void clear()
	{
		buffer = null;
		setSize(0);
	}

	/**
	 * Returns true if the LinkedList contains the specified element
	 * at least one time. 
	**/
	public boolean contains(E e)
	{
		boolean found = false;

		if(isEmpty())
			found = false;
		else
		{
			for(int i=0;i<size() && !found;++i) // linear search.
			{
				if(buffer[i] == e)
					found = true;
			}
		}

		return found;
	}

	
	/** 
	* Returns true if this LinkedList contains all of the elements in the
	* specified collection. All of them must be in the LinkedList at least
	* one time.
	* @param c, collection to look for.
	**/
	@Override
	public boolean containsAll(Collection<E> c)
	{
		boolean found = true;
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			found = found && contains(begin.next());
		
		return found;
	}

	/**
	 * Returns true if the LinkedList contains no element. 
	 **/
	@Override
	public boolean isEmpty()
	{
		return size()==0;
	}

	/**
	 * Removes the specified element from the LinkedList.
	 * All duplicates of this element in the LinkedList, are removed. 
	 * @param e, element to delete from list.
	**/
	@Override
	public void remove(E e)
	{
		while(contains(e))
		{
			setSize(size()-1);
			@SuppressWarnings("unchecked")
			E[] temp = (E[])new Object[size()];


			for(int i=0,j=0;i<buffer.length;++i) // linear search.
			{
				if(buffer[i] != e)
				{
					temp[j++] = buffer[i];
				}
			}

			buffer = temp;
		}
		
	}


	
	/**
	 * Removes all duplicates of LinkedList's elements that 
	 * are also contained in the specified collection. 
	 * @param c, elements in this collection will be deleted.   
	**/
	@Override
	public void removeAll(Collection<E> c)
	{
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			remove(begin.next());
	}

	
	
	/**
	 * Retains only the elements hashset that are contained in
	 * the specified collection. For satisfaying elements, 
	 * duplicates retains in the collection.
	 * @param c, collection to retain. 
	**/
	@Override
	public void retainAll(Collection<E> c)
	{	
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
		{
			E temp = begin.next();
			if(!contains(temp))
				c.remove(temp);
		}
	}

	/**
	 * Returns the number of elements in LinkedList
	 *@return size of LinkedList. 
	**/
	public int size()
	{	
		return buf_size;
	}

	private void setSize(int s)
	{
		buf_size = s;
	}	


	/**
	 * Retrieves, but does not remove, the head of this Linked-list.
	 * @return E, head of this queue.
	 * @exception emptyQueue, throws if the queue is empty.
	**/
	public E element()throws emptyQueue
	{
		if(isEmpty()) 
			throw new emptyQueue();
		return buffer[size()-1];
	}

	/**
	 * Inserts the specified element into this queue.
	 * @param E, element to insert to queue.
	**/
	public void offer(E e)
	{
		add(e);
	}

	/**
	 * Retrieves and removes the head of this queue, or throws if this
 	 * queue is empty.
	 * @return E, head of this queue.
 	 * @exception emptyQueue, throws if the queue is empty.
	**/
	public E poll()throws emptyQueue
	{
		if(isEmpty())
			throw new emptyQueue();

		E head = buffer[size()-1];
		remove(head);
		return head;
	}
}