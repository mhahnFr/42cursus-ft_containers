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
    };
}

#endif //FT_CONTAINERS_VECTOR_H
