/*
 * BFSGraphVertex.h
 *
 *  Created on: Dec 22, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_BFSGRAPHVERTEX_H_
#define SRC_GRAPH_BFSGRAPHVERTEX_H_

#include "BFS.h"
#include "GraphVertex.h"

template<typename T>
class BFSGraphVertex : public GraphVertex<T> {
	public:
		using GraphVertex<T>::GraphVertex;

		void setColor(const BFSColor& color) {
			this->color = color;
		}

		const BFSColor& getColor() const {
			return this->color;
		}

		void setParent(BFSGraphVertex<T>* const& parent) {
			this->parent = parent;
		}

		BFSGraphVertex<T>* const& getParent() const {
			return this->parent;
		}
	protected:
		BFSColor color;
		BFSGraphVertex<T>* parent;
};



#endif /* SRC_GRAPH_BFSGRAPHVERTEX_H_ */
