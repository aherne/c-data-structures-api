/*
 * Graph.h
 *
 *  Created on: Apr 21, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_


#include "GraphVertex.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class Graph {
	public:
		virtual ~Graph(){
			// deallocate all vertexes
			for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
				delete (*(*it));
			}
		}

		GraphVertex<T, compare, hash>* createVertex(const T& data) {
			GraphVertex<T, compare, hash> stack(data);
			if(vertexes.contains(&stack)) {
				throw std::logic_error("Vertex with that value already exists!");
			}
			GraphVertex<T, compare, hash>* temp = new GraphVertex<T, compare, hash>(data);
			vertexes.add(temp);
			return temp;
		}

		virtual void removeVertex(GraphVertex<T, compare, hash>*& vertex) =0;

		virtual void createEdge(GraphVertex<T, compare, hash>*& left, GraphVertex<T, compare, hash>*& right) =0;

		virtual void removeEdge(GraphVertex<T, compare, hash>*& left, GraphVertex<T, compare, hash>*& right) =0;

		// O(1)
		std::size_t getSize() const {
			return vertexes.size();
		}

		// O(1)
		bool contains(const T& data) const {
			GraphVertex<T, compare, hash> temp(data);
			return vertexes.contains(&temp);
		}

		// O(2)
		GraphVertex<T, compare, hash>* search(const T& data) {
			GraphVertex<T, compare, hash> temp(data);
			if(!vertexes.contains(&temp)) return nullptr;
			return *(vertexes.find(&temp));
		}
	protected:
		HashSet<GraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>> vertexes;
};



#endif /* SRC_GRAPH_GRAPH_H_ */
