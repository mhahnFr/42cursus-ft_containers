//
// Created by Manuel Hahn on 7/4/22.
//

#ifndef FT_CONTAINERS_UTILITY_H
#define FT_CONTAINERS_UTILITY_H

namespace ft {

    /**
     * A struct to combine two objects of any type.
     *
     * @tparam T1 The type of the first element
     * @tparam T2 The type of the second element
     * @since 04.07.22
     */
    template <class T1, class T2>
    struct pair {
        /** The first object. */
        T1 first;
        /** The second object. */
        T2 second;

        /**
         * Creates a pair. The two bound objects are initialized using their default constructor.
         */
        pair() : first(), second() {}

        /**
         * Creates a pair. The two bound objects are initialized using the given values.
         *
         * @param x The object to initialize the first object with.
         * @param y The object to initialize the second object with.
         */
        pair(const T1 & x, const T2 & y) : first(x), second(y) {}

        /**
         * Copies the given pair.
         *
         * @tparam U1 The type of the first parameter to copy
         * @tparam U2 The type of the second parameter to copy
         * @param p The pair which should be copied.
         */
        template <class U1, class U2>
        pair(const pair<U1, U2> & p): first(p.first), second(p.second) {}
    };

    /**
     * Constructs a pair using the given objects.
     *
     * @tparam T1 The type of the first object.
     * @tparam T2 The type of the second object.
     * @param t The first object.
     * @param u The second object.
     * @return A newly created pair with the given objects.
     */
    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 t, T2 u) {
        return pair<T1, T2>(t, u);
    }

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs) {
        return lhs.first == rhs.first && lhs.second = rhs.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs) {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs) {
        return lhs.first < rhs.first || lhs.second < rhs.second;
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs) {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs) {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs) {
        return !(lhs < rhs);
    }
}

#endif //FT_CONTAINERS_UTILITY_H
