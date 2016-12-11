# c-data-structures-api

##Introduction##

Building another STL instead of using the fast super-stable time-tested library that is already used by virtually all C++ programmers seems like a textbook example of "reinventing the wheel", which happens to be a most damning stigma in today's world of programming.

###What's Wrong with STL?###
There is nothing inherently wrong with STL! It's a very robust and heavily tested solution that proved itself to be a good companion to programmer needs, BUT there is nothing ultimate about it. It's just one IMPLEMENTATION of "data structure & algorithms" concepts, not perfect like everything else in life, with its own qualities and defects.

What I loved about STL:

- Its iterators. STL iterators are without doubt more advanced/complete than anything done on that topic at least in languages I know: Java or PHP. Clearly a LOT of effort has been put to make them as flexible as they are, with the unfortunate side effect of becoming fiendishly complicated to employ for a non-STL list.

What I failed to love about STL:

- It's disorderly. What I liked about Collections API in Java is the interface-implementation paradigm that suits data structures the best. In C++ as well, a list should be a concept (class with pure virtual methods), while a dynamic array / linked list / doubly linked list should be different implementations of same concept. Not only should programmer abstract the list implementation by using List* only (which is a no-cost operation), but he will be assured whatever functionality is defined by List will have an implementation for whatever list type he uses (eg: linked list). In STL, because data structures are not designed hierarchically, there is an absolute chaos in method names (who aren't very intuitive BTW) and functionality (which may or may not have been implemented) so one needs to constantly check documentation.
- It's coupled. It's extremely difficult to glue its components (be it iterators or dependency classes/structs) with non-STL components. It's clear that the very good programmers who have worked for it, even though they went overboard with decoupling to largest extent imaginable (which is why STL structures' implementations are so complex), the end result has been something so complicated that it becomes uninviting to understand (leaving the impression of overprogrammed code).     
- Performance of HashTable implementations (unordered_map, unordered_set @ C++11), inferior to others I've tested
- Design decisions (for example, stacks and queues expose too much functionality when theory requires them to only include two functionalities: push/pop(/peek), enqueue/dequeue)

What I missed in STL:

- LinkedHashTable (and its LinkedHashMap, LinkedHashSet implementations): this is a hashtable where entries are iterated by insertion order (by adding doubly-linked-list behavior to hash table nodes). Actually, in languages such as PHP or Python that's the only HashTable known. While coding in C++, I frequently missed this option, which actually adds less than 10% performance taxation.
- Trees & Graphs. For some reason there is no "official" implementation in any language I know of, even though they are both routinely needed and can be abstracted with not much of an effort.

Clearly STL did not fully fit what I wanted: something complete & beautiful, standing on natural unbreakable order and coded on principles of simplicity and elegance. Therefore, I decided to "reinvent the wheel"! The point is always to learn from each other's mistakes and try creating something better instead: if not fuelled by ignorance/arrogance "reinventing the wheel" becomes an invaluable vector of progress. 

###What is C++ Data Structures API (CDS)?###
CDS is my own implementation of data structures and algorithms in C++ addressing all requirements mentioned above, different from STL in being much lighter weight, structured on polymorphism (because if naturally fits the concepts of data structures) and with equal or greater performance.  

##How it works##

The API itself is nothing more than a collection of decoupled independent components and their dependencies. Each component corresponds to a data structure designed polymorphically by an interface-implementation principle. Each component has a polymorphic iterator attached that mirrors component structure. Shared behavior was delegated to dependency classes/functions for encapsulation and maximum reusal.

###Components###

Components fall into three categories:

- abstract: a pure-virtual class defining data structure operations (Eg: class Map implementing map data structure operations)
- applied: one or more classes implementing operations defined by above in their respective way (Eg: class HashMap extends Map and implements latter operations via a hash table).
- shared: shared dependencies of applied components

Unlike STL components, CDS components are polymorphic. This means, for example, we can use abstract List* to work with a list instead of its aplied ArrayList implementation: 

List<long>* list = new ArrayList<long>;

The advantage of this is hiding complexity: we can at any point decide to use a DoublyLinkedList instead and no other lines of code will need being changed. Another advantage is predictability of method names.

