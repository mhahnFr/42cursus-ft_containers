#ifndef FT_CONTAINERS_TREEITERATOR_HPP
#define FT_CONTAINERS_TREEITERATOR_HPP

#include "iterator.hpp"

namespace ft {
    /**
     * @brief This class represents a tree iterator.
     *
     * @tparam Content The content type this iterator holds.
     * @tparam Node    The node type this iterator uses.
     */
    template<class Content,
             class Node>
    class TreeIterator: public  ft::iterator <ft::bidirectional_iterator_tag, Content>,
                        public std::iterator<std::bidirectional_iterator_tag, Content> {
    public:
        /**
         * The type of this iterator.
         */
        typedef TreeIterator                                                   iterator_type;
        /**
         * The category of this iterator.
         */
        typedef typename std::iterator_traits<TreeIterator>::iterator_category iterator_category;
        /**
         * The type of the value this iterator points to.
         */
        typedef typename ft::iterator_traits<TreeIterator>::value_type         value_type;
        /**
         * The difference type used for calculations with this iterator.
         */
        typedef typename ft::iterator_traits<TreeIterator>::difference_type    difference_type;
        /**
         * The pointer type of this iterator.
         */
        typedef typename ft::iterator_traits<TreeIterator>::pointer            pointer;
        /**
         * The reference type of this iterator.
         */
        typedef typename ft::iterator_traits<TreeIterator>::reference          reference;
        /**
         * The content type of this iterator.
         */
        typedef Content                                                        contentType;
        /**
         * The node type used for this tree iterator.
         */
        typedef Node                                                           nodeType;

        /**
         * Default constructor.
         */
        TreeIterator();

        /**
         * Constructs an instance using a specified node.
         *
         * @param x The node to which this instance will point to.
         */
        explicit TreeIterator(nodeType x);

        /**
         * Trivial copy constructor.
         *
         * @param other The other tree iterator to copy.
         */
        TreeIterator(const TreeIterator & other);

        /**
         * Trivial destructor.
         */
       ~TreeIterator() {}

        /**
         * Trivial assignment operator.
         *
         * @param other The other tree iterator to copy.
         */
        TreeIterator & operator=(const TreeIterator & other);

        /**
         * Returns the node on which this iterator is based.
         *
         * @return The base node of this iterator.
         */
        nodeType base() const;

        /**
         * @brief Returns a reference to the content of the node this iterator points to.
         *
         * Same as base()->content.
         *
         * @return A reference to the content of the base node.
         */
        reference operator*() const;

        /**
         * Returns the address of the content of the base node.
         *
         * @return The address of the base node's content.
         */
        pointer operator->() const { return &operator*(); }

        /**
         * Increments this iterator.
         *
         * @return A reference to this instance.
         */
        TreeIterator & operator++();

        /**
         * Decrements this iterator.
         *
         * @return A reference to this instance.
         */
        TreeIterator & operator--();

        /**
         * Increments this iterator.
         *
         * @return A copy of this instance before the incrementation.
         */
        TreeIterator operator++(int);

        /**
         * Decrements this iterator.
         *
         * @return A copy of this instance before the decrementation.
         */
        TreeIterator operator--(int);
    };
}

#endif
