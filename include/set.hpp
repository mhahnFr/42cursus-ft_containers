//
// Created by Manuel Hahn on 10/4/22.
//

#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include <memory>
#include "functional.hpp"
#include "iterator.hpp"
#include "tree.hpp"
#include "utility.hpp"
#include "algorithm.hpp"

namespace ft {
    template<class Key,
            class Compare   = ft::less<Key>,
            class Allocator = std::allocator<Key>
            >
    class set {
    public:
        typedef Key                                         key_type;
        typedef Key                                         value_type;
        typedef Compare                                     key_compare;
        typedef Compare                                     value_compare;
        typedef Allocator                                   allocator_type;
        typedef value_type &                                reference;
        typedef const value_type &                          const_reference;
        typedef typename Allocator::pointer                 pointer;
        typedef typename Allocator::const_pointer           const_pointer;
        /**
         * The type of the used tree.
         */
        typedef Tree<key_type, key_compare, allocator_type> treeType;
        typedef typename treeType::sizeType                 size_type;
        typedef typename treeType::differenceType           difference_type;
        typedef typename treeType::iteratorType             iterator;
        typedef typename treeType::constIteratorType        const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

        set();
        explicit set(const Compare &, const Allocator & alloc = Allocator());

        template<class InputIt>
        set(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator());

        set(const set & other);

       ~set();

        set & operator=(const set & other);

        allocator_type get_allocator() const;

        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;

        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;

        reverse_iterator rend();
        const_reverse_iterator rend() const;

        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        void clear();

        ft::pair<iterator, bool> insert(const value_type & value);
        iterator insert(iterator hint, const value_type & value);

        template<class InputIt>
        void insert(InputIt first, InputIt last);

        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        size_type erase(const Key & key);

        void swap(set & other);

        size_type count(const Key & key) const;

        iterator find(const Key & key);
        const_iterator find(const Key & key) const;

        ft::pair<iterator, iterator> equal_range(const Key & key);
        ft::pair<const_iterator, const_iterator> equal_range(const Key & key) const;

        iterator lower_bound(const Key & key);
        const_iterator lower_bound(const Key & key) const;

        iterator upper_bound(const Key & key);
        const_iterator upper_bound(const Key & key) const;

        key_compare key_comp() const;

        value_compare value_comp() const;
    };

    template<class Key, class Compare, class Alloc>
    bool operator==(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs.key_comp());
    }

    template<class Key, class Compare, class Alloc>
    bool operator!=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
        return !(lhs == rhs);
    }

    template<class Key, class Compare, class Alloc>
    bool operator<(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class Key, class Compare, class Alloc>
    bool operator<=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
        return lhs < rhs || lhs == rhs;
    }

    template<class Key, class Compare, class Alloc>
    bool operator>(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
        return rhs < lhs;
    }

    template<class Key, class Compare, class Alloc>
    bool operator>=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs) {
        return rhs < lhs || lhs == rhs;
    }

    template<class Key, class Compare, class Alloc>
    void swap(ft::set<Key, Compare, Alloc> & lhs, ft::set<Key, Compare, Alloc> & rhs) {
        lhs.swap(rhs);
    }
}
#endif //FT_CONTAINERS_SET_HPP
