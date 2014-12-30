#if !defined(CW_INCL_ALGORITHM)
#	define CW_INCL_ALGORITHM

namespace std {

	template<class T> 
	const T& max(const T& a, const T& b)
	{
		return (a < b) ? b : a;
	}

	template<class T, class Compare> 
	const T& max(const T& a, const T& b, Compare comp)
	{
		return (comp(a, b)) ? b : a;
	}

//	template< class T >
//	T max( std::initializer_list<T> ilist)
//	{
//		return *std::max_element(ilist.begin(), ilist.end());
//	}

//	template< class T, class Compare >
//	T max( std::initializer_list<T> ilist, Compare comp )
//	{
//		return *std::max_element(ilist.begin(), ilist.end(), comp);
//	}

	template<class T> 
	const T& min(const T& a, const T& b)
	{
		return (b < a) ? b : a;
	}

	template<class T, class Compare> 
	const T& min(const T& a, const T& b, Compare comp)
	{
		return (comp(b, a)) ? b : a;
	}

//	template<class T>
//	T min( std::initializer_list<T> ilist)
//	{
//		return *std::min_element(ilist.begin(), ilist.end());
//	}

//	template<class T, class Compare>
//	T min(std::initializer_list<T> ilist, Compare comp)
//	{
//		return *std::min_element(ilist.begin(), ilist.end(), comp);
//	}
}

#endif