Pure virtual methods of Map class:
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

O complexity of above methods by their implementation:
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

Constructors:

- all applied maps work primarily with a no-arg constructor
- HashTable-based maps (HashMap & LinkedHashMap) also support being preallocated with a reserved size by constructor:
```c++
HashMap(const std::size_t& reservedSize)
```

Templates:

- HashTable-based maps (HashMap & LinkedHashMap) have four template arguments:
```c++
template <typename _KEY, typename _VALUE, int (*comparer)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&), std::size_t (*hasher)(const MapEntry<_KEY,_VALUE>&)>
```
	Where:
	- _KEY: data type of map key
	- _VALUE: data type of map value
	- comparer: user-provided function that compares entries, requirement of HashTable underneath
	- hasher: user-provided function that hashes entry, requirement of HashTable underneath

- RedBlackTree-based maps (TreeMap) instead have three template arguments:
```c++
template <typename _KEY, typename _VALUE, int (*comparer)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)>
```
	Where:
	- _KEY: data type of map key
	- _VALUE: data type of map value
	- comparer: user-provided function that compares entries, requirement of RedBlackTree underneath

Iterators:

- all maps are iterable via polymorphic MapIterator*:
```c++
Map<long,long>* map = new LinkedHashMap<long,long>;
map.set(1,2);
map.set(3,4);
for(auto it=map.begin(); *it!=*(map->end()); ++(*it)) {
	std::cout << (*(*it)).first << ":" << (*(*it)).last << std::endl;
}
// outputs: 1:2 (new line) 3:4
```