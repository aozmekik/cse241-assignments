#ifndef OZMEKIK_COLLECTION_QUEUE_H
#define OZMEKIK_COLLECTION_QUEUE_H

#include "Collection.h"


namespace ozmekik_collection
{
	/* Queue interface:
 	   @E object-type to hold in set.
 	   @container underlying data structure to be used in set.

 	  Queue order elements in a FIFO (first-in-first-out) manner. 
 	  There is no random access with this Collection. Some
 	  functions throw bad_request exception; indicates 
 	  request from queue is not valid.   
 	*/

	class empty_queue; // forward decl of exception.

	template <typename E, typename container=std::vector<E> >
	class Queue: public virtual Collection<E,container>
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

			virtual E element()throw(empty_queue) = 0;
			virtual void offer(E e)throw(std::bad_alloc) = 0;
			virtual E poll()throw(empty_queue) = 0; 

			/* Functions requires random access must throw bad_request
			 * in the implementation. */ 

			virtual ~Queue() = default;
	};

	class empty_queue : public std::exception
	{
		public:
			virtual const char* what() const noexcept override
			{
				return "Invalid Request! Queue is empty!";
			}
	};


}

#endif /* OZMEKIK_COLLECTION_QUEUE_H */