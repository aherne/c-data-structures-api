Methodology:

1. functions used for benchmarking can be reviewed in src/Benchmark.h and only work on UNIX systems
2. benchmarks themselves can be found in src/Benchmarks folder and can be ran by uncommenting respective lines in src/Test.cpp (Eg: ListBenchmark)
3. for maximum reliability, each benchmark for each data structure implementation has been ran individually in three rows, commenting all others.
4. results are done by compiling results of three rows of tests on each structure implementation
5. tests were ran using O2 compiler optimization on an Intel(R) Core(TM) i5-2500K CPU & 8GB RAM running on Ubuntu 16

###Lists###

Test case:

1. checking memory allocated by a list containing a million entries
2. checking duration of a million rows insertion on list's bottom
3. checking duration of iterating all list from top to bottom
4. checking duration of getting all list element values by offset from top to bottom
5. removing all list elements based on offset from bottom to top (for dynamic arrays) and top to bottom (for [doubly-]linked lists)

Results:

<table>
<tr><td>Implementation</td><td>Data Structure</td><td>Value Type</td><td>Memory (kb)</td><td>Insertion (ms)</td><td>Iteration (ms)</td><td>Selection (ms)</td><td>Deletion (ms)</td></tr>
<tr><td>std::vector</td><td>dynamic array</td><td>long</td><td>7816</td><td>4</td><td>0</td><td>0</td><td>1</td></tr>
<tr><td>ArrayList</td><td>dynamic array</td><td>long</td><td>7816</td><td>3</td><td>0</td><td>0</td><td>1</td></tr>
<tr><td>std::vector</td><td>dynamic array</td><td>char*</td><td>7816</td><td>3</td><td>0</td><td>1</td><td>1</td></tr>
<tr><td>ArrayList</td><td>dynamic array</td><td>char*</td><td>7816</td><td>2</td><td>0</td><td>0</td><td>0</td></tr>
<tr><td>std::forward_list</td><td>linked list</td><td>long</td><td>31152</td><td>30</td><td>5</td><td>5</td><td>14</td></tr>
<tr><td>LinkedList</td><td>linked list</td><td>long</td><td>31152</td><td>30</td><td>0</td><td>0</td><td>14</td></tr>
<tr><td>std::forward_list</td><td>linked list</td><td>char*</td><td>31152</td><td>31</td><td>6</td><td>6</td><td>15</td></tr>
<tr><td>LinkedList</td><td>linked list</td><td>char*</td><td>31152</td><td>30</td><td>0</td><td>0</td><td>15</td></tr>
<tr><td>std::list</td><td>doubly linked list</td><td>long</td><td>31152</td><td>35</td><td>5</td><td>5</td><td>17</td></tr>
<tr><td>DoublyLinkedList</td><td>doubly linked list</td><td>long</td><td>31152</td><td>31</td><td>0</td><td>5</td><td>17</td></tr>
<tr><td>std::list</td><td>doubly linked list</td><td>char*</td><td>31152</td><td>32</td><td>5</td><td>5</td><td>16</td></tr>
<tr><td>DoublyLinkedList</td><td>doubly linked list</td><td>char*</td><td>31152</td><td>32</td><td>0</td><td>7</td><td>17</td></tr>
</table>

Graphic: {TODO}

Several notes:

1. tests for dynamic array implementations use reserved size of one million plus one. The reason is that each implementation has its own growth point (A grows at point V, while B grows at point Z>V: if we stop insertion between V and Z, A will appear slower because it has done one more reallocation)
2. despite different programming behind, memory usage between STL and CDS is always the same and only varies by data structure.

###Maps###

Test case:

1. checking memory allocated by a map containing a million entries
2. checking duration of a million rows insertion
3. checking duration of iterating all map
4. checking duration of getting all map entry values by key
5. removing all map entries based on key

Results:

