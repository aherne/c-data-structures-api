/*
 * UniqueGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNIQUEGRAPH_H_
#define SRC_GRAPH_UNIQUEGRAPH_H_


#include "GraphVertex.h"
#include "UndirectedGraphVertex.h"
#include "../Comparator.h"
#include "../Hashing.h"


template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UniqueGraph {
	public:
		UniqueGraph(bool directed = true) {
			this->directed = directed;
		}

		~UniqueGraph(){
			// deallocate all vertexes
			for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
				delete (*(*it));
			}
		}

		// O(2)
		GraphVertex<T, compare, hash>* createVertex(const T& data) {
			GraphVertex<T, compare, hash> stack(data);
			if(vertexes.contains(&stack)) {
				throw std::logic_error("Vertex with that value already exists!");
			}
			GraphVertex<T, compare, hash>* temp = (directed?new GraphVertex<T, compare, hash>(data):new UndirectedGraphVertex<T, compare, hash>(data));
			vertexes.add(temp);
			return temp;
		}

		// O(V*E)
		void removeVertex(GraphVertex<T, compare, hash>*& vertex) {
			// remove edges that connect to vertex
			for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
				(*(*it))->removeEdge(vertex);
			}
			vertexes.remove(vertex);
			// deallocates vertex
			delete vertex;
		}

		// O(1)
		std::size_t getSize() const {
			return vertexes.size();
		}

		// O(1)
		bool contains(const T& data) const {
			GraphVertex<T, compare, hash> temp(data);
			return vertexes.contains(&temp);
		}

		// O(2)
		GraphVertex<T, compare, hash>* search(const T& data) {
			GraphVertex<T, compare, hash> temp(data);
			if(!vertexes.contains(&temp)) return nullptr;
			return *(vertexes.find(&temp));
		}
	private:
		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>> vertexes;
		bool directed;
};



#endif /* SRC_GRAPH_UNIQUEGRAPH_H_ */
