/*
 * Graph.h
 *
 *  Created on: Apr 21, 2019
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNWEIGHTEDGRAPH_H_
#define SRC_GRAPH_UNWEIGHTEDGRAPH_H_


#include "UnweightedGraphIterator.h"
#include "UnweightedGraphVertex.h"
#include "Graph.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UnweightedGraph : public Graph<UnweightedGraphVertex<T, compare, hash>, T>{
	public:
		virtual ~UnweightedGraph(){
			// deallocate all vertexes
			for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
				delete (*(*it));
			}
		}

		UnweightedGraphVertex<T, compare, hash>* createVertex(const T& data) {
			UnweightedGraphVertex<T, compare, hash> stack(data);
			if(vertexes.contains(&stack)) {
				throw std::logic_error("Vertex with that value already exists!");
			}
			UnweightedGraphVertex<T, compare, hash>* temp = new UnweightedGraphVertex<T, compare, hash>(data);
			vertexes.add(temp);
			return temp;
		}

		virtual void removeVertex(UnweightedGraphVertex<T, compare, hash>* const& vertex) =0;

		virtual void createEdge(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) =0;

		virtual void removeEdge(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) =0;

		bool isPath(UnweightedGraphVertex<T, compare, hash>* const& left, UnweightedGraphVertex<T, compare, hash>* const& right) {
			UnweightedGraphVertexVisitor__IsPath<T, compare, hash> gvvip(left,right);
			return gvvip.isFound();
		}

		// O(1)
		std::size_t getSize() const {
			return vertexes.size();
		}

		// O(1)
		bool contains(const T& data) const {
			UnweightedGraphVertex<T, compare, hash> temp(data);
			return vertexes.contains(&temp);
		}

		// O(2)
		UnweightedGraphVertex<T, compare, hash>* search(const T& data) {
			UnweightedGraphVertex<T, compare, hash> temp(data);
			if(!vertexes.contains(&temp)) return nullptr;
			return *(vertexes.find(&temp));
		}
	protected:
		HashSet<UnweightedGraphVertex<T, compare, hash>*, compareVertex<T, compare, hash>, hashVertex<T, compare, hash>> vertexes;
};



#endif /* SRC_GRAPH_UNWEIGHTEDGRAPH_H_ */
