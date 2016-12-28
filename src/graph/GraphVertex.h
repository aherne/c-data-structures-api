/*
 * GraphVertex.h
 *
 *  Created on: Dec 22, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_GRAPHVERTEX_H_
#define SRC_GRAPH_GRAPHVERTEX_H_

#include <vector>

template<typename T>
class GraphVertex {
	public:
		GraphVertex(const T& data) {
			this->data = data;
		}

		~GraphVertex() {
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() const {
			return this->data;
		}

		const std::vector<GraphVertex<T>*>& getEdges() const {
			return edges;
		}

		bool isEdge(GraphVertex<T>*& vertex) const {
			for(auto it = edges.begin(); it != edges.end(); ++it) {
				if((*it)==vertex) {
					return true;
				}
			}
			return false;
		}

		void addEdge(GraphVertex<T>*& vertex) {
			edges.push_back(vertex);
		}

		void removeEdge(GraphVertex<T>*& vertex) {
			for(auto it=edges.begin(); it!=edges.end(); ++it) {
				if(*it == vertex) {
					it = edges.erase(it);
					return;
				}
			}
		}
	protected:
		T data;
		std::vector<GraphVertex<T>*> edges;
};

#endif /* SRC_GRAPH_GRAPHVERTEX_H_ */
