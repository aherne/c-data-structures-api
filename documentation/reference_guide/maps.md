## Maps

Maps (also called dictionaries or associative arrays) are data structures alike lists only that entries are key-value pairs (instead of being just values):

- any entry value is accessible by its entry key
- a single value can exist at multiple keys
- a single key can only hold a single value 

### Abstract maps

Abstract maps implement blueprints for operations one can perform on a map. This is done via methods of **Map** class, which defines following pure virtual methods:
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
			<td>KEY</td>
			<td>VALUE</td>
			<td>Gets value by key.</td>
		</tr>
		<tr>
			<td>clear</td>
			<td>&nbsp;</td>
			<td>void</td>
			<td>Clears map of all values.</td>
		</tr>
		<tr>
			<td>containsKey</td>
			<td>KEY</td>
			<td>bool</td>
			<td>Checks if key exists in map.</td>
		</tr>
		<tr>
			<td>containsValue</td>
			<td>VALUE, COMPARATOR</td>
			<td>bool</td>
			<td>Checks if value exists in map.</td>
		</tr>
		<tr>
			<td>get</td>
			<td>KEY</td>
			<td>VALUE</td>
			<td>Gets value by key.<br/>Throws <u>std::out_of_range</u> if key is not found.</td>
		</tr>
		<tr>
			<td>set</td>
			<td nowrap>KEY, VALUE</td>
			<td>void</td>
			<td>Sets value by key.</td>
		</tr>
		<tr>
			<td>removeKey</td>
			<td>KEY</td>
			<td>void</td>
			<td>Removes element by key.<br/>Throws <u>std::out_of_range</u> if key is not found.</td>
		</tr>
		<tr>
			<td>removeValue</td>
			<td>VALUE, COMPARATOR</td>
			<td>void</td>
			<td>Removes all elements that match value.<br/>Throws <u>std::out_of_range</u> if value is not found.</td>
		</tr>
		<tr>
			<td>isEmpty</td>
			<td>&nbsp;</td>
			<td>void</td>
			<td>Checks if map is empty</td>
		</tr>
		<tr>
			<td>size</td>
			<td>&nbsp;</td>
			<td nowrap>const std::size_t&</td>
			<td>Gets map size</td>
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
						<td>KEY</td>
						<td>const KEY_TYPE&</td>
					</tr>
					<tr>
						<td>VALUE</td>
						<td>const VALUE_TYPE&</td>
					</tr>
					<tr>
						<td>ITERATOR</td>
						<td>MapIterator&lt;KEY_TYPE, VALUE_TYPE&gt;*</td>
					</tr>
					<tr>
						<td>COMPARATOR</td>
						<td>int (*comparer)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>


### Implemented maps

Implemented maps are classes that extend **Map** class and provide specific implementations for methods above:

- **HashMap**: implements a map that wraps a **HashTable** object. A hash table is a dynamic array adapted to store key-value pairs for constant key look-up time. Because wrapped C array only works with numeric consecutive positions, the hash table needs to convert entry key into a position relevant to dynamic array (via a *hash* function), then store the key-value pair in that position along with existing entries in a linked list (using a *comparator* function to verify if entry already exists). In order to preserve constant key look-up time, when dynamic array reaches capacity and grows, it needs to redistribute its old entries into new positions based on hashing algorithm, which takes a lot longer than a simple *realloc*. Simply put, a HashMap is a dynamic array of linked lists of key-value pairs. Because entries are put in random positions inside dynamic array, the hash map is by default unordered, which means the order items appear on iteration is unpredictable.
	- Strengths:
		- By far the fastest in insertion/lookup/deletion of entries: because hash table only needs to compute a hash of entry key and look up in bucket (linked list at position @ dynamic array) that corresponds to hash to add/delete/retrieve that entry. Because bucket ideally contains one entry only, this operation is considered to occur in constant O(1) time.
		- By far the smallest in memory consumption: only a dynamic array of linked lists.
	- Weaknesses:
		- Unpredictable order, which makes it hard to test.
		- Growth is costly, for reasons already mentioned above. When size of map is already known, it's MUCH faster to use a reserved size.
		- As a dynamic array, allocates more space than it actually uses. When size of map is already known, it's MUCH more optimal to use a reserved size so no space is wasted.
		- It depends on:
			- a fast hash function that guarantees even distribution throughout buckets, so that the linked list inside ideally contains only one entry.
			- a reliable comparator function that guarantees there won't be duplicates with same value of key in the map (which would violate above-mentioned map principles)
