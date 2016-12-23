/*
 * WeightedGraphVertex.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH1_WEIGHTEDGRAPHVERTEX_H_
#define SRC_GRAPH1_WEIGHTEDGRAPHVERTEX_H_

#include <vector>

template<typename T, typename W>
struct WeightedGraphEdge;

template<typename T, typename W>
class WeightedGraphVertex {
	public:
		WeightedGraphVertex(const T& data) {
			this->data = data;
		}

		~WeightedGraphVertex() {
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() const {
			return this->data;
		}

		const std::vector<WeightedGraphEdge<T,W>>& getEdges() const {
			return edges;
		}

		bool isEdge(WeightedGraphVertex<T,W>*& vertex) const {
			for(auto it = edges.begin(); it != edges.end(); ++it) {
				if((*it).vertex==vertex) {
					return true;
				}
			}
			return false;
		}

		const W& getEdgeWeight(WeightedGraphVertex<T,W>*& vertex) const {
			for(auto it = edges.begin(); it != edges.end(); ++it) {
				if((*it).vertex==vertex) {
					return  (*it).weight;
				}
			}
			throw std::out_of_range("Edge not found!");
		}

		void setEdgeWeight(WeightedGraphVertex<T,W>*& vertex, const W& weight) {
			for(auto it = edges.begin(); it != edges.end(); ++it) {
				if((*it).vertex==vertex) {
					(*it).weight = weight;
					return;
				}
			}
			throw std::out_of_range("Edge not found!");
		}

		void addEdge(WeightedGraphVertex<T,W>*& vertex, const W& weight) {
			WeightedGraphEdge<T,W> wge;
			wge.vertex = vertex;
			wge.weight = weight;
			edges.push_back(wge);
		}

		void removeEdge(WeightedGraphVertex<T,W>*& vertex) {
			for(auto it=edges.begin(); it!=edges.end(); ++it) {
				if((*it).vertex == vertex) {
					it = edges.erase(it);
					return;
				}
			}
		}
	protected:
		T data;
		std::vector<WeightedGraphEdge<T,W>> edges;
};


template<typename T, typename W>
struct WeightedGraphEdge {
	WeightedGraphVertex<T,W>* vertex;
	W weight;
};



#endif /* SRC_GRAPH1_WEIGHTEDGRAPHVERTEX_H_ */
