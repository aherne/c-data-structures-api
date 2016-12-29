Pure virtual methods of Set class:
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

O complexity of above methods by their implementation:
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

Constructors:

- all applied maps work primarily with a no-arg constructor
- HashTable-based maps (HashMap & LinkedHashMap) also support being preallocated with a reserved size by constructor:
```c++
HashMap(const std::size_t& reservedSize)
LinkedHashMap(const std::size_t& reservedSize)
```

Templates:

- HashTable-based sets (HashSet & LinkedHashSet) have three template arguments:
```c++
template <typename _VALUE_TYPE, int (*comparer)(const _VALUE_TYPE&, const _VALUE_TYPE&), std::size_t (*hasher)(const _VALUE_TYPE&)>
```
	Where:
	- _VALUE: data type of map value
	- comparer: user-provided function that compares entries, requirement of HashTable underneath
	- hasher: user-provided function that hashes entry, requirement of HashTable underneath

- RedBlackTree-based sets (TreeSet) instead have two template arguments:
```c++
template <typename _KEY, typename _VALUE, int (*comparer)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)>
```
	Where:
	- _VALUE: data type of map value
	- comparer: user-provided function that compares entries, requirement of HashTable underneath

Iterators:

- all sets are iterable via polymorphic MapIterator*:
```c++
Set<long>* set = new LinkedHashSet<long>;
set.set(1);
set.set(2);
for(auto it=map.begin(); *it!=*(map->end()); ++(*it)) {
	std::cout << *(*it) << std::endl;
}
// outputs: 1 (new line) 2
```