/*
 * UndirectedWeightedGraph.h
 *
 *  Created on: Apr 20, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNDIRECTEDWEIGHTEDGRAPH_H_
#define SRC_GRAPH_UNDIRECTEDWEIGHTEDGRAPH_H_

#include "WeightedGraph.h"

template<typename T,typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UndirectedWeightedGraph : public WeightedGraph<T,W,compare,hash> {
public:
	void removeVertex(WeightedGraphVertex<T,W,compare,hash>* const& vertex) {
		HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* edges = vertex->getEdges();
		for(auto it = edges->begin(); *it!=*(edges->end()); ++(*it)) {
			(*(*it)).first->removeEdge(vertex);
		}
		this->vertexes.remove(vertex);
		// deallocates vertex
		delete vertex;
	}

	void createEdge(WeightedGraphVertex<T, W,compare, hash>* const& left, WeightedGraphVertex<T, W,compare, hash>* const& right, const W& weight) {
		left->addEdge(right, weight);
		right->addEdge(left, weight);
	}

	void removeEdge(WeightedGraphVertex<T, W,compare, hash>* const& left, WeightedGraphVertex<T, W,compare, hash>* const& right) {
		left->removeEdge(right);
		right->removeEdge(left);
	}
};

#endif /* SRC_GRAPH_UNDIRECTEDWEIGHTEDGRAPH_H_ */
