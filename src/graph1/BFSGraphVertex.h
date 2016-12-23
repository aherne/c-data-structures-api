/*
 * BFSGraphVertex.h
 *
 *  Created on: Dec 22, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH1_BFSGRAPHVERTEX_H_
#define SRC_GRAPH1_BFSGRAPHVERTEX_H_

#include "GraphVertex.h"

enum BFSColor { WHITE, GREY, BLACK };

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



#endif /* SRC_GRAPH1_BFSGRAPHVERTEX_H_ */
