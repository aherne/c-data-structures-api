/*
 * Graph.h
 *
 *  Created on: Oct 17, 2016
 *      Author: Lucian
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "../container/Queue.h"
#include <vector>

#include "../graph_old/BFS.h"


template<typename T>
struct GraphVertex {
	T data;
	std::vector<GraphVertex<T>*> edges;
	// BFS parameters
	BFSColor color;
	GraphVertex<T>* parent;
};

template<typename T>
class GraphVertexVisitor {
public:
	virtual ~GraphVertexVisitor(){};

	virtual void visit(GraphVertex<T>*& element) = 0;
};

template<typename T>
class Graph {
public:
	Graph(){

	}

	// O(V)
	~Graph(){
		// deallocate all vertexes
		for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
			delete (*it);
		}
	}

	// O(1)
	GraphVertex<T>* createVertex(const T& data) {
		GraphVertex<T>* temp = new GraphVertex<T>();
		temp->data = data;
		temp->color = WHITE;
		temp->parent = nullptr;
		vertexes.push_back(temp);
		return temp;
	}

	// O(V*E)
	void removeVertex(GraphVertex<T>* vertex) {
		// remove edges that connect to vertex and vertex itself from graph
		std::size_t originalSize = vertexes.size();
		for(auto it1=vertexes.begin(); it1!=vertexes.end(); ++it1) {
			// remove edges that connect to vertex
			std::vector<GraphVertex<T>*>& edges = (*it1)->edges;
			for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
				if(*it2 ==  vertex) {
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
	bool isEdge(GraphVertex<T>* left, GraphVertex<T>* right) const {
		// check if edge doesn't already exist
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it)==right) {
				return true;
			}
		}
		return false;
	}

	// O(1|2)
	void createEdge(GraphVertex<T>* left, GraphVertex<T>* right, const bool& directed = true) {
		left->edges.push_back(right);
		if(!directed) createEdge(right, left, true);
	}

	// O(E|2E)
	void removeEdge(GraphVertex<T>* left, GraphVertex<T>* right, const bool& directed = true) {
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

	// O(V*E+V)
	bool isPath(GraphVertex<T>* left, GraphVertex<T>* right) const {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
		}
		left->color = GREY;
		Queue<GraphVertex<T>*> queue;
		queue.push(left);
		while(!queue.isEmpty()) {
			GraphVertex<T>* node = queue.pop();
			std::vector<GraphVertex<T>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->color == WHITE) {
					if((*it)==right) return true;
					(*it)->color = GREY;
					queue.push(*it);
				}
			}
			node->color = BLACK;
		}
		return false;
	}

	// O(V*E+V)
	std::size_t getDistance(GraphVertex<T>* left, GraphVertex<T>* right) const {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
			(*it)->parent = nullptr;
		}
		left->color = GREY;
		Queue<GraphVertex<T>*> queue;
		queue.push(left);
		while(!queue.isEmpty()) {
			GraphVertex<T>* node = queue.pop();
			std::vector<GraphVertex<T>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->color == WHITE) {
					if((*it)==right) {
						std::size_t response = 0;
						GraphVertex<T>* parent = node;
						while(parent!=nullptr) {
							parent = parent->parent;
							++ response;
						}
						return response;
					}
					(*it)->color = GREY;
					(*it)->parent = node;
					queue.push(*it);
				}
			}
			node->color = BLACK;
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E+V)
	std::vector<GraphVertex<T>*> getPath(GraphVertex<T>* left, GraphVertex<T>* right) {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
			(*it)->parent = nullptr;
		}
		left->color = GREY;
		Queue<GraphVertex<T>*> queue;
		queue.push(left);
		while(!queue.isEmpty()) {
			GraphVertex<T>* node = queue.pop();
			std::vector<GraphVertex<T>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->color == WHITE) {
					if((*it)==right) {
						std::vector<GraphVertex<T>*> response;
						response.push_back(right);
						GraphVertex<T>* parent = node;
						while(parent!=nullptr) {
							response.push_back(parent);
							parent = parent->parent;
						}
						return response;
					}
					(*it)->color = GREY;
					(*it)->parent = node;
					queue.push(*it);
				}
			}
			node->color = BLACK;
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E+V)
	void iterate(GraphVertex<T>* start, GraphVertexVisitor<T>* visitor) {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
		}
		start->color = GREY;
		Queue<GraphVertex<T>*> queue;
		queue.push(start);
		while(!queue.isEmpty()) {
			GraphVertex<T>* node = queue.pop();
			std::vector<GraphVertex<T>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->color == WHITE) {
					visitor->visit(*it);
					(*it)->color = GREY;
					queue.push(*it);
				}
			}
			node->color = BLACK;
		}
	}

	// O(V)
	void iterate(GraphVertexVisitor<T>* visitor) {
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
	std::vector<GraphVertex<T>*> search(const T& data, int (*comparator)(const T&, const T&)) const {
		std::vector<GraphVertex<T>*> response;
		for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
			if(comparator(data, (*it)->data)==0) {
				response.push_back(*it);
			}
		}
		return response;
	}
private:
	std::vector<GraphVertex<T>*> vertexes;
};
#endif /* GRAPH_H_ */
