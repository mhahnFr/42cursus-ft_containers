//
// Created by Manuel Hahn on 9/2/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <cstddef>

namespace ft {

    /**
     * This class holds a tree structure.
     *
     * @tparam T the type of the contents to be held by this tree
     * @tparam Compare the comparator function that is used to sort the contents
     * @tparam Allocator the allocator used to rebind
     */
    template<class T,
             class Compare,
             class Allocator>
    class Tree {

        /**
         * A node of the tree.
         */
        struct Node {
            /**
             * The type of the value the node can hold.
             */
            typedef T valueType;

            /**
             * A pointer to the left child of this node.
             */
            Node * left;
            /**
             * A pointer to the parent of this node.
             */
            Node * root;
            /**
             * A pointer to the right child of this node.
             */
            Node * right;
            /**
             * The actual content of this node.
             */
            valueType content;

            /**
             * Default constructor. Initializes the pointers with NULL, the content is default constructed.
             */
            Node(): left(NULL), root(NULL), right(NULL), content() {}

            /**
             * Copy constructor. Initializes all values with the ones of the other Node.
             *
             * @param other The other node to copy the values from.
             */
            Node(const Node & other): left(other.left), root(other.root), right(other.right), content(other.content) {}

            /**
             * Trivial destructor.
             *
             * Since C++11: ~Node() = default;
             */
           ~Node() {}

           /**
            * Trivial copy assignment operator. Copies all values from the right Node.
            *
            * Since C++11: Node & operator=(const Node &) = default;
            *
            * @param other The other Node to copy the values from.
            * @return A reference to this Node.
            */
            Node & operator=(const Node & other) {
                if (&other != this) {
                    left    = other.left;
                    root    = other.root;
                    right   = other.right;
                    content = other.content;
                }
            }
        };

    public:
        typedef T                                                    contentType;
        typedef std::size_t                                          sizeType;
        typedef Node                                                 nodeType;
        typedef typename Allocator::template rebind<nodeType>::other alloc;
    };
}

#endif //FT_CONTAINERS_TREE_HPP
