//
// Created by Manuel Hahn on 7/5/22.
//

#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

#include <memory>

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
        typedef T                                     value_type;
        typedef Allocator                             allocator_type;
        typedef std::size_t                           size_type;
        typedef std::ptrdiff_t                        difference_type;
        typedef value_type &                          reference;
        typedef const value_type &                    const_reference;
        typedef typename Allocator::pointer           pointer;
        typedef typename Allocator::const_pointer     const_pointer;
        typedef T *                                   iterator;
        typedef T *                                   const_iterator;
        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        /**
         * Constructs an empty vector.
         */
        vector()
            : alloc(Allocator()), start(NULL), memory_capacity(), object_count() {}

        /**
         * Constructs an empty vector, which will use the given allocator.
         *
         * @param alloc The allocator to be used by this instance.
         */
        explicit vector(const Allocator & alloc)
            : alloc(alloc), start(NULL), memory_capacity(), object_count() {}

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
            start = alloc.allocate(count);
            for (pointer i = start; ((size_type) (i - start)) < count; ++i) {
                alloc.construct(i, value);
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
        vector(InputIt first, InputIt last, const Allocator & alloc = Allocator())
            : alloc(alloc), memory_capacity(std::distance(first, last)), object_count(std::distance(first, last)) {
            start = alloc.allocate(object_count);
            for (pointer i = start; first != last; ++i, ++first) {
                alloc.construct(i, *first);
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
            return *(start + size());
        }

        /**
         * Returns a const reference to the last object in this container.
         *
         * @return A const reference to the last object.
         */
        const_reference back() const {
            return *(start + size());
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
            return start + object_count + sizeof(T);
        }

        /**
         * Returns a const iterator pointing behind the last object in this container.
         *
         * @return A const iterator pointing to the end.
         */
        const_iterator end() const {
            return start + object_count + sizeof(T);
        }

        /**
         * Returns an iterator pointing to the last element in this container. Incrementing it
         * results in pointing to the previous object.
         *
         * @return A reverse iterator pointing to the last object.
         */
        reverse_iterator rbegin();

        /**
         * Returns a const iterator pointing to the last element in this container. Incrementing it
         * results in pointing to the previous object.
         *
         * @return A const reverse iterator pointing to the last object.
         */
        const_reverse_iterator rbegin() const;

        /**
         * Returns an iterator pointing before the first object.
         *
         * @return A reverse iterator pointing before the beginning.
         */
        reverse_iterator rend();

        /**
         * Returns a const iterator pointing before the first object.
         *
         * @return A const reverse iterator pointing before the beginning.
         */
        const_reverse_iterator rend() const;

        /**
         * Returns wether this vector is empty.
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
        size_type max_size() const;

        /**
         * Allocates at least as much memory as needed to store the given count of objects. If it
         * already consists of enough memory, nothing happens.
         *
         * @param new_cap The count of objects this vector should be capable to hold.
         */
        void reserve(size_type new_cap);

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
        iterator insert(iterator pos, const T & value);

        /**
         * Inserts the given amount of copies of the given object at the position pointed to by the
         * given iterator.
         *
         * @param pos The position where to insert the objects.
         * @param count The number of objects to insert.
         * @param value The object to be copied.
         */
        void insert(iterator pos, size_type count, const T & value);

        /**
         * Inserts a copy of the given range at the given position.
         *
         * @tparam InputIt The type of the iterators defining the range.
         * @param pos The position where to insert the objects.
         * @param first The beginning of the range.
         * @param last The end of the range.
         */
        template <class InputIt>
        void insert(iterator pos, InputIt first, InputIt last);

        /**
         * Erases the object pointed to by the given iterator. Returns an iterator to the next object.
         *
         * @param pos The position where to erase the object.
         * @return An iterator to the next object.
         */
        iterator erase(iterator pos);

        /**
         * Erases the objects defined by the given range. Returns an iterator to the next object after
         * the range.
         *
         * @param first The beginning of the range.
         * @param last The end of the range.
         * @return An iterator to the next object after the range.
         */
        iterator erase(iterator first, iterator last);

        /**
         * Appends a copy of the given object to the end of this vector.
         *
         * @param value The object to append.
         */
        void push_back(const T & value);

        /**
         * Removes the last object hold by this vector.
         */
        void pop_back() {
            alloc.destruct(start + object_count);
            --object_count;
        }

        void resize(size_type count, T value = T());

        /**
         * Exchanges the contents of this vector with the contents of the given other vector.
         *
         * @param other Exchanges the contents of the given vector with this instance.
         */
        void swap(vector & other);

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
    };

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);

    template <class T, class Alloc>
    void swap(vector<T, Alloc> & lhs, vector<T, Alloc> & rhs) {
        lhs.swap(rhs);
    }
}

#endif //FT_CONTAINERS_VECTOR_H
