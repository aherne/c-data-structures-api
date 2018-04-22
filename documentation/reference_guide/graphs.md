## Graphs

Graphs are non-sequential data structures in which:

- every entry is a node (aka VERTEX) that may have links (aka EDGES) to another node 
- links can be directed (if A->B it doesn't mean B->A) or undirected (if A->B, then B->A)
- links can hold weights (eg: roads between NY->LA, LA->SF, each holding different weights expressed in miles)
- there can be multiple paths between two nodes (eg: multiple road alternatives from NY-LA)
- not all nodes have to be connected 
- nodes can connect to themselves

### Abstract Graphs

Because they are structures without any rules other than being composed of linked nodes, there is an infinite variety of graph types, each with its own set of rules tailored to solve a particular problem. The very fact structures as apparently different as linked lists, queues, stacks or trees all qualify as undirected graphs makes it obvious that no generic implementation will fit all needs. 



### Implemented graphs

For graphs that just behave like graphs and set no further rules other than those in graph theory, I've implemented following classes:

- **Graph**: a directed graph where *edges have no weights*. Makes no implementation assumptions, so it remains pure virtual. Its vertexes, encapsulated by **GraphVertex** class, are able to be traversed by **GraphVertexVisitor** class
	- **NonUniqueGraph**: a **Graph** implementation allowing vertexes with duplicate values, storing vertexes in a *std::vector* structure.
		- Strengths:
			- small memory footprint: because it uses nothing but vertexes themselves inside a self-expandable memory block
			- very fast on insert: because it just adds vertex to bottom of memory block
		- Weaknesses:
			- very slow on search: because it potentially needs to traverse the whole memory block to find matching vertexes
			- very very slow on delete: because, apart of searching costs, it also needs to pad the whole memory block once matching vertexes are deleted
	- **UniqueGraph**: a **Graph** implementation storing its vertexes in a **HashTable**, which insures their value uniqueness.
		- Strengths: 
			- relatively fast on insert: because it just adds vertex to internal hash table
			- relatively fast on search: because it just asks hashtable underneath to retrieve vertex matching value
		- Weaknesses:
			- heavy memory footprint: because it needs to maintain a hash table underneath.
			- for VALUE_TYPE vertex holds, developers MUST implement matching *comparator* and *hash* functions and load them before.
			- slow on delete: apart of inherently slow graph vertex removal requirements (traversing the entire graph to make sure no edges start from / point to vertex to be deleted), it just needs to delete from hashtable
- **WeightedGraph**: a directed graph where *edges have weights*. Makes no implementation assumptions, so it remains pure virtual. Its vertexes, encapsulated by **WeightedGraphVertex** class, and edges, encapsulated by **WeightedGraphEdge** struct, are able to be traversed by **WeightedGraphVertexVisitor** class
	- **NonUniqueWeightedGraph**: a **WeightedGraph** implementation allowing vertexes with duplicate values, storing vertexes in a *std::vector* structure. Same strength and weaknesses as **NonUniqueGraph** above, only with higher memory consumption because edges weights need to be stored as well.
	- **UniqueWeightedGraph**: a **WeightedGraph** implementation storing its vertexes in a **HashTable**, which insures their value uniqueness. Same strength and weaknesses as **UniqueGraph** above, only with higher memory consumption because edges weights need to be stored as well.

#### Graph

Class **Graph**, holding blueprints of unweighted graph operations, defines following pure virtual methods:

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
			<td>createVertex</td>
			<td>VALUE</td>
			<td>VERTEX</td>
			<td>Creates a vertex (node) in graph and returns it</td>
		</tr>
		<tr>
			<td>removeVertex</td>
			<td>VERTEX</td>
			<td>void</td>
			<td>Removes vertex from graph.</td>
		</tr>
		<tr>
			<td>getSize</td>
			<td></td>
			<td>std::size_t</td>
			<td>Gets number of vertexes in graph.</td>
		</tr>
		<tr>
			<td>isPath</td>
			<td>VERTEX, VERTEX</td>
			<td>bool</td>
			<td>Checks if a path of edges exists between two vertexes in graph.</td>
		</tr>
		<tr>
			<td>getDistance</td>
			<td>VERTEX, VERTEX</td>
			<td>std::size_t</td>
			<td>Gets minimal number of edges between two vertexes in graph.<br/>Throws std::out_of_range if vertexes are not connected.</td>
		</tr>
		<tr>
			<td>getPath</td>
			<td>VERTEX, VERTEX</td>
			<td>std::vector&lt;VERTEX&gt;</td>
			<td>Gets shortest vertex path between two vertexes in graph.<br/>Throws std::out_of_range if vertexes are not connected.</td>
		</tr>
		<tr>
			<td>iterate</td>
			<td>VISITOR</td>
			<td>void</td>
			<td>Traverses all vertexes in graph using VISITOR of choise.</td>
		</tr>
		<tr>
			<td>iterate</td>
			<td>VERTEX, VISITOR</td>
			<td>void</td>
			<td>Traverses all vertexes in graph connected to input vertex using VISITOR of choice.</td>
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
						<td>VERTEX</td>
						<td>GraphVertex&lt;VALUE_TYPE&gt;*</td>
					</tr>
					<tr>
						<td>VISITOR</td>
						<td>GraphVertexVisitor&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

Vertexes and their operations are encapsulated by **GraphVertex** class defining following methods:

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
			<td>GraphVertex</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Constructs a vertex using input value</td>
		</tr>
		<tr>
			<td>addEdge</td>
			<td>VERTEX</td>
			<td>void</td>
			<td>Creates an edge between current vertex and the one inputed.</td>
		</tr>
		<tr>
			<td>getEdges</td>
			<td></td>
			<td>EDGES</td>
			<td>Gets all edges that start from current vertex.</td>
		</tr>
		<tr>
			<td>isEdge</td>
			<td>VERTEX</td>
			<td>bool</td>
			<td>Checks if there is an edge between current vertex and the one inputed.</td>
		</tr>
		<tr>
			<td>removeEdge</td>
			<td>VERTEX</td>
			<td>void</td>
			<td>Removes edge between current vertex and the one inputed.</td>
		</tr>
		<tr>
			<td>setData</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Overrides vertex value with the one inputed.</td>
		</tr>
		<tr>
			<td>getData</td>
			<td></td>
			<td>VALUE</td>
			<td>Gets vertex data.</td>
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
						<td>VERTEX</td>
						<td>GraphVertex&lt;VALUE_TYPE&gt;*</td>
					</tr>
					<tr>
						<td>EDGES</td>
						<td>const std::vector&lt;GraphVertex&lt;VALUE_TYPE&gt;*&gt;&</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>
		
Traversal and its operations is encapsulated by abstract **GraphVertexVisitor** class which defines just a single pure virtual method:

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
			<td>visit</td>
			<td>GraphVertex&lt;VALUE_TYPE&gt;* const&</td>
			<td>void</td>
			<td>Visits a vertex during traversal.</td>
		</tr>
	</tbody>
</table>

^ Since there are multiple ways to traverse a graph, above class only defines a blueprint instead of an implementation. It is in developers' responsibility to implement a visitor on this pattern suiting product needs. 

Class **NonUniqueGraph** extends **Graph** and encapsulates a unweighted graph that makes no guarantee of **GraphVertex** data's uniqueness, stores vertexes in a dynamic array and uses *Breadth First Search* algorithm for traversal. Apart of implementing parent's pure virtual methods, it also adds following extra public methods:
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
			<td>Loops through internal dynamic array and checks via input comparator if a vertex data matches input value.</td>
		</tr>
		<tr>
			<td>search</td>
			<td>VALUE, COMPARATOR</td>
			<td>std::vector&lt;VERTEX&gt;</td>
			<td>Traverses graph using BFS algorithm and returns list of vertexes whose data matches input value via input comparator.</td>
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
						<td>VERTEX</td>
						<td>GraphVertex&lt;VALUE_TYPE&gt;*</td>
					</tr>
					<tr>
						<td>COMPARATOR</td>
						<td>int (comparator*) (const VALUE_TYPE&, const VALUE_TYPE&)</td>
					</tr>
				</table>
			</td>
		</tr>
</table>
		
Class **UniqueGraph** extends **Graph** and encapsulates a unweighted graph that guarantees **GraphVertex** data's uniqueness, stores vertexes in a HashTable and uses a customized *Breadth First Search* algorithm for traversal. Apart of implementing parent's pure virtual methods, it also adds following extra public methods:
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
			<td>VALUE</td>
			<td>bool</td>
			<td>Checks if internal hash table contains a vertex whose data matches input value.</td>
		</tr>
		<tr>
			<td>search</td>
			<td>VALUE</td>
			<td>VERTEX</td>
			<td>Returns vertex from internal hash table whose data matches input value. If none found, *nullptr* is returned.</td>
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
						<td>VERTEX</td>
						<td>GraphVertex&lt;VALUE_TYPE&gt;*</td>
					</tr>
				</table>
			</td>
		</tr>
</table>

^ Notice that, unlike extra methods by same name in NonUniqueGraph, no comparator is supplied! This is because HashTable inside assumes you already created and loaded int (comparator*) (const VALUE_TYPE&, const VALUE_TYPE&) and a std::size_t hash(const VALUE_TYPE&) functions beforehand. Failure to do so will result into undefined behavior!

#### WeightedGraph

Classes **WeightedGraph**, **WeightedGraphVisitor**, **NonUniqueWeightedGraph**, **UniqueWeightedGraph** have identical structure to **Graph**, **GraphVisitor**, **NonUniqueGraph**, **UniqueGraph**, only that they are working with **WeightedGraphVertex** objects. I've opted to implement them separately instead of templating the differences because that would have added great difficulty to whoever wants to use them.

Class **WeightedGraphVertex** differs fundamentally from **GraphVertex** by having edges encapsulated by **WeightedGraphEdge** struct. It thus defines following public methods:

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
			<td>WeightedGraphVertex</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Constructs a vertex using input value</td>
		</tr>
		<tr>
			<td>addEdge</td>
			<td>VERTEX, WEIGHT</td>
			<td>void</td>
			<td>Creates an edge between current vertex and the one inputed.</td>
		</tr>
		<tr>
			<td>getEdges</td>
			<td></td>
			<td>EDGES</td>
			<td>Gets all edges that start from current vertex.</td>
		</tr>
		<tr>
			<td>isEdge</td>
			<td>VERTEX</td>
			<td>bool</td>
			<td>Checks if there is an edge between current vertex and the one inputed.</td>
		</tr>
		<tr>
			<td>removeEdge</td>
			<td>VERTEX</td>
			<td>void</td>
			<td>Removes edge between current vertex and the one inputed.</td>
		</tr>
		<tr>
			<td>setData</td>
			<td>VALUE</td>
			<td>void</td>
			<td>Overrides vertex value with the one inputed.</td>
		</tr>
		<tr>
			<td>getData</td>
			<td></td>
			<td>VALUE</td>
			<td>Gets vertex data.</td>
		</tr>
		<tr>
			<td>getEdgeWeight</td>
			<td>VERTEX</td>
			<td>WEIGHT</td>
			<td>Gets weight of edge between current vertex and the one inputed.</td>
		</tr>
		<tr>
			<td>setEdgeWeight</td>
			<td>VERTEX, WEIGHT</td>
			<td>void</td>
			<td>Sets weight of edge between current vertex and the one inputed.</td>
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
						<td>WEIGHT</td>
						<td>const WEIGHT_TYPE&</td>
					</tr>
					<tr>
						<td>VERTEX</td>
						<td>WeightedGraphVertex&lt;VALUE_TYPE, WEIGHT_TYPE&gt;*</td>
					</tr>
					<tr>
						<td>EDGES</td>
						<td>const std::vector&lt;WeightedGraphEdge&lt;VALUE_TYPE, WEIGHT_TYPE&gt;*&gt;&</td>
					</tr>
				</table>
			</td>
		</tr>
	</tbody>
</table>

Struct **WeightedGraphEdge** encapsulates, as its name suggests, a weighted graph's edge and thus defines following public fields:

<table>
	<thead>
		<tr>
			<td><strong>Field</strong></td>
			<td><strong>Type</strong></td>
			<td><strong>Description</strong></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>vertex</td>
			<td>WeightedGraphVertex&lt;VALUE_TYPE, WEIGHT_TYPE&gt;*</td>
			<td>Vertex edge points to</td>
		</tr>
		<tr>
			<td>weight</td>
			<td>const WEIGHT_TYPE&</td>
			<td>Weight of edge vertex points to</td>
		</tr>
	</tbody>
</table>

Classes **WeightedGraphVisitor**, **NonUniqueWeightedGraph**, **UniqueWeightedGraph** have identical structure to **GraphVisitor**, **NonUniqueGraph**, **UniqueGraph**, only that they are working with **WeightedGraphVertex** objects. 
	
### Constructors

All implemented graphs (weighted or not) use a no-arg constructor.

### Templates

All classes related to **Graph** require a single template argument:  
```c++
template<typename VALUE_TYPE, typename WEIGTH_TYPE>
```

All classes related to **WeightedGraph** require two template arguments:
```c++
template<typename VALUE_TYPE, typename WEIGTH_TYPE>
```

### Iterators

Because structure is not RAII compliant, no standalone iterator was defined. In order to iterate, it is sufficient to search for a vertex, then apply graph traversal algorithms from that point on. 

### Operations complexity
In order to better illustrate the advantages and disadvantages of each graph solution, please consult below table that shows O complexity of each graph class methods described above:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>NonUniqueGraph</td>
			<td>UniqueGraph</td>
			<td>NonUniqueWeightedGraph</td>
			<td>UniqueWeightedGraph</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>createVertex</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>removeVertex</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
		</tr>
		<tr>
			<td>getDistance</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
		</tr>
		<tr>
			<td>getPath</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
		</tr>
		<tr>
			<td>isPath</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
		</tr>
		<tr>
			<td>getSize</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>iterate</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
			<td>O(V+E)</td>
		</tr>
		<tr>
			<td>contains</td>
			<td>O(V+E)</td>
			<td>O(1)</td>
			<td>O(V+E)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>search</td>
			<td>O(V+E)</td>
			<td>O(1)</td>
			<td>O(V+E)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				V = number of vertexes<br/>
				E = number of edges<br/>
			</td>
		</tr>
	</tbody>
</table>