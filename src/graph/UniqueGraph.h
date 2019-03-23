/*
 * UniqueGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNIQUEGRAPH_H_
#define SRC_GRAPH_UNIQUEGRAPH_H_


#include "../container/Queue.h"
#include "Graph.h"
#include "GraphVertex.h"
#include "../set/HashSet.h"
#include "../map/HashMap.h"
#include "GraphUtilities.h"


template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
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
			// remove edges that connect to vertex
			for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
				(*(*it))->removeEdge(vertex);
			}
			vertexes.remove(vertex);
			// deallocates vertex
			delete vertex;
		}

		// O(1)
		std::size_t getSize() const {
			return vertexes.size();
		}

		// O(V*E)
		bool isConnected(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			HashSet<GraphVertex<T>*, compareVertex<T, compare>, hashVertex<T, hash>> visited;
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
		std::vector<GraphVertex<T>*> getShortestPath(GraphVertex<T>*& left, GraphVertex<T>*& right) const {
			HashMap<GraphVertex<T>*, GraphVertex<T>*, compareVertex<T, compare>, hashVertex<T, hash>> visited;
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
		HashSet<GraphVertex<T>*, compareVertex<T, compare>, hashVertex<T, hash>> vertexes;
};



#endif /* SRC_GRAPH_UNIQUEGRAPH_H_ */
