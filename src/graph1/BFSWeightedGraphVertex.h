/*
 * BFSWeightedGraphVertex.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH1_BFSWEIGHTEDGRAPHVERTEX_H_
#define SRC_GRAPH1_BFSWEIGHTEDGRAPHVERTEX_H_


#include "WeightedGraphVertex.h"
#include "BFS.h"

template<typename T,typename W>
class BFSWeightedGraphVertex : public WeightedGraphVertex<T,W> {
	public:
		using WeightedGraphVertex<T,W>::WeightedGraphVertex;

		void setColor(const BFSColor& color) {
			this->color = color;
		}

		const BFSColor& getColor() const {
			return this->color;
		}

		void setParent(WeightedGraphEdge<T,W>* const& parent) {
			this->parent = parent;
		}

		WeightedGraphEdge<T,W>* const& getParent() const {
			return this->parent;
		}
	protected:
		BFSColor color;
		WeightedGraphEdge<T,W>* parent;
};



#endif /* SRC_GRAPH1_BFSWEIGHTEDGRAPHVERTEX_H_ */
