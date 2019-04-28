/*
 * GraphVertex.h
 *
 *  Created on: Dec 22, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_GRAPHVERTEX_H_
#define SRC_GRAPH_GRAPHVERTEX_H_

#include "../Comparator.h"
#include "../Hashing.h"
#include "../set/HashSet.h"
#include "../list/ArrayList.h"
#include "../container/Queue.h"
#include "../map/HashMap.h"

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class GraphVertex;

template<typename T, int (*comparator)(const T&, const T&), std::size_t (*hash)(const T&)>
int compareVertex(GraphVertex<T, comparator, hash>* const& left, GraphVertex<T, comparator, hash>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T, int (*comparator)(const T&, const T&), std::size_t (*hash)(const T&)>
std::size_t hashVertex(GraphVertex<T, comparator, hash>* const& node) {
	return hash(node->getData());
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class GraphVertex {
	public:
		GraphVertex(const T& data) {
			this->data = data;
			this->edges = new HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>;
		}

		~GraphVertex() {
			delete edges;
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() const {
			return this->data;
		}

		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* const& getEdges() {
			return edges;
		}

		bool isEdge(GraphVertex<T, compare, hash>* const& vertex) const {
			return edges->contains(vertex);
		}

		void addEdge(GraphVertex<T, compare, hash>* const& vertex) {
			edges->add(vertex);
		}

		void removeEdge(GraphVertex<T, compare, hash>* const& vertex) {
			if(edges->contains(vertex)) {
				edges->remove(vertex);
			}
		}
	protected:
		T data;
		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* edges;
};

#endif /* SRC_GRAPH_GRAPHVERTEX_H_ */
