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
        typedef ft::iterator <ft::bidirectional_iterator_tag, Content>         iterator_type;
        /**
         * The category of this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
        /**
         * The type of the value this iterator points to.
         */
        typedef typename ft::iterator_traits<iterator_type>::value_type        value_type;
        /**
         * The difference type used for calculations with this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::difference_type   difference_type;
        /**
         * The pointer type of this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::pointer           pointer;
        /**
         * The reference type of this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::reference         reference;
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
        TreeIterator()
            : baseNode() {}

        /**
         * Constructs an instance using a specified node.
         *
         * @param x The node to which this instance will point to.
         */
        explicit TreeIterator(nodeType x)
            : baseNode(x) {}

        /**
         * Trivial copy constructor.
         *
         * @param other The other tree iterator to copy.
         */
        TreeIterator(const TreeIterator & other)
            : baseNode(other.base()) {}

        /**
         * Trivial destructor.
         */
       ~TreeIterator() {}

        /**
         * Trivial assignment operator.
         *
         * @param other The other tree iterator to copy.
         */
        TreeIterator & operator=(const TreeIterator & other) {
            if (&other != this) {
                baseNode = other.base();
            }
        }

        /**
         * Returns the node on which this iterator is based.
         *
         * @return The base node of this iterator.
         */
        nodeType base() const { return baseNode; }

        /**
         * @brief Returns a reference to the content of the node this iterator points to.
         *
         * Same as base()->content.
         *
         * @return A reference to the content of the base node.
         */
        reference operator*() const { return baseNode->content; }

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
        TreeIterator & operator++() {
            if (baseNode->right != NULL) {
                baseNode = baseNode->right;
                while (baseNode->left != NULL) {
                    baseNode = baseNode->left;
                }
            } else {
                nodeType tmp;
                do {
                    tmp = baseNode;
                    baseNode = baseNode->root;
                } while ((baseNode->right == NULL || baseNode->right == tmp) && baseNode->left != tmp);
            }
            return *this;
        }

        /**
         * Decrements this iterator.
         *
         * @return A reference to this instance.
         */
        TreeIterator & operator--() {
            if (baseNode->left != NULL) {
                baseNode = baseNode->left;
                while (baseNode->right != NULL) {
                    baseNode = baseNode->right;
                }
            } else {
                nodeType tmp;
                do {
                    tmp = baseNode;
                    baseNode = baseNode->root;
                } while ((baseNode->left == NULL || baseNode->left == tmp) && baseNode->right != tmp);
            }
            return *this;
        }

        /**
         * Increments this iterator.
         *
         * @return A copy of this instance before the incrementation.
         */
        TreeIterator operator++(int) {
            TreeIterator tmp = *this;
            operator++();
            return tmp;
        }

        /**
         * Decrements this iterator.
         *
         * @return A copy of this instance before the decrementation.
         */
        TreeIterator operator--(int) {
            TreeIterator tmp = *this;
            operator--();
            return tmp;
        }

    private:
        /**
         * The node this iterator is based on.
         */
        nodeType baseNode;
    };

    template<class Content, class Node>
    bool operator==(const TreeIterator<Content, Node> & lhs, const TreeIterator<Content, Node> & rhs) {
        return lhs.base() == rhs.base();
    }

    template<class Content, class Node>
    bool operator!=(const TreeIterator<Content, Node> & lhs, const TreeIterator<Content, Node> & rhs) {
        return lhs.base() != rhs.base();
    }
}

#endif
