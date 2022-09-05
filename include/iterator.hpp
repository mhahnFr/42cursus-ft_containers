//
// Created by Manuel Hahn on 8/29/22.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <cstddef>

namespace ft {
    struct input_iterator_tag  {};
    struct output_iterator_tag {};
    struct forward_iterator_tag:       public input_iterator_tag         {};
    struct bidirectional_iterator_tag: public forward_iterator_tag       {};
    struct random_access_iterator_tag: public bidirectional_iterator_tag {};

    template<class Iter>
    struct iterator_traits {
        typedef typename Iter::difference_type   difference_type;
        typedef typename Iter::value_type        value_type;
        typedef typename Iter::pointer           pointer;
        typedef typename Iter::reference         reference;
        typedef typename Iter::iterator_category iterator_category;
    };

    template<class T>
    struct iterator_traits<T *> {
        typedef std::ptrdiff_t             difference_type;
        typedef T                          value_type;
        typedef T *                        pointer;
        typedef T &                        reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template<class T>
    struct iterator_traits<const T *> {
        typedef std::ptrdiff_t             difference_type;
        typedef T                          value_type;
        typedef const T *                  pointer;
        typedef const T &                  reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template<class Category,
             class T,
             class Distance  = std::ptrdiff_t,
             class Pointer   = T *,
             class Reference = T &
            >
    struct iterator {
        typedef Category  iterator_category;
        typedef T         value_type;
        typedef Distance  distance_type;
        typedef Pointer   pointer;
        typedef Reference reference;
    };

    template<class Iter>
    class reverse_iterator: public ft::iterator<typename ft::iterator_traits<Iter>::iterator_category,
                                                typename ft::iterator_traits<Iter>::value_type,
                                                typename ft::iterator_traits<Iter>::difference_type,
                                                typename ft::iterator_traits<Iter>::pointer,
                                                typename ft::iterator_traits<Iter>::reference>,

                            public std::iterator<typename std::iterator_traits<Iter>::iterator_category,
                                                 typename std::iterator_traits<Iter>::value_type,
                                                 typename std::iterator_traits<Iter>::difference_type,
                                                 typename std::iterator_traits<Iter>::pointer,
                                                 typename std::iterator_traits<Iter>::reference> {
    public:
        typedef Iter                                                   iterator_type;
        typedef typename std::iterator_traits<Iter>::iterator_category iterator_category;
        typedef typename iterator_traits<Iter>::value_type             value_type;
        typedef typename iterator_traits<Iter>::difference_type        difference_type;
        typedef typename iterator_traits<Iter>::pointer                pointer;
        typedef typename iterator_traits<Iter>::reference              reference;

        reverse_iterator(): current() {}
        explicit reverse_iterator(iterator_type x): current(x) {}

        template<class U>
        reverse_iterator(const reverse_iterator<U> & other): current(other.base()) {}

        template<class U>
        reverse_iterator & operator=(const reverse_iterator<U> & other) {
            current = other.base();
            return *this;
        }

        iterator_type base() const {
            return current;
        }

        reference operator*() const {
            Iter tmp = current;
            return *--tmp;
        }

        pointer operator->() const {
            return &operator*();
        }

        reference operator[](difference_type n) const {
            return base()[-n - 1];
        }

        reverse_iterator & operator++() {
            --current;
            return *this;
        }

        reverse_iterator & operator--() {
            ++current;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            --current;
            return tmp;
        }

        reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            ++current;
            return tmp;
        }

        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(base() - n);
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(base() + n);
        }

        reverse_iterator & operator+=(difference_type n) {
            current -= n;
            return *this;
        }

        reverse_iterator & operator-=(difference_type n) {
            current += n;
            return *this;
        }

    protected:
        iterator_type current;
    };

    template<class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
        return lhs.base() == rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
        return lhs.base() != rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator<(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
        return lhs.base() > rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
        return lhs.base() >= rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
        return lhs.base() < rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class Iter>
    reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> & it) {
        return reverse_iterator<Iter>(it.base() - n);
    }

