/*
 * WeightedGraphVertex.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPHVERTEX_H_
#define SRC_GRAPH_WEIGHTEDGRAPHVERTEX_H_

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class WeightedGraphVertex;

template<typename T,typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
int compareWeightedVertex(WeightedGraphVertex<T,W,compare,hash>* const& left, WeightedGraphVertex<T,W,compare,hash>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T,typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
std::size_t hashWeightedVertex(WeightedGraphVertex<T,W,compare,hash>* const& node) {
	return hash(node->getData());
}

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class WeightedGraphVertex {
	public:
		WeightedGraphVertex(const T& data) {
			this->data = data;
			this->edges = new HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>;
		}

		~WeightedGraphVertex() {
			delete edges;
		}

		void setData(const T& data) {
			this->data = data;
		}

		const T& getData() const {
			return this->data;
		}

		HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>*& getEdges() {
			return edges;
		}

		bool isEdge(WeightedGraphVertex<T,W,compare,hash>*& vertex) const {
			return edges->containsKey(vertex);
		}

		const W& getEdgeWeight(WeightedGraphVertex<T,W,compare,hash>*& vertex) const {
			return edges->get(vertex);
		}

		void setEdgeWeight(WeightedGraphVertex<T,W,compare,hash>*& vertex, const W& weight) {
			edges->set(vertex, weight);
		}

		void addEdge(WeightedGraphVertex<T,W,compare,hash>*& vertex, const W& weight) {
			edges->set(vertex, weight);
		}

		void removeEdge(WeightedGraphVertex<T,W,compare,hash>*& vertex) {
			if(edges->containsKey(vertex)) {
				edges->removeKey(vertex);
			}
		}

		// O(V*E)
		bool isConnected(WeightedGraphVertex<T,W,compare,hash>*& right) const {
			WeightedGraphVertex<T,W, compare, hash>* left = (WeightedGraphVertex<T,W, compare, hash>*) this;
			HashSet<WeightedGraphVertex<T,W,compare,hash>*, compareWeightedVertex<T, W, compare,hash>, hashWeightedVertex<T, W, compare,hash>> visited;
			Queue<WeightedGraphVertex<T,W,compare,hash>*> queue;
			queue.push(left);
			visited.add(left);
			while(!queue.isEmpty()) {
				WeightedGraphVertex<T,W,compare,hash>* node = queue.pop();
				HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* children = node->getEdges();
				for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
					WeightedGraphVertex<T,W,compare,hash>* tmp = (*(*it)).first;
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
		ArrayList<WeightedGraphVertex<T,W,compare,hash>*> getShortestPath(WeightedGraphVertex<T,W,compare,hash>*& right) const {
			WeightedGraphVertex<T,W,compare,hash>* left = (WeightedGraphVertex<T,W,compare,hash>*) this;
			HashMap<WeightedGraphVertex<T,W,compare,hash>*, WeightedGraphVertex<T,W,compare,hash>*, compareWeightedVertex<T,W,compare,hash>, hashWeightedVertex<T, W, compare, hash>> visited;
			Queue<WeightedGraphVertex<T,W,compare,hash>*> queue;
			queue.push(left);
			visited.set(left,nullptr);
			while(!queue.isEmpty()) {
				WeightedGraphVertex<T,W,compare,hash>* node = queue.pop();
				HashMap<WeightedGraphVertex<T,W,compare,hash>*, W, compareWeightedVertex<T,W,compare,hash>, hashWeightedVertex<T, W, compare, hash>>* children = node->getEdges();
				for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
					WeightedGraphVertex<T,W,compare,hash>* tmp = (*(*it)).first;
					if(!visited.containsKey(tmp)) {
						if(tmp==right) {
							ArrayList<WeightedGraphVertex<T,W,compare,hash>*> response;
							response.addToBottom(right);
							WeightedGraphVertex<T,W,compare,hash>* parent = node;
							while(parent!=nullptr) {
								response.addToBottom(parent);
								parent = visited.get(parent);
							}
							return response;
						}
						visited.set(tmp, node);
						queue.push(tmp);
					}
				}
			}
			throw std::out_of_range("Vertexes not connected!");
		}
	protected:
		T data;
		HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* edges;
};

#endif /* SRC_GRAPH_WEIGHTEDGRAPHVERTEX_H_ */
