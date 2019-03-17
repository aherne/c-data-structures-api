/*
 * ComparatorGraph.h
 *
 *  Created on: Mar 5, 2019
 *      Author: aherne
 */

#ifndef SRC_COMPARATORGRAPH_H_
#define SRC_COMPARATORGRAPH_H_

template<typename T, int (*comparator)(const T&, const T&)>
int compareVertex(GraphVertex<T>* const& left, GraphVertex<T>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T, std::size_t (*hash)(const T&)>
std::size_t hashVertex(GraphVertex<T>* const& node) {
	return hash(node->getData());
}

#endif /* SRC_COMPARATORGRAPH_H_ */
