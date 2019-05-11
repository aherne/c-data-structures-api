/*
 * UndirectedUnweightedGraph.h
 *
 *  Created on: Apr 20, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNDIRECTEDUNWEIGHTEDGRAPH_H_
#define SRC_GRAPH_UNDIRECTEDUNWEIGHTEDGRAPH_H_

#include "UnweightedGraph.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UndirectedUnweightedGraph : public UnweightedGraph<T,compare,hash> {
	public:
		void removeVertex(UnweightedGraphVertex<T, compare, hash>* const& vertex) {
			// remove edges that connect to vertex
			Set<UnweightedGraphVertex<T, compare, hash>*>* edges = vertex->getEdges();
			for(auto it = edges->begin(); *it!=*(edges->end()); ++(*it)) {
				(*(*it))->removeEdge(vertex);
			}
			this->vertexes.remove(vertex);
			// deallocates vertex
			delete vertex;
		}

		void createEdge(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
			left->addEdge(right);
			right->addEdge(left);
		}

		void removeEdge(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
			left->removeEdge(right);
			right->removeEdge(left);
		}
};

#endif /* SRC_GRAPH_UNDIRECTEDUNWEIGHTEDGRAPH_H_ */
