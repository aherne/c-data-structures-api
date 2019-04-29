/*
 * DirectedUnweightedGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_DIRECTEDUNWEIGHTEDGRAPH_H_
#define SRC_GRAPH_DIRECTEDUNWEIGHTEDGRAPH_H_


#include "UnweightedGraph.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class DirectedUnweightedGraph : public UnweightedGraph<T,compare,hash> {
	public:
		void removeVertex(UnweightedGraphVertex<T, compare, hash>* const& vertex) {
			// remove edges that connect to vertex
			for(auto it = this->vertexes.begin(); *it!=*(this->vertexes.end()); ++(*it)) {
				(*(*it))->removeEdge(vertex);
			}
			this->vertexes.remove(vertex);
			// deallocates vertex
			delete vertex;
		}

		void createEdge(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
			left->addEdge(right);
		}

		void removeEdge(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
			left->removeEdge(right);
		}
};



#endif /* SRC_GRAPH_DIRECTEDUNWEIGHTEDGRAPH_H_ */
