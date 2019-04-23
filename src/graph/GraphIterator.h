/*
 * GraphIterator.h
 *
 *  Created on: Mar 16, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_GRAPHITERATOR_H_
#define SRC_GRAPH_GRAPHITERATOR_H_

#include "GraphVertex.h"
#include "../container/Queue.h"
#include "../container/Stack.h"

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class BFS_GraphVertexVisitor {
public:
	virtual ~BFS_GraphVertexVisitor(){};

	virtual bool visit(GraphVertex<T, compare, hash>* const& element, GraphVertex<T, compare, hash>* const& parent) = 0;

	virtual bool isVisited(GraphVertex<T, compare, hash>* const& element) = 0;
};

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class DFS_GraphVertexVisitor {
public:
	virtual ~DFS_GraphVertexVisitor(){};

	virtual bool visit(GraphVertex<T, compare, hash>* const& element) = 0;

	virtual bool isVisited(GraphVertex<T, compare, hash>* const& element) = 0;
};

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void BreadthFirstSearchGraphIterator(GraphVertex<T, compare, hash>* const& vertex, BFS_GraphVertexVisitor<T, compare, hash>* const& visitor) {
	Queue<GraphVertex<T, compare, hash>*> queue;
	if(!visitor->visit(vertex, nullptr)) return;
	queue.push(vertex);
	while(!queue.isEmpty()) {
		GraphVertex<T, compare, hash>* node = queue.pop();
		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = node->getEdges();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			GraphVertex<T, compare, hash>* tmp = (GraphVertex<T, compare, hash>*) (*(*it));
			if(!visitor->isVisited(tmp)) {
				if(!visitor->visit(tmp, node)) return;
				queue.push(tmp);
			}
		}
	}
}

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
inline void DepthFirstSearchGraphIterator(GraphVertex<T, compare, hash>* const& vertex, DFS_GraphVertexVisitor<T, compare, hash>* const& visitor) {
	Stack<GraphVertex<T, compare, hash>*> stack;
	if(!visitor->visit(vertex)) return;
	stack.push(vertex);
	while(!stack.isEmpty()) {
		GraphVertex<T, compare, hash>* element = stack.pop();
		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>>* children = element->getEdges();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			GraphVertex<T, compare, hash>* tmp = (GraphVertex<T, compare, hash>*) (*(*it));
			if(!visitor->isVisited(tmp)) {
				if(!visitor->visit(tmp)) return;
				stack.push(tmp);
			}
		}
	}
}

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class GraphVertexVisitor__IsPath : public DFS_GraphVertexVisitor<T,compare,hash> {
public:
	GraphVertexVisitor__IsPath(GraphVertex<T, compare, hash>* const& left, GraphVertex<T, compare, hash>* const& right) {
		this->right = right;
		this->found = false;
		DepthFirstSearchGraphIterator(left,this);
	}

	bool isFound() {
		return found;
	}

	bool visit(GraphVertex<T, compare, hash>* const& element) {
		if(element == right) {
			found = true;
			return false;
		} else {
			nodes.add(element);
			return true;
		}
	}

	bool isVisited(GraphVertex<T, compare, hash>* const& element) {
		return nodes.contains(element);
	}
private:
	bool found;
	GraphVertex<T, compare, hash>* right;
	HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>> nodes;
};


template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class GraphVertexVisitor__ShortestPath : public BFS_GraphVertexVisitor<T,compare,hash> {
public:
	GraphVertexVisitor__ShortestPath(GraphVertex<T, compare, hash>* const& left, GraphVertex<T, compare, hash>* const& right) {
		this->right = right;
		BreadthFirstSearchGraphIterator(left,this);
	}

	bool visit(GraphVertex<T, compare, hash>* const& element, GraphVertex<T, compare, hash>* const& node) {
		GraphVertex<T, compare, hash>* parent = node;
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

	bool isVisited(GraphVertex<T, compare, hash>* const& element) {
		return nodes.containsKey(element);
	}

	const ArrayList<GraphVertex<T, compare, hash>*>& getResponse() {
		return response;
	}
private:
	GraphVertex<T, compare, hash>* right;
	HashMap<GraphVertex<T, compare, hash>*, GraphVertex<T, compare, hash>*, compareVertex<T, compare,hash>, hashVertex<T, compare,hash>> nodes;
	ArrayList<GraphVertex<T, compare, hash>*> response;
};

#endif /* SRC_GRAPH_GRAPHITERATOR_H_ */
