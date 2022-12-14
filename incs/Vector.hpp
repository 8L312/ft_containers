#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cstdlib>
# include <string>
# include <stdexcept>
# include <cmaths>
# include <memory>
# include <algorithm>
# include <cstddef>

namespace ft
{

    template <class T, class Allocator = std::allocator<T>>
    class vector{

    //RANDOM ACCESS ITERATOR OF VECTOR CLASS//
    template<typename L>class RandomAccessIterator
	{
        //ITERATOR MEMBER TYPES//
	    public:
	    	typedef	typename iterator_traits<L*>::value_type        value_type;
	    	typedef	typename iterator_traits<L*>::pointer           pointer;
	    	typedef	typename iterator_traits<L*>::reference         reference;
	    	typedef	typename iterator_traits<L*>::difference_type	difference_type;
	    	typedef pointer                                         iterator_type;
	    	typedef	std::random_access_iterator_tag                 iterator_category;

    	private:
    		pointer _ptr;
        //ITERATOR MEMBER TYPES//
	    

        public:
		    //ITERATOR CONSTRUCTORS//
		    RandomAccessIterator(void) : _ptr()
            {
                return ;
            }

    		RandomAccessIterator(pointer a) : _ptr(a)
            {
                return ;
            }

	    	virtual ~RandomAccessIterator(void)
            {
                return ;
            }

		    RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type> &src) : _ptr(&(*src))
            {
                return ;
            }

    		RandomAccessIterator<value_type> & operator=(RandomAccessIterator<typename remove_const<value_type>::type> const &src)
            {
	    		_ptr = &(*src);
	    		return (*this);
	    	}
            //ITERATOR CONSTRUCTORS//


		//ITERATOR OPERATOR OVERLOADS//
		RandomAccessIterator    &operator++(void)
        {
			++_ptr;
			return (*this);
		}

		RandomAccessIterator    operator++(int)
        {
			RandomAccessIterator tmp(*this);
			++_ptr;
			return (tmp);
		}

		RandomAccessIterator    &operator--(void)
        {
			--_ptr;
			return (*this);
		}

		RandomAccessIterator    operator--(int)
        {
			RandomAccessIterator tmp(*this);
			--_ptr;
			return (tmp);
		}

		RandomAccessIterator    operator+(const difference_type &a) const
        {
			return (_ptr + a);
		}

		RandomAccessIterator    operator-(const difference_type &a) const
        {
			return (_ptr - a);
		}

		RandomAccessIterator    &operator+=(const difference_type &a)
        {
			_ptr += a;
			return (*this);
		}

		RandomAccessIterator    &operator-=(const difference_type &a)
        {
			_ptr -= a;
			return (*this);
		}

		pointer operator->(void) const
        {
			return (_ptr);
		}

		reference   operator*(void) const
        {
			return (*_ptr);
		}

		reference   operator[](difference_type n) const
        {
			return *(_ptr + n);
		}
        //ITERATOR MEMBER OPERATOR OVERLOADS//
	};

    //ITERATOR NON MEMBER OPERATOR OVERLOADS//
	public:
	template<typename A, typename B>
	friend bool operator==(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
		return &(*lhs) == &(*rhs);
	}

	template<typename A, typename B>
	friend bool operator!=(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
	    return &(*lhs) != &(*rhs);
	}

	template<typename A, typename B>
	friend bool operator>(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
		return &(*lhs) > &(*rhs);
	}

	template<typename A, typename B>
	friend bool operator<(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
		return &(*lhs) < &(*rhs);
	}

	template<typename A, typename B>
	friend bool operator<=(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
    	return &(*lhs) <= &(*rhs);
	}

	template<typename A, typename B>
	friend bool operator>=(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
		return &(*lhs) >= &(*rhs);
	}

	template<typename A, typename B>
	friend typename vector::template RandomAccessIterator<A>::difference_type operator-(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
		return &(*lhs) - &(*rhs);
	}

	template<typename A, typename B>
	friend typename vector::template RandomAccessIterator<A>::difference_type operator+(const vector::template RandomAccessIterator<A> &lhs, const vector::template RandomAccessIterator<B> &rhs)
    {
		return &(*lhs) + &(*rhs);
	}

	template<typename L>
	friend vector::template RandomAccessIterator<L> operator+(const typename vector::template RandomAccessIterator<L>::difference_type &a, const vector::template RandomAccessIterator<L> &iter)
    {
		return (iter + a);
	}

