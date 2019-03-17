/*
 * WeightedGraphIterator.h
 *
 *  Created on: Mar 16, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPHITERATOR_H_
#define SRC_GRAPH_WEIGHTEDGRAPHITERATOR_H_



#include "WeightedGraphVertex.h"
#include "../container/Queue.h"

template<typename T, typename W>
class WeightedGraphVertexVisitor {
public:
	virtual ~WeightedGraphVertexVisitor(){};

	virtual bool visit(WeightedGraphVertex<T,W>* const& element) = 0;

	virtual bool isVisited(WeightedGraphVertex<T,W>* const& element) = 0;
};

template<typename T, typename W>
inline void BreadthFirstSearchGraphIterator(WeightedGraphVertex<T,W>* vertex, WeightedGraphVertexVisitor<T,W>* visitor) {
	Queue<WeightedGraphVertex<T,W>*> queue;
	visitor->visit(vertex);
	queue.push(vertex);
	while(!queue.isEmpty()) {
		WeightedGraphVertex<T,W>* node = queue.pop();
		std::vector<WeightedGraphEdge<T,W>*> children = node->getEdges();
		for(auto it = children.begin(); it != children.end(); ++it){
			WeightedGraphEdge<T,W>* tmp = (WeightedGraphEdge<T,W>*) *it;
			if(!visitor->isVisited(tmp->vertex)) {
				visitor->visit(tmp->vertex);
				queue.push(tmp->vertex);
			}
		}
	}
}

template<typename T, typename W>
inline void DepthFirstSearchGraphIterator(WeightedGraphVertex<T,W>* vertex, WeightedGraphVertexVisitor<T,W>* visitor) {
	visitor->visit(vertex);
	std::vector<WeightedGraphEdge<T,W>*> children = vertex->getEdges();
	for(auto it = children.begin(); it != children.end(); ++it){
		WeightedGraphEdge<T,W>* tmp = (WeightedGraphEdge<T,W>*) *it;
		if(!visitor->isVisited(tmp->vertex)) {
			DepthFirstSearchGraphIterator(tmp->vertex, visitor);
		}
	}
}

#endif /* SRC_GRAPH_WEIGHTEDGRAPHITERATOR_H_ */
