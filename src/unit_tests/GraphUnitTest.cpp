/*
 * GraphUnitTest.cpp
 *
 *  Created on: Oct 22, 2016
 *      Author: aherne
 */

#include "GraphUnitTest.h"



template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class PrintVertexVisitor: public UnweightedGraphVertexVisitor<T, compare, hash> {
public:
	virtual ~PrintVertexVisitor(){};

	bool isVisited(UnweightedGraphVertex<T, compare, hash>* const& element) {
		return vertexes.contains(element);
	}

	bool visit(UnweightedGraphVertex<T, compare, hash>* const& element, UnweightedGraphVertex<T, compare, hash>* const& parent) {
		vertexes.add(element);
		std::cout << "\t" << "\t" << element->getData() << std::endl;
		return true;
	}
private:
	HashSet<UnweightedGraphVertex<T, compare, hash>*, compareVertex<T,compare,hash>, hashVertex<T,compare,hash>> vertexes;
};

template<typename T, typename W, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class PrintWeightedVertexVisitor: public WeightedGraphVertexVisitor<T,W,compare,hash> {
public:
	virtual ~PrintWeightedVertexVisitor(){};

	bool isVisited(WeightedGraphVertex<T,W,compare,hash>* const& element) {
		return vertexes.contains(element);
	}
	bool visit(WeightedGraphVertex<T,W,compare,hash>* const& element, WeightedGraphVertex<T,W,compare,hash>* const& parent) {
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
	std::cout << "DirectedUnweightedGraph<long>" << std::endl;
	DirectedUnweightedGraph<long> directedUnweightedGraph;
	testUnweightedGraph(&directedUnweightedGraph);

	std::cout << "UndirectedUnweightedGraph<long>" << std::endl;
	UndirectedUnweightedGraph<long> undirectedUnweightedGraph;
	testUnweightedGraph(&undirectedUnweightedGraph);

	std::cout << "DirectedWeightedGraph<long,long>" << std::endl;
	DirectedWeightedGraph<long,long> directedWeightedGraph;
	testWeightedGraph(&directedWeightedGraph);

	std::cout << "UndirectedWeightedGraph<long,long>" << std::endl;
	UndirectedWeightedGraph<long,long> undirectedWeightedGraph;
	testWeightedGraph(&undirectedWeightedGraph);
}

void GraphUnitTest::testUnweightedGraph(UnweightedGraph<long,comparator,hash>* graph) {
	// create vertexes
	UnweightedGraphVertex<long>* v1 = graph->createVertex(1);
	UnweightedGraphVertex<long>* v2 = graph->createVertex(2);
	UnweightedGraphVertex<long>* v3 = graph->createVertex(3);
	UnweightedGraphVertex<long>* v4 = graph->createVertex(4);
	UnweightedGraphVertex<long>* v5 = graph->createVertex(5);
	UnweightedGraphVertex<long>* v6 = graph->createVertex(6);
	UnweightedGraphVertex<long>* v7 = graph->createVertex(7);
	UnweightedGraphVertex<long>* v8 = graph->createVertex(8);
	UnweightedGraphVertex<long>* v9 = graph->createVertex(9);
	UnweightedGraphVertex<long>* v10 = graph->createVertex(10);
	// create edges
	graph->createEdge(v1,v3);
	graph->createEdge(v1,v2);
	graph->createEdge(v1,v10);
	graph->createEdge(v2,v3);
	graph->createEdge(v2,v5);
	graph->createEdge(v2,v8);
	graph->createEdge(v2,v10);
	graph->createEdge(v3,v4);
	graph->createEdge(v4,v5);
	graph->createEdge(v4,v6);
	graph->createEdge(v5,v6);
	graph->createEdge(v5,v8);
	graph->createEdge(v6,v9);
	graph->createEdge(v6,v7);
	graph->createEdge(v7,v8);
	graph->createEdge(v8,v9);
	graph->createEdge(v8,v10);

	std::cout << "\t" << "BFS iteration: " << std::endl;
	PrintVertexVisitor<long> pvv1;
	BreadthFirstSearchGraphIterator(v1, &pvv1);

	std::cout << "\t" << "DFS iteration: " << std::endl;
	PrintVertexVisitor<long> pvv2;
	DepthFirstSearchGraphIterator(v1, &pvv2);

	// unit test
	std::cout << "\t" << "isPath: " << (graph->isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getSize: " << (graph->getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	graph->removeVertex(v6);

	Set<UnweightedGraphVertex<long>*>* edges = v1->getEdges();
	std::cout << "\t" << "getEdges: " << (edges->size()==3?"OK":"FAILED") << std::endl;

	std::cout << "\t" << "removeVertex: " << (!graph->contains(6)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "contains: " << (graph->contains(9)?"OK":"FAILED") << std::endl;
	graph->removeEdge(v4,v5);
	std::cout << "\t" << "removeEdge: " << (!v4->isEdge(v5)?"OK":"FAILED") << std::endl;
	UnweightedGraphVertex<long>* results = graph->search(8);
	std::cout << "\t" << "search: " << (results!=nullptr && results->getData()==8?"OK":"FAILED") << std::endl;
}

void GraphUnitTest::testWeightedGraph(WeightedGraph<long,long,comparator,hash>* graph) {
	// create vertexes
	WeightedGraphVertex<long,long>* v1 = graph->createVertex(1);
	WeightedGraphVertex<long,long>* v2 = graph->createVertex(2);
	WeightedGraphVertex<long,long>* v3 = graph->createVertex(3);
	WeightedGraphVertex<long,long>* v4 = graph->createVertex(4);
	WeightedGraphVertex<long,long>* v5 = graph->createVertex(5);
	WeightedGraphVertex<long,long>* v6 = graph->createVertex(6);
	WeightedGraphVertex<long,long>* v7 = graph->createVertex(7);
	WeightedGraphVertex<long,long>* v8 = graph->createVertex(8);
	WeightedGraphVertex<long,long>* v9 = graph->createVertex(9);
	WeightedGraphVertex<long,long>* v10 = graph->createVertex(10);
	// create edges
	graph->createEdge(v1,v3,1);
	graph->createEdge(v1,v2,2);
	graph->createEdge(v1,v10,3);
	graph->createEdge(v2,v3,4);
	graph->createEdge(v2,v5,5);
	graph->createEdge(v2,v8,6);
	graph->createEdge(v2,v10,7);
	graph->createEdge(v3,v4,8);
	graph->createEdge(v4,v5,9);
	graph->createEdge(v4,v6,10);
	graph->createEdge(v5,v6,11);
	graph->createEdge(v5,v8,12);
	graph->createEdge(v6,v9,13);
	graph->createEdge(v6,v7,14);
	graph->createEdge(v7,v8,15);
	graph->createEdge(v8,v9,16);
	graph->createEdge(v8,v10,17);
	// iterate

	std::cout << "\t" << "BFS iteration: " << std::endl;
	PrintWeightedVertexVisitor<long, long> pvv1;
	BreadthFirstSearchGraphIterator(v1, &pvv1);

	std::cout << "\t" << "DFS iteration: " << std::endl;
	PrintWeightedVertexVisitor<long, long> pvv2;
	DepthFirstSearchGraphIterator(v1, &pvv2);

	// unit test
	std::cout << "\t" << "isPath: " << (graph->isPath(v1,v8)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getSize: " << (graph->getSize()==10?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isEdge: " << (v1->isEdge(v2)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getWeight: " << (v2->getEdgeWeight(v10)==7?"OK":"FAILED") << std::endl;
	v2->setEdgeWeight(v10,11);
	std::cout << "\t" << "setWeight: " << (v2->getEdgeWeight(v10)==11?"OK":"FAILED") << std::endl;
	graph->removeVertex(v6);

	Map<WeightedGraphVertex<long,long>*, long>* edges = v1->getEdges();
	std::cout << "\t" << "getEdges: " << (edges->size()==3?"OK":"FAILED") << std::endl;

	std::cout << "\t" << "removeVertex: " << (!graph->contains(6)?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "contains: " << (graph->contains(9)?"OK":"FAILED") << std::endl;
	graph->removeEdge(v4,v5);
	std::cout << "\t" << "removeEdge: " << (!v4->isEdge(v5)?"OK":"FAILED") << std::endl;
	WeightedGraphVertex<long,long>* results = graph->search(8);
	std::cout << "\t" << "search: " << (results!=nullptr && results->getData()==8?"OK":"FAILED") << std::endl;
}