	template<typename L>
	friend vector::template RandomAccessIterator<L> operator-(const typename vector::template RandomAccessIterator<L>::difference_type &a, const vector::template RandomAccessIterator<L> &iter)
    {
		return (iter - a);
	}
    //ITERATOR NON MEMBER OPERATOR OVERLOADS//
	

    //VECTOR MEMBER TYPES//
	public:
		typedef T                                       value_type;
		typedef Allocator                               allocator_type;
		typedef std::size_t                             size_type;
		typedef std::ptrdiff_t                          difference_type;
		typedef value_type                              &reference;
		typedef const value_type                        &const_reference;
		typedef typename Allocator::pointer             pointer;
		typedef typename Allocator::const_pointer       const_pointer;
		typedef RandomAccessIterator<value_type>        iterator;
		typedef RandomAccessIterator<const value_type>  const_iterator;
		typedef reverse_iterator<const_iterator>        const_reverse_iterator;
		typedef reverse_iterator<iterator>              reverse_iterator;
	private:
		pointer         _first;
		size_type       _size
        size_type       _capacity;
		allocator_type  _allocator;
    //VECTOR MEMBER TYPES//


    public:
    //VECTOR CONSTRUCTORS//
	explicit vector(const allocator_type &alloc = allocator_type()) : _first(0), _size(0), _capacity(0), _allocator(alloc)
    {
        return ;
    }

	explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc)
	{
		_first = _allocator.allocate(n);
		for(size_type i = 0; i < n; i++)
			_allocator.construct(_first + i, val);
        return ;
	}

	template <class InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : _allocator(alloc)
    {
		if (first > last)
			throw std::length_error("vector");
		_size = last - first;
		_capacity = _size;
		_first = _allocator.allocate(_capacity);
		for (difference_type i = 0; i < static_cast<difference_type>(_size); i++)
			_allocator.construct(_first + i, *(first + i));
        return ;
	}

	vector(const vector &src) : _size(0), _capacity(0)
	{
		*this = src;
		return (*this)
	}
    //VECTOR CONSTRUCTOR//


	//VECTROR OVERLOAD OF =//
	vector	&operator=(const vector &src)
	{
			if (this == &src)
				return *this;
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_first + i);
			this->_size = src._size;
			if(_capacity < _size){
				if (_capacity != 0)
					_allocator.deallocate(_first, _capacity);
				_capacity = _size;
				_first = _allocator.allocate(_capacity);
			}
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(_first + i, src[i]);
			return (*this);
	}
	//VECTROR OVERLOAD OF =//


	//VECTOR DESTRUCTOR//
	~vector(void)
	{
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		if(_capacity)
			_allocator.deallocate(_first, _capacity);
	}
	//VECTOR DESTRUCTOR//


    //VECTOR ITERATOR FUNCTIONS//
	iterator begin(void)
	{
		return (iterator(_first));
	}

	iterator end(void)
	{
		return (iterator(_first + _size));
	}

	reverse_iterator rbegin(void)
	{
		return (reverse_iterator(end()));
	}

	reverse_iterator rend(void)
	{
		return (reverse_iterator(begin()));
	}

	const_iterator begin(void) const
	{
		return (const_iterator(_first));
	}

	const_iterator end(void) const
	{
		return (const_iterator(_first + _size));
	}

	const_reverse_iterator rbegin(void) const
	{
		return (const_reverse_iterator(end()));
	}

	const_reverse_iterator rend(void) const
	{
		return (const_reverse_iterator(begin()));
	}
	//VECTOR ITERATOR FUNCTIONS//


	//VECTOR CAPACITY FUNCTIONS//
	size_type size(void) const
	{
		return(_size);
	}

	size_type max_size(void) const
	{
		return(_allocator.max_size());
	}

	void reserve(size_type n)
	{
		if (n < _capacity)
			return ;
		
		pointer new_arr = _allocator.allocate(n);

		try
		{
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(new_arr + i, *(_first + i));
		}
		catch (std::exception &e)
		{
			size_type i = 0;
			while (newarr + i != NULL && i < _size){
				_allocator.destroy(new_arr + i);
				i++;
			}
			_allocator.deallocate(new_arr, n);
			throw ;
		}

		for(size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		if(_capacity)
			_allocator.deallocate(_first, _capacity);
		_capacity = n;
		_first = new_arr;
	}

	void resize(size_type n, value_type val = value_type())
	{
		if(n < _size)
		{
			for(size_type i = n; i < _size; i++)
				_allocator.destroy(_first + i);
			_size = n;
		}
		else if (n > _size)
		{
			if (_capacity < n)
				this->reserve( (_capacity * 2) > n ? (_capacity * 2) : n );
			for (size_type i = _size; i < n; i++)
			{
				_allocator.construct(_first + i, val);
				_size++;
			}
		}
	}
		
	size_type capacity(void) const
	{
		return (_capacity);
	}

	bool empty(void) const
	{
		return(_size == 0);
	}
	//VECTOR CAPACITY FUNCTIONS//


	//VECTOR ELEMENT ACCESS FUNCTIONS//
	reference operator[](size_type n)
	{
		return( *(_first + n) );
	}

	const_reference operator[](size_type n) const
	{
		return( *(_first + n) );
	}
		
	reference at(size_type n)
	{
		if(n > _capacity)
			throw std::out_of_range("vector at out of range");
		return( *(_first + n) );
	}
		
	const_reference at(size_type n) const
	{
		if(n > _capacity)
			throw std::out_of_range("vector at out of range");
		return( *(_first + n) );
	}

	reference front(void)
	{
		return(*_first);
	}
		
	const_reference front(void) const
	{
		return(*_first);
	}
		
	reference back(void)
	{
		return( *(_first + _size - 1) );
	}
		
	const_reference back(void) const
	{
		return( *(_first + _size - 1) );
	}

	pointer	data(void)
	{
		return (_first);
	}

	const pointer	data(void) const
	{
		return (_first);
	}
	//VECTOR ELEMENT ACCESS FUNCTIONS//


	//VECTOR MODIFIER FUNCTIONS//
	template <class InputIterator>
  	void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
	{
		if(first > last)
				throw std::logic_error("vector");
		difference_type count = last - first;
		clear();
		if ( count > static_cast<difference_type>(capacity()) )
		{
			_allocator.deallocate(_first, _capacity);
			_first = _allocator.allocate(count);
			_capacity = count;
		}
		iterator pos = begin();
		while (first < last)
		{
			_allocator.construct(&(*pos), *first);
			pos++;
			first++;
		}
		_size = count;
	}

	void assign(size_type n, const value_type &val)
	{
		clear();
		if (n > _capacity)
		{
			_allocator.deallocate(_first, _capacity);
			_first = _allocator.allocate(n);
			_capacity = n;
		}
		for (size_type i = 0; i < n; i++)
			_allocator.construct(_first + i, val);
		_size = n;
		}
		
	void push_back(const value_type &val)
	{
		if(_size == _capacity)
			reserve(_capacity == 0 ? 1 : _capacity * 2);
		_allocator.construct(_first + _size, val);
		_size++;
	}

	void pop_back(void)
	{
		_allocator.destroy(_first + _size - 1);
		_size--;
	}

	iterator insert(iterator position, const value_type &val)
	{
		if (position < begin() || position > end())
			throw std::logic_error("vector");
		difference_type start = position - begin();
		if (_size == _capacity){
			_capacity = _capacity * 2 + (_capacity == 0);
			pointer new_arr = _allocator.allocate(_capacity);
			std::uninitialized_copy(begin(), position, iterator(new_arr));
			_allocator.construct(new_arr + start, val);
			std::uninitialized_copy(position, end(), iterator(new_arr + start + 1));
			for (size_t i = 0; i < _size; i++)
				_allocator.destroy(_first + i);
			if(_size)
				_allocator.deallocate(_first, _size);
			_size++;
			_first = new_arr;
		}
		else
		{
			for (size_type i = _size; i > static_cast<size_type>(start); i--)
			{
				_allocator.destroy(_first + i);
				_allocator.construct(_first + i, *(_first + i - 1));
			}
			_allocator.destroy(&(*position));
			_allocator.construct(&(*position), val);
			_size++;
		}
		return (begin() + start);
	}

	//fill
	void insert(iterator position, size_type n, const value_type &val)
	{
		if (n == 0)
			return ;
		else if (max_size() - _size < n)
			throw std::length_error("vector");
		difference_type start = position - begin();
		if (_size + n > _capacity)
		{
			size_type new_cap = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
			pointer new_arr = _allocator.allocate(new_cap);
			std::uninitialized_copy(begin(), position, iterator(new_arr));
			for (size_type i = 0; i < n; i++)
				_allocator.construct(new_arr + start + i, val);
			std::uninitialized_copy(position, end(), iterator(new_arr + start + n));
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_first + i);
			_allocator.deallocate(_first, _capacity);
			_size += n;
			_capacity = new_cap;
			_first = new_arr;
		}
		else
		{
			for (size_type i = _size; i > static_cast<size_type>(start); i--)
			{
				_allocator.destroy(_first + i + n - 1);
				_allocator.construct(_first + i + n - 1, *(_first + i - 1));
			}
			for (size_type i = 0; i < n; i++)
			{
				_allocator.destroy(_first + i + start);
				_allocator.construct(_first + i + start, val);
			}
			_size += n;
		}
	}

	//range
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
	{
	if (position < begin() || position > end() || first > last)
		throw std::logic_error("vector");
	size_type start = static_cast<size_type>(position - begin());
	size_type count = static_cast<size_type>(last - first);
	if (_size + count > _capacity)
	{
		size_type new_cap = _capacity * 2 >= _size + count ? _capacity * 2 : _size + count;
		pointer new_arr = _allocator.allocate(new_cap);
		std::uninitialized_copy(begin(), position, iterator(new_arr));
		try {
			for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
				_allocator.construct(new_arr + start + i, *first);
			}
		catch (...)
		{
			for (size_type i = 0; i < count + start; ++i)
				_allocator.destroy(new_arr + i);
			_allocator.deallocate(new_arr, new_cap);
			throw ;
		}
		std::uninitialized_copy(position, end(), iterator(new_arr + start + count));
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		_allocator.deallocate(_first, _capacity);
		_size += count;
		_capacity = new_cap;
		_first = new_arr;
	}
	else
	{
		for (size_type i = _size; i > static_cast<size_type>(start); i--)
		{
			_allocator.destroy(_first + i + count - 1);
			_allocator.construct(_first + i + count - 1, *(_first + i - 1));
		}
		for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
		{
			_allocator.destroy(_first + i + count);
			_allocator.construct(_first + start + i, *first);
		}
		_size += count;
		}
	}

	//single element
	iterator erase(iterator position)
	{
		size_type d = static_cast<size_type>(std::distance(begin(), position));
		for (size_type i = d; i < _size - 1; ++i)
		{
			_allocator.destroy(_first + i);
			_allocator.construct(_first + i, *(_first + i + 1));
		}
		_size--;
		_allocator.destroy(_first + _size - 1);
		return iterator(_first + d);
	}

	//range
	iterator erase(iterator first, iterator last)
	{
		difference_type start = std::distance(begin(), first);
		difference_type need_to_copy = std::distance(last, end());
		bool last_is_end = (last == end());
		while (first != last){
			_allocator.destroy(&(*first));
		first++;
		}
		size_type i = start;
		while (last < end())
		{
			if (this->_first + start)
				_allocator.destroy(_first + i);
			_allocator.construct(_first + i, *last);
			i++;
			last++;
		}
		for (size_type i = start + need_to_copy; i < _size; i++)
			_allocator.destroy(_first + i);
		_size = start + need_to_copy;
		return last_is_end ? end() : iterator(_first + start);
	}
		
	void swap(vector &other)
	{
		std::swap(_first, other._first);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
		std::swap(_allocator, other._allocator);
	}

	void clear(void)
	{
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		_size = 0;
	}
	//VECTOR MODIFIER FUNCTIONS//


	//VECTOR ALLOCATOR//
	allocator_type get_allocator(void) const
	{
		return(_allocator);
	}
	//VECTOR ALLOCATOR//	
};

//VECTOR RELATIONAL OPERATORS OVERLOADS//
template<class T, class Alloc>
bool operator==( const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs )
{
	if (lhs.size() != rhs.size())
		return false;
	for (size_t i = 0; i < rhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

template< class T, class Alloc >
bool operator!=( const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs )
{
	return !(lhs == rhs);
}

template< class T, class Alloc >
bool operator<( const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
	
template< class T, class Alloc >
bool operator<=( const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs )
{
	return !(lhs > rhs);
}
	
template< class T, class Alloc >
bool operator>( const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs )
{
	return (rhs < lhs);
}

template< class T, class Alloc >
bool operator>=( const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs )
{
	return !(lhs < rhs);
}
//VECTOR RELATIONAL OPERATORS OVERLOADS//
};

//VECTOR SWAP//
namespace std
{
template< class T, class Alloc >
void swap( ft::vector<T,Alloc> &lhs, ft::vector<T,Alloc> &rhs )
{
	lhs.swap(rhs);
}
}
//VECTOR SWAP//

#endif