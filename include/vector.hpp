//
// Created by Manuel Hahn on 7/5/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include <algorithm> // FIXME: ft version!
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {
    /**
     * A class that holds a number of objects of type T. It is similar to an array, yet
     * more flexible, as more elements can be appended or removed at any time.
     *
     * @tparam T The type of the contained objects.
     * @tparam Allocator The allocator to use, by default the std::allocator.
     */
    template <class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T                                    value_type;
        typedef Allocator                            allocator_type;
        typedef std::size_t                          size_type;
        typedef std::ptrdiff_t                       difference_type;
        typedef value_type &                         reference;
        typedef const value_type &                   const_reference;
        typedef typename Allocator::pointer          pointer;
        typedef typename Allocator::const_pointer    const_pointer;
        typedef pointer                              iterator;
        typedef const_pointer                        const_iterator;
        typedef ft::reverse_iterator<iterator>       reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        /**
         * Constructs an empty vector.
         */
        vector()
            : alloc(Allocator()), start(NULL), memory_capacity(0), object_count(0) {}

        /**
         * Constructs an empty vector, which will use the given allocator.
         *
         * @param alloc The allocator to be used by this instance.
         */
        explicit vector(const Allocator & alloc)
            : alloc(alloc), start(NULL), memory_capacity(0), object_count(0) {}

        /**
         * Constructs a vector holding count number of elements. The elements are copy-constructed
         * from the optionally given value or the default constructor if omitted. All allocations
         * are made using the optionally given allocator, which is the std::allocator by default.
         *
         * @param count The number of objects.
         * @param value The value for all of the objects.
         * @param alloc The allocator to be used by this instance.
         */
        explicit vector(size_type count, const T & value = T(), const Allocator & alloc = Allocator())
            : alloc(alloc), memory_capacity(count), object_count(count) {
            start = vector::alloc.allocate(count);
            for (pointer i = start; ((size_type) (i - start)) < count; ++i) {
                vector::alloc.construct(i, value);
            }
        }

        /**
         * Constructs a vector containing a copy of the objects given in the range. Uses the given
         * allocator for all allocations.
         *
         * @tparam InputIt The type of the input iterators.
         * @param first The beginning of the range.
         * @param last The end of the range to copy.
         * @param alloc The allocator to use, by default std::allocator.
         */
        template <class InputIt>
        vector(InputIt first, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last, const Allocator & alloc = Allocator())
            : alloc(alloc), memory_capacity(ft::distance(first, last)), object_count(ft::distance(first, last)) {
            start = vector::alloc.allocate(object_count);
            for (pointer i = start; first != last; ++i, ++first) {
                vector::alloc.construct(i, *first);
            }
        }

        /**
         * Constructs a vector holding a copy of the given vector.
         *
         * @param other The vector to copy.
         */
        vector(const vector & other)
            : alloc(other.get_allocator()), memory_capacity(other.capacity()), object_count(other.size()) {
            start = alloc.allocate(memory_capacity);
            for (vector::const_iterator it = other.begin(); it != other.end(); ++it) {
                alloc.construct(start + (other.end() - it),  *it);
            }
        }

        /**
         * Destroys this vector. Deallocates all memory previously hold by this instance.
         */
        ~vector() {
            for (pointer i = start; ((size_type) (i - start)) < object_count; ++i) {
                alloc.destroy(i);
            }
            if (start != NULL) // The standard allows free(NULL)!
                alloc.deallocate(start, memory_capacity);
        }

        /**
         * Removes all objects of this instance and copies the contents of the other given vector.
         *
         * @param other The vector to copy.
         * @return A pointer to this instance.
         */
        vector & operator=(const vector & other) {
            clear();
            for (vector::const_iterator it = other.begin(); it != other.end(); ++it) {
                push_back(*it);
            }
            return *this;
        }

        /**
         * Removes all objects held by this vector and stores the given count amount of copies of
         * the given value.
         *
         * @param count The amount of copies to be stored.
         * @param value The value to be copied.
         */
        void assign(size_type count, const T & value) {
            clear();
            for (size_type i = 0; i < count; ++i) {
                push_back(value);
            }
        }

        /**
         * Removes all objects held by this vector and stores a copy of the given range.
         *
         * @tparam InputIt The type of the iterator.
         * @param first The beginning of the range.
         * @param last The end of the range.
         */
        template <class InputIt>
        void assign(InputIt first, InputIt last) {
            clear();
            for (InputIt it = first; it != last; ++it) {
                push_back(*it);
            }
        }

        /**
         * Returns the allocator used by this instance.
         *
         * @return The allocator used by this instance.
         */
        allocator_type get_allocator() const {
            return alloc;
        }

        /**
         * Returns a reference to the object at the given position. Throws an out_of_range exception
         * if the given position is out of the bounds of this vector.
         *
         * @param pos The position of the desired object.
         * @return A reference to the object at the given position.
         */
        reference at(size_type pos) {
            if (pos >= size()) throw std::out_of_range("ft::vector<T, Allocator>::at: Out of range!");
            return *(start + pos);
        }

        /**
         * Returns a const reference to the object at the given position. Throws an out_of_range exception
         * if the given position is out of the bounds of this vector.
         *
         * @param pos The position of the desired object.
         * @return A const reference to the object at the given position.
         */
        const_reference at(size_type pos) const {
            if (pos >= size() || pos < 0) throw std::out_of_range("ft::vector<T, Allocator>::at: Out of range!");
            return *(start + pos);
        }

        /**
         * Returns a reference to the object at the given position. Does not check if the given position is
         * in range.
         *
         * @param pos The position of the desired object.
         * @return The object at the given position.
         */
        reference operator[](size_type pos) {
            return *(start + pos);
        }

        /**
         * Returns a const reference to the object at the given position. Does not check if the given position
         * is in range.
         *
         * @param pos The position of the desired object.
         * @return A const reference to the object at the given position.
         */
        const_reference operator[](size_type pos) const {
            return *(start + pos);
        }

        /**
         * Returns a reference to the first element in this container.
         *
         * @return A reference to the first object.
         */
        reference front() {
            return *start;
        }

        /**
         * Returns a const reference to the first object in this container.
         *
         * @return A const reference to the first object.
         */
        const_reference front() const {
            return *start;
        }

        /**
         * Returns a reference to the last object in this container.
         *
         * @return A reference to the last object.
         */
        reference back() {
            return *(start + size() - 1);
        }

        /**
         * Returns a const reference to the last object in this container.
         *
         * @return A const reference to the last object.
         */
        const_reference back() const {
            return *(start + size() - 1);
        }

        /**
         * Returns a pointer to the memory held by this vector.
         *
         * @return A pointer to the memory block.
         */
        T * data() {
            return start;
        }

        /**
         * Returns a const pointer to the memory held by this vector.
         *
         * @return A const pointer to the memory block.
         */
        const T * data() const {
            return start;
        }

        /**
         * Returns an iterator pointing to the beginning of this container.
         *
         * @return An iterator pointing to the beginning.
         */
        iterator begin() {
            return start;
        }

        /**
         * Returns a const iterator pointing to the beginning of this container.
         *
         * @return A const iterator pointing to the beginning.
         */
        const_iterator begin() const {
            return start;
        }

        /**
         * Returns an iterator pointing behind the last object in this container.
         *
         * @return An iterator pointing to the end.
         */
        iterator end() {
            return start + object_count;
        }

        /**
         * Returns a const iterator pointing behind the last object in this container.
         *
         * @return A const iterator pointing to the end.
         */
        const_iterator end() const {
            return start + object_count;
        }

        /**
         * Returns an iterator pointing to the last element in this container. Incrementing it
         * results in pointing to the previous object.
         *
         * @return A reverse iterator pointing to the last object.
         */
        reverse_iterator rbegin() {
            return ft::reverse_iterator<iterator>(end());
        }

        /**
         * Returns a const iterator pointing to the last element in this container. Incrementing it
         * results in pointing to the previous object.
         *
         * @return A const reverse iterator pointing to the last object.
         */
        const_reverse_iterator rbegin() const {
            return ft::reverse_iterator<const_iterator>(end());
        }

        /**
         * Returns an iterator pointing before the first object.
         *
         * @return A reverse iterator pointing before the beginning.
         */
        reverse_iterator rend() {
            return ft::reverse_iterator<iterator>(begin());
        }

        /**
         * Returns a const iterator pointing before the first object.
         *
         * @return A const reverse iterator pointing before the beginning.
         */
        const_reverse_iterator rend() const {
            return ft::reverse_iterator<const_iterator>(begin());
        }

        /**
         * Returns whether this vector is empty.
         *
         * @return True, if this vector is empty, false otherwise.
         */
        bool empty() const {
            return size() == 0;
        }

        /**
         * Returns the count of elements currently being held by this instance.
         *
         * @return Returns the number of objects currently being held.
         */
        size_type size() const {
            return object_count;
        }

        /**
         * Returns the maximum count of objects this vector can hold.
         *
         * @return The maximum number of holdable objects.
         */
        size_type max_size() const {
            return alloc.max_size() > static_cast<typename Allocator::size_type>(std::numeric_limits<difference_type>::max()) ?
                std::numeric_limits<difference_type>::max() : alloc.max_size();
        }

        /**
         * Allocates at least as much memory as needed to store the given count of objects. If it
         * already consists of enough memory, nothing happens.
         *
         * @param new_cap The count of objects this vector should be capable to hold.
         */
        void reserve(size_type new_cap) {
            if (new_cap > max_size()) throw std::length_error("ft::vector<T>::reserve: Too much elements to be reserved!");
            if (new_cap > capacity()) {
                pointer tmp = alloc.allocate(new_cap);
                for (const_iterator it = begin(); it != end(); ++it) {
                    alloc.construct(tmp + (it - begin()), *it);
                    alloc.destroy(start + (it - begin()));
                }
                if (start != NULL) // Since when is it wrong to free NULL???
                    alloc.deallocate(start, memory_capacity);
                memory_capacity = new_cap;
                start = tmp;
            }
        }

        /**
         * Returns the number of objects this vector can hold.
         *
         * @return The number of objects that can be hold.
         */
        size_type capacity() const {
            return memory_capacity;
        }

        /**
         * Removes all objects from this vector. The allocated memory stays allocated.
         */
        void clear() {
            while (size() > 0) {
                pop_back();
            }
        }

        /**
         * Inserts a copy of the given object at the position pointed to by the given iterator.
         * Returns an iterator to the inserted object.
         *
         * @param pos The position where to insert the object.
         * @param value The object to be inserted.
         * @return An iterator pointing to the inserted object.
         */
        iterator insert(iterator pos, const T & value) {
            return coreInsert(pos, 1, value);
        }

        /**
         * Inserts the given amount of copies of the given object at the position pointed to by the
         * given iterator.
         *
         * @param pos The position where to insert the objects.
         * @param count The number of objects to insert.
         * @param value The object to be copied.
         */
        void insert(iterator pos, size_type count, const T & value) {
            (void) coreInsert(pos, count, value);
        }

        /**
         * Inserts a copy of the given range at the given position.
         *
         * @tparam InputIt The type of the iterators defining the range.
         * @param pos The position where to insert the objects.
         * @param first The beginning of the range.
         * @param last The end of the range.
         */
        template <class InputIt>
        void insert(iterator pos, InputIt first, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
            long p = pos - begin();
            size_type count = ft::distance(first, last);
            if (capacity() < size() + count) {
                reserve(capacity() * 2 < size() + count ? size() + count : capacity() * 2);
            }
            iterator src = end() - 1;
            iterator dst = end() + count - 1;
            for (; src >= begin() + p; --src, --dst) {
                if (dst < end()) {
                    alloc.destroy(dst);
                }
                alloc.construct(dst, *src);
            }
            ++src;
            for (; src <= dst; ++src) {
                if (src < end()) {
                    alloc.destroy(src);
                }
                alloc.construct(src, *(first++));
            }
            object_count += count;
        }

        /**
         * Erases the object pointed to by the given iterator. Returns an iterator to the next object.
         *
         * @param pos The position where to erase the object.
         * @return An iterator to the next object.
         */
        iterator erase(iterator pos) {
            for (iterator it = pos; it != end(); ++it) {
                alloc.destroy(it);
                if (it + 1 != end()) {
                    alloc.construct(it, *(it + 1));
                }
            }
            --object_count;
            return pos;
        }

        /**
         * Erases the objects defined by the given range. Returns an iterator to the next object after
         * the range.
         *
         * @param first The beginning of the range.
         * @param last The end of the range.
         * @return An iterator to the next object after the range.
         */
        iterator erase(iterator first, iterator last) {
            size_type dist = last - first;
            size_type e = end() - last;
            for (; first != end(); ++first, ++last) {
                alloc.destroy(first);
                if (last < end()) {
                    alloc.construct(first, *last);
                }
            }
            object_count -= dist;
            return end() - e;
        }

        /**
         * Appends a copy of the given object to the end of this vector.
         *
         * @param value The object to append.
         */
        void push_back(const T & value) {
            if (size() + 1 > capacity()) {
                reserve((size() > 0 ? size() : 1) * 2);
            }
            alloc.construct(start + object_count, value);
            ++object_count;
        }

        /**
         * Removes the last object hold by this vector.
         */
        void pop_back() {
            --object_count;
            alloc.destroy(start + object_count);
        }

        /**
         * Resizes this vector to hold count amount of objects. If the given count is smaller
         * than the current size, the elements that are to much are removed from the end. Otherwise,
         * if the given count is bigger than the current size, new elements with the given value are
         * appended.
         *
         * @param count The new count of elements.
         * @param value The value of the appended objects.
         */
        void resize(size_type count, T value = T()) {
            if (count < size()) {
                while (size() > count) {
                    pop_back();
                }
            } else if (count > size()) {
                insert(end(), count - size(), value);
            }
        }

        /**
         * Exchanges the contents of this vector with the contents of the given other vector.
         *
         * @param other Exchanges the contents of the given vector with this instance.
         */
        void swap(vector & other) {
            pointer tmp = start;
            size_type tmpMC = memory_capacity;
            size_type tmpOC = object_count;
            start = other.data();
            memory_capacity = other.capacity();
            object_count = other.size();
            other.start = tmp;
            other.object_count = tmpOC;
            other.memory_capacity = tmpMC;
        }

    private:
        /**
         * The allocator to be used for all memory related operations.
         */
        Allocator alloc;

        /**
         * The pointer to the beginning of the memory used by this vector.
         */
        pointer start;

        /**
         * The number of objects that can be stored inside of the allocated memory.
         */
        size_type memory_capacity;

        /**
         * The count of objects currently held by this vector.
         */
        size_type object_count;

        /**
         * Inserts the given count amount of copies of the given object into this vector.
         *
         * @param pos The position where to insert the elements.
         * @param count The amount of objects that should be inserted.
         * @param value The value that should be copied.
         * @return The iterator to the beginning of the inserted range.
         */
        iterator coreInsert(iterator pos, size_type count, const T & value) {
            long p = pos - begin();
            if (capacity() < size() + count) {
                reserve(capacity() * 2 < size() + count ? size() + count : capacity() * 2);
            }
            iterator src = end() - 1;
            iterator dst = end() + count - 1;
            for (; src >= begin() + p; --src, --dst) {
                if (dst < end()) {
                    alloc.destroy(dst);
                }
                alloc.construct(dst, *src);
            }
            ++src;
            for (; src <= dst; ++src) {
                if (src < end()) {
                    alloc.destroy(src);
                }
                alloc.construct(src, value);
            }
            object_count += count;
            return src - count;
        }
    };

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
        if (lhs.size() != rhs.size()) return false;
        for (typename vector<T, Alloc>::const_iterator lit = lhs.begin(),
                                                       rit = rhs.begin();
             lit != lhs.end();
             ++lit, ++rit) {
            if (*lit != *rit) {
                return false;
            }
        }
        return true;
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
        // FIXME: Use ft version!
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
        return lhs < rhs || lhs == rhs;
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
        return rhs < lhs || lhs == rhs;
    }

    template <class T, class Alloc>
    void swap(vector<T, Alloc> & lhs, vector<T, Alloc> & rhs) {
        lhs.swap(rhs);
    }
}

#endif //FT_CONTAINERS_VECTOR_HPP
