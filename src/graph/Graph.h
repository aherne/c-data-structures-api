/*
 * Graph.h
 *
 *  Created on: Dec 22, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

#include "GraphVertex.h"

template<typename T>
class Graph {
public:
	virtual ~Graph() {}
	virtual GraphVertex<T>* createVertex(const T& data) = 0;
	virtual void removeVertex(GraphVertex<T>*& vertex) = 0;
	virtual std::size_t getSize() const = 0;
	virtual bool isConnected(GraphVertex<T>*& left, GraphVertex<T>*& right) const = 0;
	virtual std::vector<GraphVertex<T>*> getShortestPath(GraphVertex<T>*& left, GraphVertex<T>*& right) const = 0;
};

#endif /* SRC_GRAPH_GRAPH_H_ */
