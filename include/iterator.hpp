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
    class reverse_iterator: public iterator<typename iterator_traits<Iter>::iterator_category,
                                            typename iterator_traits<Iter>::value_type,
                                            typename iterator_traits<Iter>::difference_type,
                                            typename iterator_traits<Iter>::pointer,
                                            typename iterator_traits<Iter>::reference> {
    public:
        typedef Iter                                              iterator_type;
        typedef typename iterator_traits<Iter>::iterator_category iterator_category;
        typedef typename iterator_traits<Iter>::value_type        value_type;
        typedef typename iterator_traits<Iter>::difference_type   difference_type;
        typedef typename iterator_traits<Iter>::pointer           pointer;
        typedef typename iterator_traits<Iter>::reference         reference;

        reverse_iterator(): current() {}
        reverse_iterator(iterator_type x): current(x) {}

        template<class U>
        reverse_iterator(const reverse_iterator<U> & other): current(other.current) {}

        template<class U>
        reverse_iterator & operator=(const reverse_iterator<U> & other) {
            current = other.base();
            return *this;
        }

        iterator_type base() const {
            return current;
        }

        reference operator*() {
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
        rhs.base() - lhs.base();
    }
}

#endif //FT_CONTAINERS_ITERATOR_HPP
