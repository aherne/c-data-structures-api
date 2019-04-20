/*
 * UniqueUniqueWeightedGraph.h
 *
 *  Created on: Nov 5, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_
#define SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_


#include "../container/Queue.h"
#include "../set/HashSet.h"
#include "../map/HashMap.h"
#include <vector>
#include "../Comparator.h"
#include "../Hashing.h"
#include "UndirectedWeightedGraphVertex.h"


template<typename T,typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UniqueWeightedGraph {
public:
	UniqueWeightedGraph(bool directed = true) {
		this->directed = directed;
	}

	// O(V)
	~UniqueWeightedGraph(){
		// deallocate all vertexes
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			delete (*(*it));
		}
	}

	// O(2)
	WeightedGraphVertex<T,W,compare,hash>* createVertex(const T& data) {
		WeightedGraphVertex<T,W,compare,hash> stack(data);
		if(vertexes.contains(&stack)) {
			throw std::logic_error("Vertex with that value already exists!");
		}
		WeightedGraphVertex<T,W,compare,hash>* temp = directed?new WeightedGraphVertex<T,W,compare,hash>(data):new UndirectedWeightedGraphVertex<T,W,compare,hash>(data);
		vertexes.add(temp);
		return temp;
	}

	// O(V*E)
	void removeVertex(WeightedGraphVertex<T,W,compare,hash>*& vertex) {
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
private:
	HashSet<WeightedGraphVertex<T,W,compare,hash>*, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>> vertexes;
	bool directed;
};


#endif /* SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_ */
