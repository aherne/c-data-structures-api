/*
 * GraphVertex.h
 *
 *  Created on: Dec 22, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNWEIGHTEDGRAPHVERTEX_H_
#define SRC_GRAPH_UNWEIGHTEDGRAPHVERTEX_H_

#include "../Comparator.h"
#include "../Hashing.h"
#include "../set/HashSet.h"
#include "../container/Queue.h"
#include "../map/HashMap.h"

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class UnweightedGraphVertex;

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline int compareVertex(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline std::size_t hashVertex(UnweightedGraphVertex<T, compare, hash>* const& node) {
	return hash(node->getData());
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UnweightedGraphVertex {
	public:
		UnweightedGraphVertex(const T& data) {
			this->data = data;
			this->edges = new HashSet<UnweightedGraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>;
		}

		~UnweightedGraphVertex() {
			delete edges;
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() const {
			return this->data;
		}

		Set<UnweightedGraphVertex<T, compare, hash>*>* const& getEdges() {
			return edges;
		}

		bool isEdge(UnweightedGraphVertex<T, compare, hash>* const& vertex) const {
			return edges->contains(vertex);
		}

		void addEdge(UnweightedGraphVertex<T, compare, hash>* const& vertex) {
			edges->add(vertex);
		}

		void removeEdge(UnweightedGraphVertex<T, compare, hash>* const& vertex) {
			if(edges->contains(vertex)) {
				edges->remove(vertex);
			}
		}
	protected:
		T data;
		Set<UnweightedGraphVertex<T, compare, hash>*>* edges;
};

#endif /* SRC_GRAPH_UNWEIGHTEDGRAPHVERTEX_H_ */
