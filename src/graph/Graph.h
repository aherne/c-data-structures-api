/*
 * Graph.h
 *
 *  Created on: Apr 28, 2019
 *      Author: florica
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

#include <cstddef>

template<typename NODE, typename VALUE>
class Graph {
	public:
		virtual ~Graph(){}
		virtual NODE* createVertex(const VALUE& data) = 0;
		virtual void removeVertex(NODE* const& vertex) = 0;
		virtual bool isPath(NODE* const& left, NODE* const& right) = 0;
		virtual std::size_t getSize() const = 0;
		virtual bool contains(const VALUE& data) const = 0;
		virtual NODE* search(const VALUE& data) = 0;
};


#endif /* SRC_GRAPH_GRAPH_H_ */
