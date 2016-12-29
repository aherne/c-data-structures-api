Unlike data structures above, operations a tree performs are irreducible to a common ground. Each tree type chosen reflects a very different need, which results into fundamentally different operations. For that reason, no common Tree interface has been defined and trees exist only as disparate implementations.Available implementations:

- RedBlackTree: a balanced binary search tree using red-black principles, used internally as a foundation for structures that need to stay sorted (see TreeMap and TreeSet classes above), with algorithms based on Introduction to Algorithms 3rd Edition by Thomas Cormen, Charles Leiserson & Ronald Rivest.
- Tree: a basic n-ary tree with no children size bounds, used to store node hierarchies
	- NonUniqueTree: , allowing nodes with duplicate values
	- UniqueTree: a version of above where pointers to nodes are also saved in a HashTable to prevent duplicates and allow O(1) access to any entry in tree.

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