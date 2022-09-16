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
        typedef Node *                                               nodeType;
        /**
         * The type of the compare object.
         */
        typedef Compare                                              compareType;
        /**
         * The type of the rebound allocator.
         */
        typedef typename Allocator::template rebind<nodeType>::other allocatorType;

        /**
         * Default constructor. Initializes this tree with a NULL root node.
         *
         * @param comp The compare object to be used to sort the contents of this tree.
         */
        explicit Tree(Compare comp = Compare()): root(NULL), alloc(allocatorType()), compare(comp) {}

        /**
         * Copy constructor. Copies the whole tree, all elements are deeply copied.
         *
         * @param other The other tree to copy.
         */
        Tree(const Tree & other): root(NULL), alloc(other.alloc), compare(other.compare) {
            if (other.root != NULL) {
                recursiveCopy(root, other.root);
            }
        }

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
        Tree & operator=(const Tree & other) {
            if (&other != this) {
                clear();
                if (other.root != NULL) {
                    recursiveCopy(root, other.root);
                }
            }
            return *this;
        }

        /**
         * Clears this tree properly.
         */
        void clear() {
            recursiveDestroy(root);
            root = NULL;
        }

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

         /**
          * Attempts to find the given value in this tree. A pair containing the node containing the content
          * and the insertion direction is returned.
          *
          * @param c The content to be found.
          * @return A pair with the node containing the content and an insertion point.
          */
         ft::pair<nodeType, nodeType *> find(contentType c) {
             return find(c, root);
         }

    private:
        /**
         * The root Node of this tree.
         */
        nodeType      root;
        /**
         * The allocator used to allocate nodes.
         */
        allocatorType alloc;
        /**
         * The compare object used to sort the contents of this tree.
         */
        compareType   compare;

        /**
         * @brief Destroys and deallocates the given node.
         *
         * Destroys all children of the given node beforehand.
         *
         * @param node The node to destroy.
         */
        void recursiveDestroy(nodeType node) {
            if (node->left  != NULL) { recursiveDestroy(node->left);  }
            if (node->right != NULL) { recursiveDestroy(node->right); }
            alloc.destroy(node);
            alloc.deallocate(node, sizeof(Node));
        }

        /**
         * @brief Copies the given (sub-) tree recursively.
         *
         * Firstly the given node is copied. Then its children are copied.
         *
         * @param dst The destination of the new tree.
         * @param src The tree to copy.
         */
        void recursiveCopy(nodeType dst, nodeType src) {
            alloc.allocate(dst, sizeof(Node));
            alloc.construct(dst, *src);
            if (src->left  != NULL) { recursiveCopy(dst->left, src->left);   }
            if (src->right != NULL) { recursiveCopy(dst->right, src->right); }
        }


        /**
         * Searches in the given (sub-) tree for the given content. Returns a pair consisting of the node containing the
         * searched element or NULL and an insertion point.
         *
         * @param c The content to be found.
         * @param begin The (sub-) tree to be searched.
         * @return A pair with the node containing the element and an insertion point.
         */
        ft::pair<nodeType, nodeType *> find(contentType c, nodeType begin) {
            if (compare(begin->content, c)) {
                return begin->left  == NULL ? ft::make_pair(NULL, &begin->left)  : find(c, begin->left);
            } else if (compare(c, begin->content)) {
                return begin->right == NULL ? ft::make_pair(NULL, &begin->right) : find(c, begin->right);
            } else {
                return ft::make_pair(begin, NULL);
            }
        }
    };
}

#endif //FT_CONTAINERS_TREE_HPP
