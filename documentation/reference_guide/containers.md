## Containers

Containers are "black box" data structures in which:

- only push & pull operations are supported
- insertion, access and deletion is done only on head or tail
- size can be bounded, in which case an exception will be thrown if data inserted is out of bounds
- no iteration is supported

### Abstract containers

Abstract containers implement blueprints for operations one can perform on a container. This is done via methods of **Container** class, which defines following pure virtual methods:
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
			<td>Gets value in container head @ stack or tail @ queue.<br/>
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

### Implemented containers

Implemented containers are classes that extend **Container** class and provide specific implementations for methods above:

- **Stack**: implements a LIFO container that wraps an inverted dynamic array in order to push entry to head and pull entry from head. Entries are stored in a continuous block of memory that grows (via *realloc*)  by doubling its capacity whenever latter is reached. As an *inverted* dynamic array, even though internally push & removal are done to tail (to insure  operations run in constant time), exposed operations make it appear like a stack. 
- **Queue**: implements a FIFO container that wraps a double-ended dynamic array in order to push entry to tail and pull entry from head. As a *double-ended* dynamic array, it has two additional internal coordinates that contract or expand as data is pulled or pushed so that both operations run in constant time. When dynamic array that wraps queue reaches capacity, growth always involves moving data to a new expanded memory block and resetting coordinates (which makes queues slower than stacks)

Because of above considerations, O complexity of **Container** methods varies by implementation:
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

#### Constructors

All containers work primarily with a no-arg constructor. They also support having a bounded capacity:
```c++
Stack(const std::size_t& capacity)
Queue(const std::size_t& capacity)
```

A stack with bounded capacity will have a fixed size (so it won't regrow). When it reaches capacity, any new insertion will result into an std::out_of_bounds exception thrown.

A queue with bounded capacity will also have a fixed size. When it reaches capacity, any new insertion will result into a regrowth on same capacity (if dynamic array inside contains popped entries) or a std::out_of_bounds exception (otherwise).