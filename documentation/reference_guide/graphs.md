
Operations complexity @ graphs:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>Graph</td>
			<td>UniqueGraph</td>
			<td>WeightedGraph</td>
			<td>UniqueWeightedGraph</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>createVertex(T)</td>
			<td>O(1)</td>
			<td>O(2)</td>
			<td>O(1)</td>
			<td>O(2)</td>
			<td>Creates vertex in graph.</td>
		</tr>
		<tr>
			<td>removeVertex(V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Removes vertex from graph and deallocates.</td>
		</tr>
		<tr>
			<td>createEdge(V,V,B)</td>
			<td>O(1|2)</td>
			<td>O(1|2)</td>
			<td>O(1|2)</td>
			<td>O(1|2)</td>
			<td>Creates edge between vertexes.</td>
		</tr>
		<tr>
			<td>removeEdge(V,V,B)</td>
			<td>O(E|2E)</td>
			<td>O(E|2E)</td>
			<td>O(E|2E)</td>
			<td>O(E|2E)</td>
			<td>Removes edge between vertexes.</td>
		</tr>
		<tr>
			<td>getDistance(V,V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Gets number of vertexes in path between vertexes using BFS.</td>
		</tr>
		<tr>
			<td>getPath(V,V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Gets vertexes in path between vertexes using BFS.</td>
		</tr>
		<tr>
			<td>getSize()</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Gets number of vertexes in graph.</td>
		</tr>
		<tr>
			<td>getWeight(V,V)</td>
			<td>-</td>
			<td>-</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>Gets weight of direct edge between vertexes.</td>
		</tr>
		<tr>
			<td>isEdge(V,V)</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>O(E)</td>
			<td>Checks if there is a direct edge between vertexes.</td>
		</tr>
		<tr>
			<td>isPath(V,V)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Checks if there is a path between vertexes using BFS.</td>
		</tr>
		<tr>
			<td>iterate(V,Z)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Iterates vertex's descendant tree using BFS.</td>
		</tr>
		<tr>
			<td>iterate(Z)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>O(V*E)</td>
			<td>Iterates all vertexes in graph.</td>
		</tr>
		<tr>
			<td>removeVertex(T,C?)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Removes vertex from graph and deallocates.</td>
		</tr>
		<tr>
			<td>contains(T,C?)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Checks if graph contains vertex value.</td>
		</tr>
		<tr>
			<td>search(T,C?)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>O(V*E)</td>
			<td>O(1)</td>
			<td>Searches vertexes by their value.</td>
		</tr>
		<tr>
			<td colspan=5>
				<strong>Glossary:</strong><br/>
				T = value<br/>
				V = vertex<br/>
				E = edge<br/>
				C = comparator (?: not needed when vertexes are guaranteed to hold unique values)<br/>
				B = whether or not operation should be bidirectional<br/>
				Z = vertex visitor to use during iteration<br/>
				N = number of nodes in tree<br/>
			</td>
		</tr>
	</tbody>
</table>