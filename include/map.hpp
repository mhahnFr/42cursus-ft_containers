//
// Created by Manuel Hahn on 9/2/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include <cstddef>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "functional.hpp"
#include "tree.hpp"

namespace ft {
    template<
        class Key,
        class T,
        class Compare = ft::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
    > class map {
    public:
        class value_compare;

        typedef Key                                        key_type;
        typedef T                                          mapped_type;
        typedef ft::pair<const Key, T>                     value_type;
        typedef Compare                                    key_compare;
        typedef Allocator                                  allocator_type;
        typedef value_type &                               reference;
        typedef const value_type &                         const_reference;
        typedef typename Allocator::pointer                pointer;
        typedef typename Allocator::const_pointer          const_pointer;
        /**
         * The type of the used tree.
         */
        typedef Tree<value_type, value_compare, Allocator> treeType;
        typedef typename treeType::sizeType                size_type;
        typedef typename treeType::differenceType          difference_type;
        typedef typename treeType::iteratorType            iterator;
        typedef typename treeType::constIteratorType       const_iterator;
        typedef ft::reverse_iterator<iterator>             reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;

        class value_compare: public ft::binary_function<value_type, value_type, bool> {
            friend class map;

        public:
            typedef bool       result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

            bool operator()(const value_type & lhs, const value_type & rhs) const {
                return comp(lhs.first, rhs.first);
            }

        protected:
            Compare comp;

            explicit value_compare(Compare c): comp(c) {}
        };

        map(): alloc(Allocator()), keyCompare(key_compare()), valueCompare(keyCompare), tree(valueCompare) {}

        explicit map(const Compare & comp, const Allocator & alloc = Allocator())
            : alloc(alloc), keyCompare(comp), valueCompare(comp), tree(valueCompare) {}

        template<class InputIt>
        map(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator())
            : alloc(alloc), keyCompare(comp), valueCompare(comp), tree(valueCompare) {
            insert(first, last);
        }

        map(const map & other)
            : alloc(other.alloc), keyCompare(other.keyCompare), valueCompare(other.valueCompare), tree(other.tree) {}

       ~map() {}

        map & operator=(const map & other) {
            if (&other != this) {
                alloc        = other.alloc;
                keyCompare   = other.keyCompare;
                valueCompare = other.valueCompare;
                tree         = other.tree;
            }
            return *this;
        }

        allocator_type get_allocator() const { return alloc; }

        T &       at(const Key & key)       { return tree.findOrThrow(ft::make_pair(key, mapped_type())).second;  }
        const T & at(const Key & key) const { return tree.findOrThrow(ft::make_pair(key, mapped_type())).second;  }

        T & operator[](const Key & key)     { return tree.findOrInsert(ft::make_pair(key, mapped_type())).second; }

        iterator                begin()       { return       iterator(tree.begin());    }
        const_iterator          begin() const { return const_iterator(tree.begin());    }

        reverse_iterator       rbegin()       { return       reverse_iterator(end());   }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end());   }

        iterator                end()         { return       iterator(tree.end());      }
        const_iterator          end()   const { return const_iterator(tree.end());      }

        reverse_iterator       rend()         { return       reverse_iterator(begin()); }
        const_reverse_iterator rend()   const { return const_reverse_iterator(begin()); }

        bool empty() const { return tree.isEmpty(); }

        size_type     size() const { return tree.size();    }
        size_type max_size() const { return tree.maxSize(); }

        void clear() { tree.clear(); }

        ft::pair<iterator, bool> insert(const value_type & value) { return tree.insert(value); }

        iterator insert(iterator hint, const value_type & value);

        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            for (; first != last; ++first) {
                insert(*first);
            }
        }

        void erase(iterator pos);
        void erase(iterator first, iterator last);
        size_type erase(const Key & key);

        void swap(map & other) { tree.swap(other.tree); }

        size_type count(const Key & key) const { return find(key) == end() ? 0 : 1; }

        iterator       find(const Key & key)       { return tree.find(ft::make_pair(key, mapped_type())); }
        const_iterator find(const Key & key) const { return tree.find(ft::make_pair(key, mapped_type())); }

        ft::pair<iterator, iterator> equal_range(const Key & key) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key & key) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        iterator       lower_bound(const Key & key)       { return tree.lowerBound(ft::make_pair(key, mapped_type())); }
        const_iterator lower_bound(const Key & key) const { return tree.lowerBound(ft::make_pair(key, mapped_type())); }

        iterator upper_bound(const Key & key)             { return tree.upperBound(ft::make_pair(key, mapped_type())); }
        const_iterator upper_bound(const Key & key) const { return tree.upperBound(ft::make_pair(key, mapped_type())); }

        key_compare key_comp() const { return keyCompare; }

        ft::map<Key, T, Compare, Allocator>::value_compare value_comp() const { return valueCompare; }

    private:
        allocator_type alloc;
        key_compare    keyCompare;
        value_compare  valueCompare;
        treeType       tree;
    };

    template<class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
        typename ft::map<Key, T, Compare, Alloc>::const_iterator it,
                                                                 it2;
        for (it = lhs.begin(), it2 = rhs.begin(); it != lhs.end() && it2 != rhs.end(); ++it, ++it2) {
            if (!(*it == *it2)) {
                return false;
            }
        }
        return it == lhs.end() && it2 == rhs.end();
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
        return !(lhs == rhs);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
        return lhs < rhs || lhs == rhs;
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
        return rhs < lhs;
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) {
        return rhs < lhs || lhs == rhs;
    }

    template<class Key, class T, class Compare, class Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> & lhs, ft::map<Key, T, Compare, Alloc> & rhs) { lhs.swap(rhs); }
}

#endif //FT_CONTAINERS_MAP_HPP
