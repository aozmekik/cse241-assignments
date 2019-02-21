#ifndef OZMEKIK_COLLECTION_COLLECTION_H
#define OZMEKIK_COLLECTION_COLLECTION_H

#include "Iterator.cpp"
#include <vector>
#include <exception>	

namespace ozmekik_collection
{
	template< typename E, typename container=std::vector<E> >
	class Collection
	{
		public:

			virtual Iterator<E,container> iterator() = 0;

			virtual void add(E e) throw(std::bad_alloc) = 0;

			virtual void addAll(Collection<E,container> &c) throw(std::bad_alloc) = 0;

			virtual void clear() = 0;

			virtual bool contains(E e)const = 0;

			virtual bool containsAll(Collection<E,container> &c)const = 0;

			virtual bool isEmpty()const = 0;

			virtual void remove(E e) = 0;

			virtual void removeAll(Collection<E,container> &c) = 0;

			virtual void retainAll(Collection<E,container> &c)const = 0;

			virtual unsigned int size()const = 0;

			virtual ~Collection() = default;

	}; 

}

#endif /* OZMEKIK_COLLECTION_COLLECTION_H */