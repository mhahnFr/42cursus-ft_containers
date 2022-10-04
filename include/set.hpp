//
// Created by Manuel Hahn on 10/4/22.
//

#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include <memory>
#include "functional.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "tree.hpp"
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

        set(): alloc(Allocator()), keyCompare(key_compare()), valueCompare(keyCompare), tree(valueCompare) {}

        explicit set(const Compare & comp, const Allocator & alloc = Allocator())
            : alloc(alloc), keyCompare(comp), valueCompare(comp), tree(valueCompare) {}

        template<class InputIt>
        set(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator())
            : alloc(alloc), keyCompare(comp), valueCompare(comp), tree(valueCompare) {
            insert(first, last);
        }

        set(const set & other)
            : alloc(other.alloc), keyCompare(other.keyCompare), valueCompare(other.valueCompare), tree(other.tree) {}

       ~set() {}

        set & operator=(const set & other) {
            if (&other != this) {
                alloc        = other.alloc;
                keyCompare   = other.keyCompare;
                valueCompare = other.valueCompare;
                tree         = other.tree;
            }
            return *this;
        }

        allocator_type get_allocator() const { return alloc; }

        iterator begin()                      { return       iterator(tree.begin());    }
        const_iterator begin() const          { return const_iterator(tree.begin());    }

        reverse_iterator rbegin()             { return reverse_iterator(end());         }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end());   }

        iterator end()                        { return       iterator(tree.end());      }
        const_iterator end() const            { return const_iterator(tree.end());      }

        reverse_iterator rend()               { return       reverse_iterator(begin()); }
        const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

        bool empty() const { return tree.isEmpty(); }

        size_type     size() const { return tree.size();    }
        size_type max_size() const { return tree.maxSize(); }

        void clear() { tree.clear(); }

        ft::pair<iterator, bool> insert(const value_type & value) { return tree.insert(value);       }
        iterator insert(iterator hint, const value_type & value)  { return tree.insert(hint, value); }

        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            for (; first != last; ++first) {
                insert(*first);
            }
        }

        iterator erase(iterator pos) { return tree.erase(pos); }

        iterator erase(iterator first, iterator last) {
            while (first != last) {
                iterator tmp = first;
                ++tmp;
                erase(first);
                first = tmp;
            }
        }

        size_type erase(const Key & key) {
            iterator it = find(key);
            if (it != end()) {
                erase(it);
                return 1;
            }
            return 0;
        }

        void swap(set & other) { tree.swap(other.tree); }

        size_type count(const Key & key) const { return find(key) == end() ? 0 : 1; }

        iterator       find(const Key & key)       { return tree.find(key); }
        const_iterator find(const Key & key) const { return tree.find(key); }

        ft::pair<iterator, iterator> equal_range(const Key & key) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key & key) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        iterator       lower_bound(const Key & key)       { return tree.lowerBound(key); }
        const_iterator lower_bound(const Key & key) const { return tree.lowerBound(key); }

        iterator       upper_bound(const Key & key)       { return tree.upperBound(key); }
        const_iterator upper_bound(const Key & key) const { return tree.upperBound(key); }

        key_compare key_comp() const { return keyCompare; }

        ft::set<Key, Compare, Allocator>::value_compare value_comp() const { return valueCompare; }

    private:
        allocator_type alloc;
        key_compare    keyCompare;
        value_compare  valueCompare;
        treeType       tree;
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