Supported abstract & applied components:
- List: defines signatures for list abstract data structure 
	- ArrayList: implements a list of dynamic array type (akin STL std::vector)
	- LinkedList: implements a list of singly linked type (akin STL std::forward_list @ C++11, but keeping a pointer to tail, making insertions on bottom as fast as on top) 
	- DoublyLinkedList: implements a list of doubly linked type (akin STL std::list)
- Map: defines signatures for map abstract data structure
	- HashMap: implements a map of HashTable type (akin std::unordered_map @ C++11)
	- LinkedHashMap: implements a map of LinkedHashTable type with entries iterated by insertion order (no STL equivalent)
	- TreeMap: implements a map of RedBlackTree type (akin std::map)
- Set: defines signatures for set abstract data structure
	- HashSet: implements a set of HashTable type (akin std::unordered_set @ C++11)
	- LinkedHashSet: implements a set of LinkedHashTable type with entries iterated by insertion order (no STL equivalent)
	- TreeSet: implements a set of RedBlackTree type (akin std::set)
- Container: defines signatures for container adaptors into which all read/write operations are performed only on head or tail
	- Stack: implements a LIFO container adaptor on top of a dynamic array (akin std::stack)
	- Queue: implements a FIFO container adaptor on top of a dynamic array (akin std::queue)
- Tree: no common signatures so far  (no STL equivalent)
	- Tree: A n-ary tree
	- UniqueTree: A n-ary tree also holding a HashTable, in order to guarantee unique values per node
- Graph: no common signatures so far  (no STL equivalent)
	- Graph: A non-weighted graph.
	- UniqueGraph: A non-weighted graph on top of a HashTable, in order to guarantee unique values per vertex
	- WeightedGraph: A weighted graph.
	- UniqueWeightedGraph: A weighted graph on top of a HashTable, in order to guarantee unique values per vertex
 
As one can see above, some components obviously share a structural base. For that reason, these shared components/classes were also added:

- HashTable: implements a hash table, to be used by maps, sets, trees or graphs that rely on it (akin std::hashTable)
- LinkedHashTable: implements a hash table where entries also behave like a doubly linked list for in-order iteration (no STL equivalent), to be used by maps & sets that rely on it
- RedBlackTree: implements a binary tree balanced on red-black principles, to be used by maps & sets that rely on it

Shared components are designed in such a way as to allow direct usage and not just be internal dependencies of applied structures. Design takes advantage of Strategy Design Pattern: applied structures will thus use instances of the structure they found upon instead of extending latter behavior. This means HashMap will use an instance of HashTable in order to implement Map operations instead of doubly extending Map and HashTable. The beauty of this can be appreciated when one realizes the decoupling achieved: HashMap, HashSet, UniqueTree are all oblivious of each other and only know of their HashTable service provider.

###Iterators###

Each component (abstract or applied) has a polymorphic iterator attached (Eg: class List has ListIterator attached, whereas class LinkedList has LinkedListIterator friend that extends ListIterator). CDS iterators are inspired by STL iterators, but they are much more simple in design and different in how they behave:

- CDS iterators only use forward iteration. This is a restricting move desiged to keep things simple. Nevertheless, it's easy to add backward iteration later on...
- CDS iterators invalidate automatically whenever items are added/subtracted from structure while iterating. This is a restricting move designed to GUARANTEE safety and no crashes, but at the same time produces a minor performance overhead. This is because on any loop, a check is made whether or not data structure size has changed.
- CDS iterators are polymorphic, with their structure mirroring that of components. This means, for example, a LinkedList can be iterated both by an abstract ListIterator* or by an applied LinkedListIterator:<br/>
for(auto it=list.begin(); *it!=list.end; ++*it)) { ... }<br/>
for(auto it=linkedList.begin(); it!=linkedList.end; ++it)) { ... }

###Dependencies###

Some components rely on dependencies in order to be viable:
- comparators: functions comparing two items of same type and returning an int (>0 if smaller, 0 if equal, 0> if greater), to be used in sorting and by all structures relying on RedBlackTree.
- hashers: functions compiling a hash code of an item based on type returning an unsigned int, to be used by all structures relying on (Linked)HashTable.

Unlike STL comparators & hashers, for simplicity reasons, CDS comparators & hashers are C-compliant static inline functions. One can decide not to use the default implementations provided for long & char*, in which case users must supply an additional comparator/hasher template/method argument, akin one sees in STL. 

