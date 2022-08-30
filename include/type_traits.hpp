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
        const static T value = v;

        typedef T                       value_type;
        typedef integral_constant<T, v> type;

        operator const value_type() const {
            return value;
        }
    };

    typedef ft::integral_constant<bool, true> true_type;
    typedef ft::integral_constant<bool, false> false_type;

    template<class T>
    struct is_integral: public integral_constant<bool, false> {};

    template<>
    struct is_integral<bool>: public integral_constant<bool, true> {};

    template<>
    struct is_integral<char>: public integral_constant<bool, true> {};

    template<>
    struct is_integral<wchar_t>: public integral_constant<bool, true> {};

    template<>
    struct is_integral<short>: public integral_constant<bool, true> {};

    template<>
    struct is_integral<int>: public integral_constant<bool, true> {};

    template<>
    struct is_integral<long>: public integral_constant<bool, true> {};
}

#endif //FT_CONTAINERS_TYPE_TRAITS_HPP
