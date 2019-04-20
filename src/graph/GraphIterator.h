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

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class GraphVertexVisitor {
public:
	virtual ~GraphVertexVisitor(){};

	virtual bool visit(GraphVertex<T, compare, hash>* const& element) = 0;

	virtual bool isVisited(GraphVertex<T, compare, hash>* const& element) = 0;
};

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void BreadthFirstSearchGraphIterator(GraphVertex<T, compare, hash>* vertex, GraphVertexVisitor<T, compare, hash>* visitor) {
	Queue<GraphVertex<T, compare, hash>*> queue;
	visitor->visit(vertex);
	queue.push(vertex);
	while(!queue.isEmpty()) {
		GraphVertex<T, compare, hash>* node = queue.pop();
		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = node->getEdges();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			GraphVertex<T, compare, hash>* tmp = (GraphVertex<T, compare, hash>*) (*(*it));
			if(!visitor->isVisited(tmp)) {
				visitor->visit(tmp);
				queue.push(tmp);
			}
		}
	}
}

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void DepthFirstSearchGraphIterator(GraphVertex<T, compare, hash>* vertex, GraphVertexVisitor<T, compare, hash>* visitor) {
	visitor->visit(vertex);
	HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = vertex->getEdges();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		GraphVertex<T, compare, hash>* tmp = (GraphVertex<T, compare, hash>*) (*(*it));
		if(!visitor->isVisited(tmp)) {
			DepthFirstSearchGraphIterator(tmp, visitor);
		}
	}
}

#endif /* SRC_GRAPH_GRAPHITERATOR_H_ */
