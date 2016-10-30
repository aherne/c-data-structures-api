/*
 * WeightedGraph.h
 *
 *  Created on: Oct 21, 2016
 *      Author: Lucian
 */

#ifndef WEIGHTEDGRAPH_H_
#define WEIGHTEDGRAPH_H_



template<typename T, typename W>
class WeightedGraphVertex {
	public:
		WeightedGraphVertex(const T& data) {
			this->data = data;
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() {
			return data;
		}

		const std::vector<std::pair<WeightedGraphVertex<T,W>*,W>>& getEdges() {
			return edges;
		}

		void addEdge(WeightedGraphVertex<T,W>*& vertex, const W& weight) {
			edges.push_back(std::make_pair(vertex,weight));
		}

		bool removeEdge(WeightedGraphVertex<T,W>* vertex) {
			for(auto it=edges.begin(); it!=edges.end(); ++it) {
				if((*it).first == vertex) {
					it = edges.erase(it);
					return true;
				}
			}
			return false;
		}
	private:
		T data;
		std::vector<std::pair<WeightedGraphVertex<T,W>*,W>> edges;
};



#endif /* WEIGHTEDGRAPH_H_ */
