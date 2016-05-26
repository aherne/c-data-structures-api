# c-data-structures-api

My own implementation of data structures in C++, much simpler than that used by STL, with equal or greater performance. In my tradition, it's strictly organized, structured in a way somewhat similar to Java Collections API:

- List: "interface" implementing signatures of operations common to all kinds of list data structures
	- ArrayList: implements a list of dynamic array type (similar to std::vector)
	- LinkedList: implements a list of singly linked type (similar to std::forward_list @ C++11, but keeping a pointer to tail, making insertions on bottom as fast as on top) 
	- DoublyLinkedList: implements a list of doubly linked type (similar to std::list)
- Map: "interface" implementing signatures of operations common to all kinds of map data structures
	- HashMap: implements a map of hash table type (similar to std::unordered_map @ C++11, only significantly faster and lighter weight)
	- LinkedHashMap: implements a map of hash table type ordered via a doubly linked list (no STL equivalent, elements can be iterated by insertion order)
	- TreeMap: implements a map or red-black-tree type (wrapper over std::map)
- Set: "interface" implementing signatures of operations common to all kinds of set data structures
	- HashSet: implements a set of hash table type (similar to std::unordered_set @ C++11, only significantly faster and lighter weight)
	- LinkedHashSet: implements a set of hash table type ordered via a doubly linked list (no STL equivalent, elements can be iterated by insertion order)
	- TreeSet: implements a set or red-black-tree type (wrapper over std::set)
- Container: "interface" implementing container adaptors into which all read/write operations are performed only on head or tail
	- Stack: implements a LIFO container adaptor where data is pushed to head and popped from head (similar to std::stack, also wrapping std::deque)
	- Queue: implements a FIFO container adaptor where data is pushed to bottom and popped from head (similar to std::queue, also wrapping std::deque)

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