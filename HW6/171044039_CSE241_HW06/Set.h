#ifndef OZMEKIK_COLLECTION_SET_H
#define OZMEKIK_COLLECTION_SET_H

#include "Collection.h"

namespace ozmekik_collection
{
 	/* Set interface:
 	   @E object-type to hold in set.
 	   @container underlying data structure to be used in set.

 	   Set is a collection that contains no duplicate elements. 
 	   There is no order for this collection. 
 	*/

	template <typename E, typename container=std::vector<E> >
	class Set: public Collection<E,container>
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
			
			virtual ~Set() = default;

	};


}

#endif /* OZMEKIK_COLLECTION_SET_H */