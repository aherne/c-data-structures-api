/*
 * WeightedGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPH_H_
#define SRC_GRAPH_WEIGHTEDGRAPH_H_

#include "WeightedGraphVertex.h"

template<typename T, typename W>
class WeightedGraph {
public:
	virtual ~WeightedGraph() {}
	virtual WeightedGraphVertex<T,W>* createVertex(const T& data) = 0;
	virtual void removeVertex(WeightedGraphVertex<T,W>*& vertex) = 0;
	virtual std::size_t getSize() const = 0;
	virtual bool isConnected(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const = 0;
	virtual std::vector<WeightedGraphEdge<T,W>*> getShortestPath(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const = 0;
};

#endif /* SRC_GRAPH_WEIGHTEDGRAPH_H_ */
