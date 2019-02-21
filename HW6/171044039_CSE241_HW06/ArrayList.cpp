#ifndef OZMEKIK_COLLECTION_ARRAYLIST_HPP_
#define OZMEKIK_COLLECTION_ARRAYLIST_HPP_

#include "List.h"
#include <algorithm>

namespace ozmekik_collection
{
	/* ArrayList implements List interface. */
	/* Class E, must have operator< defined */   
	template <typename E, typename container=std::vector<E> >
	class ArrayList: public List<E,container>
	{
		public:
			ArrayList();
			/* No paramater constructor. Initial size is zero, and 
		 	 * underlying container created */

			Iterator<E,container> iterator();
			/* Returns an Iterator over ArrayList. 
			 * Since List is an ordered collection, you have a precise
			 * control over where in the list each is element is inserted
			 * due to insertion order. */

			void add(E e) throw(std::bad_alloc);
			/* @param E, Element to insert.
			 * Inserts the specified element into this ArrayList
			 * You can have duplicates of an element and insertion  
			 * order specifies your sequence's order */

			
			void addAll(Collection<E,container> &c) throw(std::bad_alloc);
			/* @param c, collection to insert.  
			 * Adds all of the elements in the specified collection to ArrayList */

			void clear();
			/* Removes all of the elements from ArrayList */

			bool contains(E e)const;
			/* Returns true if the ArrayList contains the specified element,
	 		 * at least one time. */

			
			bool containsAll(Collection<E,container> &c)const;
			/* @param c, collection to look for.
			 * Returns true if this ArrayList contains all of the elements in the
		 	 * specified collection. All of them must be in the ArrayList at least
		 	 * one time. */

			bool isEmpty()const;
			/* Returns true if the ArrayList contains no element */

			void remove(E e);
		   	/* @param e, element to delete from list.
			 * Removes the specified element from the ArrayList.
			 * All duplicates of this element in the ArrayList, are removed. */

			
			void removeAll(Collection<E,container> &c);	
			/* @param c, elements in this collection will be deleted.   
			 * Removes all duplicates of ArrayList's elements that 
			 * are also contained in the specified collection. */

			
			void retainAll(Collection<E,container> &c)const;
			/* @param c, collection to retain. 
			 * Retains only the elements hashset that are contained in
			 * the specified collection. For satisfaying elements, 
			 * duplicates retains in the collection.  */

			unsigned int size()const;
			/* Returns the number of elements in ArrayList. */


		private:
			container buffer;
			unsigned int buf_size;
			void setSize(unsigned int s);

	};

	template <typename E, typename container>
	ArrayList<E,container>::ArrayList()
	: buffer(),
	  buf_size(0)
	{
		/* intentionally left blank */
	}	

	template <typename E, typename container>
	void ArrayList<E,container>::add(E e) throw(std::bad_alloc)
	{
		buffer.insert(buffer.end(), e);
		setSize(size()+1);
	}

	template <typename E, typename container>
	Iterator<E,container>  ArrayList<E,container>::iterator()
	{
		return Iterator<E,container>(&buffer);
	}

	template <typename E, typename container>
	void ArrayList<E,container>::addAll(Collection<E,container> &c)throw(std::bad_alloc)
	{

		for_each(c.iterator(), [&](E &e){add(e);});

	}

	template <typename E, typename container>
	void ArrayList<E,container>::setSize(unsigned int s)
	{
		buf_size = s;
	}

	template <typename E, typename container>
	void ArrayList<E,container>::clear()
	{
		buffer.clear();
		setSize(0);

	}

	template <typename E, typename container>
	bool ArrayList<E,container>::contains(E e)const
	{
		bool found = false;

		if(isEmpty()) 
			found = false;
		else if(std::find(buffer.begin(),buffer.end(), e) != buffer.end())
			found = true;	

		return found;
	}

	template <typename E, typename container>
	bool ArrayList<E,container>::containsAll(Collection<E,container> &c)const
	{
		bool found = true;
		for_each(c.iterator(),[&](E &e){found = found && contains(e);});
		return found; 

	}

	template <typename E, typename container>
	bool ArrayList<E,container>::isEmpty()const
	{
		return (size()==0);

	}

	template <typename E, typename container>
	void ArrayList<E,container>::remove(E e)
	{
		auto it = std::find(buffer.begin(), buffer.end(), e);
		while(buffer.end()!=it)
		{
			buffer.erase(it);
			setSize(size()-1);
			it = std::find(buffer.begin(), buffer.end(), e);
		}

	}

	template <typename E, typename container>
	void ArrayList<E,container>::removeAll(Collection<E,container> &c)
	{
		for_each(c.iterator(), [&](E &e){remove(e);});
	}

	template <typename E, typename container>
	void ArrayList<E,container>::retainAll(Collection<E,container> &c)const
	{
		for_each(c.iterator(), [&](E &e) 
		{
			if(!contains(e))
				c.remove(e);
		});
	}

	template <typename E, typename container>
	unsigned int ArrayList<E,container>::size()const
	{
		return buf_size;
	}


}

#endif /* OZMEKIK_COLLECTION_ARRAYLIST_HPP_ */