//
//  main9.cpp
//  ft_c
//
//  Created by Manuel Hahn on 01.10.22.
//  Copyright © 2022 mhahnFr. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "map.hpp"

#define PRINT_ALL(m) \
std::cout << __FILE__ << ":" << __LINE__ << std::endl;\
std::cout << (m).size() << std::endl;\
for (intmap::const_iterator it = (m).begin(); it != (m).end(); ++it) { \
    std::cout << "K: " << it->first << ", V: " << it->second << std::endl; \
} \
std::cout << std::endl;

typedef ft::map<int, std::string> intmap;

std::vector<ft::pair<int, std::string> > bla(std::size_t size) {
    std::string x[64] = { "CBCId4lUU6oYms60JkNr", "V5sbXjlqYRAV1C1LgJbt", "TPcK94z2htaoK5hWpR1j",
                          "WA1JMsjadjyjQjJLxVkE", "aDhJUsH7AVnKLfzQGcPC", "DPpRIm6G9C5CWSWYLwnt",
                          "aKyxvwuxzUAksmm7s8o3", "d8NpBFRFI87WxlYiRzJB", "5RDlRrY8OFBkqtlD5R33",
                          "W4dsiGdNWranxT1qbPt9", "uUxBDNzk3Tpg1bIow0uf", "FiKAXgTFhhPhmRkfXci9",
                          "02Fxrj1KnMufOpH1gbxw", "hSV7LrNPzTKHS6h7BRW6", "YzIjmI4i4Fum1gzs9QFy",
                          "6jjGwGu20C7dXFRgdCU8", "bej1zTuyCJGa0b4KXgQO", "ckkK36lt3kBVH1PYvbib",
                          "Gs9kLamEeSWqM9ORSlzF", "oJTGXtRpq4rz6IBt2Gc2", "6XSQM096yPnzWqydO7Fl",
                          "Kw91n77jigS09IQEYFw0", "K0Qj3EOV96U6xbBDMkaP", "i0b4NYygRb7ZuT3HOE61",
                          "C6KyCaoRm5MncGCjjP0I", "6xxl5c88m0Rq5CkTPsTU", "xtZ16NJzNU4IEnzsily8",
                          "2ofwuG2e80JGsK8VdB6r", "UjhRe94EahPlXuBbIV0q", "be5WTfjjKVBU8cezAjH8",
                          "zOWJPAQLV4wgVGJTC0uV", "nuqgXoNhZpL8uMvbDcT7", "HdCk0Gm8Gn3eqcVYxcYD",
                          "PuIS5xPbBpGe3MHG7SNm", "ZY6finqJMbHpB6dKlenn", "VJfBTOFj9reLm3iGU2Fs",
                          "UFWOX8UzTSzSAGMvGRIC", "cZfcw5yVwFprkH2v3FQO", "V34DSjjaiDianUKjRFCj",
                          "j7SHtomH6GvAY8y0nL9E", "3z82NvciqTwWW2Lp7MET", "S1BDCdeUHLIVB6I8zaIc",
                          "OkuQPNHq0AnYY9Pemxpn", "yH5J2tI4oQzVsPBB226z", "aafwp6lvuOxv5JkUBUlA",
                          "RjRwqlQ0hnxYnglid2x3", "3RBzhOIHFtRtZBHNlCVv", "lttYCjRWSXYKeyIgvpJv",
                          "6KhIc7LvaTTwklmmbjBO", "IDlAqFCEdFTJcVW36RsY", "pDGkqtvKVRReq19BFVwN",
                          "88UJAeNtrlAwEu4BGiSb", "eFN5bxsWa4dAnvZdzToE", "B3cqY0IqO2IH2yGMnX7e",
                          "BRcU6oFTAC8IWuiSrTEa", "dtBZVLQMx9MBw1eak8SB", "zM2XVrazn2fXAsRHDc16",
                          "qqlM2sERpGhcZJAv3qPR", "4Lru0dOIQpWGYlcx9oyn", "HSH0O0igQruyLC1FmQVs",
                          "mXHcnXiXhKJwJ0BUSpje", "sXhbSe7MQHhvJ9XQcrrX", "aTejup4iQw70n78erKEB",
                          "1IRLC9sfQI5AzDYeotLd" };

#define NAMESPACE ft
    std::vector<ft::pair<int, std::string> > ret(size);
    for (std::size_t i = 0; i < size; ++i) {
        ret[i] = NAMESPACE::make_pair(rand(), x[i]);
    }
    return ret;
}


int main() {
    std::vector<ft::pair<int, std::string> > intstr_arr = bla(64);
    intmap m(intstr_arr.begin(), intstr_arr.begin() + 25);

    intmap::iterator it = m.begin();

    m.erase(it);
    std::cout << "Erasing: " << it->first << std::endl;

    PRINT_ALL(m); // 24

    it = m.begin();

    std::advance(it, 21);

    m.erase(it);
    std::cout << "Erasing: " << it->first << std::endl;

    PRINT_ALL(m); // 23

    it = m.end();

    std::advance(it, -10);

    m.erase(it);
    std::cout << "Erasing: " << it->first << std::endl;

    PRINT_ALL(m); // 22

    it = m.end();

    std::advance(it, -3);

    m.erase(it);
    std::cout << "Erasing: " << it->first << std::endl;

    PRINT_ALL(m); // 21

    it = m.end();

    std::advance(it, -1);

    m.erase(it);
    std::cout << "Erasing: " << it->first << std::endl;

    PRINT_ALL(m); // 20

    it = m.begin();

    std::advance(it, 1);

    m.erase(it);
    std::cout << "Erasing: " << it->first << std::endl;

    PRINT_ALL(m); // 19

    for (it = m.begin(); it != m.end(); it = m.begin()) {
        m.erase(it);
        std::cout << "Erasing: " << it->first << std::endl;
        PRINT_ALL(m);
    }

}
