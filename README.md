# Welcome to 42cursus-ft_containers!
This repository contains a project of the [42 school].
This project is about reimplementing some standard containers of the C++ standard library.

## Overview
The containers implemented in this repository are:
- `vector`
- `map`
- `stack`
- `set` _(bonus part)_

Additionally, the following utilities have to be recoded:
- `reverse_iterator`
- `pair`
- `make_pair`
- `iterator_traits`
- `enable_if`
- `lexicographical_compare`

The general approach is quite simple: the reimplementation has to work exactly the same way as the real one.
However, one is free to choose the type of the tree for the `map`.

If one wants to implement the `set` as a bonus, the use of a [Red-Black-Tree] is mandatory.

## Approach
For the `vector`, `stack` and the utilities the approach is simple: just code them accordingly to the published
documentation of C++98.

As the "real" `map` and `set` are using a [Red-Black-Tree], the reimplementation also has to use a
[self-balancing binary-tree](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree).

My tree follows the requirements of the [Red-Black-Tree]. The most important rules of it:
- Inserted nodes are **red**.
- All paths through the tree must traverse the same amount of **black** nodes.
- There must never be two **red** nodes following consecutively in a path through the tree.

Accordingly, after an insertion or an erasing, the tree has to be rebalanced.

In order to be capable to iterate through the tree seamlessly, I added a beginning and an end sentinel.
They are treated as `NIL` nodes.

### Final notes

© Copyright 2022 [mhahnFr](https://www.github.com/mhahnFr)

[42 school]: https://www.42heilbronn.de/learncoderepeat
[Red-Black-Tree]: https://en.wikipedia.org/wiki/Red–black_tree
