#ifndef OZMEKIK_COLLECTION_LINKEDLIST_HPP_
#define OZMEKIK_COLLECTION_LINKEDLIST_HPP_

#include "List.h"
#include "Queue.h"
#include <algorithm>

namespace  ozmekik_collection
{
	/* Implements both List and Queue interfaces. */
	template <typename E, typename container=std::vector<E> >
	class LinkedList : public List<E,container>, Queue<E,container>
	{
		public:

			LinkedList();
			/* No paramater constructor. Initial size is zero, and 
		 	 * underlying container created */

			Iterator<E,container> iterator() override;
			/* Returns an Iterator over LinkedList. 
			 * In the Linked-List each is element is inserted
			 * due to insertion order. */

			void add(E e) throw(std::bad_alloc) override;
			/* @param E, Element to insert.
			 * Inserts the specified element into this LinkedList
			 * You can have duplicates of an element and insertion 
			 * order specifies your sequence's order. */

			
			void addAll(Collection<E,container> &c) throw(std::bad_alloc) override;
			/* @param c, collection to insert.  
			 * Adds all of the elements in the specified collection to LinkedList */

			void clear() override;
			/* Removes all of the elements from LinkedList */

			bool contains(E e)const override;
			/* Returns true if the LinkedList contains the specified element,
			 * at least one time. */

			
			bool containsAll(Collection<E,container> &c)const override; 
			/* @param c, collection to look for.
			 * Returns true if the linked-list contains all of the elements in the
		 	 * specified collection. All of them must be in the LinkedList at least
		 	 * one time. */

			/* Returns true if the LinkedList contains no element */
			bool isEmpty()const;

			void remove(E e) override;
		   	/* @param e, element to delete from list.
			 * Removes the specified element from the LinkedList.
			 * All duplicates of this element in the LinkedList, are removed. */

			
			void removeAll(Collection<E,container> &c) override;
			/* @param c, elements in this collection will be deleted.   
			 * Removes all duplicates of LinkedList's elements that 
			 * are also contained in the specified collection. */

			
			void retainAll(Collection<E,container> &c)const override;
			/* @param c, collection to retain. 
			 * Retains only the elements that are contained in
			 * the specified collection. For satisfaying elements, 
			 * duplicates retains in the collection.  */

			unsigned int size()const override;
			/* Returns the number of elements in LinkedList. */


			E element()throw(empty_queue)override;
			void offer(E e)throw(std::bad_alloc)override;
			E poll()throw(empty_queue)override; 

		private:
			container buffer;
			unsigned int buf_size;

			void setSize(unsigned int s);

	};

	template <typename E, typename container >
	LinkedList<E,container>::LinkedList()
	: buffer(),
	  buf_size(0)
	{
		/* intentionally left blank */
	}	

	
	template <typename E, typename container >
	void LinkedList<E,container>::add(E e) throw(std::bad_alloc)
	{
		buffer.insert(buffer.begin(), e);
		setSize(size()+1);
	}


	template <typename E, typename container >
	Iterator<E,container>  LinkedList<E,container>::iterator()
	{
		return Iterator<E,container>(&buffer);
	}

	template <typename E, typename container >
	void LinkedList<E,container>::addAll(Collection<E,container> &c)throw(std::bad_alloc)
	{

		for_each(c.iterator(), [&](E &e){add(e);});

	}

	template <typename E, typename container >
	void LinkedList<E,container>::setSize(unsigned int s)
	{
		buf_size = s;
	}

	template <typename E, typename container >
	void LinkedList<E,container>::clear()
	{
		buffer.clear();
		setSize(0);

	}

	template <typename E, typename container >
	bool LinkedList<E,container>::contains(E e)const
	{
		bool found = false;

		if(isEmpty()) 
			found = false;
		else if(std::find(buffer.begin(),buffer.end(), e) != buffer.end())
			found = true;	

		return found;
	}

	template <typename E, typename container >
	bool LinkedList<E,container>::containsAll(Collection<E,container> &c)const
	{
		bool found = true;
		for_each(c.iterator(),[&](E &e){found = found && contains(e);});
		return found; 

	}

	template <typename E, typename container >
	bool LinkedList<E,container>::isEmpty()const
	{
		return (size()==0);

	}

	template <typename E, typename container >
	void LinkedList<E,container>::remove(E e)
	{
		auto it = std::find(buffer.begin(), buffer.end(), e);
		while(buffer.end()!=it)
		{
			buffer.erase(it);
			setSize(size()-1);
			it = std::find(buffer.begin(), buffer.end(), e);
		}

	}

	template <typename E, typename container >
	void LinkedList<E,container>::removeAll(Collection<E,container> &c)
	{
		for_each(c.iterator(), [&](E &e){remove(e);});
	}

	template <typename E, typename container >
	
	void LinkedList<E,container>::retainAll(Collection<E,container> &c)const
	{
		for_each(c.iterator(), [&](E &e) 
		{
			if(!contains(e))
				c.remove(e);
		});
	}

	template <typename E, typename container >
	unsigned int LinkedList<E,container>::size()const
	{
		return buf_size;
	}

	template <typename E, typename container >
	E LinkedList<E,container>::element()throw(empty_queue)
	{
		if(isEmpty()) throw empty_queue();

		return *(buffer.begin()); // head of this queue.
	}

	template <typename E, typename container >
	void LinkedList<E,container>::offer(E e)throw(std::bad_alloc)
	{
		buffer.insert(buffer.begin(), e);
		setSize(size()+1);
	}

	template <typename E, typename container >
	E LinkedList<E,container>::poll()throw(empty_queue)
	{
		if(isEmpty()) throw empty_queue();

		E head = *(buffer.begin());

		buffer.erase(buffer.begin()); // remove the head
		setSize(size()-1);

		return head;
	}

	
}

#endif /* OZMEKIK_COLLECTION_LINKEDLIST_HPP_ */