####Comparators####

The library only comes with two comparators implemented: for long & char*. For any other data type you will have to write your own. Comparator signature is:
static inline int comparator(const TYPE&, const TYPE&)

####Hashers####

The library only comes with two comparators implemented: for long & char*. For any other data type you will have to write your own. Hasher signature is:
static inline std::size_t hash(const TYPE&)


##Reference guide##

By virtue of implementing a blueprint, all applied components have almost identical signature to their abstract parent. What changes is the way those methods are implemented and their guaranteed Ocomplexity.

###List###

Method signatures defined by List class:
<table style="font-size:12px;">
	<thead>
		<tr>
			<td>Method</td>
			<td>Arguments</td>
			<td>Returns</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>addToTop</td>
			<td>const VALUE_TYPE&</td>
			<td>void</td>
			<td>Add value on top of list.</td>
		</tr>
		<tr>
			<td>addToBottom</td>
			<td>const VALUE_TYPE&</td>
			<td>void</td>
			<td>Add value on bottom of list.</td>
		</tr>
		<tr>
			<td>clear</td>
			<td>&nbsp;</td>
			<td>void</td>
			<td>Clears list of all values.</td>
		</tr>
		<tr>
			<td>containsIndex</td>
			<td>const size_t&</td>
			<td>bool</td>
			<td>Checks if position exists in list.</td>
		</tr>
		<tr>
			<td>containsValue</td>
			<td nowrap>
				const VALUE_TYPE&,<br/>
				int (*comparator)(const VALUE_TYPE&, const VALUE_TYPE&)
			</td>
			<td>bool</td>
			<td>Checks if value exists in list.</td>
		</tr>
		<tr>
			<td>emplace</td>
			<td>const size_t&, const VALUE_TYPE&</td>
			<td>void</td>
			<td>Inserts value at position, padding existing element to the right.</td>
		</tr>
		<tr>
			<td>get</td>
			<td>const size_t&</td>
			<td>const VALUE_TYPE&</td>
			<td>Gets value by position.</td>
		</tr>
		<tr>
			<td>set</td>
			<td>const size_t&, VALUE</td>
			<td>void</td>
			<td>Sets value by position.</td>
		</tr>
		<tr>
			<td>removeIndex</td>
			<td>const size_t&</td>
			<td>void</td>
			<td>Removes element by position.</td>
		</tr>
		<tr>
			<td>removeValue</td>
			<td>const VALUE_TYPE&</td>
			<td>void</td>
			<td>Removes all elements that match value.</td>
		</tr>
		<tr>
			<td>isEmpty</td>
			<td>&nbsp;</td>
			<td>bool</td>
			<td>Checks if list is empty</td>
		</tr>
		<tr>
			<td>size</td>
			<td>&nbsp;</td>
			<td>const size_t&</td>
			<td>Gets list size</td>
		</tr>
	</tbody>
</table>


Operations complexity @ list:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>ArrayList</td>
			<td>LinkedList</td>
			<td>DoublyLinkedList</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>addToTop(V)</td>
			<td>O(N*2)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Add value on top of list.</td>
		</tr>
		<tr>
			<td>addToBottom(V)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Add value on bottom of list.</td>
		</tr>
		<tr>
			<td>clear()</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Clears list of all values.</td>
		</tr>
		<tr>
			<td>containsIndex(K)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Checks if position exists in list.</td>
		</tr>
		<tr>
			<td>containsValue(V)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Checks if value exists in list.</td>
		</tr>
		<tr>
			<td>emplace(K,V)</td>
			<td>O((N-K)*2)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
			<td>Inserts value at position, padding existing element to the right.</td>
		</tr>
		<tr>
			<td>get(K)</td>
			<td>O(1)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
			<td>Gets value by position.</td>
		</tr>
		<tr>
			<td>set(K,V)</td>
			<td>O(1)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
			<td>Sets value by position.</td>
		</tr>
		<tr>
			<td>removeIndex(K)</td>
			<td>O((N-K)*2)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
			<td>Removes element by position.</td>
		</tr>
		<tr>
			<td>removeValue(V)</td>
			<td>O(N*2)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Removes all elements that match value.</td>
		</tr>
		<tr>
			<td>isEmpty()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Checks if list is empty</td>
		</tr>
		<tr>
			<td>size()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Gets list size</td>
		</tr>
		<tr>
			<td>sort(C)</td>
			<td>O(N+log(N))</td>
			<td>O(N*2+log(N))</td>
			<td>O(N*2+log(N))</td>
			<td>Sorts list by comparator.</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				K = position in list<br/>
				N = number of elements in list<br/>
				V = value to be stored in list<br/>
				P = internal iterator position<br/>
				C = comparator
			</td>
		</tr>
	</tbody>
