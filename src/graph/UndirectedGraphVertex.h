/*
 * UndirectedGraphVertex.h
 *
 *  Created on: Mar 25, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNDIRECTEDGRAPHVERTEX_H_
#define SRC_GRAPH_UNDIRECTEDGRAPHVERTEX_H_

#include "GraphVertex.h"

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class UndirectedGraphVertex: public GraphVertex<T, compare, hash> {
public:
	using GraphVertex<T, compare, hash>::GraphVertex;

	void addEdge(GraphVertex<T, compare, hash>*& vertex) {
		GraphVertex<T, compare, hash>::addEdge(vertex);
		vertex->addEdge(this);
	}

	void removeEdge(GraphVertex<T, compare, hash>*& vertex) {
		GraphVertex<T, compare, hash>::removeEdge(vertex);
		vertex->removeEdge(this);
	}
};


#endif /* SRC_GRAPH_UNDIRECTEDGRAPHVERTEX_H_ */
