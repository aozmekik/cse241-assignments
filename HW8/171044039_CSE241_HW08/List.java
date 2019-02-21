/** 
 * Represents the List interface.
 * List is an ordered collection and interface satisfies 
 * the precise control over in structure.   
 * @param E object-type to hold in set.
 * @author Ahmed Semih Özmekik
 * @version 1.0
 * @since 2019-01-14
*/

public interface List<E> extends Collection<E>
{

	/**
	 * Returns an iterator over the List
	 * @return Iterator, iterator over List.
	 * @see Iterator
	*/
	public Iterator<E> iterator();

	/**
	 * Ensures that this List contains the specified element.
	**/
	public void add(E e);

	/**
	 * Adds all of the elements in the specified List to this
     * List.
	**/
	public void addAll(Collection<E> c);

	/**
	 * Removes all of the elements from this List.
	**/
	public void clear();

	/**
	 * Returns true if this List contains the specified element.
	 * @return true if List contains specified element, false if
	 * List does not contain the specified element. 
	**/
	public boolean contains(E e);

	/**
	 * Returns true if this List contains all of the elements in the
 	 * specified List.
 	 * @return true if List contains the specified List's all
 	 * elements, false if the List does not contain at least one element 
 	 * from the specified List. 
	**/
	public boolean containsAll(List<E> c);

	/**
	 * Returns true if this List contains no elements.
	 * @return true if List is empty, false if it's not empty.
	**/
	public boolean isEmpty();

	/**
	 * Removes a single instance of the specified element from this
     * List, if it is present.
	**/
	public void remove(E e);

	/**
	 * Removes all of this List's elements that are also contained
  	 * in the specified List.
	**/
	public void removeAll(Collection<E> c);

	/**
	 * Retains only the elements in this List that are contained in
	 * the specified List.
	**/
	public void retainAll(Collection<E> c);

	/**
	 * Returns the number of elements in this List.
	 * @return size of the List.
	**/
	public int size();
} 