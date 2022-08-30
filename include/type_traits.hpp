//
// Created by Manuel Hahn on 8/30/22.
//

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

namespace ft {
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<class T, T v>
    struct integral_constant {
        static T value = v;

        typedef T                       value_type;
        typedef integral_constant<T, v> type;

        operator value_type() {
            return value;
        }
    };

    typedef ft::integral_constant<bool, true> true_type;
    typedef ft::integral_constant<bool, false> false_type;
}

#endif //FT_CONTAINERS_TYPE_TRAITS_HPP