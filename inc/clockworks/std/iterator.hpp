#if !defined(CW_INCL_STD_ITERATOR)
#	define CW_INCL_STD_ITERATOR

namespace std
{
    enum iterator_status_flag
    {
        isf_none            = 0x00,
        isf_valid           = 0x01,
        isf_current         = 0x02,
        isf_can_dereference = 0x04
    };

        struct input_iterator_tag { };
        struct output_iterator_tag { };
        struct forward_iterator_tag       : public input_iterator_tag { };
        struct bidirectional_iterator_tag : public forward_iterator_tag { };
        struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    template <typename Category, typename T, typename Distance = ptrdiff_t, 
              typename Pointer = T*, typename Reference = T&>
    struct iterator
    {
        typedef Category  iterator_category;
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
    };
	
    template <typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    template <typename T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                                        value_type;
        typedef ptrdiff_t                                difference_type;
        typedef T*                                       pointer;
        typedef T&                                       reference;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                                        value_type;
        typedef ptrdiff_t                                difference_type;
        typedef const T*                                 pointer;
        typedef const T&                                 reference;
    };

    template <typename Iterator>
    class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                                             typename iterator_traits<Iterator>::value_type,
                                             typename iterator_traits<Iterator>::difference_type,
                                             typename iterator_traits<Iterator>::pointer,
                                             typename iterator_traits<Iterator>::reference>
    {
    public:
        typedef Iterator                                                   iterator_type;
        typedef typename iterator_traits<Iterator>::pointer         pointer;
        typedef typename iterator_traits<Iterator>::reference       reference;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;

    protected:
        Iterator mIterator;

    public:
        reverse_iterator()
            : mIterator() { }

        explicit reverse_iterator(iterator_type i)
            : mIterator(i) { }

        reverse_iterator(const reverse_iterator& ri)
            : mIterator(ri.mIterator) { }

        template <typename U>
        reverse_iterator(const reverse_iterator<U>& ri)
            : mIterator(ri.base()) { }

        iterator_type base() const
            { return mIterator; }

        reference operator*() const
        {
            iterator_type i(mIterator);
            return *--i;
        }

        pointer operator->() const
            { return &(operator*()); }

        reverse_iterator& operator++()
            { --mIterator; return *this; }

        reverse_iterator operator++(int)
        {
            reverse_iterator ri(*this);
            --mIterator;
            return ri;
        }

        reverse_iterator& operator--()
            { ++mIterator; return *this; }

        reverse_iterator operator--(int)
        {
            reverse_iterator ri(*this);
            ++mIterator;
            return ri;
        }

        reverse_iterator operator+(difference_type n) const
            { return reverse_iterator(mIterator - n); }

        reverse_iterator& operator+=(difference_type n)
            { mIterator -= n; return *this; }

        reverse_iterator operator-(difference_type n) const
            { return reverse_iterator(mIterator + n); }

        reverse_iterator& operator-=(difference_type n)
            { mIterator += n; return *this; }

        reference operator[](difference_type n) const
            { return mIterator[-n - 1]; } 
    };

    template <typename Iterator1, typename Iterator2>
    inline bool
    operator==(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
        { return a.base() == b.base(); }


    template <typename Iterator1, typename Iterator2>
    inline bool
    operator<(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
        { return a.base() > b.base(); }


    template <typename Iterator1, typename Iterator2>
    inline bool
    operator!=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
        { return a.base() != b.base(); }


    template <typename Iterator1, typename Iterator2>
    inline bool
    operator>(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
        { return a.base() < b.base(); }


    template <typename Iterator1, typename Iterator2>
    inline bool
    operator<=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
        { return a.base() >= b.base(); }


    template <typename Iterator1, typename Iterator2>
    inline bool
    operator>=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
        { return a.base() <= b.base(); }


    template <typename Iterator1, typename Iterator2>
    inline typename reverse_iterator<Iterator1>::difference_type
    operator-(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
        { return b.base() - a.base(); }


    template <typename Iterator>
    inline reverse_iterator<Iterator>
    operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& a)
        { return reverse_iterator<Iterator>(a.base() - n); }

    template <typename Container>
    class back_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:
        typedef Container                           container_type;
        typedef typename Container::const_reference const_reference;

    protected:
        Container& container;

    public:
        explicit back_insert_iterator(Container& x)
            : container(x) { }

        back_insert_iterator& operator=(const_reference value)
            { container.push_back(value); return *this; }

        back_insert_iterator& operator*()
            { return *this; }

        back_insert_iterator& operator++()
            { return *this; }

        back_insert_iterator operator++(int)
            { return *this; }
    };

    template <typename Container>
    inline back_insert_iterator<Container>
    back_inserter(Container& x)
        { return back_insert_iterator<Container>(x); }

    template <typename Container>
    class front_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:
        typedef Container                           container_type;
        typedef typename Container::const_reference const_reference;

    protected:
        Container& container;

    public:
        explicit front_insert_iterator(Container& x)
            : container(x) { }

        front_insert_iterator& operator=(const_reference value)
            { container.push_front(value); return *this; }

        front_insert_iterator& operator*()
            { return *this; }

        front_insert_iterator& operator++()
            { return *this; }

        front_insert_iterator operator++(int)
            { return *this; }
    };

    template <typename Container>
    inline front_insert_iterator<Container>
    front_inserter(Container& x)
        { return front_insert_iterator<Container>(x); }

    template <typename Container>
    class insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:
        typedef Container                           container_type;
        typedef typename Container::iterator        iterator_type;
        typedef typename Container::const_reference const_reference;

    protected:
        Container&     container;
        iterator_type  it; 

    public:

        insert_iterator(Container& x, iterator_type itNew)
            : container(x), it(itNew) {}

        insert_iterator& operator=(const_reference value)
        {
            it = container.insert(it, value);
            ++it;
            return *this;
        }

        insert_iterator& operator*()
            { return *this; }

        insert_iterator& operator++()
            { return *this; }

        insert_iterator& operator++(int)
            { return *this; }

    };

    template <typename Container, typename Iterator>
    inline insert_iterator<Container>
    inserter(Container& x, Iterator i)
    {
        typedef typename Container::iterator iterator;
        return insert_iterator<Container>(x, iterator(i));
    }

    template <typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance_impl(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;

        while(first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <typename RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    distance_impl(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
    {
        return last - first;
    }

    template <typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category IC;

        return distance_impl(first, last, IC());
    }

    template <typename InputIterator, typename Distance>
    inline void
    advance_impl(InputIterator& i, Distance n, input_iterator_tag)
    {
        while(n--)
            ++i;
    }

    template <typename BidirectionalIterator, typename Distance>
    inline void
    advance_impl(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
    {
        if(n > 0)
        {
            while(n--)
                ++i;
        }
        else
        {
            while(n++)
                --i;
        }
    }

    template <typename RandomAccessIterator, typename Distance>
    inline void
    advance_impl(RandomAccessIterator& i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    template <typename InputIterator, typename Distance>
    inline void
    advance(InputIterator& i, Distance n)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category IC;

        advance_impl(i, n, IC());
    }


}

#endif