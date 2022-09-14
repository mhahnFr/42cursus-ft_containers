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

        /**
         * The root Node of this tree.
         */
        Node * root;

    public:
        /**
         * The type of the content held by the nodes.
         */
        typedef T                                                    contentType;
        /**
         * The type used for sizes.
         */
        typedef std::size_t                                          sizeType;
        /**
         * The type of the used Nodes.
         */
        typedef Node                                                 nodeType;
        /**
         * The type of the rebound allocator.
         */
        typedef typename Allocator::template rebind<nodeType>::other allocatorType;

        /**
         * Default constructor. Initializes this tree with a NULL root node.
         */
        Tree(): root(NULL) {}

        /**
         * Copy constructor. Copies the whole tree, all elements are deeply copied.
         *
         * @param other The other tree to copy.
         */
        Tree(const Tree & other);

        /**
         * Default destructor. Destroys all elements properly.
         */
       ~Tree() { clear(); }

        /**
         * Copy assignment operator. Clears this tree and copies the given tree deeply.
         *
         * @param other The other tree to copy.
         * @return A reference to this tree.
         */
        Tree & operator=(const Tree & other);

        /**
         * Clears this tree properly.
         */
        void clear();

        /**
         * Swaps this tree with the other one.
         *
         * @param other The other tree to exchange the values with.
         */
         void swap(Tree & other) {
             Node * tmp = root;
             root = other.root;
             other.root = tmp;
         }

         /**
          * Returns whether this tree is empty, e. g. does not contain any nodes.
          *
          * @return Whether this tree is empty.
          */
         bool isEmpty() const { return root == NULL; }
    };
}

#endif //FT_CONTAINERS_TREE_HPP