</table>

Operations complexity @ map:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>HashMap</td>
			<td>LinkedHashMap</td>
			<td>TreeMap</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>clear()</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Clears map of all values.</td>
		</tr>
		<tr>
			<td>containsKey(K)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
			<td>Checks if key exists in map.</td>
		</tr>
		<tr>
			<td>containsValue(V)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Checks if value exists in map.</td>
		</tr>
		<tr>
			<td>get(K)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
			<td>Gets value by key.</td>
		</tr>
		<tr>
			<td>set(K,V)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
			<td>Sets value by key.</td>
		</tr>
		<tr>
			<td>removeKey(K)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
			<td>Removes element by key.</td>
		</tr>
		<tr>
			<td>removeValue(V)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Removes all elements that match value.</td>
		</tr>
		<tr>
			<td>isEmpty()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Checks if map is empty</td>
		</tr>
		<tr>
			<td>size()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Gets map size</td>
		</tr>
		<tr>
			<td>getKeys()</td>
			<td>O(N*2)</td>
			<td>O(N*2)</td>
			<td>O(N*2)</td>
			<td>Gets map keys as std::vector.</td>
		</tr>
		<tr>
			<td>getValues()</td>
			<td>O(N*2)</td>
			<td>O(N*2)</td>
			<td>O(N*2)</td>
			<td>Gets map values as std::vector.</td>
		</tr>
		<tr>
			<td>sortByKey(C)</td>
			<td>-</td>
			<td>O(N*2+log(N))</td>
			<td>-</td>
			<td>Sorts map by keys and comparator.</td>
		</tr>
		<tr>
			<td>sortByValue(C)</td>
			<td>-</td>
			<td>O(N*2+log(N))</td>
			<td>-</td>
			<td>Sorts map by values and comparator.</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				K = position in list<br/>
				N = number of elements in list<br/>
				V = value to be stored in map<br/>
				C = comparator
			</td>
		</tr>
	</tbody>
</table>

Operations complexity @ set:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>HashSet</td>
			<td>LinkedHashSet</td>
			<td>TreeSet</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>clear()</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Clears set of all values.</td>
		</tr>
		<tr>
			<td>contains(V)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
			<td>Checks if value exists in set.</td>
		</tr>
		<tr>
			<td>remove(V)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
			<td>Removes element by value.</td>
		</tr>
		<tr>
			<td>isEmpty()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Checks if set is empty</td>
		</tr>
		<tr>
			<td>size()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Gets set size</td>
		</tr>
		<tr>
			<td>getValues()</td>
			<td>O(N*2)</td>
			<td>O(N*2)</td>
			<td>O(N*2)</td>
			<td>Gets set values as std::vector.</td>
		</tr>
		<tr>
			<td>sort(C)</td>
			<td>-</td>
			<td>O(N*2+log(N))</td>
			<td>-</td>
			<td>Sorts set by values.</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				N = number of elements in set<br/>
				V = value to be stored in set<br/>
				C = comparator
			</td>
		</tr>
	</tbody>
</table>

Operations complexity @ container:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>Stack</td>
			<td>Queue</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>clear()</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Clears container of all values.</td>
		</tr>
		<tr>
			<td>size()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Gets container size</td>
		</tr>
		<tr>
			<td>isEmpty()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Checks if container is empty</td>
		</tr>
		<tr>
			<td>push(V)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Pushes value to head @ stack or tail @ queue.</td>
		</tr>
		<tr>
			<td>peek()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Gets value in container head.</td>
		</tr>
		<tr>
			<td>pop()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Removes head element of container and returns its value.</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				N = number of elements in container
			</td>
		</tr>
	</tbody>
</table>

