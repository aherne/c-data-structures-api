/*
 * GraphIterator.h
 *
 *  Created on: Mar 16, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_GRAPHITERATOR_H_
#define SRC_GRAPH_GRAPHITERATOR_H_

#include "GraphVertex.h"
#include "../container/Queue.h"

template<typename T>
class GraphVertexVisitor {
public:
	virtual ~GraphVertexVisitor(){};

	virtual bool visit(GraphVertex<T>* const& element) = 0;

	virtual bool isVisited(GraphVertex<T>* const& element) = 0;
};

template<typename T>
inline void BreadthFirstSearchGraphIterator(GraphVertex<T>* vertex, GraphVertexVisitor<T>* visitor) {
	Queue<GraphVertex<T>*> queue;
	visitor->visit(vertex);
	queue.push(vertex);
	while(!queue.isEmpty()) {
		GraphVertex<T>* node = queue.pop();
		std::vector<GraphVertex<T>*> children = node->getEdges();
		for(auto it = children.begin(); it != children.end(); ++it){
			GraphVertex<T>* tmp = (GraphVertex<T>*) *it;
			if(!visitor->isVisited(tmp)) {
				visitor->visit(tmp);
				queue.push(tmp);
			}
		}
	}
}

template<typename T>
inline void DepthFirstSearchGraphIterator(GraphVertex<T>* vertex, GraphVertexVisitor<T>* visitor) {
	visitor->visit(vertex);
	std::vector<GraphVertex<T>*> children = vertex->getEdges();
	for(auto it = children.begin(); it != children.end(); ++it){
		GraphVertex<T>* tmp = (GraphVertex<T>*) *it;
		if(!visitor->isVisited(tmp)) {
			DepthFirstSearchGraphIterator(tmp, visitor);
		}
	}
}

#endif /* SRC_GRAPH_GRAPHITERATOR_H_ */
