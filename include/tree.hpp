//
// Created by Manuel Hahn on 9/2/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <cstddef>
#include <stdexcept>
#include "TreeIterator.hpp"

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
         * The type of an iterator for this tree.
         */
        typedef typename TreeIterator      <contentType, nodeType>   iteratorType;
        /**
         * The type of a const iterator for this tree.
         */
        typedef typename TreeIterator<const contentType, nodeType>   constIteratorType;

        /**
         * Default constructor. Initializes this tree with a NULL root node.
         *
         * @param comp The compare object to be used to sort the contents of this tree.
         */
        explicit Tree(Compare comp = Compare()): root(NULL), alloc(allocatorType()), compare(comp), count(0) {}

        /**
         * Copy constructor. Copies the whole tree, all elements are deeply copied.
         *
         * @param other The other tree to copy.
         */
        Tree(const Tree & other): root(NULL), alloc(other.alloc), compare(other.compare), count(0) {
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
             std::size_t tmpSize = size();
             root = other.root;
             count = other.size();
             other.root = tmp;
             other.count = tmpSize;
         }

         /**
          * Returns whether this tree is empty, e. g. does not contain any nodes.
          *
          * @return Whether this tree is empty.
          */
         bool isEmpty() const { return root == NULL; }

         /**
          * Searches for a node containing the given content. If no such node is found an out of range exception
          * is thrown.
          *
          * @param c The content to search for.
          * @return A reference to that content.
          */
         contentType & find(const contentType & c) {
             ft::pair<nodeType, nodeType *> result = find(c, root);
             if (result.second != NULL) {
                 throw std::out_of_range("Value not found!");
             }
             return result.first->content;
         }

         /**
          * Searches for the given content. If no node containing the given content is found, a new node with a
          * default constructed content is inserted and a reference to that content is returned. Otherwise, a
          * reference to the content of the found node is returned.
          *
          * @param c The content to search for.
          * @return A reference to the content of the found or inserted node.
          */
         contentType & findOrInsert(const contentType & c) {
             ft::pair<nodeType, nodeType *> result = find(c, root);
             if (result.second == NULL) {
                 return result.first->content;
             } else {
                 return *coreInsert(result, c).first;
             }
         }

         /**
          * Returns the size of this tree.
          *
          * @return The size of this tree.
          */
         std::size_t size() const { return count; }

         /**
          * @brief Inserts the given value into this tree if it is not already present.
          *
          * If the given value already exists, nothing happens.
          *
          * @return A pair consisting of an iterator pointing to the inserted or already
          * existing node and a boolean value representing whether the value has been inserted or not.
          */
         ft::pair<iteratorType, bool> insert(const contentType & value) {
             ft::pair<nodeType, nodeType *> position = find(value, root);
             return coreInsert(position, value);
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
         * The count of stored elements.
         */
        std::size_t   count;

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
         * @brief Searches in the given (sub-) tree for the given content.
         * Returns a pair consisting of the node containing the searched element
         * or NULL and an insertion point.
         *
         * @param c The content to be found.
         * @param begin The (sub-) tree to be searched.
         * @return A pair with the node containing the element and an insertion point.
         */
        ft::pair<nodeType, nodeType *> find(contentType & c, nodeType begin) {
            if (compare(begin->content, c)) {
                return begin->left  == NULL ? ft::make_pair(begin, &begin->left)  : find(c, begin->left);
            } else if (compare(c, begin->content)) {
                return begin->right == NULL ? ft::make_pair(begin, &begin->right) : find(c, begin->right);
            } else {
                return ft::make_pair(begin, NULL);
            }
        }

        /**
         * @brief Inserts the given content value at the given position.
         *
         * Does nothing if the content already exists.
         *
         * @param position The position where to insert the new node.
         * @param value    The value to be inserted.
         * @return A pair consisting of an iterator pointing to the inserted node or to the node
         * that already consists of the given value and a boolean value representing the information
         * whether the value has been inserted or not.
         */
        ft::pair<iteratorType, bool> coreInsert(ft::pair<nodeType, nodeType *> position, const contentType & value) {
            if (position.first == NULL) {
                Node tmp;
                tmp.content = value;
                tmp.root = position.first;
                alloc.allocate(*position.second, sizeof(Node));
                alloc.construct(*position.second, tmp);
                // TODO: rebalance
                return ft::make_pair(iteratorType(*position.second), true);
            }
            return ft::make_pair(iteratorType(position.first), false);
        }
    };
}

#endif //FT_CONTAINERS_TREE_HPP
