/*
 * BFSGraph.h
 *
 *  Created on: Oct 21, 2016
 *      Author: Lucian
 */

#ifndef BFSGRAPH_H_
#define BFSGRAPH_H_

#include "../container/Queue.h"
#include "../HashTable.h"
#include "Graph.h"

/**
for each vertex u @ G:V - {s}
 	u.color D WHITE
 	u.d = infinite
 	u.parent = NIL
s.color = GRAY
s.d = 0
s.parent = NIL
Q = 0;
ENQUEUE(Q,s)
while Q != 0
	u = DEQUEUE(Q)
	for each v @ G.Adj[u]
		if v.color == WHITE
			v.color = GRAY
			v.d = u.d + 1
			v.parent = u
			ENQUEUE(Q,V)
 		u.color = BLACK
 */
template<typename T>
static inline void BreadthFirstSearch(const GraphVertex<T>*& search, GraphVertexVisitor<T>* visitor) {
	HashTable<GraphVertex<T>*, compareVertex, hashVertex> visited;

	Queue<GraphVertex<T>*> queue;
	queue.push(search);
	visited.add(search);
	while(!queue.isEmpty()) {
		GraphVertex<T>* node = queue.pop();
		visitor->visit(node);
		std::vector<GraphVertex<T>*> children = node->getChildren();

        for(auto it = children.begin(); it != children.end(); ++it){
            if(!visited.contains(*it)) {
                visited.set(*it);
                queue.push(*it);
            }
        }
    }
}



#endif /* BFSGRAPH_H_ */
