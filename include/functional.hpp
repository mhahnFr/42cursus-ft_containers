#ifndef FT_CONTAINERS_FUNCTIONAL_HPP
#define FT_CONTAINERS_FUNCTIONAL_HPP

namespace ft {
    template <class Arg1, class Arg2, class Result>
    struct binary_function {
        typedef Arg1   first_argument_type;
        typedef Arg2   second_argument_type;
        typedef Result result_type;
    };

    template<class T>
    struct less: public binary_function<T, T, bool> {
        typedef bool result_type;
        typedef T    first_argument_type;
        typedef T    second_argument_type;

        bool operator()(const T & lhs, const T & rhs) const {
            return lhs < rhs;
        }
    };
}

#endif //FT_CONTAINERS_FUNCTIONAL_HPP
