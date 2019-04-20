/*
 * GraphUnitTest.cpp
 *
 *  Created on: Oct 22, 2016
 *      Author: aherne
 */

#include "GraphUnitTest.h"
#include "../graph/UniqueGraph.h"
#include "../graph/UniqueWeightedGraph.h"
#include "../graph/GraphIterator.h"
#include "../graph/WeightedGraphIterator.h"


template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class PrintVertexVisitor: public GraphVertexVisitor<T, compare, hash> {
public:
	virtual ~PrintVertexVisitor(){};

	bool isVisited(GraphVertex<T,compare,hash>* const& element) {
		return vertexes.contains(element);
	}
	bool visit(GraphVertex<T,compare,hash>* const& element) {
		vertexes.add(element);
		std::cout << "\t" << "\t" << element->getData() << std::endl;
		return true;
	}
private:
	HashSet<GraphVertex<T,compare,hash>*, compareVertex<T,compare,hash>, hashVertex<T,compare,hash>> vertexes;
};

template<typename T, typename W,int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class PrintWeightedVertexVisitor: public WeightedGraphVertexVisitor<T,W,compare,hash> {
public:
	virtual ~PrintWeightedVertexVisitor(){};

	bool isVisited(WeightedGraphVertex<T,W,compare,hash>* const& element) {
		return vertexes.contains(element);
	}
	bool visit(WeightedGraphVertex<T,W,compare,hash>* const& element) {
		vertexes.add(element);
		std::cout << "\t" << "\t" << element->getData() << std::endl;
		return true;
	}
private:
	HashSet<WeightedGraphVertex<T,W,compare,hash>*, compareWeightedVertex<T, W,compare,hash>, hashWeightedVertex<T, W,compare,hash>> vertexes;
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
	std::cout << "UniqueGraph<long>" << std::endl;
//	simpleUniqueGraphTest();
	std::cout << "WeightedUniqueGraph<long,long>" << std::endl;
	weightedUniqueGraphTest();
}

void GraphUnitTest::simpleUniqueGraphTest() {
	UniqueGraph<long> graph;
	// create vertexes
	GraphVertex<long, comparator, hash>* v1 = graph.createVertex(1);
	GraphVertex<long, comparator, hash>* v2 = graph.createVertex(2);
	GraphVertex<long, comparator, hash>* v3 = graph.createVertex(3);
	GraphVertex<long, comparator, hash>* v4 = graph.createVertex(4);
	GraphVertex<long, comparator, hash>* v5 = graph.createVertex(5);
	GraphVertex<long, comparator, hash>* v6 = graph.createVertex(6);
	GraphVertex<long, comparator, hash>* v7 = graph.createVertex(7);
	GraphVertex<long, comparator, hash>* v8 = graph.createVertex(8);
	GraphVertex<long, comparator, hash>* v9 = graph.createVertex(9);
	GraphVertex<long, comparator, hash>* v10 = graph.createVertex(10);
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
	// iterate
	std::cout << "\t" << "BFS iteration: " << std::endl;
	PrintVertexVisitor<long, comparator, hash> pvv1;
	BreadthFirstSearchGraphIterator(v1, &pvv1);
	std::cout << "\t" << "DFS iteration: " << std::endl;
	PrintVertexVisitor<long, comparator, hash> pvv2;
	DepthFirstSearchGraphIterator(v1, &pvv2);
	// unit test
	std::cout << "\t" << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isConnected: " << (v1->isConnected(v8)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getShortestPath: " << (v1->getShortestPath(v7).size()==5?"OK":"FAILED") << std::endl;
	graph.removeVertex(v6);
	std::cout << "\t" << "removeVertex: " << (!graph.contains(6)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "contains: " << (graph.contains(9)?"OK":"FAILED") << std::endl;
	v4->removeEdge(v5);
	std::cout << "\t" << "removeEdge: " << (!v4->isEdge(v5)?"OK":"FAILED") << std::endl;
	GraphVertex<long, comparator, hash>* results = graph.search(8);
	std::cout << "\t" << "search: " << (results!=nullptr && results->getData()==8?"OK":"FAILED") << std::endl;
}

void GraphUnitTest::weightedUniqueGraphTest() {
	UniqueWeightedGraph<long,long> graph;
	// create vertexes
	WeightedGraphVertex<long,long,comparator,hash>* v1 = graph.createVertex(1);
	WeightedGraphVertex<long,long,comparator,hash>* v2 = graph.createVertex(2);
	WeightedGraphVertex<long,long,comparator,hash>* v3 = graph.createVertex(3);
	WeightedGraphVertex<long,long,comparator,hash>* v4 = graph.createVertex(4);
	WeightedGraphVertex<long,long,comparator,hash>* v5 = graph.createVertex(5);
	WeightedGraphVertex<long,long,comparator,hash>* v6 = graph.createVertex(6);
	WeightedGraphVertex<long,long,comparator,hash>* v7 = graph.createVertex(7);
	WeightedGraphVertex<long,long,comparator,hash>* v8 = graph.createVertex(8);
	WeightedGraphVertex<long,long,comparator,hash>* v9 = graph.createVertex(9);
	WeightedGraphVertex<long,long,comparator,hash>* v10 = graph.createVertex(10);
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
	// iterate
	std::cout << "\t" << "BFS iteration: " << std::endl;
	PrintWeightedVertexVisitor<long, long, comparator, hash> pvv1;
	BreadthFirstSearchGraphIterator(v1, &pvv1);
	std::cout << "\t" << "DFS iteration: " << std::endl;
	PrintWeightedVertexVisitor<long, long, comparator, hash> pvv2;
	DepthFirstSearchGraphIterator(v1, &pvv2);
	// unit test
	std::cout << "\t" << "getSize: " << (graph.getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getWeight: " << (v2->getEdgeWeight(v10)==7?"OK":"FAILED") << std::endl;
	v2->setEdgeWeight(v10,11);
	std::cout << "\t" << "setWeight: " << (v2->getEdgeWeight(v10)==11?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isConnected: " << (v1->isConnected(v8)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getShortestPath: " << (v1->getShortestPath(v7).size()==5?"OK":"FAILED") << std::endl;
	graph.removeVertex(v6);
	std::cout << "\t" << "removeVertex: " << (!graph.contains(6)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "contains: " << (graph.contains(9)?"OK":"FAILED") << std::endl;
	v4->removeEdge(v5);
	std::cout << "\t" << "removeEdge: " << (!v4->isEdge(v5)?"OK":"FAILED") << std::endl;
	WeightedGraphVertex<long,long, comparator, hash>* results = graph.search(8);
	std::cout << "\t" << "search: " << (results!=nullptr && results->getData()==8?"OK":"FAILED") << std::endl;
}
