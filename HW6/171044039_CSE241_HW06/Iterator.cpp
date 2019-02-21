#ifndef OZMEKIK_COLLECTION_ITERATOR_H
#define OZMEKIK_COLLECTION_ITERATOR_H

#include <vector>
#include <exception>

namespace ozmekik_collection
{
	class bad_iter; // forward declaration of exception.

	template <typename E, typename container=std::vector<E> >
	class Iterator
	{	
		public:
			Iterator(container*);
			Iterator();

			const E& operator*()const; // dereference as an lvalue.
			E& operator*(); // dereference as an rvalue.

			/* Returns the next element in the iteration and advances the
			 * iterator. */
			E& next();

			/* Removes from the underlying collection the last element returned
			 * by this iterator. */
			void remove()throw(bad_iter);

			/* Returns true if the iteration has more elements. */
			bool hasNext()const;

			bool isNull()const { return (it==cp->end());}

		private:
			// Pointer to buffer. 
			container *cp; 
			// underlying std iterator to handle stuff..
			typename container::iterator it;

			// keeps track of last returned Iterator
			typename container::iterator last_returned;


	};

	template <typename E, typename container > 
	Iterator<E,container>::Iterator(): cp(nullptr),it(), last_returned()
	{/* intentionally left blank*/}

	template <typename E, typename container >
	Iterator<E,container>::Iterator(container* c)
	:cp(c), 
	 it(c->begin()), 
	 last_returned(c->end()) // Null value for iterator
	{/* intentionally left blank*/}

	template <typename E, typename container >
	E& Iterator<E,container>::next()
	{
		++it;
		last_returned = it;
		return *(*this);	
	}

	template<typename E, typename container > 
	const E& Iterator<E,container>::operator*()const
	{
		last_returned = it;
		return *it;  
	}

	template <typename E, typename container >
	E& Iterator<E,container>::operator*()
	{
		last_returned = it;
		return *it;
	} 

	template <typename E, typename container >
	bool Iterator<E,container>::hasNext()const
	{
		return (std::next(it,1)!=cp->end());
	}

	template <typename E, typename container >
	void Iterator<E,container>::remove()throw(bad_iter)
	{
		// nothing returned in session.
		if(last_returned==cp->end()) throw bad_iter();

		cp->erase(last_returned);
	}


	/* ozmekik_collection::for_each implementation.
	 * Similar to stl::for_each.(probably not implementational wise)
	 * I needed a function to iterate over my collection for 
	 * the lots of the cases. So for the sake of reuse, I added this one.
	 */ 
	template<typename E, typename container, typename F> 
	void for_each(Iterator<E,container> begin, F&& fun)
	{

	
		do // does the given unary functor to elements 
		{  //from starting iterator 'til the end.
			fun(*begin);
			begin.next();
		}while(begin.hasNext());

		fun(*begin);
		
	}


	class bad_iter : public std::exception
	{
		public:
			virtual const char* what() const noexcept override
			{
				return "Can't Remove! There isn't any last returned iterator.";
			}
	};
	


}

#endif // OZMEKIK_COLLECTION_ITERATOR_H