Operations complexity @ n-ary trees:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>Tree</td>
			<td>UniqueTree</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>createNode(V,T)</td>
			<td>O(1)</td>
			<td>O(2)</td>
			<td>Creates tree node and assigns it to parent.</td>
		</tr>
		<tr>
			<td>getHeight()</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>Gets tree height.</td>
		</tr>
		<tr>
			<td>getRoot()</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>Gets a reference to root node.</td>
		</tr>
		<tr>
			<td>getSize()</td>
			<td>O(N)</td>
			<td>O(1)</td>
			<td>Gets number of nodes in tree.</td>
		</tr>
		<tr>
			<td>removeBranch(T)</td>
			<td>O(N)</td>
			<td>O(2N)</td>
			<td>Removes node and its descendants from both tree and memory.</td>
		</tr>
		<tr>
			<td>removeNode(T)</td>
			<td>O(1)</td>
			<td>O(2)</td>
			<td>Removes node from both tree and memory.</td>
		</tr>
		<tr>
			<td>contains(V,C?)</td>
			<td>O(N)</td>
			<td>O(1)</td>
			<td>Checks if tree contains node value.</td>
		</tr>
		<tr>
			<td>search(V,C?)</td>
			<td>O(N)</td>
			<td>O(1)</td>
			<td>Removes head element of container and returns its value.</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				T = tree node<br/>
				V = value<br/>
				C = comparator (?: not needed when nodes are guaranteed to hold unique values)<br/>
				N = number of nodes in tree<br/>
			</td>
		</tr>
	</tbody>
</table>

