/*
 * UniqueUniqueWeightedGraph.h
 *
 *  Created on: Nov 5, 2016
 *      Author: aherne
 */

#ifndef SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_
#define SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_


#include "../container/Queue.h"
#include "../set/HashSet.h"
#include "../map/HashMap.h"
#include "WeightedGraph.h"
#include <vector>
#include "WeightedGraphUtilities.h"


template<typename T,typename W, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class UniqueWeightedGraph : public WeightedGraph<T,W> {
public:
	// O(V)
	~UniqueWeightedGraph(){
		// deallocate all vertexes
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			delete (*(*it));
		}
	}

	// O(2)
	WeightedGraphVertex<T,W>* createVertex(const T& data) {
		WeightedGraphVertex<T,W> stack(data);
		if(vertexes.contains(&stack)) {
			throw std::logic_error("Vertex with that value already exists!");
		}
		WeightedGraphVertex<T,W>* temp = new WeightedGraphVertex<T,W>(data);
		vertexes.add(temp);
		return temp;
	}

	// O(V*E)
	void removeVertex(WeightedGraphVertex<T,W>*& vertex) {
		// remove edges that connect to vertex
		for(auto it = vertexes.begin(); *it!=*(vertexes.end()); ++(*it)) {
			(*(*it))->removeEdge(vertex);
		}
		vertexes.remove(vertex);
		// deallocates vertex
		delete vertex;
	}

	// O(1)
	std::size_t getSize() const {
		return vertexes.size();
	}

	// O(V*E)
	bool isPath(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const {
		HashSet<WeightedGraphVertex<T,W>*, compareWeightedVertex<T, W, compare>, hashWeightedVertex<T, W, hash>> visited;
		Queue<WeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		visited.add(left);
		while(!queue.isEmpty()) {
			WeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<WeightedGraphEdge<T,W>*> children = node->getEdges();
			for(auto it = children.begin(); it != children.end(); ++it){
				WeightedGraphVertex<T,W>* tmp = (*it)->vertex;
				if(!visited.contains(tmp)) {
					if(tmp==right) return true;
					visited.add(tmp);
					queue.push(tmp);
				}
			}
		}
		return false;
	}

	// O(V*E)
	std::size_t getDistance(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const {
		HashMap<WeightedGraphVertex<T,W>*, long, compareWeightedVertex<T, W, compare>, hashWeightedVertex<T, W, hash>> visited;
		Queue<WeightedGraphVertex<T,W>*> queue;
		queue.push(left);
		visited.set(left,0);
		while(!queue.isEmpty()) {
			WeightedGraphVertex<T,W>* node = queue.pop();
			std::vector<WeightedGraphEdge<T,W>*> children = node->getEdges();
			for(auto it = children.begin(); it != children.end(); ++it){
				WeightedGraphVertex<T,W>* tmp = (*it)->vertex;
				if(!visited.containsKey(tmp)) {
					if(tmp==right) return visited.get(node)+1;
					visited.set(tmp, visited.get(node)+1);
					queue.push(tmp);
				}
			}
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(V*E)
	std::vector<WeightedGraphEdge<T,W>*> getPath(WeightedGraphVertex<T,W>*& left, WeightedGraphVertex<T,W>*& right) const {
		WeightedGraphEdge<T,W> element;
		element.vertex = left;
		element.weight = 0;

		HashMap<WeightedGraphEdge<T,W>*, WeightedGraphEdge<T,W>*, compareWeightedVertexParent<T, W, compare>, hashWeightedVertexParent<T, W, hash>> visited;
		Queue<WeightedGraphEdge<T,W>*> queue;
		queue.push(&element);
		visited.set(&element,nullptr);
		while(!queue.isEmpty()) {
			WeightedGraphEdge<T,W>* node = queue.pop();
			std::vector<WeightedGraphEdge<T,W>*> children = node->vertex->getEdges();
			for(auto it = children.begin(); it != children.end(); ++it){
				if(!visited.containsKey(*it)) {
					if((*it)->vertex==right) {
						std::vector<WeightedGraphEdge<T,W>*> response;
						response.push_back(*it);
						WeightedGraphEdge<T,W>* parent = node;
						while(parent!=nullptr) {
							if(parent->vertex == left) break;
							response.push_back(parent);
							parent = visited.get(parent);
						}
						return response;
					}
					visited.set(*it, node);
					queue.push(*it);
				}
			}
		}
		throw std::out_of_range("Vertexes not connected!");
	}

	// O(1)
	bool contains(const T& data) const {
		WeightedGraphVertex<T,W> temp(data);
		return vertexes.contains(&temp);
	}

	// O(2)
	WeightedGraphVertex<T,W>* search(const T& data) {
		WeightedGraphVertex<T,W> temp(data);
		if(!vertexes.contains(&temp)) return nullptr;
		return *(vertexes.find(&temp));
	}
private:
	HashSet<WeightedGraphVertex<T,W>*, compareWeightedVertex<T, W, compare>, hashWeightedVertex<T, W, hash>> vertexes;
};


#endif /* SRC_GRAPH_UNIQUEWEIGHTEDGRAPH_H_ */