    template<class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) {
        return rhs.base() - lhs.base();
    }

    template<class Iter>
    class __wrap_iter: public ft::iterator<typename ft::iterator_traits<Iter>::iterator_category,
                                           typename ft::iterator_traits<Iter>::value_type,
                                           typename ft::iterator_traits<Iter>::difference_type,
                                           typename ft::iterator_traits<Iter>::pointer,
                                           typename ft::iterator_traits<Iter>::reference>,

                              std::iterator<typename std::iterator_traits<Iter>::iterator_category,
                                            typename std::iterator_traits<Iter>::value_type,
                                            typename std::iterator_traits<Iter>::difference_type,
                                            typename std::iterator_traits<Iter>::pointer,
                                            typename std::iterator_traits<Iter>::reference> {
    public:
        typedef Iter                                                   iterator_type;
        typedef typename std::iterator_traits<Iter>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type         value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type    difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer            pointer;
        typedef typename ft::iterator_traits<Iter>::reference          reference;

        __wrap_iter(): current() {}
        explicit __wrap_iter(iterator_type x): current(x) {}

        template<class U>
        __wrap_iter(const __wrap_iter<U> & other): current(other.base()) {}

        template<class U>
        __wrap_iter & operator=(const __wrap_iter<U> & other) {
            current = other.base();
            return *this;
        }

        iterator_type base() const {
            return current;
        }

        reference operator*() const {
            return *current;
        }

        pointer operator->() const {
            return &operator*();
        }

        reference operator[](difference_type n) const {
            return current[n];
        }

        __wrap_iter & operator++() {
            ++current;
            return *this;
        }

        __wrap_iter & operator--() {
            --current;
            return *this;
        }

        __wrap_iter operator++(int) {
            __wrap_iter tmp = *this;
            ++current;
            return tmp;
        }

        __wrap_iter operator--(int) {
            __wrap_iter tmp = *this;
            --current;
            return tmp;
        }

        __wrap_iter operator+(difference_type n) const {
            return __wrap_iter(current + n);
        }

        __wrap_iter operator-(difference_type n) const {
            return __wrap_iter(current - n);
        }

        __wrap_iter & operator+=(difference_type n) {
            current += n;
            return *this;
        }

        __wrap_iter & operator-=(difference_type n) {
            current -= n;
            return *this;
        }

    protected:
        iterator_type current;
    };

    template<class Iterator1, class Iterator2>
    bool operator==(const __wrap_iter<Iterator1> & lhs, const __wrap_iter<Iterator2> & rhs) {
        return lhs.base() == rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator!=(const __wrap_iter<Iterator1> & lhs, const __wrap_iter<Iterator2> & rhs) {
        return lhs.base() != rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator<(const __wrap_iter<Iterator1> & lhs, const __wrap_iter<Iterator2> & rhs) {
        return lhs.base() < rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator<=(const __wrap_iter<Iterator1> & lhs, const __wrap_iter<Iterator2> & rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator>(const __wrap_iter<Iterator1> & lhs, const __wrap_iter<Iterator2> & rhs) {
        return lhs.base() > rhs.base();
    }

    template<class Iterator1, class Iterator2>
    bool operator>=(const __wrap_iter<Iterator1> & lhs, const __wrap_iter<Iterator2> & rhs) {
        return lhs.base() >= rhs.base();
    }

    template<class Iter>
    __wrap_iter<Iter> operator+(typename __wrap_iter<Iter>::difference_type n, const __wrap_iter<Iter> & it) {
        return __wrap_iter<Iter>(it.base() + n);
    }

    template<class Iterator>
    typename __wrap_iter<Iterator>::difference_type operator-(const __wrap_iter<Iterator> & lhs, const __wrap_iter<Iterator> & rhs) {
        return lhs.base() - rhs.base();
    }

    template<class InputIt>
    typename ft::iterator_traits<InputIt>::difference_type do_distance(InputIt first, InputIt last, ft::random_access_iterator_tag) {
        return last - first;
    }

    template<class InputIt>
    typename ft::iterator_traits<InputIt>::difference_type do_distance(InputIt first, InputIt last, std::random_access_iterator_tag) {
        return last - first;
    }

    template<class InputIt>
    inline typename ft::iterator_traits<InputIt>::difference_type do_distance(InputIt first, InputIt last, ft::input_iterator_tag) {
        typename ft::iterator_traits<InputIt>::difference_type ret = 0;
        for (ret = 0; first != last; ++first, ++ret);
        return ret;
    }

    template<class InputIt>
    inline typename ft::iterator_traits<InputIt>::difference_type do_distance(InputIt first, InputIt last, std::input_iterator_tag) {
        typename ft::iterator_traits<InputIt>::difference_type ret;
        for (ret = 0; first != last; ++first, ++ret);
        return ret;
    }

    template<class InputIt>
    inline typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
        return do_distance(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
    }
}

#endif //FT_CONTAINERS_ITERATOR_HPP
