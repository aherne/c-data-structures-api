Pure virtual methods of Container class:
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
			<td>clear</td>
			<td>&nbsp;</td>
			<td>void</td>
			<td>Clears container of all values.</td>
		</tr>
		<tr>
			<td>size</td>
			<td>&nbsp;</td>
			<td>const std::size_t&</td>
			<td>Gets container size</td>
		</tr>
		<tr>
			<td>isEmpty</td>
			<td>&nbsp;</td>
			<td>bool</td>
			<td>Checks if container is empty</td>
		</tr>
		<tr>
			<td>push</td>
			<td>const VALUE_TYPE&</td>
			<td>void</td>
			<td>Pushes value to head @ stack or tail @ queue.<br/>
			Throws <u>std::out_of_range</u> if container is bounded and exceeds limit.
			</td>
		</tr>
		<tr>
			<td>peek</td>
			<td>&nbsp;</td>
			<td>const VALUE_TYPE&</td>
			<td>Gets value in container head/tail.<br/>
			Throws <u>std::out_of_range</u> if container is empty.</td>
		</tr>
		<tr>
			<td>pop</td>
			<td>&nbsp;</td>
			<td>VALUE_TYPE</td>
			<td>Removes entry in container head @ stack or tail @ queue and returns its value.<br/>
			Throws <u>std::out_of_range</u> if container is empty.</td>
		</tr>
	</tbody>
</table>

O complexity of above methods by their implementation:
<table>
	<thead>
		<tr>
			<td>Operation</td>
			<td>Stack</td>
			<td>Queue</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>clear</td>
			<td>O(N)</td>
			<td>O(N)</td>
		</tr>
		<tr>
			<td>size</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>isEmpty</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>push</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>peek</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td>pop</td>
			<td>O(1)</td>
			<td>O(1)</td>
		</tr>
		<tr>
			<td colspan=3>
				<strong>Glossary:</strong><br/>
				N = number of elements in container
			</td>
		</tr>
	</tbody>
</table>

Constructors:

- both applied containers work primarily with a no-arg constructor
- both applied containers also support having a bounded capacity via constructor:
```c++
Stack(const std::size_t& capacity)
Queue(const std::size_t& capacity)
```
Iterators:

- by virtue of conception as black boxes whose contents only become available through push/pop, containers do not support iterators