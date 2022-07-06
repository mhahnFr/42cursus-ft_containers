//
// Created by Manuel Hahn on 7/5/22.
//

#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

#include <memory>

namespace ft {
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
        typedef void                                  iterator;
        typedef void                                  const_iterator;
        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        vector();
        explicit vector(const Allocator & alloc);
        explicit vector(size_type count, const T & value = T(), const Allocator & alloc = Allocator());

        template <class InputIt>
        vector(InputIt first, InputIt last, const Allocator & alloc = Allocator());

        vector(const vector & other);

        ~vector();

        vector & operator=(const vector & other);

        void assign(size_type count, const T & value);

        template <class InputIt>
        void assign(InputIt first, InputIt last);

        allocator_type get_allocator() const {
            return alloc;
        }

        reference at(size_type pos);
        const_reference at(size_type pos) const;

        reference operator[](size_type pos);
        const_reference operator[](size_type pos) const;

        reference front();
        const_reference front() const;

        reference back();
        const_reference back() const;

        T * data();
        const T * data() const;

        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;

        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;

        reverse_iterator rend();
        const_reverse_iterator rend() const;

        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        void reserve(size_type new_cap);

        size_type capacity() const;

        void clear();

        iterator insert(iterator pos, const T & value);
        void insert(iterator pos, size_type count, const T & value);

        template <class InputIt>
        void insert(iterator pos, InputIt first, InputIt last);

        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);

        void push_back(const T & value);

        void pop_back();

        void resize(size_type count, T value = T());

        void swap(vector & other);

    private:
        Allocator alloc;
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
