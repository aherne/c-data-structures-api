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

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class GraphVertex {
	public:
		GraphVertex(const T& data) {
			this->data = data;
			this->edges = new HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>;
		}

		virtual ~GraphVertex() {
			delete edges;
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() const {
			return this->data;
		}

		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>*& getEdges() {
			return edges;
		}

		bool isEdge(GraphVertex<T, compare, hash>*& vertex) const {
			return edges->contains(vertex);
		}

		void addEdge(GraphVertex<T, compare, hash>*& vertex) {
			edges->add(vertex);
		}

		void removeEdge(GraphVertex<T, compare, hash>*& vertex) {
			if(edges->contains(vertex)) {
				edges->remove(vertex);
			}
		}

		bool isConnected(GraphVertex<T, compare, hash>*& right) const {
			GraphVertex<T, compare, hash>* left = (GraphVertex<T, compare, hash>*) this;
			HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare,hash>, hashVertex<T, compare,hash>> visited;
			Queue<GraphVertex<T, compare, hash>*> queue;
			queue.push(left);
			visited.add(left);
			while(!queue.isEmpty()) {
				GraphVertex<T, compare, hash>* node = queue.pop();
				HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = node->getEdges();
				for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
					if(!visited.contains(*(*it))) {
						if((*(*it))==right) return true;
						visited.add(*(*it));
						queue.push(*(*it));
					}
				}
			}
			return false;
		}

		ArrayList<GraphVertex<T, compare, hash>*> getShortestPath(GraphVertex<T, compare, hash>*& right) const {
			GraphVertex<T, compare, hash>* left = (GraphVertex<T, compare, hash>*) this;
			HashMap<GraphVertex<T, compare, hash>*, GraphVertex<T, compare, hash>*, compareVertex<T, compare,hash>, hashVertex<T, compare,hash>> visited;
			Queue<GraphVertex<T, compare, hash>*> queue;
			queue.push(left);
			visited.set(left,nullptr);
			while(!queue.isEmpty()) {
				GraphVertex<T, compare, hash>* node = queue.pop();
				HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = node->getEdges();
				for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
					if(!visited.containsKey(*(*it))) {
						if((*(*it))==right) {
							ArrayList<GraphVertex<T, compare, hash>*> response;
							response.addToBottom(right);
							GraphVertex<T, compare, hash>* parent = node;
							while(parent!=nullptr) {
								response.addToBottom(parent);
								parent = visited.get(parent);
							}
							return response;
						}
						visited.set(*(*it), node);
						queue.push(*(*it));
					}
				}
			}
			throw std::out_of_range("Vertexes not connected!");
		}
	protected:
		T data;
		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* edges;
};

#endif /* SRC_GRAPH_GRAPHVERTEX_H_ */
