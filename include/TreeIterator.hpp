#ifndef FT_CONTAINERS_TREEITERATOR_HPP
#define FT_CONTAINERS_TREEITERATOR_HPP

#include "iterator.hpp"

namespace ft {
    template<class Content,
             class Node>
    class TreeIterator: public  ft::iterator <ft::bidirectional_iterator_tag, Content>,
                        public std::iterator<std::bidirectional_iterator_tag, Content> {
    public:
        typedef TreeIterator                                                   iterator_type;
        typedef typename std::iterator_traits<TreeIterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<TreeIterator>::value_type         value_type;
        typedef typename ft::iterator_traits<TreeIterator>::difference_type    difference_type;
        typedef typename ft::iterator_traits<TreeIterator>::pointer            pointer;
        typedef typename ft::iterator_traits<TreeIterator>::reference          reference;
        typedef Content                                                        contentType;
        typedef Node                                                           nodeType;

        TreeIterator();
        explicit TreeIterator(nodeType x);
        TreeIterator(const TreeIterator & other);
       ~TreeIterator() {}

        TreeIterator & operator=(const TreeIterator & other);

        nodeType base() const;

        reference operator*() const;

        pointer operator->() const { return &operator*(); }

        TreeIterator & operator++();
        TreeIterator & operator--();

        TreeIterator & operator++(int);
        TreeIterator & operator--(int);
    };
}

#endif
