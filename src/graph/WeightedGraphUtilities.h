/*
 * WeightedGraphUtilities.h
 *
 *  Created on: Mar 10, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPHUTILITIES_H_
#define SRC_GRAPH_WEIGHTEDGRAPHUTILITIES_H_


template<typename T,typename W, int (*comparator)(const T&, const T&)>
int compareWeightedVertex(WeightedGraphVertex<T,W>* const& left, WeightedGraphVertex<T,W>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T,typename W, std::size_t (*hash)(const T&)>
std::size_t hashWeightedVertex(WeightedGraphVertex<T,W>* const& node) {
	return hash(node->getData());
}

template<typename T,typename W, std::size_t (*hash)(const T&)>
std::size_t hashWeightedVertexParent(WeightedGraphEdge<T, W>* const& entry) {
	return hash(entry->vertex->getData());
}

template<typename T,typename W, int (*comparator)(const T&, const T&)>
int compareWeightedVertexParent(WeightedGraphEdge<T, W>* const& left, WeightedGraphEdge<T, W>* const& right) {
	return comparator(left->vertex->getData(), right->vertex->getData());
}



#endif /* SRC_GRAPH_WEIGHTEDGRAPHUTILITIES_H_ */
