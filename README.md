# c-data-structures-api

My own implementation of data structures in C++, much simpler than that used by STL, with equal or greater performance. In my tradition, it's strictly organized, structured in a way somewhat similar to Java Collections API:

- List: "interface" implementing signatures of operations common to all kinds of list data structures
	- ArrayList: implements a list of dynamic array type (same as std::vector)
	- LinkedList: implements a list of singly linked type (same as std::forward_list @ C++11, but keeping a pointer to tail, making insertions on bottom as fast as on top) 
	- DoublyLinkedList: implements a list of doubly linked type (same as std::list)
- Map: "interface" implementing signatures of operations common to all kinds of map data structures
	- HashMap: implements a map of hash table type (same as std::unordered_map @ C++11)
	- LinkedHashMap: implements a map of hash table type ordered via a doubly linked list (no STL equivalent, elements can be iterated by insertion order)
	- TreeMap: implements a map or red-black-tree type (wrapper over std::map)
- Set: "interface" implementing signatures of operations common to all kinds of set data structures
	- HashMap: implements a set of hash table type (same as std::unordered_set @ C++11)
	- LinkedHashMap: implements a set of hash table type ordered via a doubly linked list (no STL equivalent, elements can be iterated by insertion order)
	- TreeMap: implements a set or red-black-tree type (wrapper over std::set)