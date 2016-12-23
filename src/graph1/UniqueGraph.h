/*
 * UniqueGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH1_UNIQUEGRAPH_H_
#define SRC_GRAPH1_UNIQUEGRAPH_H_


#include "../container/Queue.h"
#include "../set/HashSet.h"
#include "../map/HashMap.h"
#include "GraphVertex.h"
#include "Graph.h"

template<typename T>
int compareVertex(GraphVertex<T>* const& left, GraphVertex<T>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T>
std::size_t hashVertex(GraphVertex<T>* const& node) {
	return hash(node->getData());
}

template<typename T>
std::size_t hashVertexDistance(const MapEntry<GraphVertex<T>*, long>& entry) {
	return hash(entry.key->getData());
}

template<typename T>
int compareVertexDistance(const MapEntry<GraphVertex<T>*, long>& left, const MapEntry<GraphVertex<T>*, long>& right) {
	return comparator(left.key->getData(), right.key->getData());
}

template<typename T>
std::size_t hashVertexParent(const MapEntry<GraphVertex<T>*, GraphVertex<T>*>& entry) {
	return hash(entry.key->getData());
}

template<typename T>
int compareVertexParent(const MapEntry<GraphVertex<T>*, GraphVertex<T>*>& left, const MapEntry<GraphVertex<T>*, GraphVertex<T>*>& right) {
	return comparator(left.key->getData(), right.key->getData());
}

template<typename T>
class UniqueGraph : public Graph<T> {
	public:
		~UniqueGraph(){
			// deallocate all vertexes
			for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
				delete (*(*it));
			}
		}

		// O(2)
		GraphVertex<T>* createVertex(const T& data) {
			GraphVertex<T> stack(data);
			if(vertexes.contains(&stack)) {
				throw std::logic_error("Vertex with that value already exists!");
			}
			GraphVertex<T>* temp = new GraphVertex<T>(data);
			vertexes.add(temp);
			return temp;
		}

		// O(V*E)
		void removeVertex(GraphVertex<T>*& vertex) {
			// remove edges that connect to vertex and vertex itself from graph
			std::size_t originalSize = vertexes.size();
			// remove edges that connect to vertex
			for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
				(*(*it))->removeEdge(vertex);
			}
			vertexes.remove(vertex);
			if(vertexes.size() == originalSize) {
				throw std::out_of_range("Vertex not found!");
			}
			// deallocates vertex
			delete vertex;
		}

		// O(1)
		std::size_t getSize() const {
			return vertexes.size();
		}

		// O(V*E)
		bool isPath(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			HashSet<GraphVertex<T>*, compareVertex, hashVertex> visited;
			Queue<GraphVertex<T>*> queue;
			queue.push(left);
			visited.add(left);
			while(!queue.isEmpty()) {
				GraphVertex<T>* node = queue.pop();
				std::vector<GraphVertex<T>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					if(!visited.contains(*it)) {
						if((*it)==right) return true;
						visited.add(*it);
						queue.push(*it);
					}
				}
			}
			return false;
		}

		// O(V*E)
		std::size_t getDistance(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			HashMap<GraphVertex<T>*, long, compareVertexDistance, hashVertexDistance> visited;
			Queue<GraphVertex<T>*> queue;
			queue.push(left);
			visited.set(left,0);
			while(!queue.isEmpty()) {
				GraphVertex<T>* node = queue.pop();
				std::vector<GraphVertex<T>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					if(!visited.containsKey(*it)) {
						if((*it)==right) return visited.get(node)+1;
						visited.set(*it, visited.get(node)+1);
						queue.push(*it);
					}
				}
			}
			throw std::out_of_range("Vertexes not connected!");
		}

		// O(V*E)
		std::vector<GraphVertex<T>*> getPath(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			HashMap<GraphVertex<T>*, GraphVertex<T>*, compareVertexParent, hashVertexParent> visited;
			Queue<GraphVertex<T>*> queue;
			queue.push(left);
			visited.set(left,nullptr);
			while(!queue.isEmpty()) {
				GraphVertex<T>* node = queue.pop();
				std::vector<GraphVertex<T>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					if(!visited.containsKey(*it)) {
						if((*it)==right) {
							std::vector<GraphVertex<T>*> response;
							response.push_back(right);
							GraphVertex<T>* parent = node;
							while(parent!=nullptr) {
								response.push_back(parent);
								parent = visited.get(parent);
							}
							return response;
						}
						visited.set(*it, node);
						queue.push(*it);
					}
				}
			}
			throw std::out_of_range("Vertexes not connected!");
		}

		// O(1)
		bool contains(const T& data) const {
			GraphVertex<T> temp(data);
			return vertexes.contains(&temp);
		}

		// O(2)
		GraphVertex<T>* search(const T& data) {
			GraphVertex<T> temp(data);
			if(!vertexes.contains(&temp)) return nullptr;
			return *(vertexes.find(&temp));
		}
	private:
		HashSet<GraphVertex<T>*, compareVertex, hashVertex> vertexes;
};



#endif /* SRC_GRAPH1_UNIQUEGRAPH_H_ */
