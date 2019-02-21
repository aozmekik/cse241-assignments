#ifndef OZMEKIK_COLLECTION_HashSet_HPP_
#define OZMEKIK_COLLECTION_HashSet_HPP_

#include "Set.h"
#include "Iterator.cpp"
#include <algorithm>

namespace ozmekik_collection
{
	/* HashSet implements Set interface. */  
	template <typename E, typename container=std::vector<E> >
	class HashSet : public Set<E,container>
	{
		public:
			HashSet();
			/* No paramater constructor. Initial size is zero, and 
			 * underlying container created */

			Iterator<E,container> iterator();
			/* Returns an Iterator over HashSet. */


			void add(E e) throw(std::bad_alloc) override;
			/* @param e, element to insert to HashSet. 
			 * Ensures that HashSet contains the specified element 
			 * Adds if it's not in the HashSet, does not do anything 
			 * if it's already in the HashSet. 
			 */

			
			void addAll(Collection<E,container>&) throw(std::bad_alloc) override;
			/* @param c, collection to insert.
			 * Ensures that HashSet contains all of the elements in the 
			 * specified collection. Again, duplicates are permitted. */

			void clear()override;
			/* Removes all of the elements from HashSet */

			bool contains(E e)const override;
			/* Returns true if the HashSet contains the specified element */

			
			bool containsAll(Collection<E,container>&)const override;
			/* @param c, collection to look for.
			 * Returns true if this HashSet contains all of the elements in the
		     * specified collection. */

			bool isEmpty()const override;
			/* Returns true if the HashSet contains no element */

			void remove(E e) override;
			/* @param e, element to remove from HashSet.
			 * Ensures that HashSet does not contain the specified element
			 * Removes if it's in the HashSet, does not do anything
			 * if it's already not in the HashSet */

			
			void removeAll(Collection<E,container>&) override;
			/* @param c, collection to remove from set.
			 * Removes all of HashSet's elements that are also contained
			 * in the specified collection */

			
			void retainAll(Collection<E,container>&)const override;
			/* @param c, collection to retain. 
			 * Retains only the elements HashSet that are contained in
			 * the specified collection */

			unsigned int size()const override;
			/* Returns the number of elements in HashSet */

		
		private:
			container buffer; // underlying container.
			unsigned int buf_size;

			void setSize(unsigned int);
	};

	template <typename E, typename container>
	HashSet<E,container>::HashSet()
	: buffer(),
	  buf_size(0)
	{
		/* intentionally left blank */
	}	

	
	template <typename E, typename container>
	void HashSet<E,container>::add(E e) throw(std::bad_alloc)
	{
		if(!contains(e))
		{
			buffer.insert(buffer.end(),e);
			setSize(size()+1);
		}
		
	}

	template <typename E, typename container>
	void HashSet<E,container>::addAll(Collection<E,container> &c)throw(std::bad_alloc)
	{

		for_each(c.iterator(), [&](E& e){add(e);});

	}

	template <typename E, typename container>
	void HashSet<E,container>::setSize(unsigned int s)
	{
		buf_size = s;
	}

	template <typename E, typename container>
	void HashSet<E,container>::clear()
	{
		buffer.clear();
		setSize(0);

	}

	template <typename E, typename container>
	Iterator<E,container>  HashSet<E,container>::iterator()
	{
		return Iterator<E,container>(&buffer);
	}

	template <typename E, typename container>
	bool HashSet<E,container>::contains(E e)const
	{
		bool found = false;

		if(isEmpty()) 
			found = false;
		else if(std::find(buffer.begin(),buffer.end(), e) != buffer.end())
			found = true;	

		return found;
	}


	template <typename E, typename container>
	bool HashSet<E,container>::containsAll(Collection<E,container> &c)const
	{
		bool found = true;
		for_each(c.iterator(),[&](E &e){found = found && contains(e);});
		return found; 

	}

	template <typename E, typename container>
	bool HashSet<E,container>::isEmpty()const
	{
		return (size()==0);

	}

	template <typename E, typename container>
	void HashSet<E,container>::remove(E e)
	{
		auto it = std::find(buffer.begin(), buffer.end(), e);
		if(it!=buffer.end())
		{
			buffer.erase(it);
			setSize(size()-1);
		}

	}

	
	template <typename E, typename container>
	void HashSet<E,container>::removeAll(Collection<E,container> &c)
	{
		for_each(c.iterator(), [&](E &e){remove(e);});
	}

	template <typename E, typename container>
	
	void HashSet<E,container>::retainAll(Collection<E,container> &c)const
	{
		for_each(c.iterator(), [&](E &e) 
		{
			if(!contains(e))
				c.remove(e);
			
		});

	}

	template <typename E, typename container>
	unsigned int HashSet<E,container>::size()const
	{
		return buf_size;
	}

}


#endif /* OZMEKIK_COLLECTION_HashSet_HPP_ */