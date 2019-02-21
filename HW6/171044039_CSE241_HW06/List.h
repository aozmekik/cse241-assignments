#ifndef OZMEKIK_COLLECTION_LIST_H
#define OZMEKIK_COLLECTION_LIST_H

#include "Collection.h"

namespace ozmekik_collection
{
	/* List interface:
 	   @E object-type to hold in set.
 	   @container underlying data structure to be used in set.

 	   List is an ordered collection and interface satisfies 
 	   the precise control over in structure.  
 	*/


	template <typename E, typename container=std::vector<E> >
	class List: public virtual Collection<E,container>
	{
		public:

			virtual Iterator<E,container> iterator() override = 0;

			virtual void add(E e) throw(std::bad_alloc)  override = 0;

			virtual void addAll(Collection<E,container> &c) throw(std::bad_alloc) override  = 0;

			virtual void clear() override  = 0;

			virtual bool contains(E e)const  override = 0;
			
			virtual bool containsAll(Collection<E,container> &c)const override  = 0;

			virtual bool isEmpty()const override  = 0;

			virtual void remove(E e)  override = 0;

			virtual void removeAll(Collection<E,container> &c) override = 0;
			
			virtual void retainAll(Collection<E,container> &c)const override  = 0;

			virtual unsigned int size()const override = 0;
			
			virtual ~List() = default;

	};


}

#endif /* OZMEKIK_COLLECTION_LIST_H */