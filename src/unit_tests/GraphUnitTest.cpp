/*
 * GraphUnitTest.cpp
 *
 *  Created on: Oct 22, 2016
 *      Author: aherne
 */

#include "GraphUnitTest.h"
#include "../graph/Graph.h"
#include "../Comparator.h"
#include "../graph/UniqueGraph.h"
#include "../graph/WeightedGraph.h"
#include "../graph/UniqueWeightedGraph.h"

template<typename T>
class PrintVertexVisitor: public GraphVertexVisitor<T> {
public:
	virtual ~PrintVertexVisitor(){};

	void visit(GraphVertex<T>*& element) {
		std::cout << element->data << std::endl;
	}
};

template<typename T>
class PrintUniqueVertexVisitor: public UniqueGraphVertexVisitor<T> {
public:
	virtual ~PrintUniqueVertexVisitor(){};

	void visit(UniqueGraphVertex<T>* const element) {
		std::cout << element->data << std::endl;
	}
};

template<typename T, typename W>
class PrintWeightedVertexVisitor: public WeightedGraphVertexVisitor<T,W> {
public:
	virtual ~PrintWeightedVertexVisitor(){};

	void visit(WeightedGraphVertex<T,W>*& element) {
		std::cout << element->data << std::endl;
	}
};

template<typename T, typename W>
class PrintWeightedEdgeVisitor: public WeightedGraphEdgeVisitor<T,W> {
public:
	virtual ~PrintWeightedEdgeVisitor(){};

	void visit(WeightedGraphEdge<T,W>* const element) {
		std::cout << element->vertex->data << std::endl;
	}
};

template<typename T, typename W>
class PrintUniqueWeightedVertexVisitor: public UniqueWeightedGraphVertexVisitor<T,W> {
public:
	virtual ~PrintUniqueWeightedVertexVisitor(){};

	void visit(UniqueWeightedGraphVertex<T,W>* const element) {
		std::cout << element->data << std::endl;
	}
};

template<typename T, typename W>
class PrintUniqueWeightedEdgeVisitor: public UniqueWeightedGraphEdgeVisitor<T,W> {
public:
	virtual ~PrintUniqueWeightedEdgeVisitor(){};

	void visit(UniqueWeightedGraphEdge<T,W>* const element) {
		std::cout << element->vertex->data << std::endl;
	}
};

void GraphUnitTest::execute() {
	/**
	 * 1--3--4--6
	 * |\ |  | /|\
	 * | \|  |/ | \
	 * |  2--5  9  \
	 * | / \ | /    \
	 * |/   \|/      \
	 * 10----8--------7
	 */
//	std::cout << "=====Graph<long>=====" << std::endl;
//	simpleGraphTest();
//	std::cout << "=====UniqueGraph<long>=====" << std::endl;
//	simpleUniqueGraphTest();
//	std::cout << "=====WeightedGraph<long,long>=====" << std::endl;
//	weightedGraphTest();
	std::cout << "=====WeightedUniqueGraph<long,long>=====" << std::endl;
	weightedUniqueGraphTest();
}

void GraphUnitTest::simpleGraphTest() {
	Graph<long> graph;
	// create vertexes
	GraphVertex<long>* v1 = graph.createVertex(1);
	GraphVertex<long>* v2 = graph.createVertex(2);
	GraphVertex<long>* v3 = graph.createVertex(3);
	GraphVertex<long>* v4 = graph.createVertex(4);
	GraphVertex<long>* v5 = graph.createVertex(5);
	GraphVertex<long>* v6 = graph.createVertex(6);
	GraphVertex<long>* v7 = graph.createVertex(7);
	GraphVertex<long>* v8 = graph.createVertex(8);
	GraphVertex<long>* v9 = graph.createVertex(9);
	GraphVertex<long>* v10 = graph.createVertex(10);
	// create edges
	graph.createEdge(v1,v3);
	graph.createEdge(v1,v2);
	graph.createEdge(v1,v10);
	graph.createEdge(v2,v3);
	graph.createEdge(v2,v5);
	graph.createEdge(v2,v8);
	graph.createEdge(v2,v10);
	graph.createEdge(v3,v4);
	graph.createEdge(v4,v5);
	graph.createEdge(v4,v6);
	graph.createEdge(v5,v6);
	graph.createEdge(v5,v8);
	graph.createEdge(v6,v9);
	graph.createEdge(v6,v7);
	graph.createEdge(v7,v8);
	graph.createEdge(v8,v9);
	graph.createEdge(v8,v10);
	// iterate
	std::cout << "Iterate (from point):" << std::endl;
	PrintVertexVisitor<long> pvv;
	graph.iterate(v1,&pvv);
	std::cout << "Iterate:" << std::endl;
	graph.iterate(&pvv);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (graph.isEdge(v1,v2)?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==5?"OK":"FAILED") << std::endl;
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9,comparator)?"OK":"FAILED") << std::endl;
	graph.removeEdge(v4,v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	std::vector<GraphVertex<long>*> results = graph.search(8,comparator);
	std::cout << "search: " << (!results.empty() && results[0]->data==8?"OK":"FAILED") << std::endl;
}

