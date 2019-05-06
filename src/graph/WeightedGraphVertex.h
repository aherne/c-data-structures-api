/*
 * WeightedGraphVertex.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPHVERTEX_H_
#define SRC_GRAPH_WEIGHTEDGRAPHVERTEX_H_

#include "../Comparator.h"
#include "../Hashing.h"
#include "../set/HashSet.h"
#include "../list/ArrayList.h"
#include "../container/Queue.h"
#include "../map/HashMap.h"

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class WeightedGraphVertex;

template<typename T,typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline int compareWeightedVertex(WeightedGraphVertex<T,W,compare,hash>* const& left, WeightedGraphVertex<T,W,compare,hash>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T,typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline std::size_t hashWeightedVertex(WeightedGraphVertex<T,W,compare,hash>* const& node) {
	return hash(node->getData());
}

template<typename T, typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class WeightedGraphVertex {
	public:
		WeightedGraphVertex(const T& data) {
			this->data = data;
			this->edges = new HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>;
		}

		~WeightedGraphVertex() {
			delete edges;
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() const {
			return this->data;
		}

		HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* const& getEdges() {
			return edges;
		}

		bool isEdge(WeightedGraphVertex<T,W,compare,hash>* const& vertex) const {
			return edges->containsKey(vertex);
		}

		const W& getEdgeWeight(WeightedGraphVertex<T,W,compare,hash>* const& vertex) const {
			return edges->get(vertex);
		}

		void setEdgeWeight(WeightedGraphVertex<T,W,compare,hash>* const& vertex, const W& weight) {
			edges->set(vertex, weight);
		}

		void addEdge(WeightedGraphVertex<T,W,compare,hash>* const& vertex, const W& weight) {
			edges->set(vertex, weight);
		}

		void removeEdge(WeightedGraphVertex<T,W,compare,hash>* const& vertex) {
			if(edges->containsKey(vertex)) {
				edges->removeKey(vertex);
			}
		}
	protected:
		T data;
		HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* edges;
};

#endif /* SRC_GRAPH_WEIGHTEDGRAPHVERTEX_H_ */
