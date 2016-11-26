/*
 * WeightedGraph.h
 *
 *  Created on: Nov 5, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPH_H_
#define SRC_GRAPH_WEIGHTEDGRAPH_H_

#include "../container/Queue.h"
#include <vector>
#include "BFS.h"

template<typename T, typename W>
struct WeightedGraphVertex {
	T data;
	std::vector<std::pair<WeightedGraphVertex<T,W>*,W>> edges;
	// BFS parameters
	BFSColor color;
	std::size_t distance;
	WeightedGraphVertex<T,W>* parent;
};

template<typename T,typename W>
class WeightedGraphVertexVisitor {
public:
	virtual ~WeightedGraphVertexVisitor(){};

	virtual void visit(WeightedGraphVertex<T,W>*& element) = 0;
};

template<typename T,typename W>
class WeightedGraphEdgeVisitor {
public:
	virtual ~WeightedGraphEdgeVisitor(){};

	virtual void visit(const std::pair<WeightedGraphVertex<T,W>*,W>& element) = 0;
};

template<typename T,typename W>
class WeightedGraph {
public:
	WeightedGraph(){

	}

	// O(V)
	~WeightedGraph(){
		// deallocate all vertexes
		for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
			delete (*it);
		}
	}

	// O(1)
	WeightedGraphVertex<T,W>* createVertex(const T& data) {
		WeightedGraphVertex<T,W>* temp = new WeightedGraphVertex<T,W>();
		temp->data = data;
		temp->color = WHITE;
		temp->parent = nullptr;
		vertexes.push_back(temp);
		return temp;
	}

	// O(V*E)
	void removeVertex(WeightedGraphVertex<T,W>* vertex) {
		// remove edges that connect to vertex and vertex itself from graph
		std::size_t originalSize = vertexes.size();
		for(auto it1=vertexes.begin(); it1!=vertexes.end(); ++it1) {
			// remove edges that connect to vertex
			std::vector<std::pair<WeightedGraphVertex<T,W>*,W>>& edges = (*it1)->edges;
			for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
				if((*it2).first ==  vertex) {
					it2 = edges.erase(it2);
					break;
				}
			}

			// remove from graph
			if(*it1 ==  vertex) {
				it1 = vertexes.erase(it1);
			}
		}
		if(vertexes.size() == originalSize) {
			throw std::out_of_range("Vertex not found!");
		}
		// deallocates vertex
		delete vertex;
	}

	// O(E)
	bool isEdge(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right) const {
		// check if edge doesn't already exist
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it).first==right) {
				return true;
			}
		}
		return false;
	}

	// O(1|2)
	void createEdge(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right, const W& weight, const bool& directed = true) {
		left->edges.push_back(std::make_pair(right,weight));
		if(!directed) createEdge(right, left, weight, true);
	}

	// O(E|2E)
	void removeEdge(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right, const bool& directed = true) {
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
	const W& getWeight(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right) const {
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it).first==right) {
				return (*it).second;
			}
		}
		throw std::out_of_range("Edge not found!");
	}

	// O(1)
	std::size_t getSize() const {
		return vertexes.size();
	}

	// O(V*E+V)
	bool isPath(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right) const {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
		}
		left->color = GREY;
		Queue<WeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		while(!queue.isEmpty()) {
			WeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<WeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it).first->color == WHITE) {
					if((*it).first==right) return true;
					(*it).first->color = GREY;
					queue.push((*it).first);
				}
			}
			node->color = BLACK;
		}
		return false;
	}

	// O(V*E+V)
	std::size_t getDistance(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right) const {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
			(*it)->distance = -1;
		}
		left->color = GREY;
		left->distance = 0;
		Queue<WeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		while(!queue.isEmpty()) {
			WeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<WeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it).first->color == WHITE) {
					if((*it).first==right) {
						return node->distance + 1;
					}
					(*it).first->color = GREY;
					(*it).first->distance = node->distance + 1;
					queue.push((*it).first);
				}
			}
			node->color = BLACK;
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E+V)
	std::vector<WeightedGraphVertex<T,W>*> getPath(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right) {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
			(*it)->parent = nullptr;
		}
		left->color = GREY;
		Queue<WeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		while(!queue.isEmpty()) {
			WeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<WeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it).first->color == WHITE) {
					if((*it).first==right) {
						std::vector<WeightedGraphVertex<T,W>*> response;
						response.push_back(right);
						WeightedGraphVertex<T,W>* parent = node;
						while(parent!=nullptr) {
							response.push_back(parent);
							parent = parent->parent;
						}
						return response;
					}
					(*it).first->color = GREY;
					(*it).first->parent = node;
					queue.push((*it).first);
				}
			}
			node->color = BLACK;
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E+V)
	void iterate(WeightedGraphVertex<T,W>* start, WeightedGraphEdgeVisitor<T,W>* visitor) {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
		}
		start->color = GREY;
		Queue<WeightedGraphVertex<T,W>*> queue;
		queue.push(start);
		while(!queue.isEmpty()) {
			WeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<std::pair<WeightedGraphVertex<T,W>*,W>> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it).first->color == WHITE) {
					visitor->visit(*it);
					(*it).first->color = GREY;
					queue.push((*it).first);
				}
			}
			node->color = BLACK;
		}
	}

	// O(V)
	void iterate(WeightedGraphVertexVisitor<T,W>* visitor) {
		for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
			visitor->visit(*it);
		}
	}

	// O(V)
	bool contains(const T& data, int (*comparator)(const T&, const T&)) const {
		for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
			if(comparator(data, (*it)->data)==0) return true;
		}
		return false;
	}

	// O(V)
	std::vector<WeightedGraphVertex<T,W>*> search(const T& data, int (*comparator)(const T&, const T&)) const {
		std::vector<WeightedGraphVertex<T,W>*> response;
		for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
			if(comparator(data, (*it)->data)==0) {
				response.push_back(*it);
			}
		}
		return response;
	}
private:
	std::vector<WeightedGraphVertex<T,W>*> vertexes;
};




#endif /* SRC_GRAPH_WEIGHTEDGRAPH_H_ */