<table>
<tr><td>Implementation</td><td>Data Structure</td><td>Key type</td><td>Value type</td><td>Memory (kb)</td><td>Insertion (ms)</td><td>Iteration (ms)</td><td>Selection (ms)</td><td>Deletion (ms)</td></tr>
<tr><td>std::map</td><td>red black tree</td><td>long</td><td>long</td><td>62436</td><td>320</td><td>17</td><td>172</td><td>141</td></tr>
<tr><td>TreeMap</td><td>red black tree</td><td>long</td><td>long</td><td>62436</td><td>314</td><td>14</td><td>148</td><td>124</td></tr>
<tr><td>std::map</td><td>red black tree</td><td>char*</td><td>char*</td><td>62568</td><td>277</td><td>21</td><td>181</td><td>216</td></tr>
<tr><td>TreeMap</td><td>red black tree</td><td>char*</td><td>char*</td><td>62568</td><td>263</td><td>20</td><td>164</td><td>156</td></tr>
<tr><td>std::unordered_map</td><td>hash table</td><td>long</td><td>long</td><td>39408</td><td>55</td><td>4</td><td>12</td><td>25</td></tr>
<tr><td>HashMap</td><td>hash table</td><td>long</td><td>long</td><td>46860</td><td>46</td><td>8</td><td>12</td><td>26</td></tr>
<tr><td>std::unordered_map</td><td>hash table</td><td>char*</td><td>char*</td><td>46860</td><td>89</td><td>16</td><td>45</td><td>61</td></tr>
<tr><td>HashMap</td><td>hash table</td><td>char*</td><td>char*</td><td>46860</td><td>62</td><td>10</td><td>32</td><td>46</td></tr>
<tr><td>LinkedHashMap</td><td>linked hash table</td><td>long</td><td>long</td><td>62436</td><td>51</td><td>9</td><td>13</td><td>29</td></tr>
<tr><td>LinkedHashMap</td><td>linked hash table</td><td>char*</td><td>char*</td><td>62568</td><td>65</td><td>11</td><td>34</td><td>44</td></tr>
</table>

Several notes:

1. tests for hash table implementations use reserved size of one million plus one. The reason is that each implementation has its own growth point (A grows at point V, while B grows at point Z>V: if we stop insertion between V and Z, A will appear slower because it has done one more reallocation)
2. despite different programming behind, memory usage between STL and CDS is always the same and only varies by data structure EXCEPT for std::unordered_map<long,long> who for reason I do not understand allocates LESS.

###Sets###

Test case:

1. checking memory allocated by a set containing a million entries
2. checking duration of a million rows insertion
3. checking duration of iterating all set
4. removing all set entries based on value

Results:

<table>
<tr><td>Implementation</td><td>Data Structure</td><td>Value Type</td><td>Memory (kb)</td><td>Insertion (ms)</td><td>Iteration (ms)</td><td>Deletion (ms)</td></tr>
<tr><td>std::set</td><td>red black tree</td><td>long</td><td>46860</td><td>237</td><td>22</td><td>116</td></tr>
<tr><td>TreeSet</td><td>red black tree</td><td>long</td><td>46860</td><td>231</td><td>20</td><td>112</td></tr>
<tr><td>std::set</td><td>red black tree</td><td>char*</td><td>46860</td><td>260</td><td>15</td><td>211</td></tr>
<tr><td>TreeSet</td><td>red black tree</td><td>char*</td><td>46860</td><td>293</td><td>15</td><td>139</td></tr>
<tr><td>std::unordered_set</td><td>hash table</td><td>long</td><td>39408</td><td>57</td><td>4</td><td>26</td></tr>
<tr><td>HashSet</td><td>hash table</td><td>long</td><td>31152</td><td>40</td><td>7</td><td>24</td></tr>
<tr><td>std::unordered_set</td><td>hash table</td><td>char*</td><td>31284</td><td>75</td><td>15</td><td>62</td></tr>
<tr><td>HashSet</td><td>hash table</td><td>char*</td><td>31284</td><td>55</td><td>12</td><td>42</td></tr>
<tr><td>LinkedHashSet</td><td>linked hash table</td><td>long</td><td>46860</td><td>47</td><td>7</td><td>27</td></tr>
<tr><td>LinkedHashSet</td><td>linked hash table</td><td>char*</td><td>46860</td><td>64</td><td>7</td><td>42</td></tr>
</table>

Several notes:

1. tests for hash table implementations use reserved size of one million plus one. The reason is that each implementation has its own growth point (A grows at point V, while B grows at point Z>V: if we stop insertion between V and Z, A will appear slower because it has done one more reallocation)
2. despite different programming behind, memory usage between STL and CDS is always the same and only varies by data structure EXCEPT for std::unordered_set<long,long> who for reason I do not understand this time allocates MORE.