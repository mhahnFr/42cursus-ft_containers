//
// Created by Manuel Hahn on 7/4/22.
//

#ifndef FT_CONTAINERS_STACK_H
#define FT_CONTAINERS_STACK_H

#include "vector.h"

namespace ft {
    template <class T, class Container = ft::vector<T> >
    class stack {
    public:
        typedef Container                           container_type;
        typedef typename Container::value_type      value_type;
        typedef typename Container::size_type       size_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;

        explicit stack(const Container & cont = Container()): c(cont) {}
        stack(const stack & other): c(other.c) {}
        ~stack() {}

        reference top() {
            return c.back();
        }

        const_reference top() const {
            return c.back();
        }

        bool empty() const {
            return c.empty();
        }

        size_type size() const {
            return c.size();
        }

        void push(const value_type & value) {
            c.push_back(value);
        }

        void pop() {
            c.pop_back();
        }

    protected:
        Container c;
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
        return lhs.c == rhs.c;
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
        return lhs.c != rhs.c;
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
        return lhs.c <= rhs.c;
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
        return lhs.c < rhs.c;
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
        return lhs.c >= rhs.c;
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs) {
        return lhs.c > rhs.c;
    }
}

#endif //FT_CONTAINERS_STACK_H