void GraphUnitTest::simpleUniqueGraphTest() {
	UniqueGraph<long> graph;
	// create vertexes
	UniqueGraphVertex<long>* v1 = graph.createVertex(1);
	UniqueGraphVertex<long>* v2 = graph.createVertex(2);
	UniqueGraphVertex<long>* v3 = graph.createVertex(3);
	UniqueGraphVertex<long>* v4 = graph.createVertex(4);
	UniqueGraphVertex<long>* v5 = graph.createVertex(5);
	UniqueGraphVertex<long>* v6 = graph.createVertex(6);
	UniqueGraphVertex<long>* v7 = graph.createVertex(7);
	UniqueGraphVertex<long>* v8 = graph.createVertex(8);
	UniqueGraphVertex<long>* v9 = graph.createVertex(9);
	UniqueGraphVertex<long>* v10 = graph.createVertex(10);
	// create edges
	graph.createEdge(v1,v3);
	graph.createEdge(v1,v2);
	graph.createEdge(v1,v10);
	graph.createEdge(v2,v3);
	graph.createEdge(v2,v5);
	graph.createEdge(v2,v8);
	graph.createEdge(v2,v10);
	graph.createEdge(v3,v4);
	graph.createEdge(v4,v5);
	graph.createEdge(v4,v6);
	graph.createEdge(v5,v6);
	graph.createEdge(v5,v8);
	graph.createEdge(v6,v9);
	graph.createEdge(v6,v7);
	graph.createEdge(v7,v8);
	graph.createEdge(v8,v9);
	graph.createEdge(v8,v10);
	// iterate
	std::cout << "Iterate (from point):" << std::endl;
	PrintUniqueVertexVisitor<long> pvv;
	graph.iterate(v1,&pvv);
	std::cout << "Iterate:" << std::endl;
	graph.iterate(&pvv);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (graph.isEdge(v1,v2)?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==5?"OK":"FAILED") << std::endl;
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9)?"OK":"FAILED") << std::endl;
	graph.removeEdge(v4,v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	UniqueGraphVertex<long>* results = graph.search(8);
	std::cout << "search: " << (results!=nullptr && results->data==8?"OK":"FAILED") << std::endl;
}

