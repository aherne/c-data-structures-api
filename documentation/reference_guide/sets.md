## Sets

Sets are data structures very much like lists, only that:

- entries must be unique
- entries are not accessible by position

### Abstract sets

Abstract sets implement blueprints for operations one can perform on a set. This is done via methods of **Set** class, which defines following pure virtual methods:
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
			<td>add</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Adds value to set.</td>
		</tr>
		<tr>
			<td>clear</td>
			<td>&nbsp;</td>
			<td>void</td>
			<td>Clears set of all values.</td>
		</tr>
		<tr>
			<td>contains</td>
			<td>VALUE</td>
			<td>bool</td>
			<td>Checks if value exists in set.</td>
		</tr>
		<tr>
			<td>remove</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Removes element by value.<br/>Throws <u>std::out_of_range</u> if value is not found.</td>
		</tr>
		<tr>
			<td>isEmpty</td>
			<td>&nbsp;</td>
			<td>bool</td>
			<td>Checks if set is empty</td>
		</tr>
		<tr>
			<td>size</td>
			<td>&nbsp;</td>
			<td nowrap>const std::size_t&</td>
			<td>Gets set size</td>
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
						<td>VALUE</td>
						<td>const VALUE_TYPE&</td>
					</tr>
					<tr>
						<td>ITERATOR</td>
						<td>SetIterator&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>


### Implemented sets

Implemented sets are classes that extend **Set** class and provide specific implementations for methods above:

- **HashSet**: implements a set that wraps a **HashTable** object. A hash table is a dynamic array adapted to store entries for constant look-up time. Because wrapped C array only works with numeric consecutive positions, the hash table needs to convert entry into a position relevant to dynamic array (via a *hash* function), then store it in that position along with existing entries in a linked list (using a *comparator* function to verify if entry already exists). In order to preserve constant look-up time, when dynamic array reaches capacity and grows, it needs to redistribute its old entries into new positions based on hashing algorithm, which takes a lot longer than a simple *realloc*. Simply put, a HashSet is a dynamic array of linked lists of entries. Because entries are put in random positions inside dynamic array, the hash set is by default unordered, which means the order items appear on iteration is unpredictable.
	- Strengths:
		- By far the fastest in insertion/lookup/deletion of entries: because hash table only needs to compute a hash of entry and look up in bucket (linked list at position @ dynamic array) that corresponds to hash to add/delete that entry. Because bucket ideally contains one entry only, this operation is considered to occur in constant O(1) time.
		- By far the smallest in memory consumption: only a dynamic array of linked lists.
	- Weaknesses:
		- Unpredictable order, which makes it hard to test.
		- Growth is costly, for reasons already mentioned above. When size of set is already known, it's MUCH faster to use a reserved size.
		- As a dynamic array, allocates more space than it actually uses. When size of set is already known, it's MUCH more optimal to use a reserved size so no space is wasted.
		- It depends on:
			- a fast hash function that guarantees even distribution throughout buckets, so that the linked list inside ideally contains only one entry.
			- a reliable comparator function that guarantees there won't be duplicates (which would violate above-mentioned set principles)
- **LinkedHashSet**: implements a set that wraps a **LinkedHashTable** object. A linked hash table is a hash table like above, only that entries not only keep track of next element in bucket (value at position in dynamic array) but also of previously inserted entry (which may be nil) and next inserted entry. Thanks to this, it becomes iterable in predictable order, namely that of elements' insertion, but at the same time taking more space to fulfill that requirement.
	- Strengths:
		- Almost as fast, just a bit slower (5-10%) than HashSet on insertion/lookup/deletion of entries: because it needs to maintain the doubly linked list that preserves insertion order as well.
		- Predictable order, which makes testing easy
	- Weaknesses:
		- Greater memory consumption (33%) than HashSet, because it needs to store the doubly linked list that maintains insertion order.
		- Growth is costly, for reasons already mentioned above. When size of set is already known, it's MUCH faster to use a reserved size.
		- As a dynamic array, allocates more space than it actually uses. When size of set is already known, it's MUCH more optimal to use a reserved size so no space is wasted.
		- Same dependency on a good hash/comparator function.
- **TreeSet**: implements a set that wraps a **RedBlackTree** object. A red black tree is a binary search tree balanced using Red-Black principles. The way latter works is very complicated, but the end result is that, by employing a *comparator* function for entries, the red black tree is able to stay ordered whenever an item is added/deleted and also support acceptable O(logN) look-up times thanks to the fact it's balanced. Like LinkedHashSet, TreeSet is also iterable in predictable order, this time based on comparator algorithm.
	- Strengths:
		- Stays ordered.
		- Predictable order, which makes testing easy
	- Weaknesses:
		- Much slower (6-7 times) than HashSet in insertion/deletion of entries: because the red black tree always has to rebalance itself, which is a VERY costly operation that may involve the whole data set.
		- Greater memory consumption (33%) than HashSet, because it needs to store the doubly linked list that maintains insertion order.
		- Depends on a reliable comparator function.

Because of above considerations, O complexity of **Set** methods varies by implementation:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>HashSet</td>
			<td>LinkedHashSet</td>
			<td>TreeSet</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>add</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
		</tr>
		<tr>
			<td>clear</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>contains</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
		</tr>
		<tr>
			<td>remove</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
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
				N = number of elements in set
			</td>
		</tr>
	</tbody>
</table>

#### Constructors

All implemented sets work primarily with a no-arg constructor. HashTable-based sets (HashSet & LinkedHashSet) also support being preallocated with a reserved size by constructor:
```c++
HashSet(const std::size_t& reservedSize)
LinkedHashSet(const std::size_t& reservedSize)
```

#### Templates

- HashTable-based sets (HashSet & LinkedHashSet) have three template arguments:
```c++
template <typename VALUE_TYPE, int (*comparer)(const VALUE_TYPE&, const VALUE_TYPE&), std::size_t (*hasher)(const VALUE_TYPE&)>
```
	Where:
	- VALUE_TYPE: data type of entry
	- comparer: user-provided function that compares entries, requirement of HashTable underneath
	- hasher: user-provided function that hashes entry, requirement of HashTable underneath

- RedBlackTree-based sets (TreeSet) instead have two template arguments:
```c++
template <typename VALUE_TYPE, int (*comparer)(const VALUE_TYPE&, const VALUE_TYPE&)>
```
	Where:
	- _VALUE: data type of entry
	- comparer: user-provided function that compares entries, requirement of HashTable underneath

#### Iterators

All sets are iterable via polymorphic MapIterator*:
```c++
Set<long>* set = new LinkedHashSet<long>;
set.set(1);
set.set(2);
for(auto it=map.begin(); *it!=*(map->end()); ++(*it)) {
	std::cout << *(*it) << std::endl;
}
// outputs: 1 (new line) 2
```
Currently, only forward iteration is supported. Unlike STL iterators, this one self-invalidates (iteration ends gracefully) when an item is added to /deleted from set while iterating.