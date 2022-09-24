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
             * A boolean value indicating whether this node is to be treated as a sentinel node.
             */
            bool sentinel;
            /**
             * The actual content of this node.
             */
            valueType content;

            /**
             * @brief Default constructor.
             *
             * Initializes the pointers with NULL, the content is default constructed.
             *
             * @param sentinel Optionally marks this node as a sentinel node.
             */
            explicit Node(bool sentinel = false)
                : left(NULL), root(NULL), right(NULL), sentinel(sentinel), content() {}

            /**
             * @brief Initializes this node using the given content.
             *
             * The pointers are set to NULL.
             *
             * @param content The content this node will store.
             */
            explicit Node(const valueType & content)
                : left(NULL), root(NULL), right(NULL), sentinel(false), content(content) {}

            /**
             * Copy constructor. Initializes all values with the ones of the other Node.
             *
             * @param other The other node to copy the values from.
             */
            Node(const Node & other)
                : left(other.left), root(other.root), right(other.right), sentinel(other.sentinel), content(other.content) {}

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
                    left     = other.left;
                    root     = other.root;
                    right    = other.right;
                    sentinel = other.sentinel;
                    content  = other.content;
                }
            }
        };

    public:
        /**
         * The type of the content held by the nodes.
         */
        typedef T                                                contentType;
        /**
         * The type used for sizes.
         */
        typedef std::size_t                                      sizeType;
        /**
         * The type of the used Nodes.
         */
        typedef Node *                                           nodeType;
        /**
         * The const type of the used Nodes.
         */
        typedef Node * const                                     constNodeType;
        /**
         * The type of the compare object.
         */
        typedef Compare                                          compareType;
        /**
         * The type of the rebound allocator.
         */
        typedef typename Allocator::template rebind<Node>::other allocatorType;
        /**
         * The type of an iterator for this tree.
         */
        typedef TreeIterator      <contentType, nodeType>        iteratorType;
        /**
         * The type of a const iterator for this tree.
         */
        typedef TreeIterator<const contentType, nodeType>        constIteratorType;

        /**
         * Default constructor. Initializes this tree with a NULL root node.
         *
         * @param comp The compare object to be used to sort the contents of this tree.
         */
        explicit Tree(Compare comp)
            : root(NULL), beginSentinel(NULL), endSentinel(NULL), alloc(allocatorType()), compare(comp), count(0) {
        }

        /**
         * Copy constructor. Copies the whole tree, all elements are deeply copied.
         *
         * @param other The other tree to copy.
         */
        Tree(const Tree & other): root(NULL), alloc(other.alloc), compare(other.compare), count(other.count) {
            if (other.root != NULL) {
                recursiveCopy(&root, other.root, NULL);
                beginSentinel = findBeginSentinel();
                endSentinel   = findEndSentinel();
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
                    recursiveCopy(&root, other.root, NULL);
                    beginSentinel = findBeginSentinel();
                    endSentinel   = findEndSentinel();
                }
                count = other.count;
            }
            return *this;
        }

        /**
         * @brief Clears this tree properly.
         */
        void clear() {
            if (root != NULL) {
                recursiveDestroy(root);
                root = beginSentinel = endSentinel = NULL;
            }
            count = 0;
        }

        /**
         * Swaps this tree with the other one.
         *
         * @param other The other tree to exchange the values with.
         */
        void swap(Tree & other) {
            nodeType tmpRoot          = root,
                     tmpBeginSentinel = beginSentinel,
                     tmpEndSentinel   = endSentinel;

            std::size_t tmpSize = size();

            root          = other.root;
            beginSentinel = other.beginSentinel;
            endSentinel   = other.endSentinel;
            count         = other.size();

            other.root          = tmpRoot;
            other.beginSentinel = tmpBeginSentinel;
            other.endSentinel   = tmpEndSentinel;
            other.count         = tmpSize;
        }

        /**
         * Returns whether this tree is empty, e. g. does not contain any nodes.
         *
         * @return Whether this tree is empty.
         */
        bool isEmpty() const { return root == NULL; }

        /**
         * Returns an iterator pointing past the last element of this tree.
         *
         * @return A past the last iterator for this tree.
         */
        iteratorType end() { return iteratorType(endSentinel); }

        /**
         * Returns an iterator pointing past the last element of this tree.
         *
         * @return A past the last iterator for this tree.
         */
        constIteratorType end() const { return constIteratorType(endSentinel); }

        /**
         * Returns an iterator pointing to the first element of this tree.
         *
         * @return An iterator to the beginning of this tree.
         */
        iteratorType begin() {
            iteratorType it = iteratorType(beginSentinel);
            if (isEmpty()) {
                return it;
            } else {
                return ++it;
            }
        }

         /**
         * Returns an iterator pointing to the first element of this tree.
         *
         * @return An iterator to the beginning of this tree.
         */
        constIteratorType begin() const {
            constIteratorType it = constIteratorType(beginSentinel);
            if (isEmpty()) {
                return it;
            } else {
                return ++it;
            }
        }

        /**
         * @brief Searches for a node consisting of the given value.
         *
         * If no such node is found, an iterator pointing to the end of the tree
         * is returned.
         *
         * @param value The value to search for.
         * @return An iterator pointing to the found node or to the end of the tree.
         */
        iteratorType find(const contentType & value) {
            ft::pair<nodeType, nodeType *> result = find(value, &root);
            if (*result.second == result.first && result.first != NULL) {
                return iteratorType(result.first);
            }
            return iteratorType(end());
        }

        /**
         * @brief Searches for a node consisting of the given value.
         *
         * If no such node is found, an iterator pointing to the end of the tree
         * is returned.
         *
         * @param value The value to search for.
         * @return An iterator pointing to the found node or to the end of the tree.
         */
        constIteratorType find(const contentType & value) const {
            ft::pair<constNodeType, constNodeType *> result = find(value, &root);
            if (*result.second == result.first && result.first != NULL) {
                return constIteratorType(result.first);
            }
            return constIteratorType(end());
        }

        /**
         * Searches for a node containing the given content. If no such node is found an out of range exception
         * is thrown.
         *
         * @param c The content to search for.
         * @return A reference to that content.
         */
        contentType & findOrThrow(const contentType & c) {
            ft::pair<nodeType, nodeType *> result = find(c, &root);
            if (*result.second == result.first && result.first != NULL) {
                return result.first->content;
            }
            throw std::out_of_range("Value not found!");
        }

        /**
         * Searches for a node containing the given content. If no such node is found an out of range exception
         * is thrown.
         *
         * @param c The content to search for.
         * @return A reference to that content.
         */
        const contentType & findOrThrow(const contentType & c) const {
            ft::pair<constNodeType, constNodeType *> result = find(c, &root);
            if (*result.second == result.first && result.first != NULL) {
                return result.first->content;
            }
            throw std::out_of_range("Value not found!");
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
            ft::pair<nodeType, nodeType *> result = find(c, &root);
            if (*result.second == result.first && result.first != NULL) {
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
            ft::pair<nodeType, nodeType *> position = find(value, &root);
            return coreInsert(position, value);
        }

        iteratorType lowerBound(const contentType & value) {
            // TODO: Implement
            return end();
        }

        constIteratorType lowerBound(const contentType & value) const {
            // TODO: Implement
            return end();
        }

        iteratorType upperBound(const contentType & value) {
            // TODO: Implement
            return end();
        }

        constIteratorType upperBound(const contentType & value) const {
            // TODO: Implement
            return end();
        }

    private:
        /**
         * The root Node of this tree.
         */
        nodeType      root;
        /**
         * A pointer to the element preceding the first element of this tree.
         */
        nodeType      beginSentinel;
        /**
         * A pointer to the element past the last element of this tree.
         */
        nodeType      endSentinel;
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
        nodeType recursiveCopy(nodeType * dst, nodeType src, nodeType parent) {
            *dst = alloc.allocate(sizeof(Node));
            alloc.construct(*dst, *src);
            (*dst)->root = parent;
            if (src->left  != NULL) { (*dst)->left  = recursiveCopy(&(*dst)->left,  src->left,  *dst); }
            if (src->right != NULL) { (*dst)->right = recursiveCopy(&(*dst)->right, src->right, *dst); }
            return *dst;
        }

        /**
         * @brief Searches in the given (sub-) tree for the given content.
         *
         * Returns a pair consisting of the node containing the searched element
         * or NULL and an insertion point.
         *
         * @param c The content to be found.
         * @param begin The (sub-) tree to be searched.
         * @return A pair with the node containing the element and an insertion point.
         */
        ft::pair<nodeType, nodeType *> find(const contentType & c, nodeType * begin) {
            if (*begin != NULL) {
                if (compare(c, (*begin)->content)) {
                    return (*begin)->left == NULL || (*begin)->left->sentinel
                    /* true:  */ ? ft::make_pair(*begin, &(*begin)->left)
                    /* false: */ : find(c, &(*begin)->left);
                } else if (compare((*begin)->content, c)) {
                    return (*begin)->right == NULL || (*begin)->right->sentinel
                    /* true:  */ ? ft::make_pair(*begin, &(*begin)->right)
                    /* false: */ : find(c, &(*begin)->right);
                }
            }
            return ft::make_pair(*begin, begin);
        }

        /**
         * @brief Searches in the given (sub-) tree for the given content.
         *
         * Returns a pair consisting of the node containing the searched element
         * or NULL and an insertion point.
         *
         * @param c The content to be found.
         * @param begin The (sub-) tree to be searched.
         * @return A pair with the node containing the element and an insertion point.
         */
        ft::pair<constNodeType, constNodeType *> find(const contentType & c, constNodeType * begin) const {
            if (*begin != NULL) {
                if (compare(c, (*begin)->content)) {
                    return (*begin)->left == NULL || (*begin)->left->sentinel
                    /* true:  */ ? ft::make_pair<constNodeType, constNodeType *>(*begin, &(*begin)->left)
                    /* false: */ : find(c, &(*begin)->left);
                } else if (compare((*begin)->content, c)) {
                    return (*begin)->right == NULL || (*begin)->right->sentinel
                    /* true:  */ ? ft::make_pair<constNodeType, constNodeType *>(*begin, &(*begin)->right)
                    /* false: */ : find(c, &(*begin)->right);
                }
            }
            return ft::make_pair(*begin, begin);
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
            if (position.first == NULL || position.first != *position.second) {
                Node tmp(value);
                tmp.root = position.first;
                if (isEmpty()) {
                    // Create the root and init sentinels
                    *position.second = alloc.allocate(sizeof(Node));
                    alloc.construct(*position.second, tmp);
                    initSentinels();
                } else {
                    // Make sure to not lose the sentinels
                    nodeType maybeSentinel = *position.second;
                    const bool right = maybeSentinel == position.first->right;
                    nodeType newOne = alloc.allocate(sizeof(Node));
                    if (maybeSentinel != NULL) {
                        if (right) {
                            tmp.right = maybeSentinel;
                        } else {
                            tmp.left = maybeSentinel;
                        }
                        maybeSentinel->root = newOne;
                    }
                    *position.second = newOne;
                    alloc.construct(*position.second, tmp);
                }
                // TODO: rebalance
                ++count;
                return ft::make_pair(iteratorType(*position.second), true);
            }
            return ft::make_pair(iteratorType(position.first), false);
        }

        /**
         * Searches for the begin sentinel of this tree.
         *
         * @return The begin sentinel of this tree.
         */
        nodeType findBeginSentinel() {
            nodeType tmp = root;
            for (; tmp != NULL && !tmp->sentinel && tmp->left != NULL; tmp = tmp->left);
            return tmp;
        }

        /**
         * Searches for the end sentinel of this tree.
         *
         * @return The end sentinel of this tree.
         */
        nodeType findEndSentinel() {
            nodeType tmp = root;
            for (; tmp != NULL && !tmp->sentinel && tmp->right != NULL; tmp = tmp->right);
            return tmp;
        }

        /**
         * Initializes the begin and end sentinels.
         */
        void initSentinels() {
            Node tmp(true);
            tmp.root = root;
            root->left = alloc.allocate(sizeof(Node));
            alloc.construct(root->left, tmp);
            root->right = alloc.allocate(sizeof(Node));
            alloc.construct(root->right, tmp);
            beginSentinel = root->left;
            endSentinel = root->right;
        }
    };
}

#endif //FT_CONTAINERS_TREE_HPP
