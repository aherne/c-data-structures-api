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

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class WeightedGraphVertexVisitor {
public:
	virtual ~WeightedGraphVertexVisitor(){};

	virtual bool visit(WeightedGraphVertex<T,W,compare,hash>* const& element) = 0;

	virtual bool isVisited(WeightedGraphVertex<T,W,compare,hash>* const& element) = 0;
};

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void BreadthFirstSearchGraphIterator(WeightedGraphVertex<T,W,compare,hash>* vertex, WeightedGraphVertexVisitor<T,W,compare,hash>* visitor) {
	Queue<WeightedGraphVertex<T,W,compare,hash>*> queue;
	visitor->visit(vertex);
	queue.push(vertex);
	while(!queue.isEmpty()) {
		WeightedGraphVertex<T,W,compare,hash>* node = queue.pop();
		HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* children = node->getEdges();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			std::pair<WeightedGraphVertex<T,W,compare,hash>*,W> tmp = (std::pair<WeightedGraphVertex<T,W,compare,hash>*,W>) (*(*it));
			if(!visitor->isVisited(tmp.first)) {
				visitor->visit(tmp.first);
				queue.push(tmp.first);
			}
		}
	}
}

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void DepthFirstSearchGraphIterator(WeightedGraphVertex<T,W,compare,hash>* vertex, WeightedGraphVertexVisitor<T,W,compare,hash>* visitor) {
	visitor->visit(vertex);
	HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* children = vertex->getEdges();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		std::pair<WeightedGraphVertex<T,W,compare,hash>*,W> tmp = (std::pair<WeightedGraphVertex<T,W,compare,hash>*,W>) (*(*it));
		if(!visitor->isVisited(tmp.first)) {
			DepthFirstSearchGraphIterator(tmp.first, visitor);
		}
	}
}

#endif /* SRC_GRAPH_WEIGHTEDGRAPHITERATOR_H_ */
