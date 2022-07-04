//
// Created by Manuel Hahn on 7/4/22.
//

#ifndef FT_CONTAINERS_UTILITY_H
#define FT_CONTAINERS_UTILITY_H

namespace ft {

    template<class T1,
            class T2>
    struct pair {
        T1 first;
        T2 second;

        pair() : first(), second() {}

        pair(const T1 &x, const T2 &y) : first(x), second(y) {}

        template<class U1,
                class U2>
        pair(const pair<U1, U2> &p): first(p.first), second(p.second) {}


    };

    template<class T1,
            class T2>
    pair<T1, T2> make_pair(T1 t, T2 u) {
        return pair<T1, T2>(t, u);
    }
}

#endif //FT_CONTAINERS_UTILITY_H
