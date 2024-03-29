#ifndef FT_CONTAINERS_TREEITERATOR_HPP
#define FT_CONTAINERS_TREEITERATOR_HPP

#include "iterator.hpp"

namespace ft {
    template<class Content, class Node> class ConstTreeIterator;

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
        typedef  ft::iterator <ft::bidirectional_iterator_tag, Content>             iterator_type;
        /**
         * The standard compliant type of this iterator.
         */
        typedef std::iterator<std::bidirectional_iterator_tag, Content>             std_iterator_type;
        /**
         * The category of this iterator. (Standard compliant.)
         */
        typedef typename std::iterator_traits<std_iterator_type>::iterator_category iterator_category;
        /**
         * The type of the value this iterator points to.
         */
        typedef typename ft::iterator_traits<iterator_type>::value_type             value_type;
        /**
         * The difference type used for calculations with this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::difference_type        difference_type;
        /**
         * The pointer type of this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::pointer                pointer;
        /**
         * The reference type of this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::reference              reference;
        /**
         * The content type of this iterator.
         */
        typedef Content                                                             contentType;
        /**
         * The node type used for this tree iterator.
         */
        typedef Node                                                                nodeType;

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
         * Explicit conversion from const to non-const tree iterator.
         *
         * @param other The const iterator to be used as source.
         */
        explicit TreeIterator(const ConstTreeIterator<Content, Node> & other)
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
            return *this;
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

        friend bool operator==(const TreeIterator & lhs, const TreeIterator & rhs) {
            return lhs.baseNode == rhs.baseNode;
        }

        friend bool operator!=(const TreeIterator & lhs, const TreeIterator & rhs) {
            return !(lhs.baseNode == rhs.baseNode);
        }

    private:
        /**
         * The node this iterator is based on.
         */
        nodeType baseNode;
    };

    /**
     * @brief This class represents a TreeIterator with a const content and node.
     *
     * @tparam Content The content type.
     * @tparam Node The type of the node, expected to be a pointer.
     */
    template<class Content,
             class Node>
    class ConstTreeIterator: public  ft::iterator <ft::bidirectional_iterator_tag, const Content>,
                             public std::iterator<std::bidirectional_iterator_tag, const Content> {
    public:
        /**
         * The type of this iterator.
         */
        typedef  ft::iterator <ft::bidirectional_iterator_tag, const Content>       iterator_type;
        /**
         * The standard compliant type of this iterator.
         */
        typedef std::iterator<std::bidirectional_iterator_tag, const Content>       std_iterator_type;
        /**
         * The category of this iterator. (Standard compliant.)
         */
        typedef typename std::iterator_traits<std_iterator_type>::iterator_category iterator_category;
        /**
         * The type of the value this iterator points to.
         */
        typedef typename ft::iterator_traits<iterator_type>::value_type             value_type;
        /**
         * The difference type used for calculations with this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::difference_type        difference_type;
        /**
         * The pointer type of this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::pointer                pointer;
        /**
         * The reference type of this iterator.
         */
        typedef typename ft::iterator_traits<iterator_type>::reference              reference;
        /**
         * The content type of this iterator.
         */
        typedef const Content                                                       contentType;
        /**
         * The node type used for this tree iterator.
         */
        typedef Node                                                                nodeType;

        /**
         * Default constructor.
         */
        ConstTreeIterator()
                : baseNode() {}

        /**
         * Constructs an instance using a specified node.
         *
         * @param x The node to which this instance will point to.
         */
        explicit ConstTreeIterator(nodeType x)
            : baseNode(x) {}

        /**
         * Trivial copy constructor.
         *
         * @param other The other tree iterator to copy.
         */
        ConstTreeIterator(const ConstTreeIterator & other)
            : baseNode(other.base()) {}

        /**
         * Implicit conversion from non-const to const iterator.
         *
         * @param other The non-const tree iterator to be used as source.
         */
        ConstTreeIterator(const TreeIterator<Content, Node> & other)
            : baseNode(other.base()) {}

        /**
         * Trivial destructor.
         */
       ~ConstTreeIterator() {}

        /**
         * Trivial assignment operator.
         *
         * @param other The other tree iterator to copy.
         */
        ConstTreeIterator & operator=(const ConstTreeIterator & other) {
            if (&other != this) {
                baseNode = other.base();
            }
            return *this;
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
        ConstTreeIterator & operator++() {
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
        ConstTreeIterator & operator--() {
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
        ConstTreeIterator operator++(int) {
            ConstTreeIterator tmp = *this;
            operator++();
            return tmp;
        }

        /**
         * Decrements this iterator.
         *
         * @return A copy of this instance before the decrementation.
         */
        ConstTreeIterator operator--(int) {
            ConstTreeIterator tmp = *this;
            operator--();
            return tmp;
        }

        friend bool operator==(const ConstTreeIterator & lhs, const ConstTreeIterator & rhs) {
            return lhs.baseNode == rhs.baseNode;
        }

        friend bool operator!=(const ConstTreeIterator & lhs, const ConstTreeIterator & rhs) {
            return !(lhs.baseNode == rhs.baseNode);
        }

    private:
        /**
         * The node this iterator is based on.
         */
        nodeType baseNode;
    };
}

#endif
