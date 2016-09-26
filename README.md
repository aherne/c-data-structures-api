# c-data-structures-api

##Genesis##

Building another STL instead of using the fast super-stable time-tested library that is already used by virtually all C++ programmers seems like a textbook example of "reinventing the wheel", which happens to be a most damning stigma in today's world of programming (especially in higher level languages such as Java, but increasingly so in C++ as well). 

###Reinventing the Wheel 101###

Why is "reinventing the wheel" so bad? Because  apparently some people long before you had a godly intelligence to create something that is beyond redesign! You, as a "senior developer" should just use your mind as a bucket of others' ideas and concoct solutions based on those. The more you learn, the more your bucket enlarges so you will ultimatly reach a level of no "wheel reinvention" and finally achieved ultimate "seniorship". Sounds like a mindless religion? Sure is! The end result of this mindset is:

- overly complicated code. Chances are nobody made a solution PRECISELY for your needs, so you end up using something that is needlessly complex, which taxes performance as well as making code hard to understand. In the world of Java or PHP (the other languages I'm competent at) you encounter a profusion of frameworks geared at making above-mentioned bucket enormous enough to fit "everything" a coder will ever possibly need. 
- abominable code made by programmers who never got their chance to exercise their mind. Obviously, years or even decades of experience while working like a factory robot doesn't increase your intelligence and problem-solving skills. The things you write will always reflect the lack of fundamental logic: zero concern on performance, simplicity, elegance or even common sense. Typically here we find classes doing EVERYTHING, technologies used because developer could not write two lines of proper code, orgies of pre-processor macros (in C/C++) and an omnious messy look from top to bottom.
- the standards. Factory work would not be complete without standards. A worker is supposed to obey standards as his second nature! Generally the standards have themselves become standardized, so companies have created tools that check if your code obeys the standards (be it test coverage, code quality, design patterns or whatever). The end result gives the impression of a quality improvement, but real life experience tells you they are to a large extent useless hindrance. Hiring a few competent developers is always a better long term solution (in terms of quality & performance) than imposing standards to sub-standard workers.
- WARNING: this may hurt feelings! Because programming is a well-payed job, it has lately attracted an army of people unsuitable for this job, incapable to do any better EVEN IF they are trained "the standards" or to think for themselves.

Are all of above responsable for the steady decline in the quality of programming? You bet! What is the alternative then? The alternative is to "reinvent the wheel" whenever you can think you can do better, learn from your/others' mistakes and move your level ever higher while maintaining rock-solid allegiance to above-mentioned principles of performance, simplicity and elegance. Why only these three abstract ideas I qualify as standards? Because they define a working methodology that imposes no constraints except striving for clarity and perfection. This way programming becomes an ungoing quest to intellectual discovery and delight! 

###What's Wrong with STL?###
There is nothing inherently wrong with STL. It's a very robust and heavily tested solution that proved itself to be a good companion to programmer needs, BUT there is nothing ultimate about it. It's just one IMPLEMENTATION of "data structure & algorithms" concepts, not perfect like everything else in life, with its own qualities and defects.

What I liked about STL implementation is its iterators. STL iterators are without doubt more advanced/complete than anything done on that topic (at least in languages I know: Java and PHP). They have unbeatable flexibility, but they have the major defect of being non-extensible. It is fiendishly complicated to employ a STL iterator for a custom-defined (non-STL) data structure, which is why I unfortunately had to give up and implement my own (more primitive) versions of it. 

What I failed to like about STL and made me think I can do better:

- It's unstructured. What I liked about Collections API in Java is the interface-implementation paradigm that suits data structures the best. In C++ as well, a list should be a concept (class with pure virtual methods), while a dynamic array / linked list / doubly linked list should be different implementations of same concept. Not only should programmer abstract the list implementation by using List* only (which is a no-cost operation), but he will be assured whatever functionality is defined by List will have an implementation for whatever list type he uses (eg: linked list). In STL, because data structures are not designed hierarchically, there is an absolute chaos in method names (who aren't very intuitive BTW) and functionality (which may or may not have been implemented) so one needs to constantly check documentation. This was DEFINITELY something that needed to be changed.
- It's coupled. It's extremely difficult to glue its components (be it iterators or dependency classes/structs) with non-STL components. It's clear that the very good programmers who have worked for it, even though they went overboard with decoupling to largest extent imaginable (which is why STL structures' implementations are so complex), the end result has been something so complicated that it becomes uninviting to understand (leaving the impression of overprogrammed code).     
- Its HashTable implementations (unordered_map, unordered_set @ C++11) are too slow and could definitely be improved. For example, my implementations are TWO TIMES faster for char* keys (using same hashing algorithm: DJBX33A) than unordered_map/unordered_set.
- Stacks are queues expose too much functionality when theory requires them to only include two functionalities: push/pop(/peek), enqueue/dequeue

What I found missing in STL, but found useful enough to be included in my implementation:

- LinkedHashTable (and its LinkedHashMap, LinkedHashSet implementations): this is a hashtable where entries are iterated by insertion order (by adding doubly-linked-list functionality to hash table nodes). Actually, in languages such as PHP or Python that's the only HashTable known. Even in C++, I frequently missed this option, which in my implementation only adds less than 10% performance taxation.
- Trees & Graphs. I always found incredible how n-ary trees lack an "official" implementation in all languages I know, even though they are routinely needed and can easily be abstracted.

###What's Data Structures API###
This is my own implementation of data structures and algorithms in C++, built on principles of performance, simplicity and elegance described above, different from STL in being much lighter weight, tightly organized through polymorphism and with equal or greater performance. Its principles are somewhat inspired by Java Collections API in concept-implementation separation: here we have pure virtual classes defining concept (abstract data structure) requires (eg: List) followed by implementations of that concept using real data structures (eg: LinkedList). The former will be classes with pure-virtual methods, while the latter will be classes that extend them and implement all methods defined in parent.

Supported data structures:

- List: defines signatures for list abstract data structure 
	- ArrayList: implements a list of dynamic array type (akin STL std::vector)
	- LinkedList: implements a list of singly linked type (akin STL std::forward_list @ C++11, but keeping a pointer to tail, making insertions on bottom as fast as on top) 
	- DoublyLinkedList: implements a list of doubly linked type (akin STL std::list)
- Map: defines signatures for map abstract data structure
	- HashMap: implements a map of hash table type (akin STL std::unordered_map @ C++11, but faster and lighter weight)
	- LinkedHashMap: implements a map of hash table type with entries iterated by insertion order (no STL equivalent)
	- TreeMap: implements a map of red black tree type (akin STL std::map)
- Set: defines signatures for set abstract data structure
	- HashSet: implements a set of hash table type (akin std::unordered_set @ C++11, but faster and lighter weight)
	- LinkedHashSet: implements a set of hash table type with entries iterated by insertion order (no STL equivalent)
	- TreeSet: implements a set of red black tree type (akin STL std::set)
- Container: defines signatures for container adaptors into which all read/write operations are performed only on head or tail
	- Stack: implements a LIFO container adaptor where data is pushed to head and popped from head (similar to std::stack, but using dynamic arrays)
	- Queue: implements a FIFO container adaptor where data is pushed to bottom and popped from head (similar to std::queue, but using dynamic arrays)
- Tree: none (trying to set a common ground is unintuitive and would lead to over-programming)
	- RedBlackTree: A binary search tree balanced on red-black principles.
	- TreeNode: A n-ary tree (no STL equivalent)

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

##Benchmarks##

####Lists####

Test case:

1. checking the memory allocated by insertion of a million rows into the list
2. checking duration of inserting a million rows on list's bottom
3. checking duration of iterating list from top to bottom
4. checking getting list element values by offset from top to bottom 
5. removing list elements based on offset from bottom to top (for dynamic arrays) and top to bottom (for [doubly-]linked lists)

Results:

<table>
	<thead>
		<tr><td>&nbsp;</td><td>MEMORY (KB)</td><td>INSERTION (MS)</td><td>ITERATION (MS)</td><td>SELECTION (MS)</td><td>DELETION (MS)</td></tr>
	</thead>
	<tbody>
		<tr><td>std::vector<long></td><td>7816</td><td>4</td><td>0</td><td>0</td><td>1</td></tr>
		<tr><td>ArrayList<long></td><td>7816</td><td>3</td><td>0</td><td>0</td><td>1</td></tr>
		<tr><td>std::forward_list<long></td><td>31152</td><td>30</td><td>5</td><td>5</td><td>14</td></tr>
		<tr><td>LinkedList<long></td><td>31152</td><td>30</td><td>0</td><td>0</td><td>14</td></tr>
		<tr><td>std::list<long></td><td>31152</td><td>35</td><td>5</td><td>5</td><td>17</td></tr>
		<tr><td>DoublyLinkedList<long></td><td>31152</td><td>31</td><td>0</td><td>5</td><td>17</td></tr>
		<tr><td>std::vector<char*></td><td>7816</td><td>3</td><td>0</td><td>1</td><td>1</td></tr>
		<tr><td>ArrayList<char*></td><td>7816</td><td>2</td><td>0</td><td>0</td><td>0</td></tr>
		<tr><td>std::forward_list<char*></td><td>31152</td><td>31</td><td>6</td><td>6</td><td>15</td></tr>
		<tr><td>LinkedList<char*></td><td>31152</td><td>30</td><td>0</td><td>0</td><td>15</td></tr>
		<tr><td>std::list<char*></td><td>31152</td><td>32</td><td>5</td><td>5</td><td>16</td></tr>
		<tr><td>DoublyLinkedList<char*></td><td>31152</td><td>32</td><td>0</td><td>7</td><td>17</td></tr>
	</tbody>
<table>
