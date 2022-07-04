//
// Created by Manuel Hahn on 7/4/22.
//

#ifndef FT_CONTAINERS_UTILITY_H
#define FT_CONTAINERS_UTILITY_H

template <class T1,
          class T2>
struct pair {
    T1 first;
    T2 second;

    pair(): first(), second() {}
    pair(const T1 & x, const T2 & y): first(x), second(y) {}

    template <class U1,
              class U2>
    pair(const pair<U1, U2> & p): first(p.first), second(p.second) {}
};

#endif //FT_CONTAINERS_UTILITY_H
