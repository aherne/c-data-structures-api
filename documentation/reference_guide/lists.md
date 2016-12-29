## What are lists? ##

Lists are data structures in which:

- all elements are stored sequentially from position 0 to position length-1 without empty gaps
- any element is accessible by its position in sequence
- a single value can exist at multiple positions
- a single position can only hold a single value 

###Abstract lists###

Abstract lists implement blueprints for operations one can perform on a list. This is done via pure virtual methods of **List** class:
<table>
	<thead>
		<tr>
			<td><strong>Method</strong></td>
			<td><strong>Arguments</strong></td>
			<td><strong>Returns</strong></td>
			<td><strong>Description</strong></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>operator[]</td>
			<td>POSITION</td>
			<td>VALUE</td>
			<td>Gets value by position.</td>
		</tr>
		<tr>
			<td>addToTop</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Add value on top of list.</td>
		</tr>
		<tr>
			<td>addToBottom</td>
			<td>VALUE</td>
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
			<td>POSITION</td>
			<td>bool</td>
			<td>Checks if position exists in list.</td>
		</tr>
		<tr>
			<td>containsValue</td>
			<td nowrap>
				VALUE, COMPARATOR
			</td>
			<td>bool</td>
			<td>Checks if value exists in list by comparator.</td>
		</tr>
		<tr>
			<td>emplace</td>
			<td>POSITION, VALUE</td>
			<td>void</td>
			<td>Inserts value at position, padding existing element to the right.<br/>Throws <u>std::out_of_range</u> if position exceeds size.</td>
		</tr>
		<tr>
			<td>get</td>
			<td>POSITION</td>
			<td>VALUE</td>
			<td>Gets value by position.<br/>Throws <u>std::out_of_range</u> if position not found.</td>
		</tr>
		<tr>
			<td>set</td>
			<td>POSITION, VALUE</td>
			<td>void</td>
			<td>Sets value by position.<br/>Throws <u>std::out_of_range</u> if position not found.</td>
		</tr>
		<tr>
			<td>removeIndex</td>
			<td>POSITION</td>
			<td>void</td>
			<td>Removes element by position.<br/>Throws <u>std::out_of_range</u> if position not found.</td>
		</tr>
		<tr>
			<td>removeValue</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Removes all elements that match value.<br/>Throws <u>std::out_of_range</u> if value not found.</td>
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
			<td nowrap>const size_t&</td>
			<td>Gets list size</td>
		</tr>
		<tr>
			<td>begin</td>
			<td>&nbsp;</td>
			<td>ITERATOR</td>
			<td>Starts iterator</td>
		</tr>
		<tr>
			<td>end</td>
			<td>&nbsp;</td>
			<td>ITERATOR</td>
			<td>Ends iterator</td>
		</tr>
		<tr>
			<td colspan=4>
				<strong>Signatures:</strong>
				<table>
					<tr>
						<td>POSITION</td>
						<td>const std::size_t&</td>
					</tr>
					<tr>
						<td>VALUE</td>
						<td>const VALUE_TYPE&</td>
					</tr>
					<tr>
						<td>COMPARATOR</td>
						<td>int (comparator*) (const VALUE_TYPE&, const VALUE_TYPE&)</td>
					</tr>
					<tr>
						<td>ITERATOR</td>
						<td>ListIterator&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

###Implemented lists###

Implemented lists extend **List** class and provide specific implementations for blueprints above, each with its own strength and weaknesses:

- **ArrayList**: implements a list that works like a dynamic array. Entries are stored in a continuous block of memory that expands (via realloc) whenever capacity is reached.
	- Strengths:
		- by far the fastest in accessing random position: because it only involves navigating through the C array it wraps.
		- by far the fastest in adding element to bottom of list: because it only requires incrementing count and adding value to next position in already preallocated (unless an expand is pending) block 
		- by far the fastest in removing element from bottom of list: because it only requires decrementing count value.
		- smallest in memory consumption: because nothing but elements themselves plus remaining empty slots in preallocated block are stored 
	- Weaknesses:
		- by far the slowest in deleting element at random position: because it involves padding all entries after position one step left.
		- by far the slowest in adding element at random position: because it involves padding all entries after position one step right.
