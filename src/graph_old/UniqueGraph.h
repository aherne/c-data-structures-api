/*
 * UniqueGraph.h
 *
 *  Created on: Oct 30, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_OLD_UNIQUEGRAPH_H_
#define SRC_GRAPH_OLD_UNIQUEGRAPH_H_

#include "../container/Queue.h"
#include "../set/HashSet.h"
#include "../map/HashMap.h"

template<typename T>
struct UniqueGraphVertex {
	T data;
	std::vector<UniqueGraphVertex<T>*> edges;
};

template<typename T>
int compareVertex(UniqueGraphVertex<T>* const& left, UniqueGraphVertex<T>* const& right) {
	return comparator(left->data, right->data);
}

template<typename T>
std::size_t hashVertex(UniqueGraphVertex<T>* const& node) {
	return hash(node->data);
}

template<typename T>
std::size_t hashVertexDistance(const MapEntry<UniqueGraphVertex<T>*, long>& entry) {
	return hash(entry.key->data);
}

template<typename T>
int compareVertexDistance(const MapEntry<UniqueGraphVertex<T>*, long>& left, const MapEntry<UniqueGraphVertex<T>*, long>& right) {
	return comparator(left.key->data, right.key->data);
}

template<typename T>
std::size_t hashVertexParent(const MapEntry<UniqueGraphVertex<T>*, UniqueGraphVertex<T>*>& entry) {
	return hash(entry.key->data);
}

template<typename T>
int compareVertexParent(const MapEntry<UniqueGraphVertex<T>*, UniqueGraphVertex<T>*>& left, const MapEntry<UniqueGraphVertex<T>*, UniqueGraphVertex<T>*>& right) {
	return comparator(left.key->data, right.key->data);
}

template<typename T>
class UniqueGraphVertexVisitor {
public:
	virtual ~UniqueGraphVertexVisitor(){};

	virtual void visit(UniqueGraphVertex<T>* const element) = 0;
};

template<typename T>
class UniqueGraph {
public:
	UniqueGraph(){

	}

	// O(V)
	~UniqueGraph(){
		// deallocate all vertexes
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			delete (*(*it));
		}
	}

	// O(2)
	UniqueGraphVertex<T>* createVertex(const T& data) {
		UniqueGraphVertex<T>* temp = new UniqueGraphVertex<T>;
		temp->data=data;
		if(vertexes.contains(temp)) {
			delete temp;
			throw std::logic_error("Vertex with that value already exists!");
		}
		vertexes.add(temp);
		return temp;
	}

	// O(V*E)
	void removeVertex(UniqueGraphVertex<T>* vertex) {
		// remove edges that connect to vertex and vertex itself from graph
		std::size_t originalSize = vertexes.size();
		// remove edges that connect to vertex
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			std::vector<UniqueGraphVertex<T>*>& edges = (*(*it))->edges;
			for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
				if(*it2 ==  vertex) {
					it2 = edges.erase(it2);
					break;
				}
			}
		}
		vertexes.remove(vertex);
		if(vertexes.size() == originalSize) {
			throw std::out_of_range("Vertex not found!");
		}
		// deallocates vertex
		delete vertex;
	}

	// O(E)
	bool isEdge(UniqueGraphVertex<T>* left, UniqueGraphVertex<T>* right) const {
		// check if edge doesn't already exist
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it)==right) {
				return true;
			}
		}
		return false;
	}

	// O(1|2)
	void createEdge(UniqueGraphVertex<T>* left, UniqueGraphVertex<T>* right, const bool& directed = true) {
		left->edges.push_back(right);
		if(!directed) createEdge(right, left, true);
	}

	// O(E|2E)
	void removeEdge(UniqueGraphVertex<T>* left, UniqueGraphVertex<T>* right, const bool& directed = true) {
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it)==right) {
				it = left->edges.erase(it);
				return;
			}
		}
		throw std::out_of_range("Edge not found!");
		if(!directed) removeEdge(right, left, true);
	}

	// O(1)
	std::size_t getSize() const {
		return vertexes.size();
	}

	// O(V*E)
	bool isPath(UniqueGraphVertex<T>* left, UniqueGraphVertex<T>* right) const {
		HashSet<UniqueGraphVertex<T>*, compareVertex, hashVertex> visited;
		Queue<UniqueGraphVertex<T>*> queue;
		queue.push(left);
		visited.add(left);
		while(!queue.isEmpty()) {
			UniqueGraphVertex<T>* node = queue.pop();
			std::vector<UniqueGraphVertex<T>*> children = node->edges;
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
	std::size_t getDistance(UniqueGraphVertex<T>* left, UniqueGraphVertex<T>* right) const {
		HashMap<UniqueGraphVertex<T>*, long, compareVertexDistance, hashVertexDistance> visited;
		Queue<UniqueGraphVertex<T>*> queue;
		queue.push(left);
		visited.set(left,0);
		while(!queue.isEmpty()) {
			UniqueGraphVertex<T>* node = queue.pop();
			std::vector<UniqueGraphVertex<T>*> children = node->edges;
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
	std::vector<UniqueGraphVertex<T>*> getPath(UniqueGraphVertex<T>* left, UniqueGraphVertex<T>* right) {
		HashMap<UniqueGraphVertex<T>*, UniqueGraphVertex<T>*, compareVertexParent, hashVertexParent> visited;
		Queue<UniqueGraphVertex<T>*> queue;
		queue.push(left);
		visited.set(left,nullptr);
		while(!queue.isEmpty()) {
			UniqueGraphVertex<T>* node = queue.pop();
			std::vector<UniqueGraphVertex<T>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if(!visited.containsKey(*it)) {
					if((*it)==right) {
						std::vector<UniqueGraphVertex<T>*> response;
						response.push_back(right);
						UniqueGraphVertex<T>* parent = node;
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

	// O(V*E)
	void iterate(UniqueGraphVertex<T>* start, UniqueGraphVertexVisitor<T>* visitor) {
		HashSet<UniqueGraphVertex<T>*, compareVertex, hashVertex> visited;
		Queue<UniqueGraphVertex<T>*> queue;
		queue.push(start);
		visited.add(start);
		while(!queue.isEmpty()) {
			UniqueGraphVertex<T>* node = queue.pop();
			std::vector<UniqueGraphVertex<T>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if(!visited.contains(*it)) {
					visitor->visit(*it);
					visited.add(*it);
					queue.push(*it);
				}
			}
		}
	}

	// O(V)
	void iterate(UniqueGraphVertexVisitor<T>* visitor) {
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			visitor->visit(*(*it));
		}
	}

	// O(1)
	bool contains(const T& data) const {
		UniqueGraphVertex<T> temp;
		temp.data = data;
		return vertexes.contains(&temp);
	}

	// O(2)
	UniqueGraphVertex<T>* search(const T& data) {
		UniqueGraphVertex<T> temp;
		temp.data = data;
		if(!vertexes.contains(&temp)) return nullptr;
		return *(vertexes.find(&temp));
	}
private:
	HashSet<UniqueGraphVertex<T>*, compareVertex, hashVertex> vertexes;
};



#endif /* SRC_GRAPH_OLD_UNIQUEGRAPH_H_ */
