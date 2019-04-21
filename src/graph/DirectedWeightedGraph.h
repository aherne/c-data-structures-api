/*
 * DirectedWeightedGraph.h
 *
 *  Created on: Nov 5, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_DIRECTEDWEIGHTEDGRAPH_H_
#define SRC_GRAPH_DIRECTEDWEIGHTEDGRAPH_H_

#include "WeightedGraph.h"

template<typename T,typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class DirectedWeightedGraph : public WeightedGraph<T,W,compare,hash> {
public:
	void removeVertex(WeightedGraphVertex<T,W,compare,hash>*& vertex) {
		for(auto it = this->vertexes.begin(); *it!=*(this->vertexes.end()); ++(*it)) {
			(*(*it))->removeEdge(vertex);
		}
		this->vertexes.remove(vertex);
		// deallocates vertex
		delete vertex;
	}

	void createEdge(WeightedGraphVertex<T, W,compare, hash>*& left, WeightedGraphVertex<T, W,compare, hash>*& right, const W& weight) {
		left->addEdge(right,weight);
	}

	void removeEdge(WeightedGraphVertex<T, W,compare, hash>*& left, WeightedGraphVertex<T, W,compare, hash>*& right) {
		left->removeEdge(right);
	}
};


#endif /* SRC_GRAPH_DIRECTEDWEIGHTEDGRAPH_H_ */
