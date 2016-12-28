/*
 * GraphUnitTest.cpp
 *
 *  Created on: Oct 22, 2016
 *      Author: aherne
 */

#include "GraphUnitTest.h"
#include "../Comparator.h"
#include "../graph/NonUniqueGraph.h"
#include "../graph/NonUniqueWeightedGraph.h"
#include "../graph/UniqueGraph.h"
#include "../graph/UniqueWeightedGraph.h"


template<typename T>
class PrintVertexVisitor: public GraphVertexVisitor<T> {
public:
	virtual ~PrintVertexVisitor(){};

	void visit(GraphVertex<T>* const& element) {
		std::cout << element->getData() << std::endl;
	}
};

template<typename T, typename W>
class PrintWeightedVertexVisitor: public WeightedGraphVertexVisitor<T,W> {
public:
	virtual ~PrintWeightedVertexVisitor(){};

	void visit(WeightedGraphVertex<T,W>* const& element) {
		std::cout << element->getData() << std::endl;
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
	std::cout << "=====NonUniqueGraph<long>=====" << std::endl;
	simpleGraphTest();
	std::cout << "=====UniqueGraph<long>=====" << std::endl;
	simpleUniqueGraphTest();
	std::cout << "=====WeightedGraph<long,long>=====" << std::endl;
	weightedGraphTest();
	std::cout << "=====WeightedUniqueGraph<long,long>=====" << std::endl;
	weightedUniqueGraphTest();
}

void GraphUnitTest::simpleGraphTest() {
	NonUniqueGraph<long> graph;
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
	v1->addEdge(v3);
	v1->addEdge(v2);
	v1->addEdge(v10);
	v2->addEdge(v3);
	v2->addEdge(v5);
	v2->addEdge(v8);
	v2->addEdge(v10);
	v3->addEdge(v4);
	v4->addEdge(v5);
	v4->addEdge(v6);
	v5->addEdge(v6);
	v5->addEdge(v8);
	v6->addEdge(v9);
	v6->addEdge(v7);
	v7->addEdge(v8);
	v8->addEdge(v9);
	v8->addEdge(v10);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==5?"OK":"FAILED") << std::endl;
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9,comparator)?"OK":"FAILED") << std::endl;
	v4->removeEdge(v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	std::vector<GraphVertex<long>*> results = graph.search(8,comparator);
	std::cout << "search: " << (!results.empty() && results[0]->getData()==8?"OK":"FAILED") << std::endl;
	// iterate
	std::cout << "ITERATE WHOLE GRAPH:" << std::endl;
	PrintVertexVisitor<long> pvv;
	graph.iterate(pvv);
	std::cout << "ITERATE GRAPH PORTION:" << std::endl;
	graph.iterate(v2, pvv);
}

void GraphUnitTest::simpleUniqueGraphTest() {
	UniqueGraph<long> graph;
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
	v1->addEdge(v3);
	v1->addEdge(v2);
	v1->addEdge(v10);
	v2->addEdge(v3);
	v2->addEdge(v5);
	v2->addEdge(v8);
	v2->addEdge(v10);
	v3->addEdge(v4);
	v4->addEdge(v5);
	v4->addEdge(v6);
	v5->addEdge(v6);
	v5->addEdge(v8);
	v6->addEdge(v9);
	v6->addEdge(v7);
	v7->addEdge(v8);
	v8->addEdge(v9);
	v8->addEdge(v10);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==5?"OK":"FAILED") << std::endl;
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9)?"OK":"FAILED") << std::endl;
	v4->removeEdge(v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	GraphVertex<long>* results = graph.search(8);
	std::cout << "search: " << (results!=nullptr && results->getData()==8?"OK":"FAILED") << std::endl;
	// iterate
	std::cout << "ITERATE WHOLE GRAPH:" << std::endl;
	PrintVertexVisitor<long> pvv;
	graph.iterate(pvv);
	std::cout << "ITERATE GRAPH PORTION:" << std::endl;
	graph.iterate(v2, pvv);
}

