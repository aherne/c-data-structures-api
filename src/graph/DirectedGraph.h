/*
 * DirectedGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_DIRECTEDGRAPH_H_
#define SRC_GRAPH_DIRECTEDGRAPH_H_


#include "Graph.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class DirectedGraph : public Graph<T,compare,hash> {
	public:
		void removeVertex(GraphVertex<T, compare, hash>*& vertex) {
			// remove edges that connect to vertex
			for(auto it = this->vertexes.begin(); *it!=*(this->vertexes.end()); ++(*it)) {
				(*(*it))->removeEdge(vertex);
			}
			this->vertexes.remove(vertex);
			// deallocates vertex
			delete vertex;
		}

		void createEdge(GraphVertex<T, compare, hash>*& left, GraphVertex<T, compare, hash>*& right) {
			left->addEdge(right);
		}

		void removeEdge(GraphVertex<T, compare, hash>*& left, GraphVertex<T, compare, hash>*& right) {
			left->removeEdge(right);
		}
};



#endif /* SRC_GRAPH_DIRECTEDGRAPH_H_ */
