//
// Created by Manuel Hahn on 9/2/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <cstddef>
#include <limits>
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
             * The types specifying the type of the node.
             */
            enum Type {
                /**
                 * Indicating the node is red.
                 */
                RED,
                /**
                 * Indicating the node is black.
                 */
                BLACK,
                /**
                 * Indicating the node is a NIL node (which are considered to be black).
                 */
                NIL,
                /**
                 * Indicating the node is a sentinel (which are considered to be black).
                 */
                SENTINEL
            };

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
             * The type of this node.
             */
            Type type;
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
                : left(NULL), root(NULL), right(NULL), type(sentinel ? SENTINEL : RED), content() {}

            /**
             * @brief Initializes this node using the given content.
             *
             * The pointers are set to NULL.
             *
             * @param content The content this node will store.
             */
            explicit Node(const valueType & content)
                : left(NULL), root(NULL), right(NULL), type(RED), content(content) {}

            /**
             * Copy constructor. Initializes all values with the ones of the other Node.
             *
             * @param other The other node to copy the values from.
             */
            Node(const Node & other)
                : left(other.left), root(other.root), right(other.right), type(other.type), content(other.content) {}

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
                    type    = other.type;
                    content = other.content;
                }
            }
        };

    public:
        /**
         * The type of the content held by the nodes.
         */
        typedef T                                                contentType;
        /**
         * The type of the rebound allocator.
         */
        typedef typename Allocator::template rebind<Node>::other allocatorType;
        /**
         * The type used for sizes.
         */
        typedef typename allocatorType::size_type                sizeType;
        /**
         * The type used for differences.
         */
        typedef std::ptrdiff_t                                   differenceType;
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
         * The type of an iterator for this tree.
         */
        typedef TreeIterator      <contentType, nodeType>        iteratorType;
        /**
         * The type of a const iterator for this tree.
         */
        typedef ConstTreeIterator<contentType, nodeType>         constIteratorType;

        /**
         * Default constructor. Initializes this tree with a NULL root node.
         *
         * @param comp The compare object to be used to sort the contents of this tree.
         */
        explicit Tree(Compare comp)
            : root(NULL), beginSentinel(emptySentinel()), endSentinel(beginSentinel), alloc(allocatorType()), compare(comp), count(0) {
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
       ~Tree() { internalClear(); }

        /**
         * Copy assignment operator. Clears this tree and copies the given tree deeply.
         *
         * @param other The other tree to copy.
         * @return A reference to this tree.
         */
        Tree & operator=(const Tree & other) {
            if (&other != this) {
                internalClear();
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
                beginSentinel = endSentinel;
                endSentinel->root = endSentinel->left = endSentinel->right = NULL;
                root = NULL;
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

            sizeType tmpSize = size();

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
        sizeType size() const { return count; }

        /**
         * @brief Inserts the given value into this tree if it is not already present.
         *
         * If the given value already exists, nothing happens.
         *
         * @param value The value that should be inserted.
         * @return A pair consisting of an iterator pointing to the inserted or already
         * existing node and a boolean value representing whether the value has been inserted or not.
         */
        ft::pair<iteratorType, bool> insert(const contentType & value) {
            ft::pair<nodeType, nodeType *> position = find(value, &root);
            return coreInsert(position, value);
        }

        /**
         * @brief Inserts the given value into this tree if it is not already present.
         *
         * If the given value already exists, nothing happens. The iterator is used as a hint where to
         * start the search of the insertion point.
         *
         * @param hint The hint where the insertion point should be.
         * @param value The value that should be inserted.
         */
        iteratorType insert(iteratorType hint, const contentType & value) {
            if (hint.base() != beginSentinel) {
                --hint;
                const bool lower          = compare(value, *hint);
                const bool insertSideNull = (lower ? hint.base()->left : hint.base()->right) == NULL;
                if (canInsert(hint.base(), value) && insertSideNull) {
                    return coreInsert(ft::make_pair(hint.base(), lower ? &hint.base()->left : &hint.base()->right), value).first;
                }
            }
            return insert(value).first;
        }
        
        /**
         * @brief Erases the node pointed to by the given iterator.
         *
         * Rebalances this tree using the logic of the red / black tree if necessary.
         *
         * @param position The position that should be removed.
         */
        void erase(iteratorType position) {
            nodeType toDelete = position.base();
            if (toDelete != beginSentinel && toDelete != endSentinel) {
                if (toDelete == root && count == 1) {
                    rootDeletion();
                    count = 0;
                    return;
                }
                nodeType            movedUp = NULL;
                typename Node::Type wasType = Node::SENTINEL;
                if (toDelete->left == NULL || toDelete->right == NULL) {
                    wasType = toDelete->type;
                    movedUp = deleteSingleChildNode(toDelete);
                } else if (toDelete->right == endSentinel) {
                    wasType = toDelete->type;
                    rotateReplace(toDelete->root, toDelete, toDelete->left);
                    movedUp = toDelete->left;
                    endSentinel->root = movedUp;
                    findMaximum(movedUp)->right = endSentinel;
                } else {
                    nodeType successor = findMinimum(toDelete->right);

                    nodeType            tmpRoot  = toDelete->root;
                    nodeType            tmpLeft  = toDelete->left;
                    nodeType            tmpRight = toDelete->right;
                    typename Node::Type tmpType  = toDelete->type;

                    toDelete->left  = successor->left;
                    toDelete->type  = successor->type;
                    toDelete->right = successor->right;
                    toDelete->root  = successor->root == toDelete ? successor : successor->root;

                    successor->left  = tmpLeft;
                    successor->root  = tmpRoot;
                    successor->type  = tmpType;
                    successor->right = tmpRight == successor ? toDelete : tmpRight;

                    if (successor->left != NULL) {
                        successor->left->root = successor;
                    }
                    if (successor->right != NULL) {
                        successor->right->root = successor;
                    }
                    if (successor->root != NULL) {
                        (toDelete == successor->root->right ? successor->root->right : successor->root->left) = successor;
                    }

                    movedUp = deleteSingleChildNode(toDelete);
                    wasType = toDelete->type;
                    if (toDelete == root) {
                        root = successor;
                    }
                }
                deleteNode(toDelete);
                if (wasType != Node::RED) {
                    rebalanceDelete(movedUp);
                    if (movedUp->type == Node::NIL) {
                        rotateReplace(movedUp->root, movedUp, NULL);
                        alloc.destroy(movedUp);
                        alloc.deallocate(movedUp, sizeof(Node));
                    }
                }
                --count;
            }
        }
        
        /**
         * @brief Searches for the first element whose value is not less than the key.
         *
         * Returns the past the end iterator if no such element exists.
         *
         * @param value The value whose lower bound to be found.
         * @return The first element not lower than the given one.
         */
        iteratorType lowerBound(const contentType & value) {
            return iteratorType(lowerBound(value, root));
        }

        /**
         * @brief Searches for the first element whose value is not less than the key.
         *
         * Returns the past the end iterator if no such element exists.
         *
         * @param value The value whose lower bound to be found.
         * @return The first element not lower than the given one.
         */
        constIteratorType lowerBound(const contentType & value) const {
            return constIteratorType(lowerBound(value, root));
        }

        /**
         * @brief Searches for the first element whose value is greater than the given one.
         *
         * If no such element exists, the past the end iterator is returned.
         *
         * @param value The value whose upper bound to be found.
         * @return The first element greater than the given value.
         */
        iteratorType upperBound(const contentType & value) {
            return iteratorType(upperBound(value, root));
        }

        /**
         * @brief Searches for the first element whose value is greater than the given one.
         *
         * If no such element exists, the past the end iterator is returned.
         *
         * @param value The value whose upper bound to be found.
         * @return The first element greater than the given value.
         */
        constIteratorType upperBound(const contentType & value) const {
            return constIteratorType(upperBound(value, root));
        }

        /**
         * Returns the maximal count of nodes this tree can hold.
         *
         * @return The maximum count of nodes.
         */
        sizeType maxSize() const {
            sizeType allocatorSize  = alloc.max_size(),
                     diffSize       = static_cast<sizeType>(std::numeric_limits<differenceType>::max());
            return allocatorSize > diffSize ? diffSize : allocatorSize;
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
        sizeType      count;

        /**
         * Clears everything in this tree, including any sentinels.
         */
        void internalClear() {
            clear();
            if (endSentinel != NULL) {
                alloc.destroy(endSentinel);
                alloc.deallocate(endSentinel, sizeof(Node));
                endSentinel = beginSentinel = NULL;
            }
        }

        /**
         * @brief Destroys and deallocates the given node.
         *
         * Destroys all children of the given node beforehand.
         *
         * @param node The node to destroy.
         */
        void recursiveDestroy(nodeType node) {
            if (node->left  != NULL)                                        { recursiveDestroy(node->left);  }
            if (node->right != NULL && node->right->type != Node::SENTINEL) { recursiveDestroy(node->right); }
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
                    return ((*begin)->left == NULL || (*begin)->left->type == Node::SENTINEL)
                    /* true:  */ ? ft::make_pair(*begin, &(*begin)->left)
                    /* false: */ : find(c, &(*begin)->left);
                } else if (compare((*begin)->content, c)) {
                    return ((*begin)->right == NULL || (*begin)->right->type == Node::SENTINEL)
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
                    return ((*begin)->left == NULL || (*begin)->left->type == Node::SENTINEL)
                    /* true:  */ ? ft::make_pair<constNodeType, constNodeType *>(*begin, &(*begin)->left)
                    /* false: */ : find(c, &(*begin)->left);
                } else if (compare((*begin)->content, c)) {
                    return ((*begin)->right == NULL || (*begin)->right->type == Node::SENTINEL)
                    /* true:  */ ? ft::make_pair<constNodeType, constNodeType *>(*begin, &(*begin)->right)
                    /* false: */ : find(c, &(*begin)->right);
                }
            }
            return ft::make_pair(*begin, begin);
        }

        /**
         * Finds the left most child of the given node.
         *
         * @param node The node whose left most child should be found.
         * @return The left most child of the given node.
         */
        inline nodeType findMinimum(nodeType node) {
            for (; node->left != NULL; node = node->left);
            return node;
        }
        
        /**
         * Finds the right most child of the given node.
         *
         * @param node The node whose right most child should be found.
         * @return The right most child of the given node.
         */
        inline nodeType findMaximum(nodeType node) {
            for (; node->right != NULL; node = node->right);
            return node;
        }

        /**
         * Returns whether the given value can be inserted at the given position.
         *
         * @param node The node below which the value should be inserted.
         * @param value The value that should be inserted.
         * @return Whether the value can be inserted according to the sorting at the given position.
         */
        inline bool canInsert(nodeType node, const contentType & value) {
            while (node != root && node->root != NULL) {
                if (!compare(value, node->content)) {
                    return false;
                }
                node = node->root;
            }
            return true;
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
                iteratorType retIt;
                Node tmp(value);
                tmp.root = position.first;
                if (isEmpty()) {
                    // Create the root and init sentinels
                    *position.second = alloc.allocate(sizeof(Node));
                    try {
                        alloc.construct(*position.second, tmp);
                    } catch (...) {
                        alloc.deallocate(*position.second, sizeof(Node));
                        throw;
                    }
                    retIt = iteratorType(*position.second);
                    try {
                        initSentinels();
                    } catch (...) {
                        alloc.destroy(*position.second);
                        alloc.deallocate(*position.second, sizeof(Node));
                        throw;
                    }
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
                    try {
                        alloc.construct(*position.second, tmp);
                    } catch (...) {
                        alloc.deallocate(*position.second, sizeof(Node));
                        throw;
                    }
                    retIt = iteratorType(*position.second);
                    rebalance(*position.second);
                }
                ++count;
                return ft::make_pair(retIt, true);
            }
            return ft::make_pair(iteratorType(position.first), false);
        }
        
        /**
         * Exchanges the children of the given nodes.
         *
         * @param parent The parent of the old child.
         * @param oldChild The old child to be replaced.
         * @param newChild The new child to replace the old one.
         */
        inline void rotateReplace(nodeType parent, nodeType oldChild, nodeType newChild) {
            if (parent == NULL) {
                root = newChild;
            } else {
                (parent->right == oldChild ? parent->right : parent->left) = newChild;
            }
            if (newChild != NULL) {
                newChild->root = parent;
            }
        }
        
        /**
         * Performs a rotation to the right around the given node.
         *
         * @param node The node to rotate around.
         */
        inline void rotateRight(nodeType node) {
            nodeType parent    = node->root,
                     leftChild = node->left;
            node->left = leftChild->right;
            if (leftChild->right != NULL) {
                leftChild->right->root = node;
            }
            leftChild->right = node;
            node->root = leftChild;
            rotateReplace(parent, node, leftChild);
        }
        
        /**
         * Performs a rotation to the left around the given node.
         *
         * @param node The node to rotate around.
         */
        inline void rotateLeft(nodeType node) {
            nodeType parent     = node->root,
                     rightChild = node->right;
            node->right = rightChild->left;
            if (rightChild->left != NULL) {
                rightChild->left->root = node;
            }
            rightChild->left = node;
            node->root = rightChild;
            rotateReplace(parent, node, rightChild);
        }

        /**
         * Returns the uncle of the given node.
         *
         * @param node The node whose uncle to return.
         * @return The found uncle or NULL if not found.
         */
        inline nodeType getUncle(nodeType node) {
            nodeType grandParent = node->root;
            return grandParent->right == node ? grandParent->left : grandParent->right;
        }
        
        /**
         * @brief Removes the given node from this tree.
         *
         * Replaces the node by its single child if it as one, or by NULL or a temporary node
         * depending on the colour of the given node.
         *
         * @param node The node to be deleted.
         * @return The node that replaces the given one.
         */
        inline nodeType deleteSingleChildNode(nodeType node) {
            if (node->right != NULL) {
                rotateReplace(node->root, node, node->right);
                return node->right;
            } else if (node->left != NULL) {
                rotateReplace(node->root, node, node->left);
                return node->left;
            } else {
                nodeType newOne = NULL;
                if (node->type != Node::RED) {
                    Node tmp(true);
                    tmp.type = Node::NIL;
                    newOne = alloc.allocate(sizeof(Node));
                    alloc.construct(newOne, tmp);
                }
                rotateReplace(node->root, node, newOne);
                return newOne;
            }
        }

        /**
         * @brief Deletes the root node and the begin sentinel.
         *
         * Sets the pointers to NULL.
         */
        inline void rootDeletion() {
            alloc.destroy(root);
            alloc.destroy(beginSentinel);
            alloc.deallocate(root,          sizeof(Node));
            alloc.deallocate(beginSentinel, sizeof(Node));
            root = NULL;
            beginSentinel = endSentinel;
            endSentinel->right = endSentinel->left = endSentinel->root = NULL;
        }
        
        /**
         * @brief Deletes the given node.
         *
         * If no node is given, nothing happens.
         *
         * @param node The node to be deleted.
         */
        inline void deleteNode(nodeType node) {
            if (node != NULL) {
                alloc.destroy(node);
                alloc.deallocate(node, sizeof(Node));
            }
        }
        
        /**
         * Rebalances this tree using the logic of the red / black tree.
         *
         * @param node The inserted node.
         */
        void rebalance(nodeType node) {
            nodeType parent = node->root;
            if (parent == NULL || parent->type == Node::BLACK) {
                return;
            }
            nodeType grandParent = parent->root;
            if (grandParent == NULL) {
                parent->type = Node::BLACK;
                return;
            }
            nodeType uncle = getUncle(parent);
            if (uncle != NULL && uncle->type == Node::RED) {
                parent->type = Node::BLACK;
                grandParent->type = Node::RED;
                uncle->type = Node::BLACK;
                rebalance(grandParent);
            } else if (parent == grandParent->left) {
                if (node == parent->right) {
                    rotateLeft(parent);
                    parent = node;
                }
                rotateRight(grandParent);
                parent->type = Node::BLACK;
                grandParent->type = Node::RED;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    parent = node;
                }
                rotateLeft(grandParent);
                parent->type = Node::BLACK;
                grandParent->type = Node::RED;
            }
        }

        /**
         * Returns whether the given node is to be treaten like a black node.
         *
         * @param node The node to be checked.
         * @return Whether the given node can be treaten as a black node.
         */
        inline bool isBlack(nodeType node) { return node == NULL || node->type == Node::SENTINEL
                                                                 || node->type == Node::BLACK;
                                           }
        
        /**
         * Returns whether the given node has a sentinel as child.
         *
         * @param node The node to be checked.
         * @return Whether at least one of the children of the given node is a sentinel,
         */
        inline bool hasSentinel(nodeType node) {
            return (node->left  != NULL && node->left->type  == Node::SENTINEL)
                || (node->right != NULL && node->right->type == Node::SENTINEL);
        }
        
        /**
         * Returns the sibling of the given node.
         *
         * @param node The node whose sibling to return.
         * @return The sibling of the given node.
         */
        inline nodeType getSibling(nodeType node) {
            nodeType parent = node->root;
            return node == parent->left ? parent->right
                                        : parent->left;
        }
        
        /**
         * Balances the given node and its sibling.
         *
         * @param node The node where to balance.
         * @param sibling The sibling of the given node.
         */
        inline void balanceRedSibling(nodeType node, nodeType sibling) {
            sibling->type = Node::BLACK;
            node->root->type = Node::RED;
            if (node == node->root->left) {
                rotateLeft(node->root);
            } else {
                rotateRight(node->root);
            }
        }
        
        /**
         * Performs the balancing if the sibling of the given node has at least one black child.
         *
         * @param node The node to handle.
         * @param sibling The sibling of the given node.
         */
        inline void balanceRedSiblingBlackChild(nodeType node, nodeType sibling) {
            const bool isLeft = node == node->root->left;
            if (isLeft && isBlack(sibling->right)) {
                sibling->left->type = Node::BLACK;
                sibling->type       = Node::RED;
                rotateRight(sibling);
                sibling = node->root->right;
            } else if (!isLeft && isBlack(sibling->left)) {
                sibling->right->type = Node::BLACK;
                sibling->type        = Node::RED;
                rotateLeft(sibling);
                sibling = node->root->left;
            }
            sibling->type    = node->root->type;
            node->root->type = Node::BLACK;
            if (isLeft) {
                sibling->right->type = Node::BLACK;
                rotateLeft(node->root);
            } else {
                sibling->left->type  = Node::BLACK;
                rotateRight(node->root);
            }
        }
        
        /**
         * Rebalances this tree after a deletion using the logic of the red / black tree.
         *
         * @param node The node where to begin the rebalancing.
         */
        void rebalanceDelete(nodeType node) {
            if (node == root) {
                return;
            }
            nodeType sibling = getSibling(node);
            if (sibling->type == Node::RED) {
                balanceRedSibling(node, sibling);
                sibling = getSibling(node);
            }
            if (isBlack(sibling->left) && isBlack(sibling->right)) {
                sibling->type = Node::RED;
                if (node->root->type == Node::RED) {
                    node->root->type = Node::BLACK;
                } else {
                    rebalanceDelete(node->root);
                }
            } else {
                balanceRedSiblingBlackChild(node, sibling);
            }
        }
        
        /**
         * Searches for the begin sentinel of this tree.
         *
         * @return The begin sentinel of this tree.
         */
        nodeType findBeginSentinel() {
            nodeType tmp = root;
            for (; tmp != NULL && tmp->type != Node::SENTINEL && tmp->left != NULL; tmp = tmp->left);
            return tmp;
        }

        /**
         * Searches for the end sentinel of this tree.
         *
         * @return The end sentinel of this tree.
         */
        nodeType findEndSentinel() {
            nodeType tmp = root;
            for (; tmp != NULL && tmp->type != Node::SENTINEL && tmp->right != NULL; tmp = tmp->right);
            return tmp;
        }

        /**
         * Allocates an empty sentinel node.
         *
         * @return A new sentinel node.
         */
        nodeType emptySentinel() {
            Node tmp(true);
            nodeType ret = alloc.allocate(sizeof(Node));
            try {
                alloc.construct(ret, tmp);
            } catch (...) {
                alloc.deallocate(ret, sizeof(Node));
                throw;
            }
            return ret;
        }

        /**
         * Initializes the begin and end sentinels.
         */
         void initSentinels() {
             root->left = emptySentinel();
             root->left->root = root;
             root->right = endSentinel;
             endSentinel->root = root;
             beginSentinel = root->left;
         }

        /**
         * @brief Searches for the first element whose value is greater than the given one.
         *
         * If no such element exists, the past the end iterator is returned.
         *
         * @param value The value whose upper bound to be found.
         * @return The first element greater than the given value.
         */
        nodeType upperBound(const contentType & value, nodeType begin) const {
            nodeType result = end().base();
            while (begin != NULL && begin->type != Node::SENTINEL) {
                if (compare(value, begin->content)) {
                    result = begin;
                    begin = begin->left;
                } else {
                    begin = begin->right;
                }
            }
            return result;
        }

        /**
         * @brief Searches for the first element whose value is not less than the key.
         *
         * Returns the past the end iterator if no such element exists.
         *
         * @param value The value whose lower bound to be found.
         * @param begin The node where to start the search.
         * @return The first element not lower than the given one.
         */
        nodeType lowerBound(const contentType & value, nodeType begin) const {
            nodeType result = end().base();
            while (begin != NULL && begin->type != Node::SENTINEL) {
                if (!compare(begin->content, value)) {
                    result = begin;
                    begin = begin->left;
                } else {
                    begin = begin->right;
                }
            }
            return result;
        }
    };
}

#endif //FT_CONTAINERS_TREE_HPP
