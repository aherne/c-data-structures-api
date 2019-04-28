/*
 * UndirectedGraph.h
 *
 *  Created on: Apr 20, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNDIRECTEDGRAPH_H_
#define SRC_GRAPH_UNDIRECTEDGRAPH_H_

#include "Graph.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UndirectedGraph : public Graph<T,compare,hash> {
	public:
		void removeVertex(GraphVertex<T, compare, hash>* const& vertex) {
			// remove edges that connect to vertex
			HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* edges = vertex->getEdges();
			for(auto it = edges->begin(); *it!=*(edges->end()); ++(*it)) {
				(*(*it))->removeEdge(vertex);
			}
			this->vertexes.remove(vertex);
			// deallocates vertex
			delete vertex;
		}

		void createEdge(GraphVertex<T, compare, hash>* const& left, GraphVertex<T, compare, hash>* const& right) {
			left->addEdge(right);
			right->addEdge(left);
		}

		void removeEdge(GraphVertex<T, compare, hash>* const& left, GraphVertex<T, compare, hash>* const& right) {
			left->removeEdge(right);
			right->removeEdge(left);
		}
};

#endif /* SRC_GRAPH_UNDIRECTEDGRAPH_H_ */