- **LinkedHashMap**: implements a map that wraps a **LinkedHashTable** object. A linked hash table is a hash table like above, only that entries (key-value pairs) not only keep track of next element in bucket (value at position in dynamic array) but also of previously inserted entry (which may be nil) and next inserted entry. Thanks to this, it becomes iterable in predictable order, namely that of elements' insertion, but at the same time taking more space to fulfill that requirement.
	- Strengths:
		- Almost as fast, just a bit slower (5-10%) than HashMap on insertion/lookup/deletion of entries: because it needs to maintain the doubly linked list that preserves insertion order as well.
		- Predictable order, which makes testing easy
	- Weaknesses:
		- Greater memory consumption (33%) than HashMap, because it needs to store the doubly linked list that maintains insertion order.
		- Growth is costly, for reasons already mentioned above. When size of map is already known, it's MUCH faster to use a reserved size.
		- As a dynamic array, allocates more space than it actually uses. When size of map is already known, it's MUCH more optimal to use a reserved size so no space is wasted.
		- Same dependency on a good hash/comparator function.
- **TreeMap**: implements a map that wraps a **RedBlackTree** object. A red black tree is a binary search tree balanced using Red-Black principles. The way latter works is very complicated, but the end result is that, by employing a comparator function for entry keys, the red black tree is able to stay ordered whenever an item is added/deleted and also support acceptable O(logN) look-up times thanks to the fact it's balanced. Like LinkedHashMap, TreeMap is also iterable in predictable order, this time based on comparator algorithm.
	- Strengths:
		- Stays ordered by key.
		- Predictable order, which makes testing easy
	- Weaknesses:
		- Much slower (6-7 times) than HashMap in insertion/deletion of entries: because the red black tree always has to rebalance itself, which is a VERY costly operation that may involve the whole data set.
		- Greater memory consumption (33%) than HashMap, because it needs to store the doubly linked list that maintains insertion order.
		- Depends on a reliable key comparator function.

Because of above considerations, O complexity of **Map** methods varies by implementation:
<table>
	<thead>
		<tr>
			<td><strong>Method</strong></td>
			<td><strong>HashMap</strong></td>
			<td><strong>LinkedHashMap</strong></td>
			<td><strong>TreeMap</strong></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>clear</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>containsKey</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
		</tr>
		<tr>
			<td>containsValue</td>
			<td>O(N)</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>get</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
		</tr>
		<tr>
			<td>set</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
		</tr>
		<tr>
			<td>removeKey</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(log(N))</td>
		</tr>
		<tr>
			<td>removeValue</td>
			<td>O(N)</td>
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
				N = number of elements in map
			</td>
		</tr>
	</tbody>
</table>

Because of its many advantages in terms of speed and memory consumption, **HashMap** should be solution of choice, unless one needs predictable iteration (in which case **LinkedHashMap** should be used) or being ordered by key (in which case **TreeMap** should be used).

#### Constructors

All implemented maps work primarily with a no-arg constructor. HashMap & LinkedHashMap also support being preallocated with a reserved size by constructor:
```c++
HashMap(const std::size_t& reservedSize) {...}
LinkedHashMap(const std::size_t& reservedSize) {...}
```

#### Templates

- HashTable-based maps (HashMap & LinkedHashMap) have four template arguments:
```c++
template <typename _KEY, typename _VALUE, int (*comparer)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&), std::size_t (*hasher)(const MapEntry<_KEY,_VALUE>&)>
```
	Where:
	- _KEY: data type of map key
	- _VALUE: data type of map value
	- comparer: user-provided function that compares entries by key, requirement of HashTable underneath
	- hasher: user-provided function that hashes entry by key, requirement of HashTable underneath

- RedBlackTree-based maps (TreeMap) instead have three template arguments:
```c++
template <typename _KEY, typename _VALUE, int (*comparer)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)>
```
	Where:
	- _KEY: data type of map key
	- _VALUE: data type of map value
	- comparer: user-provided function that compares entries by key, requirement of RedBlackTree underneath

#### Iterators

All maps are iterable via polymorphic MapIterator*:
```c++
Map<long,long>* map = new LinkedHashMap<long,long>;
map.set(1,2);
map.set(3,4);
for(auto it=map.begin(); *it!=*(map->end()); ++(*it)) {
	std::cout << (*(*it)).first << ":" << (*(*it)).last << std::endl;
}
// outputs: 1:2 (new line) 3:4
```
Currently, only forward iteration is supported. Unlike STL iterators, this one self-invalidates (iteration ends gracefully) when an item is added to /deleted from map while iterating.