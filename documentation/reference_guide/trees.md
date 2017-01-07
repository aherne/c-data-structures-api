## Trees

Trees are non-sequential data structures in which:

- every entry is a node that has links to:
	- a single parent node (unless it's root)
	- a number of child nodes (if any)
- there is a single root node all others descend from directly or indirectly. This node is the only entry that has a nil parent.
- by following child nodes recursively, no node should be able to reach itself (it should be acyclic)
- there must be a single path from one node to another (no reference is duplicated)

One of the reasons why no programming language offers an official implementation for trees apart of their diversity is that tree operations demand exposure of internal elements (nodes), which fails the RAII principle. Unlike sequential data structures, trees are much greater in scope and irreducible to a common ground because each type chosen reflects a very different need, which reflects into different operations. For that reason, no abstract tree class has been defined and trees exist only as implementations.

### Abstract Trees

As mentioned above, tree implementations differs by type of tree, of which these two are the most common in usage:

- *n-ary trees*: threes where there are no restrictions on children size. They are used to store hierarchical data. 
- *binary trees*: trees where a node can have only max two children. Outside didactic examples, in "real life" they are almost always used as *balanced binary search trees*. These are in turn almost always used as a structural basis behind sequential data structures (maps and sets) to keep entries self-sorted. 

#### Balanced binary search trees

A *search tree* is a binary tree that uses a *comparator* function to have its entries (nodes) self-sorted. The algorithm is: 

*Whatever is smaller than root should be looked after on left child. Whatever is greater than root should be looked after on right child. Do so recursively until a match is found!*. 

Thanks to this algorithm if we populate a binary search tree with random entries we would achieve an acceptable O(log(N)) look-up time. What happens when we populate it with already sorted entries? In this case it keeps up populating right children until we end up with a big ugly linked list with linear O(N) look-up time. 

A *balanced search tree* solves above problem by having the tree balance itself on entry insertion/deletion, so depth searches (number of recursions until a match is found) are kept to a minimum. The ugly side of balancing is that it's very complicated to design and, regardless of solution chosen, any insertion/deletion requires potentially the whole tree being rebalanced (which is what makes this structure so slow compared to a hash table). The solution of choice for balancing a BST, employed by standard libraries of both Java and C++, is the Red Black Tree. 

### Implemented trees

Below classes provide specific implementations for selected types above:

- **RedBlackTree**: a balanced binary search tree using red-black principles, used internally as a foundation for structures that need to stay sorted (see TreeMap and TreeSet classes above), with algorithms based on *Introduction to Algorithms 3rd Edition by Thomas Cormen, Charles Leiserson & Ronald Rivest*.
	- Strengths:
		- makes structure self-sorted
		- acceptable performance on searches/inserts/deletes
		- small memory footprint: because nothing but node and color are saved
	- Weaknesses:
		- not usable for arbitrary (non self-sorted) structures
		- much slower than a hash table
- **Tree**: a basic n-ary tree with no children size bounds, used to store node hierarchies. Node operations are encapsulated by **TreeNode** class.
	- **NonUniqueTree**: extends **Tree**, allowing nodes with duplicate values
		- Strengths:
			- smallest memory footprint: because it uses nothing but 
			- very fast on insert/delete: because it's just setting a couple of local relationships
		- Weaknesses:
			- very slow on searches: because it requires scanning the whole tree hierarchy.
	- **UniqueTree**: extends **Tree** to prevent nodes with duplicate values by having nodes saved in a HashTable as well, to prevent duplicates and allow constant time access to any entry in tree.
		- Strengths:
			- very fast on insert/lookup/delete: because it's backed by a hash table
		- Weaknesses:
			- biggest memory footprint: because node locations duplicate in hash table

#### TreeNode

This class exposes following methods:
<table>
	<thead>
		<tr>
			<td><strong>Method</strong></td>
			<td><strong>Arguments</strong></td>
			<td><strong>Returns</strong></td>
			<td><strong>Complexity</strong></td>
			<td><strong>Description</strong></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>operator[]</td>
			<td>ARGUMENTS</td>
			<td>RETURNS</td>
			<td>COMPLEXITY</td>
			<td>Gets valut by position.</td>
		</tr>
	</tbody>
</table>
	TreeNode(const T& data)
	void setParent(TreeNode<T>* parent)
	TreeNode<T>*& getParent()
	void setData(const T& data)
	const T& getData() const
	const std::vector<TreeNode<T>*>& getChildren() const
	void addChild(TreeNode<T>*& node)
	void removeChild(TreeNode<T>*& node)
	void removeChildren()
	bool isDescendantOf(TreeNode<T>*& node)
	bool isAncestorOf(TreeNode<T>*& node) const
	TreeNode<T>* getRoot()
	std::vector<TreeNode<T>*> getAncestors()
	std::vector<TreeNode<T>*> getDescendants() const
	std::size_t getSize() const
	std::size_t getHeight() const
	std::size_t getDepth() const

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