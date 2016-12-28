/*
 * WeightedGraph.h
 *
 *  Created on: Dec 23, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_WEIGHTEDGRAPH_H_
#define SRC_GRAPH_WEIGHTEDGRAPH_H_

template<typename T, typename W>
class WeightedGraphVertexVisitor;

template<typename T, typename W>
class WeightedGraph {
public:
	virtual ~WeightedGraph() {}
	virtual WeightedGraphVertex<T,W>* createVertex(const T& data) = 0;
	virtual void removeVertex(WeightedGraphVertex<T,W>*& vertex) = 0;
	virtual std::size_t getSize() const = 0;
	virtual bool isPath(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const = 0;
	virtual std::size_t getDistance(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const = 0;
	virtual std::vector<WeightedGraphEdge<T,W>*> getPath(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const = 0;
	// add edge iterator
	virtual void iterate(WeightedGraphVertexVisitor<T,W>& visitor) = 0;
	virtual void iterate(WeightedGraphVertex<T,W>*& start, WeightedGraphVertexVisitor<T,W>& visitor) = 0;
};

template<typename T, typename W>
class WeightedGraphVertexVisitor {
public:
	virtual ~WeightedGraphVertexVisitor(){};

	virtual void visit(WeightedGraphVertex<T,W>* const& element) = 0;
};

#endif /* SRC_GRAPH_WEIGHTEDGRAPH_H_ */
