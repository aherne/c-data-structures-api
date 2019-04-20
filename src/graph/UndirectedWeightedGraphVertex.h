/*
 * UndirectedWeightedGraphVertex.h
 *
 *  Created on: Mar 25, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNDIRECTEDWEIGHTEDGRAPHVERTEX_H_
#define SRC_GRAPH_UNDIRECTEDWEIGHTEDGRAPHVERTEX_H_

#include "WeightedGraphVertex.h"

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class UndirectedWeightedGraphVertex: public WeightedGraphVertex<T,W,compare,hash> {
public:
	using WeightedGraphVertex<T,W,compare,hash>::WeightedGraphVertex;


	void addEdge(WeightedGraphVertex<T,W,compare,hash>*& vertex, const W& weight) {
		WeightedGraphVertex<T,W,compare,hash>::addEdge(vertex, weight);
		vertex->addEdge(this, weight);
	}

	void removeEdge(WeightedGraphVertex<T,W,compare,hash>*& vertex) {
		WeightedGraphVertex<T,W,compare,hash>::removeEdge(vertex);
		vertex->removeEdge(this);
	}
};

#endif /* SRC_GRAPH_UNDIRECTEDWEIGHTEDGRAPHVERTEX_H_ */
