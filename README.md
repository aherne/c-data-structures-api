# c-data-structures-api

Building another STL instead of using the fast super-stable time-tested library that is already used by virtually all C++ programmers seems like a textbook example of "reinventing the wheel", which happens to be a most damning stigma in today's world of programming. CDS is my own implementation of data structures and algorithms in C++ built on a harmonical structure different from STL in being much lighter weight, structured on polymorphism (because if naturally fits the concepts of data structures), larger in scope (supporting trees and graphs also) and with equal or greater performance. The API itself (let's call it CDS from now on) is nothing more than a collection of decoupled independent components and their dependencies. Each component corresponds to a data structure designed polymorphically by an interface-implementation principle. Following data structures are supported:

- sequences (dynamic arrays, linked lists, doubly linked lists, stacks, queues)
- maps (backed by hash table, backed by hash table and linked list to stay ordered, backed by red black tree)
- sets (same as above)
- trees (free structured aka k-ary or binary in red black tree shape)
- graphs (directed or undirected, weighted or unweighted, backed by hash table for fast search or dynamic arrays for fast inserts)

For more info, check dedicated site:

www.data-types.com
