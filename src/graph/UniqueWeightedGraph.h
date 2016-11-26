/*
 * UniqueUniqueWeightedGraph.h
 *
 *  Created on: Nov 5, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_
#define SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_


#include "../container/Queue.h"
#include "../set/HashSet.h"
#include "../map/HashMap.h"
#include <vector>

template<typename T,typename W>
struct UniqueWeightedGraphVertex {
	T data;
	std::vector<std::pair<UniqueWeightedGraphVertex<T,W>*,W>> edges;
};

template<typename T,typename W>
int compareVertex(UniqueWeightedGraphVertex<T,W>* const& left, UniqueWeightedGraphVertex<T,W>* const& right) {
	return comparator(left->data, right->data);
}

template<typename T,typename W>
std::size_t hashVertex(UniqueWeightedGraphVertex<T,W>* const& node) {
	return hash(node->data);
}

template<typename T,typename W>
std::size_t hashVertexDistance(const MapEntry<UniqueWeightedGraphVertex<T,W>*, long>& entry) {
	return hash(entry.key->data);
}

template<typename T,typename W>
int compareVertexDistance(const MapEntry<UniqueWeightedGraphVertex<T,W>*, long>& left, const MapEntry<UniqueWeightedGraphVertex<T,W>*, long>& right) {
	return comparator(left.key->data, right.key->data);
}

template<typename T,typename W>
std::size_t hashVertexParent(const MapEntry<UniqueWeightedGraphVertex<T,W>*, UniqueWeightedGraphVertex<T,W>*>& entry) {
	return hash(entry.key->data);
}

template<typename T,typename W>
int compareVertexParent(const MapEntry<UniqueWeightedGraphVertex<T,W>*, UniqueWeightedGraphVertex<T,W>*>& left, const MapEntry<UniqueWeightedGraphVertex<T,W>*, UniqueWeightedGraphVertex<T,W>*>& right) {
	return comparator(left.key->data, right.key->data);
}

template<typename T,typename W>
class UniqueWeightedGraphVertexVisitor {
public:
	virtual ~UniqueWeightedGraphVertexVisitor(){};

	virtual void visit(UniqueWeightedGraphVertex<T,W>* const element) = 0;
};

template<typename T,typename W>
class UniqueWeightedGraphEdgeVisitor {
public:
	virtual ~UniqueWeightedGraphEdgeVisitor(){};

	virtual void visit(const std::pair<UniqueWeightedGraphVertex<T,W>*,W>& element) = 0;
};

template<typename T,typename W>
class UniqueWeightedGraph {
public:
	UniqueWeightedGraph(){

	}

	// O(V)
	~UniqueWeightedGraph(){
		// deallocate all vertexes
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			delete (*(*it));
		}
	}

	// O(2)
	UniqueWeightedGraphVertex<T,W>* createVertex(const T& data) {
		UniqueWeightedGraphVertex<T,W>* temp = new UniqueWeightedGraphVertex<T,W>;
		temp->data=data;
		if(vertexes.contains(temp)) {
			delete temp;
			throw std::logic_error("Vertex with that value already exists!");
		}
		vertexes.add(temp);
		return temp;
	}

	// O(V*E)
	void removeVertex(UniqueWeightedGraphVertex<T,W>* vertex) {
		// remove edges that connect to vertex and vertex itself from graph
		std::size_t originalSize = vertexes.size();
		// remove edges that connect to vertex
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			std::vector<std::pair<UniqueWeightedGraphVertex<T,W>*,W>>& edges = (*(*it))->edges;
			for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
				if((*it2).first ==  vertex) {
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
	bool isEdge(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right) const {
		// check if edge doesn't already exist
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it).first==right) {
				return true;
			}
		}
		return false;
	}

	// O(1|2)
	void createEdge(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right, const W& weight, const bool& directed = true) {
		left->edges.push_back(std::make_pair(right,weight));
		if(!directed) createEdge(right, left, weight, true);
	}

	// O(E|2E)
	void removeEdge(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right, const bool& directed = true) {
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it).first==right) {
				it = left->edges.erase(it);
				return;
			}
		}
		throw std::out_of_range("Edge not found!");
		if(!directed) removeEdge(right, left, true);
	}

	// O(E)
	const W& getWeight(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right) const {
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it).first==right) {
				return (*it).second;
			}
		}
		throw std::out_of_range("Edge not found!");
	}

	// O(1)
	const std::size_t& getSize() const {
		return vertexes.size();
	}

	// O(V*E)
	bool isPath(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right) const {
		HashSet<UniqueWeightedGraphVertex<T,W>*, compareVertex, hashVertex> visited;
		Queue<UniqueWeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		visited.add(left);
		while(!queue.isEmpty()) {
			UniqueWeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<UniqueWeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				UniqueWeightedGraphVertex<T,W>* tmp = (*it).first;
				if(!visited.contains(tmp)) {
					if(tmp==right) return true;
					visited.add(tmp);
					queue.push(tmp);
				}
			}
		}
		return false;
	}

	// O(V*E)
	std::size_t getDistance(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right) const {
		HashMap<UniqueWeightedGraphVertex<T,W>*, long, compareVertexDistance, hashVertexDistance> visited;
		Queue<UniqueWeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		visited.set(left,0);
		while(!queue.isEmpty()) {
			UniqueWeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<UniqueWeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				UniqueWeightedGraphVertex<T,W>* tmp = (*it).first;
				if(!visited.containsKey(tmp)) {
					if(tmp==right) return visited.get(node)+1;
					visited.set(tmp, visited.get(node)+1);
					queue.push(tmp);
				}
			}
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E)
	std::vector<UniqueWeightedGraphVertex<T,W>*> getPath(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right) {
		HashMap<UniqueWeightedGraphVertex<T,W>*, UniqueWeightedGraphVertex<T,W>*, compareVertexParent, hashVertexParent> visited;
		Queue<UniqueWeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		visited.set(left,nullptr);
		while(!queue.isEmpty()) {
			UniqueWeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<UniqueWeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				UniqueWeightedGraphVertex<T,W>* tmp = (*it).first;
				if(!visited.containsKey(tmp)) {
					if(tmp==right) {
						std::vector<UniqueWeightedGraphVertex<T,W>*> response;
						response.push_back(right);
						UniqueWeightedGraphVertex<T,W>* parent = node;
						while(parent!=nullptr) {
							response.push_back(parent);
							parent = visited.get(parent);
						}
						return response;
					}
					visited.set(tmp, node);
					queue.push(tmp);
				}
			}
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E)
	void iterate(UniqueWeightedGraphVertex<T,W>* start, UniqueWeightedGraphEdgeVisitor<T,W>* visitor) {
		HashSet<UniqueWeightedGraphVertex<T,W>*, compareVertex, hashVertex> visited;
		Queue<UniqueWeightedGraphVertex<T,W>*> queue;
		queue.push(start);
		visited.add(start);
		while(!queue.isEmpty()) {
			UniqueWeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<UniqueWeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				UniqueWeightedGraphVertex<T,W>* tmp = (*it).first;
				if(!visited.contains(tmp)) {
					visitor->visit(*it);
					visited.add(tmp);
					queue.push(tmp);
				}
			}
		}
	}

	// O(V)
	void iterate(UniqueWeightedGraphVertexVisitor<T,W>* visitor) {
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			visitor->visit(*(*it));
		}
	}

	// O(1)
	bool contains(const T& data) const {
		UniqueWeightedGraphVertex<T,W> temp;
		temp.data = data;
		return vertexes.contains(&temp);
	}

	// O(2)
	UniqueWeightedGraphVertex<T,W>* search(const T& data) {
		UniqueWeightedGraphVertex<T,W> temp;
		temp.data = data;
		if(!vertexes.contains(&temp)) return nullptr;
		return *(vertexes.find(&temp));
	}
private:
	HashSet<UniqueWeightedGraphVertex<T,W>*, compareVertex, hashVertex> vertexes;
};


#endif /* SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_ */
