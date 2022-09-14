//
// Created by Manuel Hahn on 9/2/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include <cstddef>
#include "iterator.hpp"
#include "utility.hpp"
#include "functional.hpp"

namespace ft {
    template<
        class Key,
        class T,
        class Compare = ft::less<T>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
    > class map {
    public:
        typedef Key                                  key_type;
        typedef T                                    mapped_type;
        typedef ft::pair<const Key, T>               value_type;
        typedef std::size_t                          size_type;
        typedef std::ptrdiff_t                       difference_type;
        typedef Compare                              key_compare;
        typedef Allocator                            allocator_type;
        typedef value_type &                         reference;
        typedef const value_type &                   const_reference;
        typedef typename Allocator::pointer          pointer;
        typedef typename Allocator::const_pointer    const_pointer;
        typedef void *       /* TODO */              iterator;
        typedef const void * /* TODO */              const_iterator;
        typedef ft::reverse_iterator<iterator>       reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        class value_compare: public ft::binary_function<value_type, value_type, bool> {
        public:
            typedef bool       result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

            bool operator()(const value_type & lhs, const value_type & rhs) const {
                return comp(lhs.first, rhs.first);
            }

        protected:
            Compare comp;

            value_compare(Compare c): comp(c) {}
        };

        map();
        explicit map(const Compare & comp, const Allocator & alloc = Allocator());

        template<class InputIt>
        map(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator());

        map(const map & other);
        ~map();

        map & operator=(const map & other);

        allocator_type get_allocator() const {
            return alloc;
        }

        T & at(const Key & key);
        const T & at(const Key & key) const;

        T & operator[](const Key & key);

        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;

        reverse_iterator rbegin() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(begin());
        }

        reverse_iterator rend() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(end());
        }

        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        void clear();

        ft::pair<iterator, bool> insert(const value_type & value);
        iterator insert(iterator hint, const value_type & value);

        template<class InputIt>
        void insert(InputIt first, InputIt last);

        void erase(iterator pos);
        void erase(iterator first, iterator last);
        size_type erase(const Key & key);

        void swap(map & other);

        size_type count(const Key & key);

        iterator find(const Key & key);
        const_iterator find(const Key & key) const;

        ft::pair<iterator, iterator> equal_range(const Key & key);
        ft::pair<const_iterator, const_iterator> equal_range(const Key & key) const;

        iterator lower_bound(const Key & key);
        const_iterator lower_bound(const Key & key) const;

        iterator upper_bound(const Key & key);
        const_iterator upper_bound(const Key & key) const;

        key_compare key_comp() const {
            return valueCompare;
        }

        ft::map<Key, T, Compare, Allocator>::value_compare value_comp() const {
            return keyCompare;
        }

    private:
        allocator_type alloc;
        key_compare    keyCompare;
        value_compare  valueCompare;
    };

    template<class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs);

    template<class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs);

    template<class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs);

    template<class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs);

    template<class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs);

    template<class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs);

    template<class Key, class T, class Compare, class Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> & lhs, ft::map<Key, T, Compare, Alloc> & rhs) {
        lhs.swap(rhs);
    }
}

#endif //FT_CONTAINERS_MAP_HPP
