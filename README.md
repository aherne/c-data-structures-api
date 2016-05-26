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
	- HashSet: implements a set of hash table type (same as std::unordered_set @ C++11)
	- LinkedHashSet: implements a set of hash table type ordered via a doubly linked list (no STL equivalent, elements can be iterated by insertion order)
	- TreeSet: implements a set or red-black-tree type (wrapper over std::set)

Operations complexity @ list:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>ArrayList</td>
			<td>LinkedList</td>
			<td>DoublyLinkedList</td>
		</tr>
	</thead>
</table>

Operation								|	ArrayList	|	LinkedList	|	DoublyLinkedList
Insertion on top						O(N*2)			O(1)		O(1)
Insertion on random position			O(K+(N-K)*2)	O(K)		O(K)/O(N-K)
Insertion on bottom						O(1)			O(1)		O(1)
Retrieval of top element				O(1)			O(1)		O(1)
Retrieval of random position element	O(1)			O(K)		O(K)/O(N-K)
Retrieval of next position element		O(1)			O(1)		O(1)
Retrieval of previous position element	O(1)			O(K)		O(1)
Retrieval of bottom element				O(1)			O(N)		O(1)
Removal of top element					O(N)			O(1)		O(1)
Removal of random position element		O(K+(N-K)*2)	O(K)		O(K)/O(N-K)
Removal of next position element		O(K+(N-K)*2)	O(1)		O(1)
Removal of previous position element	O(K+(N-K)*2)	O(K)		O(1)
Removal of bottom element				O(1)			O(N)		O(1)