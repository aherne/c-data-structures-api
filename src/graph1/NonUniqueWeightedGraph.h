/*
 * NonUniqueWeightedGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH1_NONUNIQUEWEIGHTEDGRAPH_H_
#define SRC_GRAPH1_NONUNIQUEWEIGHTEDGRAPH_H_


#include "../container/Queue.h"
#include "BFSWeightedGraphVertex.h"
#include "WeightedGraph.h"

template<typename T, typename W>
class NonUniqueWeightedGraph : public WeightedGraph<T,W> {
public:
		// O(V)
		~NonUniqueWeightedGraph(){
			// deallocate all vertexes
			for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
				delete (*it);
			}
		}

		// O(1)
		WeightedGraphVertex<T,W>* createVertex(const T& data) {
			BFSWeightedGraphVertex<T,W>* temp = new BFSWeightedGraphVertex<T,W>(data);
			vertexes.push_back(temp);
			return temp;
		}

		// O(V*E)
		void removeVertex(WeightedGraphVertex<T,W>*& vertex) {
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
		bool isPath(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const {
			for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
				(*it)->setColor(WHITE);
			}
			BFSWeightedGraphVertex<T,W>* leftConverted = (BFSWeightedGraphVertex<T,W>*) left;
			leftConverted->setColor(GREY);
			Queue<BFSWeightedGraphVertex<T,W>*> queue;
			queue.push(leftConverted);
			while(!queue.isEmpty()) {
				BFSWeightedGraphVertex<T,W>* node = queue.pop();
				std::vector<WeightedGraphEdge<T,W>*> children = node->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					BFSWeightedGraphVertex<T,W>* tmp = (BFSWeightedGraphVertex<T,W>*) (*it)->vertex;
					if(tmp->getColor() == WHITE) {
						if((*it)->vertex==right) return true;
						tmp->setColor(GREY);
						queue.push(tmp);
					}
				}
				node->setColor(BLACK);
			}
			return false;
		}

		// O(V*E+V)
		std::size_t getDistance(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const {
			for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
				(*it)->setColor(WHITE);
				(*it)->setParent(nullptr);
			}

			BFSWeightedGraphVertex<T,W>* leftConverted = (BFSWeightedGraphVertex<T,W>*) left;
			leftConverted->setColor(GREY);

			WeightedGraphEdge<T,W> baseEdge;
			baseEdge.vertex = leftConverted;
			baseEdge.weight = 0;

			Queue<WeightedGraphEdge<T,W>*> queue;
			queue.push(&baseEdge);
			while(!queue.isEmpty()) {
				WeightedGraphEdge<T,W>* node = queue.pop();
				std::vector<WeightedGraphEdge<T,W>*> children = node->vertex->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					BFSWeightedGraphVertex<T,W>* tmp = (BFSWeightedGraphVertex<T,W>*) (*it)->vertex;
					if(tmp->getColor() == WHITE) {
						if((*it)->vertex==right) {
							std::size_t response = 0;
							WeightedGraphEdge<T,W>* parent = node;
							while(parent!=nullptr) {
								parent = ((BFSWeightedGraphVertex<T,W>*) parent->vertex)->getParent();
								++response;
							}
							return response;
						}
						tmp->setColor(GREY);
						tmp->setParent(node);
						queue.push((*it));
					}
				}
				((BFSWeightedGraphVertex<T,W>*) node->vertex)->setColor(BLACK);
			}
			throw std::out_of_range("Vertexes not connected!");
		}

		// O(V*E+V)
		std::vector<WeightedGraphEdge<T,W>*> getPath(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const {
			for(auto it = vertexes.begin(); it!=vertexes.end(); ++it) {
				(*it)->setColor(WHITE);
				(*it)->setParent(nullptr);
			}

			BFSWeightedGraphVertex<T,W>* leftConverted = (BFSWeightedGraphVertex<T,W>*) left;
			leftConverted->setColor(GREY);

			WeightedGraphEdge<T,W> baseEdge;
			baseEdge.vertex = leftConverted;
			baseEdge.weight = 0;

			Queue<WeightedGraphEdge<T,W>*> queue;
			queue.push(&baseEdge);
			while(!queue.isEmpty()) {
				WeightedGraphEdge<T,W>* node = queue.pop();
				std::vector<WeightedGraphEdge<T,W>*> children = node->vertex->getEdges();
				for(auto it = children.begin(); it != children.end(); ++it){
					BFSWeightedGraphVertex<T,W>* tmp = (BFSWeightedGraphVertex<T,W>*) (*it)->vertex;
					if(tmp->getColor() == WHITE) {
						if((*it)->vertex==right) {
							std::vector<WeightedGraphEdge<T,W>*> response;
							response.push_back(*it);
							WeightedGraphEdge<T,W>* parent = node;
							while(parent!=nullptr) {
								if(parent->vertex == left) break;
								response.push_back(parent);
								parent = ((BFSWeightedGraphVertex<T,W>*) parent->vertex)->getParent();
							}
							return response;
						}
						tmp->setColor(GREY);
						tmp->setParent(node);
						queue.push((*it));
					}
				}
				((BFSWeightedGraphVertex<T,W>*) node->vertex)->setColor(BLACK);
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
		std::vector<WeightedGraphVertex<T,W>*> search(const T& data, int (*comparator)(const T&, const T&)) const {
			std::vector<WeightedGraphVertex<T,W>*> response;
			for(auto it=vertexes.begin(); it!=vertexes.end(); ++it) {
				if(comparator(data, (*it)->getData())==0) {
					response.push_back(*it);
				}
			}
			return response;
		}
	private:
		std::vector<BFSWeightedGraphVertex<T,W>*> vertexes;
};

#endif /* SRC_GRAPH1_NONUNIQUEWEIGHTEDGRAPH_H_ */
