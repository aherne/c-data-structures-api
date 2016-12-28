/*
 * NonUniqueGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_NONUNIQUEGRAPH_H_
#define SRC_GRAPH_NONUNIQUEGRAPH_H_

#include "../container/Queue.h"
#include "BFSGraphVertex.h"
#include "Graph.h"

template<typename T>
class NonUniqueGraph : public Graph<T> {
public:
		// O(V)
		~NonUniqueGraph(){
			// deallocate all vertexes
			for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
				delete (*it);
			}
		}

		// O(1)
		GraphVertex<T>* createVertex(const T& data) {
			BFSGraphVertex<T>* temp = new BFSGraphVertex<T>(data);
			vertexes.push_back(temp);
			return temp;
		}

		// O(V*E)
		void removeVertex(GraphVertex<T>*& vertex) {
			// remove edges that connect to vertex and vertex itself from graph
			std::size_t originalSize = vertexes.size();
			for(auto it1=vertexes.begin(); it1!=vertexes.end(); ++it1) {
				// remove edges that connect to vertex
				(*it1)->removeEdge(vertex);

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

		// O(1)
		std::size_t getSize() const {
			return vertexes.size();
		}

		// O(V*E+V)
		bool isPath(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
				(*it)->setColor(WHITE);
			}
			BFSGraphVertex<T>* leftConverted = (BFSGraphVertex<T>*) left;
			leftConverted->setColor(GREY);
			Queue<BFSGraphVertex<T>*> queue;
			queue.push(leftConverted);
			while(!queue.isEmpty()) {
				BFSGraphVertex<T>* node = queue.pop();
				std::vector<GraphVertex<T>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					BFSGraphVertex<T>* tmp = (BFSGraphVertex<T>*) *it;
					if(tmp->getColor() == WHITE) {
						if((*it)==right) return true;
						tmp->setColor(GREY);
						queue.push(tmp);
					}
				}
				node->setColor(BLACK);
			}
			return false;
		}

		// O(V*E+V)
		std::size_t getDistance(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
				(*it)->setColor(WHITE);
				(*it)->setParent(nullptr);
			}
			BFSGraphVertex<T>* leftConverted = (BFSGraphVertex<T>*) left;
			leftConverted->setColor(GREY);
			Queue<BFSGraphVertex<T>*> queue;
			queue.push(leftConverted);
			while(!queue.isEmpty()) {
				BFSGraphVertex<T>* node = queue.pop();
				std::vector<GraphVertex<T>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					BFSGraphVertex<T>* tmp = (BFSGraphVertex<T>*) *it;
					if(tmp->getColor() == WHITE) {
						if((*it)==right) {
							std::size_t response = 0;
							BFSGraphVertex<T>* parent = node;
							while(parent!=nullptr) {
								parent = parent->getParent();
								++ response;
							}
							return response;
						}
						tmp->setColor(GREY);
						tmp->setParent(node);
						queue.push(tmp);
					}
				}
				node->setColor(BLACK);
			}
			throw std::out_of_range("Vertexes not connected!");
		}

		// O(V*E+V)
		std::vector<GraphVertex<T>*> getPath(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
				(*it)->setColor(WHITE);
				(*it)->setParent(nullptr);
			}
			BFSGraphVertex<T>* leftConverted = (BFSGraphVertex<T>*) left;
			leftConverted->setColor(GREY);
			Queue<BFSGraphVertex<T>*> queue;
			queue.push(leftConverted);
			while(!queue.isEmpty()) {
				BFSGraphVertex<T>* node = queue.pop();
				std::vector<GraphVertex<T>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					BFSGraphVertex<T>* tmp = (BFSGraphVertex<T>*) *it;
					if(tmp->getColor() == WHITE) {
						if((*it)==right) {
							std::vector<GraphVertex<T>*> response;
							response.push_back(right);
							BFSGraphVertex<T>* parent = node;
							while(parent!=nullptr) {
								response.push_back(parent);
								parent = parent->getParent();
							}
							return response;
						}
						tmp->setColor(GREY);
						tmp->setParent(node);
						queue.push(tmp);
					}
				}
				node->setColor(BLACK);
			}
			throw std::out_of_range("Vertexes not connected!");
		}

		// O(V)
		bool contains(const T& data, int (*comparator)(const T&, const T&)) const {
			for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
				if(comparator(data, (*it)->getData())==0) return true;
			}
			return false;
		}

		// O(V)
		std::vector<GraphVertex<T>*> search(const T& data, int (*comparator)(const T&, const T&)) const {
			std::vector<GraphVertex<T>*> response;
			for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
				if(comparator(data, (*it)->getData())==0) {
					response.push_back(*it);
				}
			}
			return response;
		}

		// O(V*E+V)
		void iterate(GraphVertex<T>*& start, GraphVertexVisitor<T>& visitor) {
			for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
				(*it)->setColor(WHITE);
			}
			BFSGraphVertex<T>* leftConverted = (BFSGraphVertex<T>*) start;
			leftConverted->setColor(GREY);
			Queue<BFSGraphVertex<T>*> queue;
			queue.push(leftConverted);
			while(!queue.isEmpty()) {
				BFSGraphVertex<T>* node = queue.pop();
				std::vector<GraphVertex<T>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					BFSGraphVertex<T>* tmp = (BFSGraphVertex<T>*) *it;
					if(tmp->getColor() == WHITE) {
						visitor.visit(tmp);
						tmp->setColor(GREY);
						queue.push(tmp);
					}
				}
				node->setColor(BLACK);
			}
		}

		// O(V)
		void iterate(GraphVertexVisitor<T>& visitor) {
			for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
				visitor.visit(*it);
			}
		}
	private:
		std::vector<BFSGraphVertex<T>*> vertexes;
};


#endif /* SRC_GRAPH_NONUNIQUEGRAPH_H_ */
