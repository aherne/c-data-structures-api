/*
 * WeightedGraphIterator.h
 *
 *  Created on: Mar 16, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPHITERATOR_H_
#define SRC_GRAPH_WEIGHTEDGRAPHITERATOR_H_



#include "WeightedGraphVertex.h"
#include "../container/Queue.h"

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class DFS_WeightedGraphVertexVisitor {
public:
	virtual ~DFS_WeightedGraphVertexVisitor(){};

	virtual bool visit(WeightedGraphVertex<T,W,compare,hash>* const& element) = 0;

	virtual bool isVisited(WeightedGraphVertex<T,W,compare,hash>* const& element) = 0;
};

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class BFS_WeightedGraphVertexVisitor {
public:
	virtual ~BFS_WeightedGraphVertexVisitor(){};

	virtual bool visit(WeightedGraphVertex<T,W,compare,hash>* const& element, WeightedGraphVertex<T,W,compare,hash>* const& parent) = 0;

	virtual bool isVisited(WeightedGraphVertex<T,W,compare,hash>* const& element) = 0;
};

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void BreadthFirstSearchGraphIterator(WeightedGraphVertex<T,W,compare,hash>* vertex, BFS_WeightedGraphVertexVisitor<T,W,compare,hash>* visitor) {
	Queue<WeightedGraphVertex<T,W,compare,hash>*> queue;
	if(!visitor->visit(vertex, nullptr)) return;
	queue.push(vertex);
	while(!queue.isEmpty()) {
		WeightedGraphVertex<T,W,compare,hash>* node = queue.pop();
		HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* children = node->getEdges();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			std::pair<WeightedGraphVertex<T,W,compare,hash>*,W> tmp = (std::pair<WeightedGraphVertex<T,W,compare,hash>*,W>) (*(*it));
			if(!visitor->isVisited(tmp.first)) {
				if(!visitor->visit(tmp.first, node)) return;
				queue.push(tmp.first);
			}
		}
	}
}

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void DepthFirstSearchGraphIterator(WeightedGraphVertex<T,W,compare,hash>* vertex, DFS_WeightedGraphVertexVisitor<T,W,compare,hash>* visitor) {
	if(!visitor->visit(vertex)) return;
	HashMap<WeightedGraphVertex<T, W, compare, hash>*, W, compareWeightedVertex<T, W, compare, hash>, hashWeightedVertex<T, W, compare, hash>>* children = vertex->getEdges();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		std::pair<WeightedGraphVertex<T,W,compare,hash>*,W> tmp = (std::pair<WeightedGraphVertex<T,W,compare,hash>*,W>) (*(*it));
		if(!visitor->isVisited(tmp.first)) {
			DepthFirstSearchGraphIterator(tmp.first, visitor);
		}
	}
}

template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class WeightedGraphVertexVisitor__IsPath : public DFS_WeightedGraphVertexVisitor<T,W,compare,hash> {
public:
	WeightedGraphVertexVisitor__IsPath(WeightedGraphVertex<T, W, compare, hash>* const& left, WeightedGraphVertex<T, W, compare, hash>* const& right) {
		this->right = right;
		this->found = false;
		DepthFirstSearchGraphIterator(left,this);
	}

	bool isFound() {
		return found;
	}

	bool visit(WeightedGraphVertex<T, W, compare, hash>* const& element) {
		if(element == right) {
			found = true;
			return false;
		} else {
			nodes.add(element);
			return true;
		}
	}

	bool isVisited(WeightedGraphVertex<T, W, compare, hash>* const& element) {
		return nodes.contains(element);
	}
private:
	bool found;
	WeightedGraphVertex<T, W, compare, hash>* right;
	HashSet<WeightedGraphVertex<T,W,compare,hash>*, compareWeightedVertex<T, W, compare,hash>, hashWeightedVertex<T, W, compare,hash>> nodes;
};


template<typename T, typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class WeightedGraphVertexVisitor__ShortestPath : public BFS_WeightedGraphVertexVisitor<T,W,compare,hash> {
public:
	WeightedGraphVertexVisitor__ShortestPath(WeightedGraphVertex<T, W,compare, hash>* const& left, WeightedGraphVertex<T, W,compare, hash>* const& right) {
		this->right = right;
		BreadthFirstSearchGraphIterator(left,this);
	}

	bool visit(WeightedGraphVertex<T, W,compare, hash>* const& element, WeightedGraphVertex<T, W,compare, hash>* const& node) {
		WeightedGraphVertex<T, W,compare, hash>* parent = node;
		if(element == right) {
			response.addToBottom(right);
			while(parent!=nullptr) {
				response.addToBottom(parent);
				parent = nodes.get(parent);
			}
			return false;
		} else {
			nodes.set(element, parent);
			return true;
		}
	}

	bool isVisited(WeightedGraphVertex<T, W,compare, hash>* const& element) {
		return nodes.containsKey(element);
	}

	const ArrayList<WeightedGraphVertex<T, W,compare, hash>*>& getResponse() {
		return response;
	}
private:
	WeightedGraphVertex<T, W,compare, hash>* right;
	HashMap<WeightedGraphVertex<T,W,compare,hash>*, WeightedGraphVertex<T,W,compare,hash>*, compareWeightedVertex<T,W,compare,hash>, hashWeightedVertex<T, W, compare, hash>> nodes;
	ArrayList<WeightedGraphVertex<T, W,compare, hash>*> response;
};
#endif /* SRC_GRAPH_WEIGHTEDGRAPHITERATOR_H_ */
