/*
 * WeightedGraph.h
 *
 *  Created on: Apr 21, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPH_H_
#define SRC_GRAPH_WEIGHTEDGRAPH_H_

#include "WeightedGraphVertex.h"


template<typename T,typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class WeightedGraph {
public:
	// O(V)
	virtual ~WeightedGraph(){
		// deallocate all vertexes
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			delete (*(*it));
		}
	}

	virtual WeightedGraphVertex<T,W,compare,hash>* createVertex(const T& data) {
		WeightedGraphVertex<T,W,compare,hash> stack(data);
		if(vertexes.contains(&stack)) {
			throw std::logic_error("Vertex with that value already exists!");
		}
		WeightedGraphVertex<T,W,compare,hash>* temp = new WeightedGraphVertex<T,W,compare,hash>(data);
		vertexes.add(temp);
		return temp;
	}

	virtual void removeVertex(WeightedGraphVertex<T,W,compare,hash>*& vertex) =0;

	virtual void createEdge(WeightedGraphVertex<T,W, compare, hash>*& left, WeightedGraphVertex<T,W, compare, hash>*& right, const W& weight) =0;

	virtual void removeEdge(WeightedGraphVertex<T,W, compare, hash>*& left, WeightedGraphVertex<T,W, compare, hash>*& right) =0;

	// O(1)
	std::size_t getSize() const {
		return vertexes.size();
	}

	// O(1)
	bool contains(const T& data) const {
		WeightedGraphVertex<T,W,compare,hash> temp(data);
		return vertexes.contains(&temp);
	}

	// O(2)
	WeightedGraphVertex<T,W,compare,hash>* search(const T& data) {
		WeightedGraphVertex<T,W,compare,hash> temp(data);
		if(!vertexes.contains(&temp)) return nullptr;
		return *(vertexes.find(&temp));
	}
protected:
	HashSet<WeightedGraphVertex<T,W,compare,hash>*, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>> vertexes;
};



#endif /* SRC_GRAPH_WEIGHTEDGRAPH_H_ */