Operations complexity @ graphs:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>Graph</td>
			<td>UniqueGraph</td>
			<td>WeightedGraph</td>
			<td>UniqueWeightedGraph</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>createVertex(T)</td>
			<td>O(1)</td>
			<td>O(2)</td>
			<td>O(1)</td>
			<td>O(2)</td>
			<td>Creates vertex in graph.</td>
		</tr>
		<tr>
			<td>removeVertex(V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Removes vertex from graph and deallocates.</td>
		</tr>
		<tr>
			<td>createEdge(V,V,B)</td>
			<td>O(1|2)</td>
			<td>O(1|2)</td>
			<td>O(1|2)</td>
			<td>O(1|2)</td>
			<td>Creates edge between vertexes.</td>
		</tr>
		<tr>
			<td>removeEdge(V,V,B)</td>
			<td>O(E|2E)</td>
			<td>O(E|2E)</td>
			<td>O(E|2E)</td>
			<td>O(E|2E)</td>
			<td>Removes edge between vertexes.</td>
		</tr>
		<tr>
			<td>getDistance(V,V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Gets number of vertexes in path between vertexes using BFS.</td>
		</tr>
		<tr>
			<td>getPath(V,V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Gets vertexes in path between vertexes using BFS.</td>
		</tr>
		<tr>
			<td>getSize()</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Gets number of vertexes in graph.</td>
		</tr>
		<tr>
			<td>getWeight(V,V)</td>
			<td>-</td>
			<td>-</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>Gets weight of direct edge between vertexes.</td>
		</tr>
		<tr>
			<td>isEdge(V,V)</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>Checks if there is a direct edge between vertexes.</td>
		</tr>
		<tr>
			<td>isPath(V,V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Checks if there is a path between vertexes using BFS.</td>
		</tr>
		<tr>
			<td>iterate(V,Z)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Iterates vertex's descendant tree using BFS.</td>
		</tr>
		<tr>
			<td>iterate(Z)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Iterates all vertexes in graph.</td>
		</tr>
		<tr>
			<td>removeVertex(T,C?)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Removes vertex from graph and deallocates.</td>
		</tr>
		<tr>
			<td>contains(T,C?)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Checks if graph contains vertex value.</td>
		</tr>
		<tr>
			<td>search(T,C?)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Searches vertexes by their value.</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				T = value<br/>
				V = vertex<br/>
				E = edge<br/>
				C = comparator (?: not needed when vertexes are guaranteed to hold unique values)<br/>
				B = whether or not operation should be bidirectional<br/>
				Z = vertex visitor to use during iteration<br/>
				N = number of nodes in tree<br/>
			</td>
		</tr>
	</tbody>
</table>

##Benchmarks##

Methodology:

1. functions used for benchmarking can be reviewed in src/Benchmark.h and only work on UNIX systems
2. benchmarks themselves can be found in src/Benchmarks folder and can be ran by uncommenting respective lines in src/Test.cpp (Eg: ListBenchmark)
3. for maximum reliability, each benchmark for each data structure implementation has been ran individually in three rows, commenting all others.
4. results are done by compiling results of three rows of tests on each structure implementation
5. tests were ran using O2 compiler optimization on an Intel(R) Core(TM) i5-2500K CPU & 8GB RAM running on Ubuntu 16

###Lists###

Test case:

1. checking memory allocated by a list containing a million entries
2. checking duration of a million rows insertion on list's bottom
3. checking duration of iterating all list from top to bottom
4. checking duration of getting all list element values by offset from top to bottom 
5. removing all list elements based on offset from bottom to top (for dynamic arrays) and top to bottom (for [doubly-]linked lists)

Results:

<table>
<tr><td>Implementation</td><td>Data Structure</td><td>Value Type</td><td>Memory (kb)</td><td>Insertion (ms)</td><td>Iteration (ms)</td><td>Selection (ms)</td><td>Deletion (ms)</td></tr>
<tr><td>std::vector</td><td>dynamic array</td><td>long</td><td>7816</td><td>4</td><td>0</td><td>0</td><td>1</td></tr>
<tr><td>ArrayList</td><td>dynamic array</td><td>long</td><td>7816</td><td>3</td><td>0</td><td>0</td><td>1</td></tr>
<tr><td>std::vector</td><td>dynamic array</td><td>char*</td><td>7816</td><td>3</td><td>0</td><td>1</td><td>1</td></tr>
<tr><td>ArrayList</td><td>dynamic array</td><td>char*</td><td>7816</td><td>2</td><td>0</td><td>0</td><td>0</td></tr>
<tr><td>std::forward_list</td><td>linked list</td><td>long</td><td>31152</td><td>30</td><td>5</td><td>5</td><td>14</td></tr>
<tr><td>LinkedList</td><td>linked list</td><td>long</td><td>31152</td><td>30</td><td>0</td><td>0</td><td>14</td></tr>
<tr><td>std::forward_list</td><td>linked list</td><td>char*</td><td>31152</td><td>31</td><td>6</td><td>6</td><td>15</td></tr>
<tr><td>LinkedList</td><td>linked list</td><td>char*</td><td>31152</td><td>30</td><td>0</td><td>0</td><td>15</td></tr>
<tr><td>std::list</td><td>doubly linked list</td><td>long</td><td>31152</td><td>35</td><td>5</td><td>5</td><td>17</td></tr>
<tr><td>DoublyLinkedList</td><td>doubly linked list</td><td>long</td><td>31152</td><td>31</td><td>0</td><td>5</td><td>17</td></tr>
<tr><td>std::list</td><td>doubly linked list</td><td>char*</td><td>31152</td><td>32</td><td>5</td><td>5</td><td>16</td></tr>
<tr><td>DoublyLinkedList</td><td>doubly linked list</td><td>char*</td><td>31152</td><td>32</td><td>0</td><td>7</td><td>17</td></tr>
</table>

Graphic: {TODO}

Several notes:

1. tests for dynamic array implementations use reserved size of one million plus one. The reason is that each implementation has its own growth point (A grows at point V, while B grows at point Z>V: if we stop insertion between V and Z, A will appear slower because it has done one more reallocation)
2. despite different programming behind, memory usage between STL and CDS is always the same and only varies by data structure.

###Maps###

Test case:

1. checking memory allocated by a map containing a million entries
2. checking duration of a million rows insertion
3. checking duration of iterating all map
4. checking duration of getting all map entry values by key
5. removing all map entries based on key

Results:

<table>
<tr><td>Implementation</td><td>Data Structure</td><td>Key type</td><td>Value type</td><td>Memory (kb)</td><td>Insertion (ms)</td><td>Iteration (ms)</td><td>Selection (ms)</td><td>Deletion (ms)</td></tr>
<tr><td>std::map</td><td>red black tree</td><td>long</td><td>long</td><td>62436</td><td>320</td><td>17</td><td>172</td><td>141</td></tr>
<tr><td>TreeMap</td><td>red black tree</td><td>long</td><td>long</td><td>62436</td><td>314</td><td>14</td><td>148</td><td>124</td></tr>
<tr><td>std::map</td><td>red black tree</td><td>char*</td><td>char*</td><td>62568</td><td>277</td><td>21</td><td>181</td><td>216</td></tr>
<tr><td>TreeMap</td><td>red black tree</td><td>char*</td><td>char*</td><td>62568</td><td>263</td><td>20</td><td>164</td><td>156</td></tr>
<tr><td>std::unordered_map</td><td>hash table</td><td>long</td><td>long</td><td>39408</td><td>55</td><td>4</td><td>12</td><td>25</td></tr>
<tr><td>HashMap</td><td>hash table</td><td>long</td><td>long</td><td>46860</td><td>46</td><td>8</td><td>12</td><td>26</td></tr>
<tr><td>std::unordered_map</td><td>hash table</td><td>char*</td><td>char*</td><td>46860</td><td>89</td><td>16</td><td>45</td><td>61</td></tr>
<tr><td>HashMap</td><td>hash table</td><td>char*</td><td>char*</td><td>46860</td><td>62</td><td>10</td><td>32</td><td>46</td></tr>
<tr><td>LinkedHashMap</td><td>linked hash table</td><td>long</td><td>long</td><td>62436</td><td>51</td><td>9</td><td>13</td><td>29</td></tr>
<tr><td>LinkedHashMap</td><td>linked hash table</td><td>char*</td><td>char*</td><td>62568</td><td>65</td><td>11</td><td>34</td><td>44</td></tr>
</table>

Several notes:

1. tests for hash table implementations use reserved size of one million plus one. The reason is that each implementation has its own growth point (A grows at point V, while B grows at point Z>V: if we stop insertion between V and Z, A will appear slower because it has done one more reallocation)
2. despite different programming behind, memory usage between STL and CDS is always the same and only varies by data structure EXCEPT for std::unordered_map<long,long> who for reason I do not understand allocates LESS.

###Sets###

Test case:

1. checking memory allocated by a set containing a million entries
2. checking duration of a million rows insertion
3. checking duration of iterating all set
4. removing all set entries based on value

Results:

<table>
<tr><td>Implementation</td><td>Data Structure</td><td>Value Type</td><td>Memory (kb)</td><td>Insertion (ms)</td><td>Iteration (ms)</td><td>Deletion (ms)</td></tr>
<tr><td>std::set</td><td>red black tree</td><td>long</td><td>46860</td><td>237</td><td>22</td><td>116</td></tr>
<tr><td>TreeSet</td><td>red black tree</td><td>long</td><td>46860</td><td>231</td><td>20</td><td>112</td></tr>
<tr><td>std::set</td><td>red black tree</td><td>char*</td><td>46860</td><td>260</td><td>15</td><td>211</td></tr>
<tr><td>TreeSet</td><td>red black tree</td><td>char*</td><td>46860</td><td>293</td><td>15</td><td>139</td></tr>
<tr><td>std::unordered_set</td><td>hash table</td><td>long</td><td>39408</td><td>57</td><td>4</td><td>26</td></tr>
<tr><td>HashSet</td><td>hash table</td><td>long</td><td>31152</td><td>40</td><td>7</td><td>24</td></tr>
<tr><td>std::unordered_set</td><td>hash table</td><td>char*</td><td>31284</td><td>75</td><td>15</td><td>62</td></tr>
<tr><td>HashSet</td><td>hash table</td><td>char*</td><td>31284</td><td>55</td><td>12</td><td>42</td></tr>
<tr><td>LinkedHashSet</td><td>linked hash table</td><td>long</td><td>46860</td><td>47</td><td>7</td><td>27</td></tr>
<tr><td>LinkedHashSet</td><td>linked hash table</td><td>char*</td><td>46860</td><td>64</td><td>7</td><td>42</td></tr>
</table>

Several notes:

1. tests for hash table implementations use reserved size of one million plus one. The reason is that each implementation has its own growth point (A grows at point V, while B grows at point Z>V: if we stop insertion between V and Z, A will appear slower because it has done one more reallocation)
2. despite different programming behind, memory usage between STL and CDS is always the same and only varies by data structure EXCEPT for std::unordered_set<long,long> who for reason I do not understand this time allocates MORE.
