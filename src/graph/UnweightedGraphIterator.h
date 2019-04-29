/*
 * GraphIterator.h
 *
 *  Created on: Mar 16, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNWEIGHTEDGRAPHITERATOR_H_
#define SRC_GRAPH_UNWEIGHTEDGRAPHITERATOR_H_

#include "../container/Queue.h"
#include "../container/Stack.h"
#include "UnweightedGraphVertex.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UnweightedGraphVertexVisitor {
public:
	virtual ~UnweightedGraphVertexVisitor(){};

	virtual bool visit(UnweightedGraphVertex<T, compare, hash>* const& element, UnweightedGraphVertex<T, compare, hash>* const& parent) = 0;

	virtual bool isVisited(UnweightedGraphVertex<T, compare, hash>* const& element) = 0;
};

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline void BreadthFirstSearchGraphIterator(UnweightedGraphVertex<T, compare, hash>* const& vertex, UnweightedGraphVertexVisitor<T, compare, hash>* const& visitor) {
	Queue<UnweightedGraphVertex<T, compare, hash>*> queue;
	if(!visitor->visit(vertex, nullptr)) return;
	queue.push(vertex);
	while(!queue.isEmpty()) {
		UnweightedGraphVertex<T, compare, hash>* node = queue.pop();
		HashSet<UnweightedGraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = node->getEdges();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			UnweightedGraphVertex<T, compare, hash>* tmp = (UnweightedGraphVertex<T, compare, hash>*) (*(*it));
			if(!visitor->isVisited(tmp)) {
				if(!visitor->visit(tmp, node)) return;
				queue.push(tmp);
			}
		}
	}
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline void DepthFirstSearchGraphIterator(UnweightedGraphVertex<T, compare, hash>* const& vertex, UnweightedGraphVertexVisitor<T, compare, hash>* const& visitor) {
	Stack<UnweightedGraphVertex<T, compare, hash>*> stack;
	if(!visitor->visit(vertex, nullptr)) return;
	stack.push(vertex);
	while(!stack.isEmpty()) {
		UnweightedGraphVertex<T, compare, hash>* node = stack.pop();
		HashSet<UnweightedGraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = node->getEdges();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			UnweightedGraphVertex<T, compare, hash>* tmp = (UnweightedGraphVertex<T, compare, hash>*) (*(*it));
			if(!visitor->isVisited(tmp)) {
				if(!visitor->visit(tmp, node)) return;
				stack.push(tmp);
			}
		}
	}
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UnweightedGraphVertexVisitor__IsPath : public UnweightedGraphVertexVisitor<T,compare,hash> {
public:
	UnweightedGraphVertexVisitor__IsPath(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
		this->right = right;
		this->found = false;
		DepthFirstSearchGraphIterator(left,this);
	}

	bool isFound() {
		return found;
	}

	bool visit(UnweightedGraphVertex<T, compare, hash>* const& element, UnweightedGraphVertex<T, compare, hash>* const& parent) {
		if(element == right) {
			found = true;
			return false;
		} else {
			nodes.add(element);
			return true;
		}
	}

	bool isVisited(UnweightedGraphVertex<T, compare, hash>* const& element) {
		return nodes.contains(element);
	}
private:
	bool found;
	UnweightedGraphVertex<T, compare, hash>* right;
	HashSet<UnweightedGraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>> nodes;
};


template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UnweightedGraphVertexVisitor__ShortestPath : public UnweightedGraphVertexVisitor<T,compare,hash> {
public:
	UnweightedGraphVertexVisitor__ShortestPath(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
		this->right = right;
		BreadthFirstSearchGraphIterator(left,this);
	}

	bool visit(UnweightedGraphVertex<T, compare, hash>* const& element, UnweightedGraphVertex<T, compare, hash>* const& node) {
		UnweightedGraphVertex<T, compare, hash>* parent = node;
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

	bool isVisited(UnweightedGraphVertex<T, compare, hash>* const& element) {
		return nodes.containsKey(element);
	}

	const ArrayList<UnweightedGraphVertex<T, compare, hash>*>& getResponse() {
		return response;
	}
private:
	UnweightedGraphVertex<T, compare, hash>* right;
	HashMap<UnweightedGraphVertex<T, compare, hash>*, UnweightedGraphVertex<T, compare, hash>*, compareVertex<T, compare,hash>, hashVertex<T, compare,hash>> nodes;
	ArrayList<UnweightedGraphVertex<T, compare, hash>*> response;
};

#endif /* SRC_GRAPH_UNWEIGHTEDGRAPHITERATOR_H_ */
