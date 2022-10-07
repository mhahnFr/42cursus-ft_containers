//
// Created by Manuel Hahn on 10/5/22.
//

#ifndef NS
#define NS ft
#endif

#ifndef SEED
#define SEED 1
#endif

#include <map>
#include "map.hpp"

#include <vector>
#include "vector.hpp"

#include <stack>
#include "stack.hpp"

#include <set>
#include "set.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#define ARRAY_SIZE 32000

/**
 * An array with some strings.
 */
static std::string stringArray[ARRAY_SIZE];

/**
 * An array with some integer values.
 */
static int intArray[ARRAY_SIZE];

/**
 * An array with some paired values.
 */
static NS::pair<int, std::string> pairs[ARRAY_SIZE];

/**
 * Fills the string array.
 */
static inline void fillStringArray() {
    for (unsigned long i = 0; i < ARRAY_SIZE; ++i) {
        std::stringstream s;
        s << "SomeRandomString ABCDEFGHIJKLMNOPQRSTUVWXYZ n: " << i;
        stringArray[i] = s.str();
    }
}

/**
 * Fills the integer array.
 */
static inline void fillIntArray() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        intArray[i] = i;
    }
}

/**
 * Initializes the pair array.
 */
static inline void makePairs() {
    for (unsigned long i = 0; i < ARRAY_SIZE; ++i) {
        pairs[i] = NS::make_pair(i, stringArray[random() % ARRAY_SIZE]);
    }
}

/**
 * @brief Prints the relevant information about the given map.
 *
 * Prints the size of the container and its content.
 *
 * @tparam Map The type of the map, should be a ft or a STL map. Cannot be any other container.
 * @param m The actual map whose infos should be printed.
 */
template<typename Map>
static inline void printInfoMap(const Map & m) {
    std::cout << "Map stats:"         << std::endl
              << "Size: " << m.size() << std::endl
              << "Content:"           << std::endl;
    for (typename Map::const_iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << NS::distance(m.begin(), it) << ": Key: '"    << it->first
                                                 << "', Value: '" << it->second
                                                 << "'" << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief Prints the relevant information about the given container.
 *
 * Prints the size of the container and its content.
 *
 * @tparam Container The type of the container, should be a ft or a STL container, cannot be a map.
 * @param c The actual container whose infos should be printed.
 */
template<typename Container>
static inline void printInfo(const Container & c) {
    std::cout << "Container stats:"   << std::endl
              << "Size: " << c.size() << std::endl
              << "Content:"           << std::endl;
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it) {
        std::cout << NS::distance(c.begin(), it) << ": '" << *it << "'" << std::endl;
    }
    std::cout << std::endl;
}

/**
 * Calls all functions needed for the setup.
 */
static inline void setup() {
    srandom(SEED);
    fillIntArray();
    fillStringArray();
    makePairs();
    std::cout << std::boolalpha;
}

static inline void testVector() {
    NS::vector<std::string> vec;
    std::cout << "Vector assign" << std::endl;
    vec = NS::vector<std::string>(stringArray, stringArray + ARRAY_SIZE);
    printInfo(vec);

    std::cout << "Vector insert" << std::endl;
    vec.insert(vec.begin(), stringArray + 1, stringArray + ARRAY_SIZE - 1);
    printInfo(vec);

    std::cout << "Vector clear" << std::endl;
    vec.clear();
    std::cout << "Empty: " << vec.empty() << std::endl
              << "begin() == end(): " << (vec.begin() == vec.end()) << std::endl;
    printInfo(vec);

}

static inline void testMap() {
    NS::map<int, std::string> m;
    std::cout << "Map assign" << std::endl;
    m = NS::map<int, std::string>(pairs, pairs + ARRAY_SIZE);
    printInfoMap(m);

    std::cout << "Map subscript operator" << std::endl;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        const int pos = intArray[random() % ARRAY_SIZE];
        std::cout << "Map[" << pos << "]: '" << m[pos] << "'" << std::endl;
    }
    printInfoMap(m);

    std::cout << "Map erase" << std::endl;
    m.erase(++(++m.begin()), --(--m.end()));
    printInfoMap(m);
}

static inline void testStack() {
    NS::stack<std::string, NS::vector<std::string> > st;
    std::cout << "Stack push" << std::endl;
    for (unsigned long i = 0; i < ARRAY_SIZE; ++i) {
        st.push(stringArray[random() % ARRAY_SIZE]);
    }

    std::cout << "Stack size: " << st.size()                     << std::endl
              << "Stack top() and pop() while stack not empty()" << std::endl;
    while (!st.empty()) {
        std::cout << st.top() << std::endl;
        st.pop();
    }
    std::cout << std::endl;
}

static inline void testSet() {
    NS::set<int> s;
    std::cout << "Set assign" << std::endl;
    s = NS::set<int>(NS::reverse_iterator<const int *>(intArray + ARRAY_SIZE), NS::reverse_iterator<const int *>(intArray));
    printInfo(s);

    std::cout << "Set erase" << std::endl;
    s.erase(++(++s.begin()), --(--s.end()));
    printInfo(s);
}

int main() {
    setup();

    testVector();
    testStack();
    testMap();
    testSet();

    std::cout << "--- End of ft_containers test main ---" << std::endl;
}
