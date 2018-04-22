## Trees

Trees are non-sequential data structures in which:

- every entry is a node that has links to:
	- a single parent node (unless it's root)
	- a number of child nodes (if any)
- there is a single root node all others descend from directly or indirectly. This node is the only entry that has a nil parent.
- by following child nodes recursively, no node should be able to reach itself (it should be acyclic)
- there must be a single path from one node to another (no reference is duplicated)

### Abstract Trees

One of the reasons why no programming language comes with an official implementation for trees (eg: there is no STL for trees!) is that their operations demand exposure of internal elements (nodes), which fails the RAII principle. Another reason is that, unlike sequential data structures, trees are irreducible to a common ground: each type of tree chosen reflects a very different need, requiring fundamentally different operations. Because of reasons above, there should not be any abstract Tree class and trees should only exist as implementations.

### Implemented trees

Out of the sheer variety of trees available, only most common ones were chosen to be implemented: 

- **Tree**: a generic (*n-ary*) tree used to store node hierarchies. Nodes and their operations are encapsulated by **TreeNode** class.
	- **NonUniqueTree**: extends **Tree**, allowing nodes with duplicate values
		- Strengths:
			- smallest memory footprint: because it holds nothing but nodes themselves
			- very fast on insert/delete: because it's just setting a couple of local relationships
		- Weaknesses:
			- very slow on searches: because it requires scanning the whole tree hierarchy.
	- **UniqueTree**: extends **Tree** to prevent nodes with duplicate values by having nodes saved in a HashTable as well, to prevent duplicates and allow constant time access to any entry in tree.
		- Strengths:
			- very fast on insert/lookup/delete: because it's backed by a hash table
		- Weaknesses:
			- biggest memory footprint: because node locations duplicate in hash table
- **RedBlackTree**: a special *balanced binary search*  tree using red-black principles, used internally as a foundation for structures that need to stay sorted (see TreeMap and TreeSet classes above) and algorithms based on *Introduction to Algorithms 3rd Edition by Thomas Cormen, Charles Leiserson & Ronald Rivest*.
	- Strengths:
		- makes structure self-sorted
		- acceptable performance on searches/inserts/deletes
		- small memory footprint: because nothing but node and color are saved
	- Weaknesses:
		- not usable for arbitrary (non self-sorted) structures
		- much slower than a hash table
		
#### N-ary trees

An n-ary tree is one without any restrictions, except those all trees by definition must obey to. In common practice, they are just used to store hierarchical un-ordered data.

Class **TreeNode** encapsulates a node in an n-ary tree and exposes following methods:
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
			<td>TreeNode</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Constructs a node by value.</td>
		</tr>
		<tr>
			<td>setParent</td>
			<td>NODE</td>
			<td>void</td>
			<td>Sets parent of node (overrides if needed).</td>
		</tr>
		<tr>
			<td>getParent</td>
			<td></td>
			<td>NODE&</td>
			<td>Gets parent of node reference.</td>
		</tr>
		<tr>
			<td>setData</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Overrides value stored in node.</td>
		</tr>
		<tr>
			<td>getData const</td>
			<td></td>
			<td>VALUE</td>
			<td>Gets value stored in node.</td>
		</tr>
		<tr>
			<td>getChildren</td>
			<td></td>
			<td>std::vector&lt;NODE&gt;&</td>
			<td>Gets all node children.</td>
		</tr>
		<tr>
			<td>addChild</td>
			<td>NODE&</td>
			<td>void</td>
			<td>Adds node child.</td>
		</tr>
		<tr>
			<td>removeChild</td>
			<td>NODE&</td>
			<td>void</td>
			<td>Removes node child.</td>
		</tr>
		<tr>
			<td>removeChildren</td>
			<td></td>
			<td>void</td>
			<td>Removes all node children.</td>
		</tr>
		<tr>
			<td>isDescendantOf</td>
			<td>NODE&</td>
			<td>bool</td>
			<td>Traverses node's parents recursively and checks if one of them matches node inputted.</td>
		</tr>
		<tr>
			<td>isAncestorOf</td>
			<td>NODE&</td>
			<td>bool</td>
			<td>Traverses node's children recursively and checks if one of them matches node inputted.</td>
		</tr>
		<tr>
			<td>getRoot</td>
			<td></td>
			<td>NODE</td>
			<td>Traverses node's parents recursively and returns root node.</td>
		</tr>
		<tr>
			<td>getAncestors</td>
			<td></td>
			<td>std::vector&lt;NODE&gt;</td>
			<td>Traverses node's parents recursively and returns them as list.</td>
		</tr>
		<tr>
			<td>getDescendants</td>
			<td></td>
			<td>std::vector&lt;NODE&gt;</td>
			<td>Traverses node's children recursively and returns them as list.</td>
		</tr>
		<tr>
			<td>getSize</td>
			<td></td>
			<td>std::size_t</td>
			<td>Traverses node's children recursively and returns their total number.</td>
		</tr>
		<tr>
			<td>getHeight</td>
			<td></td>
			<td>std::size_t</td>
			<td>Traverses node's children recursively and returns their maximum depth.</td>
		</tr>
		<tr>
			<td>getDepth</td>
			<td></td>
			<td>std::size_t</td>
			<td>Traverses node's parents recursively and returns their number.</td>
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
						<td>NODE</td>
						<td>TreeNode&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

Class **Tree** encapsulates a generic n-ary tree that employs nodes encapsulated by **TreeNode** and exposes following methods:

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
			<td>Tree</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Constructs root node by value.</td>
		</tr>
		<tr>
			<td>createNode</td>
			<td>VALUE, NODE&</td>
			<td>NODE</td>
			<td>Constructs node by value, makes it child of input parent node, then returns it</td>
		</tr>
		<tr>
			<td>getRoot</td>
			<td></td>
			<td>NODE</td>
			<td>Gets tree root node.</td>
		</tr>
		<tr>
			<td>getHeight</td>
			<td></td>
			<td>std::size_t</td>
			<td>Gets maximum number of branches in tree.</td>
		</tr>
		<tr>
			<td>getSize</td>
			<td></td>
			<td>std::size_t</td>
			<td>Gets total number of nodes in tree.</td>
		</tr>
		<tr>
			<td>removeNode</td>
			<td>NODE&</td>
			<td>void</td>
			<td>Destructs input node and moves all its former children to former parent.</td>
		</tr>
		<tr>
			<td>removeBranch</td>
			<td>NODE&</td>
			<td>void</td>
			<td>Destructs input node and its children recursively.</td>
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
						<td>NODE</td>
						<td>TreeNode&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

Class **NonUniqueTree** extends **Tree** and encapsulates an n-ary tree that makes no guarantee of **TreeNode** data's uniqueness, exposing following extra public methods:
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
			<td>contains</td>
			<td>VALUE, COMPARATOR</td>
			<td>bool</td>
			<td>Traverses tree recursively and checks via comparator if at least one node's data matches the one inputted.</td>
		</tr>
		<tr>
			<td>search</td>
			<td>VALUE, COMPARATOR</td>
			<td>std::vector&lt;NODE&gt;</td>
			<td>Traverses tree recursively and returns all nodes whose data matches via comparator the one inputted.</td>
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
						<td>COMPARATOR</td>
						<td>int (comparator*) (const VALUE_TYPE&, const VALUE_TYPE&)</td>
					</tr>
					<tr>
						<td>NODE</td>
						<td>TreeNode&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

Class **UniqueTree** extends **Tree** and encapsulates an n-ary tree that makes guarantees **TreeNode** data's uniqueness via an internal **HashTable**. Every read/write operation will reflect into that HashTable as well, which makes this structure very fast on random searches but slower on insertion/deletion. It overrides Tree class' methods related to creation/deletion to reflect into HashTable and exposes following extra public methods:

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
			<td>removeNode</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Queries internal HashTable if it contains a TreeNode with that value, then removes it from both HashTable and Tree.</td>
		</tr>
		<tr>
			<td>removeBranch</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Queries internal HashTable if it contains a TreeNode with that value, then removes it from both HashTable and Tree, as well as its children recursively.</td>
		</tr>
		<tr>
			<td>contains</td>
			<td>VALUE</td>
			<td>bool</td>
			<td>Queries internal HashTable if it contains a TreeNode with that value.</td>
		</tr>
		<tr>
			<td>search</td>
			<td>VALUE</td>
			<td>NODE|nullptr</td>
			<td>Queries internal HashTable and returns TreeNode with that value.</td>
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
						<td>NODE</td>
						<td>TreeNode&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

^ Note that unlike **NonUniqueTree**, above methods do not include a COMPARATOR. This is because HashTable will *implicitly* use COMPARATOR and HASHER functions for VALUE stored by NODE! By default, API provides them only for char* and long, so if you're using any other type but string or numeric you MUST add your own comparator & hasher. Lacking one will result into undefined behavior!

In order to better see the advantages and disadvantages of each n-ary tree solution, please consult below table that shows O complexity of **Tree** methods:

<table>
	<thead>
		<tr>
			<td><strong>Method</strong></td>
			<td><strong>NonUniqueTree</strong></td>
			<td><strong>UniqueTree</strong></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>Tree</td>
			<td>O(1)</td>
			<td>O(2)</td>
		</tr>
		<tr>
			<td>createNode</td>
			<td>O(1)</td>
			<td>O(3)</td>
		</tr>
		<tr>
			<td>getRoot</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>getHeight</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>getSize</td>
			<td>O(N)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>removeNode</td>
			<td>O(N*2)</td>
			<td>O(N*3)</td>
		</tr>
		<tr>
			<td>removeBranch</td>
			<td>O(N*2)</td>
			<td>O(N*3)</td>
		</tr>
		<tr>
			<td>contains</td>
			<td>O(N)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>search</td>
			<td>O(N)</td>
			<td>O(2)</td>
		</tr>
		<tr>
			<td colspan=4>
				<strong>Glossary:</strong><br/>
				N = number of nodes in tree<br/>
			</td>
		</tr>
	</tbody>
</table>

##### Constructors

All n-ary trees require a single argument constructor (necessary to create root node):
```c++
Tree(const VALUE_TYPE& value)
```

##### Templates

All n-ary trees have a single template argument:  
```c++
template<typename VALUE_TYPE>
```

##### Iterators

Because structure is not RAII compliant, no standalone iterator was defined for **Tree** or its derived classes. In order to iterate a tree, you just need to get node to start from (eg: getRoot) then use its **TreeNode** dedicated methods for recursively navigating through children (eg: getChildren) or parents (eg: getParent). 
 
#### Balanced binary search trees

A **binary tree** (aka BT) is one where a node can have only max two children. In common practice, they are mostly used as a structural basis (in balanced search form) behind sequential data structures (maps and sets) whose entries need to remain sorted.

A **binary search tree** (aka BST) is a binary tree that uses a *comparator* function to have its entries (nodes) self-sorted. The algorithm is: *Whatever is smaller than root should be looked after on left child. Whatever is greater than root should be looked after on right child. Do so recursively until a match is found!*. Thanks to this algorithm if we populate a binary search tree with random entries we would achieve an acceptable O(log(N)) look-up time. What happens when we populate it with already sorted entries? In this case it keeps up populating right children until we end up with a big ugly linked list with linear O(N) look-up time. 

A **balanced binary search tree** (aka BBST) solves above problem by having the tree balance itself on entry insertion/deletion, so depth searches (number of recursions until a match is found) are kept to a minimum. The ugly side of balancing is that it's very complicated to design and, regardless of solution chosen, any insertion/deletion requires potentially the whole tree being rebalanced (which is what makes this structure so slow compared to a hash table). The solution of choice for balancing a search tree, employed by standard libraries of both Java and C++, is the Red Black Tree.

The **red-black tree** (aka RBT) is a type of search tree using an ingenious algorithm for balancing too complex to be described here (search on Wiki for more info), so complex in fact that all implementations (including mine) just transliterate recipes from *Introduction to Algorithms by Thomas Cormen, Charles Leiserson & Ronald Rivest*.

Class **RedBlackTree** is a transliteration of *Introduction to Algorithms 3rd edition* recipes described above working with nodes of **RedBlackTreeNode** type, themselves also following same recipe.

**RedBlackTreeNode** is a struct encapsulating RBT nodes via following (public by default) members:

<table>
	<thead>
		<tr>
			<td><strong>Name</strong></td>
			<td><strong>Type</strong></td>
			<td><strong>Description</strong></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>data</td>
			<td>VALUE</td>
			<td>Data node is storing (general tree requirement).</td>
		</tr>
		<tr>
			<td>left</td>
			<td>NODE</td>
			<td>Child node whose value is smaller or equal than parent's (BST requirement)</td>
		</tr>
		<tr>
			<td>right</td>
			<td>NODE</td>
			<td>Child node whose value is greater than parent's (BST requirement)</td>
		</tr>
		<tr>
			<td>parent</td>
			<td>NODE|nullptr</td>
			<td>Node's parent, to be used in balancing (BBST requirement).</td>
		</tr>
		<tr>
			<td>color</td>
			<td>COLOR</td>
			<td>Node's "color", to be used in balancing (RBT requirement).</td>
		</tr>
		<tr>
			<td colspan=3>
				<strong>Signatures:</strong>
				<table>
					<tr>
						<td>VALUE</td>
						<td>const VALUE_TYPE&</td>
					</tr>
					<tr>
						<td>NODE</td>
						<td>RedBlackTreeNode&lt;VALUE_TYPE&gt;*</td>
					</tr>
					<tr>
						<td>COLOR</td>
						<td>enum{RED,BLACK}</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

**RedBlackTree** encapsulates RBT operations via following public methods:
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
			<td>insertNode</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Inserts node by its value into tree (may rebalance)</td>
		</tr>
		<tr>
			<td>hasNode</td>
			<td>VALUE</td>
			<td>bool</td>
			<td>Checks if tree contains a node by that value</td>
		</tr>
		<tr>
			<td>hasMatches</td>
			<td>VALUE, COMPARATOR</td>
			<td>bool</td>
			<td>Checks via comparator if tree contains a node by that value</td>
		</tr>
		<tr>
			<td>deleteNode</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Deletes node by its value from  tree (may rebalance)</td>
		</tr>
		<tr>
			<td>deleteMatches</td>
			<td>VALUE, COMPARATOR</td>
			<td>void</td>
			<td>Deletes all nodes matching value via comparator (may rebalance).</td>
		</tr>
		<tr>
			<td>getNextNode</td>
			<td>NODE</td>
			<td>NODE</td>
			<td>Gets node adjacent to one inputted (important in rebalancing).</td>
		</tr>
		<tr>
			<td>getNodeValue</td>
			<td>VALUE</td>
			<td>VALUE_PTR</td>
			<td>Gets node matching value and returns a reference to node's value (HashTable requirement).<br/>Throws <u>std::out_of_range</u> if value not found.</td>
		</tr>
		<tr>
			<td>getSize</td>
			<td></td>
			<td>std::size_t</td>
			<td>Gets number of nodes in tree.</td>
		</tr>
		<tr>
			<td>min</td>
			<td></td>
			<td>NODE</td>
			<td>Gets node with smallest value in tree (important in rebalancing).</td>
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
						<td>VALUE_PTR</td>
						<td>const VALUE_TYPE*</td>
					</tr>
					<tr>
						<td>NODE</td>
						<td>RedBlackTreeNode&lt;VALUE_TYPE&gt;*</td>
					</tr>
					<tr>
						<td>COMPARATOR</td>
						<td>int (comparator*) (const VALUE_TYPE&, const VALUE_TYPE&)</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

^ Although RBT can be used independently, in practice it's only useful behind the scenes in self-sorted maps/sets (our TreeMap, TreeSet). The end result are structures where insertion/deletion/searching are performed with LOG(N) complexity.

##### Constructors

RBT uses a no-arg constructor.

##### Templates

RBT requires two template arguments:  
```c++
template<typename VALUE_TYPE, int (*compare)(const VALUE_TYPE&,const VALUE_TYPE&)>
```

##### Iterators

Because structure is not RAII compliant, no standalone iterator was defined for RBT. Like in n-ary trees, RBT nodes can be iterated by themselves by navigating through parent & children.