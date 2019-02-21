/** 
 * Represents the Set interface.
 * Set is a Set that contains no duplicate elements. 
 * There is no order for this Set. 
 * @param E object-type to hold in set.
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-14
*/

public interface Set<E> extends Collection<E>
{

	/**
	 * Returns an iterator over the set
	 * @return Iterator, iterator over set.
	 * @see Iterator
	*/
	public Iterator<E> iterator();

	/**
	 * Ensures that this Set contains the specified element.
	**/
	public void add(E e);

	/**
	 * Adds all of the elements in the specified Set to this
     * Set.
	**/
	public void addAll(Collection<E> c);

	/**
	 * Removes all of the elements from this Set.
	**/
	public void clear();

	/**
	 * Returns true if this Set contains the specified element.
	 * @return true if Set contains specified element, false if
	 * Set does not contain the specified element. 
	**/
	public boolean contains(E e);

	/**
	 * Returns true if this Set contains all of the elements in the
 	 * specified Set.
 	 * @return true if Set contains the specified Set's all
 	 * elements, false if the Set does not contain at least one element 
 	 * from the specified Set. 
	**/
	public boolean containsAll(Collection<E> c);

	/**
	 * Returns true if this Set contains no elements.
	 * @return true if Set is empty, false if it's not empty.
	**/
	public boolean isEmpty();

	/**
	 * Removes a single instance of the specified element from this
     * Set, if it is present.
	**/
	public void remove(E e);

	/**
	 * Removes all of this Set's elements that are also contained
  	 * in the specified Set.
	**/
	public void removeAll(Collection<E> c);

	/**
	 * Retains only the elements in this Set that are contained in
	 * the specified Set.
	**/
	public void retainAll(Collection<E> c);

	/**
	 * Returns the number of elements in this Set.
	 * @return size of the Set.
	**/
	public int size();
}  