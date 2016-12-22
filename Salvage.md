Unlike data structures above, operations a tree performs are irreducible to a common ground. Each tree type chosen reflects a very different need, which results into fundamentally different operations:

- binary trees: trees that can have a maximum of two nodes. Optimal for searching nodes with O(log(N)) complexity if balanced, assuming those nodes hold unique comparable values; non-optimal for insertion speed and memory consumption
- n-ary trees:

There are endless variations of trees, but most common are:

- binary trees: trees where a node can have only max two children. These are almost always used for searching (thus requiring a comparator) and as such they need being balanced (thus requiring an algorithm to keep depths at their minimum). Probably the best solution for all above, used by both STL @ C++ and Collections API @ Java, is the "red black tree" (RBT).
- n-ary trees: threes where there are no restrictions on children size. They are used to store hierarchical data. They are fastest at insertion and with smallest memory imprint, but slowest when searching a node (which may take O(n) time compared to O(log(n)) of balanced binary trees).

CDS comes with its own RedBlackTree class, with algorithms from CormenIntroduction to Algorithms, 3rd Edition


One of the reasons why no programming language offers an official implementation for trees is that tree operations demand exposure of internal elements (nodes), which fails the RAII principle.

At their most basic, trees can be classified into:

- binary trees: trees that can have a maximum of two nodes. Optimal for searching nodes with O(log(N)) complexity if balanced, assuming those nodes hold unique comparable values, also able to remain sorted on new node insertion. The most commonly used balanced binary search tree is the red-black-tree.
- n-ary trees: trees that have no restrictions on number of nodes


####Binary trees####

Binary trees, once properly balanced, are able to produce structures that allow fast search/insertion/deletion of any node while remaining sorted, all with O(log(N)) complexity. The red-black-tree balancing algorithm proved itself good enough to become solution of choice by both C++ and Java standard libraries, employed as structural basis for their Maps and Sets that need to stay sorted. This library also employs a RedBlackTree class for a similar purpose, with algorithms based on Introduction to Algorithms 3rd Edition by Thomas Cormen, Charles Leiserson & Ronald Rivest.