void GraphUnitTest::weightedGraphTest() {
	NonUniqueWeightedGraph<long,long> graph;
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
	v1->addEdge(v3,1);
	v1->addEdge(v2,2);
	v1->addEdge(v10,3);
	v2->addEdge(v3,4);
	v2->addEdge(v5,5);
	v2->addEdge(v8,6);
	v2->addEdge(v10,7);
	v3->addEdge(v4,8);
	v4->addEdge(v5,9);
	v4->addEdge(v6,10);
	v5->addEdge(v6,11);
	v5->addEdge(v8,12);
	v6->addEdge(v9,13);
	v6->addEdge(v7,14);
	v7->addEdge(v8,15);
	v8->addEdge(v9,16);
	v8->addEdge(v10,17);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	std::cout << "getWeight: " << (v2->getEdgeWeight(v10)==7?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==4?"OK":"FAILED") << std::endl;
	std::vector<WeightedGraphEdge<long,long>*> path = graph.getPath(v1,v7);
	for(auto it = path.begin(); it!=path.end(); ++it) {
		std::cout << (*it)->vertex->getData() << ":" << (*it)->weight << std::endl;
	}
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9,comparator)?"OK":"FAILED") << std::endl;
	v4->removeEdge(v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	std::vector<WeightedGraphVertex<long,long>*> results = graph.search(8,comparator);
	std::cout << "search: " << (!results.empty() && results[0]->getData()==8?"OK":"FAILED") << std::endl;
	// iterate
	std::cout << "ITERATE WHOLE GRAPH:" << std::endl;
	PrintWeightedVertexVisitor<long,long> pvv;
	graph.iterate(pvv);
	std::cout << "ITERATE GRAPH PORTION:" << std::endl;
	graph.iterate(v2, pvv);
}

void GraphUnitTest::weightedUniqueGraphTest() {
	UniqueWeightedGraph<long,long> graph;
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
	v1->addEdge(v3,1);
	v1->addEdge(v2,2);
	v1->addEdge(v10,3);
	v2->addEdge(v3,4);
	v2->addEdge(v5,5);
	v2->addEdge(v8,6);
	v2->addEdge(v10,7);
	v3->addEdge(v4,8);
	v4->addEdge(v5,9);
	v4->addEdge(v6,10);
	v5->addEdge(v6,11);
	v5->addEdge(v8,12);
	v6->addEdge(v9,13);
	v6->addEdge(v7,14);
	v7->addEdge(v8,15);
	v8->addEdge(v9,16);
	v8->addEdge(v10,17);
	// unit test
	std::cout << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	std::cout << "getWeight: " << (v2->getEdgeWeight(v10)==7?"OK":"FAILED") << std::endl;
	std::cout << "isPath: " << (graph.isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "getDistance: " << (graph.getDistance(v1,v7)==4?"OK":"FAILED") << std::endl;
	std::cout << "getPath: " << (graph.getPath(v1,v7).size()==4?"OK":"FAILED") << std::endl;
	std::vector<WeightedGraphEdge<long,long>*> path = graph.getPath(v1,v7);
	for(auto it = path.begin(); it!=path.end(); ++it) {
		std::cout << (*it)->vertex->getData() << ":" << (*it)->weight << std::endl;
	}
	graph.removeVertex(v6);
	std::cout << "removeVertex: " << (!graph.isPath(v4,v7)?"OK":"FAILED") << std::endl;
	std::cout << "contains: " << (graph.contains(9)?"OK":"FAILED") << std::endl;
	v4->removeEdge(v5);
	std::cout << "removeEdge: " << (!graph.isPath(v4,v8)?"OK":"FAILED") << std::endl;
	WeightedGraphVertex<long,long>* results = graph.search(8);
	std::cout << "search: " << (results != nullptr && results->getData()==8?"OK":"FAILED") << std::endl;
	// iterate
	std::cout << "ITERATE WHOLE GRAPH:" << std::endl;
	PrintWeightedVertexVisitor<long,long> pvv;
	graph.iterate(pvv);
	std::cout << "ITERATE GRAPH PORTION:" << std::endl;
	graph.iterate(v2, pvv);
}
