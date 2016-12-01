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

template<typename T, typename W>
struct UniqueWeightedGraphEdge;

template<typename T,typename W>
struct UniqueWeightedGraphVertex {
	T data;
	std::vector<UniqueWeightedGraphEdge<T,W>*> edges;
};

template<typename T, typename W>
struct UniqueWeightedGraphEdge {
	UniqueWeightedGraphVertex<T,W>* vertex;
	W weight;
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
std::size_t hashVertexParent(const MapEntry<UniqueWeightedGraphEdge<T,W>*, UniqueWeightedGraphEdge<T,W>*>& entry) {
	return hash(entry.key->vertex->data);
}

template<typename T,typename W>
int compareVertexParent(const MapEntry<UniqueWeightedGraphEdge<T,W>*, UniqueWeightedGraphEdge<T,W>*>& left, const MapEntry<UniqueWeightedGraphEdge<T,W>*, UniqueWeightedGraphEdge<T,W>*>& right) {
	return comparator(left.key->vertex->data, right.key->vertex->data);
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

	virtual void visit(UniqueWeightedGraphEdge<T,W>* const element) = 0;
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
			for(auto it1 = (*(*it))->edges.begin(); it1 != (*(*it))->edges.end(); ++it1) {
				delete (*it1);
			}
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
		for(auto it1 = vertexes.begin(); *it1!=*(vertexes.end()); ++(*it1)) {
			// remove edges connecting to vertex
			std::vector<UniqueWeightedGraphEdge<T,W>*>& edges = (*(*it1))->edges;
			for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
				if((*it2)->vertex ==  vertex) {
					UniqueWeightedGraphEdge<T,W>* edgeToRemove = (*it2);
					it2 = edges.erase(it2);
					delete edgeToRemove;
					break;
				}
			}

			// remove edges starting from vertex
			if(*(*it1) ==  vertex) {
				for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
					delete (*it2);
				}
			}
		}
		vertexes.remove(vertex);
		delete vertex;
	}

	// O(E)
	bool isEdge(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right) const {
		// check if edge doesn't already exist
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it)->vertex==right) {
				return true;
			}
		}
		return false;
	}

	// O(1|2)
	void createEdge(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right, const W& weight, const bool& directed = true) {
		UniqueWeightedGraphEdge<T,W>* wge = new UniqueWeightedGraphEdge<T,W>;
		wge->vertex = right;
		wge->weight = weight;
		left->edges.push_back(wge);
		if(!directed) createEdge(right, left, weight, true);
	}

	// O(E|2E)
	void removeEdge(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right, const bool& directed = true) {
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it)->vertex==right) {
				delete (*it);
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
			if((*it)->vertex==right) {
				return (*it)->weight;
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
			std::vector<UniqueWeightedGraphEdge<T,W>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				UniqueWeightedGraphVertex<T,W>* tmp = (*it)->vertex;
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
			std::vector<UniqueWeightedGraphEdge<T,W>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				UniqueWeightedGraphVertex<T,W>* tmp = (*it)->vertex;
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
	std::vector<UniqueWeightedGraphEdge<T,W>*> getPath(UniqueWeightedGraphVertex<T,W>* left, UniqueWeightedGraphVertex<T,W>* right) {
		UniqueWeightedGraphEdge<T,W> element;
		element.vertex = left;
		element.weight = 0;

		HashMap<UniqueWeightedGraphEdge<T,W>*, UniqueWeightedGraphEdge<T,W>*, compareVertexParent, hashVertexParent> visited;
		Queue<UniqueWeightedGraphEdge<T,W>*> queue;
		queue.push(&element);
		visited.set(&element,nullptr);
		while(!queue.isEmpty()) {
			UniqueWeightedGraphEdge<T,W>* node = queue.pop();
			std::vector<UniqueWeightedGraphEdge<T,W>*> children = node->vertex->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if(!visited.containsKey(*it)) {
					if((*it)->vertex==right) {
						std::vector<UniqueWeightedGraphEdge<T,W>*> response;
						response.push_back(*it);
						UniqueWeightedGraphEdge<T,W>* parent = node;
						while(parent!=nullptr) {
							if(parent->vertex == left) break;
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
	void iterate(UniqueWeightedGraphVertex<T,W>* start, UniqueWeightedGraphEdgeVisitor<T,W>* visitor) {
		HashSet<UniqueWeightedGraphVertex<T,W>*, compareVertex, hashVertex> visited;
		Queue<UniqueWeightedGraphVertex<T,W>*> queue;
		queue.push(start);
		visited.add(start);
		while(!queue.isEmpty()) {
			UniqueWeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<UniqueWeightedGraphEdge<T,W>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				UniqueWeightedGraphVertex<T,W>* tmp = (*it)->vertex;
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