void GraphUnitTest::weightedGraphTest() {
	WeightedGraph<long,long> graph;
	// create vertexes
	WeightedGraphVertex<long,long>* v1 = graph.createVertex(1);
	WeightedGraphVertex<long,long>* v2 = graph.createVertex(2);
	WeightedGraphVertex<long,long>* v3 = graph.createVertex(3);
	WeightedGraphVertex<long,long>* v4 = graph.createVertex(4);
	WeightedGraphVertex<long,long>* v5 = graph.createVertex(5);
	WeightedGraphVertex<long,long>* v6 = graph.createVertex(6);
	WeightedGraphVertex<long,long>* v7 = graph.createVertex(7);
	WeightedGraphVertex<long,long>* v8 = graph.createVertex(8);
	WeightedGraphVertex<long,long>* v9 = graph.createVertex(9);
	WeightedGraphVertex<long,long>* v10 = graph.createVertex(10);
	// create edges
	graph.createEdge(v1,v3,1);
	graph.createEdge(v1,v2,2);
	graph.createEdge(v1,v10,3);
	graph.createEdge(v2,v3,4);
	graph.createEdge(v2,v5,5);
	graph.createEdge(v2,v8,6);
	graph.createEdge(v2,v10,7);
	graph.createEdge(v3,v4,8);
	graph.createEdge(v4,v5,9);
	graph.createEdge(v4,v6,10);
	graph.createEdge(v5,v6,11);
	graph.createEdge(v5,v8,12);
	graph.createEdge(v6,v9,13);
	graph.createEdge(v6,v7,14);
	graph.createEdge(v7,v8,15);
	graph.createEdge(v8,v9,16);
	graph.createEdge(v8,v10,17);
	// iterate
	std::cout << "Iterate (from point):" << std::endl;
	PrintWeightedEdgeVisitor<long,long> pev;
	graph.iterate(v1,&pev);
	std::cout << "Iterate:" << std::endl;
	PrintWeightedVertexVisitor<long,long> pvv;
	graph.iterate(&pvv);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (graph.isEdge(v1,v2)?"OK":"FAILED") << std::endl;
	std::cout << "getWeight: " << (graph.getWeight(v2,v10)==7?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==4?"OK":"FAILED") << std::endl;
	std::vector<WeightedGraphEdge<long,long>*> path = graph.getPath(v1,v7);
	for(auto it = path.begin(); it!=path.end(); ++it) {
		std::cout << (*it)->vertex->data << ":" << (*it)->weight << std::endl;
	}
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9,comparator)?"OK":"FAILED") << std::endl;
	graph.removeEdge(v4,v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	std::vector<WeightedGraphVertex<long,long>*> results = graph.search(8,comparator);
	std::cout << "search: " << (!results.empty() && results[0]->data==8?"OK":"FAILED") << std::endl;
}

void GraphUnitTest::weightedUniqueGraphTest() {
	UniqueWeightedGraph<long,long> graph;
	// create vertexes
	UniqueWeightedGraphVertex<long,long>* v1 = graph.createVertex(1);
	UniqueWeightedGraphVertex<long,long>* v2 = graph.createVertex(2);
	UniqueWeightedGraphVertex<long,long>* v3 = graph.createVertex(3);
	UniqueWeightedGraphVertex<long,long>* v4 = graph.createVertex(4);
	UniqueWeightedGraphVertex<long,long>* v5 = graph.createVertex(5);
	UniqueWeightedGraphVertex<long,long>* v6 = graph.createVertex(6);
	UniqueWeightedGraphVertex<long,long>* v7 = graph.createVertex(7);
	UniqueWeightedGraphVertex<long,long>* v8 = graph.createVertex(8);
	UniqueWeightedGraphVertex<long,long>* v9 = graph.createVertex(9);
	UniqueWeightedGraphVertex<long,long>* v10 = graph.createVertex(10);
	// create edges
	graph.createEdge(v1,v3,1);
	graph.createEdge(v1,v2,2);
	graph.createEdge(v1,v10,3);
	graph.createEdge(v2,v3,4);
	graph.createEdge(v2,v5,5);
	graph.createEdge(v2,v8,6);
	graph.createEdge(v2,v10,7);
	graph.createEdge(v3,v4,8);
	graph.createEdge(v4,v5,9);
	graph.createEdge(v4,v6,10);
	graph.createEdge(v5,v6,11);
	graph.createEdge(v5,v8,12);
	graph.createEdge(v6,v9,13);
	graph.createEdge(v6,v7,14);
	graph.createEdge(v7,v8,15);
	graph.createEdge(v8,v9,16);
	graph.createEdge(v8,v10,17);
	// iterate
	std::cout << "Iterate (from point):" << std::endl;
	PrintUniqueWeightedEdgeVisitor<long,long> pev;
	graph.iterate(v1,&pev);
	std::cout << "Iterate:" << std::endl;
	PrintUniqueWeightedVertexVisitor<long,long> pvv;
	graph.iterate(&pvv);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (graph.isEdge(v1,v2)?"OK":"FAILED") << std::endl;
	std::cout << "getWeight: " << (graph.getWeight(v1,v2)==2?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==4?"OK":"FAILED") << std::endl;
	std::vector<UniqueWeightedGraphEdge<long,long>*> path = graph.getPath(v1,v7);
	for(auto it = path.begin(); it!=path.end(); ++it) {
		std::cout << (*it)->vertex->data << ":" << (*it)->weight << std::endl;
	}
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9)?"OK":"FAILED") << std::endl;
	graph.removeEdge(v4,v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	UniqueWeightedGraphVertex<long,long>* results = graph.search(8);
	std::cout << "search: " << (results!=nullptr && results->data==8?"OK":"FAILED") << std::endl;
}
