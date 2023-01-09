#ifndef ITERATORS_HPP
# define ITERATORS_HPP

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

template <class Iterator> class iterator_traits
{
	public:
		typedef typename Iterator::difference_type	    difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer		    	pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
};

template <class T> class iterator_traits<T*>
{
	public:
		typedef std::ptrdiff_t	                    difference_type;
		typedef T			                    	value_type;
		typedef T			                        *pointer;
		typedef T			                        &reference;
		typedef	std::random_access_iterator_tag	    iterator_category;
};

template <class T> class iterator_traits<const T*>
{
	public:
		typedef std::ptrdiff_t                  	difference_type;
		typedef const T			                	value_type;
		typedef const T 		                	*pointer;
		typedef const T	                       		&reference;
		typedef	std::random_access_iterator_tag	    iterator_category;
};

template <class Iterator> class reverse_iterator
{
    //CLASS MEMBERS TYPES//
	public:
		typedef	Iterator	                                            iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;;
		typedef typename iterator_traits<Iterator>::value_type          value_type;
		typedef typename iterator_traits<Iterator>::difference_type     difference_type;
		typedef typename iterator_traits<Iterator>::pointer             pointer;
		typedef typename iterator_traits<Iterator>::reference           reference;
	
    private:
		iterator_type	base_iterator;
	//CLASS MEMBERS TYPES//

    public:
        //CLASS MEMBER FUNCTIONS//
        reverse_iterator() : base_iterator() {}

		explicit reverse_iterator (iterator_type it) : base_iterator(it) {}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it)
        {
			base_iterator = rev_it.base_iterator;
		}

		iterator_type	base(void) const
		{
			return (base_iterator);
		}
        //CLASS MEMBER FUNCTIONS//


        //CLASS OPERATOR OVERLOADS//
		reference   operator*(void) const
		{
			iterator_type tmp = base_iterator;
			return (*--tmp);
		}

		reverse_iterator    operator+(difference_type n) const
		{
			return (reverse_iterator(base_iterator - n));	
		}

		reverse_iterator    &operator++(void)
		{
			--base_iterator;
			return(*this);
		}

		reverse_iterator    operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return temp;	
		}

		reverse_iterator    &operator+=(difference_type n)
        {
			base_iterator -= n;
			return (*this);
		}

		reverse_iterator    operator-(difference_type n) const
        {
			return (reverse_iterator(base_iterator + n)); 
		}

		reverse_iterator    &operator--(void)
		{
			++base_iterator;
			return(*this);
		}

		reverse_iterator    operator--(int)
        {
			reverse_iterator temp = *this;
			--(*this);
			return temp;
		}

		reverse_iterator    &operator-=(difference_type n)
        {
			base_iterator += n;
			return (*this);
		}

		pointer operator->(void) const
        {
			return &(operator*());
		}

		reference   operator[](difference_type n) const
        {
			return (base_iterator[-n-1]);
		}
        //CLASS OPEARATOR OVERLOADS//
};

//NON MEMBER CLASS OPERATOR OVERLOADS//
template <class Iterator>
bool    operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return(lhs.base() == rhs.base());
}

template <class Iterator>
bool    operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return(lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

template <class Iterator>
reverse_iterator<Iterator>  operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
{
	return(rev_it + n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return( lhs.base() - rhs.base() );
}
//NON MEMBER CLASS OPERATOR OVERLOADS//

}

#endif