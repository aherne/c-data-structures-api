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
struct WeightedGraphEdge;;

template<typename T, typename W>
struct WeightedGraphVertex {
	T data;
	std::vector<WeightedGraphEdge<T,W>*> edges;
	// BFS parameters
	BFSColor color;
	WeightedGraphEdge<T,W>* parent;
	// TODO: store parent in such a way when connecting paths are returned weight is included with O(1) costs
	// TODO: getShortestWeightedDistance (shortest path != shortest weighted distance => DFS???)
};

template<typename T, typename W>
struct WeightedGraphEdge {
	WeightedGraphVertex<T,W>* vertex;
	W weight;
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

	virtual void visit(WeightedGraphEdge<T,W>* const element) = 0;
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
			for(auto it1 = (*it)->edges.begin(); it1 != (*it)->edges.end(); ++it1) {
				delete (*it1);
			}
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
			// remove edges that connect to/from vertex
			std::vector<WeightedGraphEdge<T,W>*>& edges = (*it1)->edges;
			for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
				if((*it2)->vertex ==  vertex) {
					WeightedGraphEdge<T,W>* edgeToRemove = (*it2);
					it2 = edges.erase(it2);
					delete edgeToRemove;
					break;
				}
			}

			// remove from graph
			if(*it1 ==  vertex) {
				for(auto it2 = edges.begin(); it2!=edges.end(); ++it2) {
					delete (*it2);
				}
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
			if((*it)->vertex==right) {
				return true;
			}
		}
		return false;
	}

	// O(1|2)
	void createEdge(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right, const W& weight, const bool& directed = true) {
		WeightedGraphEdge<T,W>* wge = new WeightedGraphEdge<T,W>;
		wge->vertex = right;
		wge->weight = weight;
		left->edges.push_back(wge);
		if(!directed) createEdge(right, left, weight, true);
	}

	// O(E|2E)
	void removeEdge(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right, const bool& directed = true) {
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
	const W& getWeight(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right) const {
		for(auto it = left->edges.begin(); it != left->edges.end(); ++it) {
			if((*it)->vertex==right) {
				return (*it)->weight;
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
			std::vector<WeightedGraphEdge<T,W>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->vertex->color == WHITE) {
					if((*it)->vertex==right) return true;
					(*it)->vertex->color = GREY;
					queue.push((*it)->vertex);
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
			(*it)->parent = nullptr;
		}
		left->color = GREY;

		WeightedGraphEdge<T,W> element;
		element.vertex = left;
		element.weight = 0;

		Queue<WeightedGraphEdge<T,W>*> queue;
		queue.push(&element);
		while(!queue.isEmpty()) {
			WeightedGraphEdge<T,W>* node = queue.pop();
			std::vector<WeightedGraphEdge<T,W>*> children = node->vertex->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->vertex->color == WHITE) {
					if((*it)->vertex==right) {
						std::size_t response = 0;
						WeightedGraphEdge<T,W>* parent = node;
						while(parent!=nullptr) {
							parent = parent->vertex->parent;
							++response;
						}
						return response;
					}
					(*it)->vertex->color = GREY;
					(*it)->vertex->parent = node;
					queue.push((*it));
				}
			}
			node->vertex->color = BLACK;
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E+V)
	std::vector<WeightedGraphEdge<T,W>*> getPath(WeightedGraphVertex<T,W>* left, WeightedGraphVertex<T,W>* right) {
		for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
			(*it)->color = WHITE;
			(*it)->parent = nullptr;
		}
		left->color = GREY;

		WeightedGraphEdge<T,W> element;
		element.vertex = left;
		element.weight = 0;

		Queue<WeightedGraphEdge<T,W>*> queue;
		queue.push(&element);
		while(!queue.isEmpty()) {
			WeightedGraphEdge<T,W>* node = queue.pop();
			std::vector<WeightedGraphEdge<T,W>*> children = node->vertex->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->vertex->color == WHITE) {
					if((*it)->vertex==right) {
						std::vector<WeightedGraphEdge<T,W>*> response;
						WeightedGraphEdge<T,W>* parent = node;
						while(parent!=nullptr) {
							response.push_back(parent);
							parent = parent->vertex->parent;
						}
						return response;
					}
					(*it)->vertex->color = GREY;
					(*it)->vertex->parent = node;
					queue.push((*it));
				}
			}
			node->vertex->color = BLACK;
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
			std::vector<WeightedGraphEdge<T,W>*> children = node->edges;
			for(auto it = children.begin(); it != children.end(); ++it){
				if((*it)->vertex->color == WHITE) {
					visitor->visit(*it);
					(*it)->vertex->color = GREY;
					queue.push((*it)->vertex);
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