- **LinkedList**: implements a list that works like a linked list. Entries are stored in random places in memory, always keeping track of the next entry. 
	- Strengths:
		- fast in deleting element on top position: because it only requires swapping head element with the next.
		- fast in deleting element on next position: because it keeps track of element after the one deleted.
		- fast in adding element on top of list: because it only involves switching top position with the new one and next position with the old top.
		- fast in adding element on bottom of list: because it keeps track of list tail.
	- Weaknesses:
		- relatively slow in traversal: because it needs to move from random memory position to the other.
		- slow at deleting/accessing/inserting element on random position: because it needs to traverse all entries in list until position.
		- slow at deleting element on bottom: because it needs to traverse the whole list.
		- higher in memory consumption: because every element needs to store a pointer to the next
- **DoublyLinkedList**: implements a list that works like a doubly linked list. Entries are stored in random places in memory, always keeping track of the next and previous entry.
	- Strengths:
		- fast in deleting element on top position: because it only requires swapping head element with the next.
		- fast in deleting element on bottom position: because it only requires swapping tail element with the previous.
		- fast in deleting element on next position: because it keeps track of element before the one deleted.
		- fast in deleting element on previous position: because it keeps track of element before the one deleted.
		- fast in adding element on top of list: because it only involves switching top position with the new one and next position with the old top.
		- fast in adding element on bottom of list: because it keeps track of list tail.
	- Weaknesses:
		- slow at deleting/accessing/inserting element on random position: because it needs to traverse all entries in list until position.
		- slow at deleting element on bottom: because it needs to traverse the whole list.
		- higher in memory consumption: because every element needs to store a pointer to the next



O complexity of above methods by their implementation:
<table>
	<thead>
		<tr>
			<td><strong>Method</strong></td>
			<td><strong>ArrayList</strong></td>
			<td><strong>LinkedList</strong></td>
			<td><strong>DoublyLinkedList</strong></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>operator[]</td>
			<td>O(1)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
		</tr>
		<tr>
			<td>addToTop</td>
			<td>O(N*2)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>addToBottom</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>clear</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>containsIndex</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>containsValue</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>emplace</td>
			<td>O((N-K)*2)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
		</tr>
		<tr>
			<td>get</td>
			<td>O(1)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
		</tr>
		<tr>
			<td>set</td>
			<td>O(1)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
		</tr>
		<tr>
			<td>removeIndex</td>
			<td>O((N-K)*2)</td>
			<td>O(K)/O(K-P)</td>
			<td>O(K)/O(N-K)/O(K-P)/O(P-K)</td>
		</tr>
		<tr>
			<td>removeValue</td>
			<td>O(N*2)</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>isEmpty</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>size</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>begin</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>end</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td colspan=4>
				<strong>Glossary:</strong><br/>
				K = position in list<br/>
				N = number of elements in list<br/>
				P = internal iterator position
			</td>
		</tr>
	</tbody>
</table>

Constructors:

- all applied lists work primarily with a no-arg constructor
- ArrayList also supports being preallocated with a reserved size by constructor:
```c++
ArrayList(const std::size_t& reservedSize)
```

Templates:

- all lists (abstract or applied) have a single template argument:  
```c++
template<typename VALUE_TYPE>
```

Iterators:

- all lists are iterable via polymorphic ListIterator*:
```c++
List<long>* list = new ArrayList<long>;
list.addToBottom(1);
list.addToBottom(2);
for(auto it=list.begin(); *it!=*(list->end()); ++(*it)) {
	std::cout << *(*it) << std::endl;
}
// outputs: 1 (new line) 2
```