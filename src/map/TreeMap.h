/*
 * TreeMap.h
 *
 *  Created on: Aug 14, 2016
 *      Author: aherne
 */

#ifndef SRC_MAP_TREEMAP_H_
#define SRC_MAP_TREEMAP_H_

#include "../RedBlackTree.h"
#include "MapEntry.h"
#include "Map.h"
#include "../Comparator.h"

template<typename _KEY, typename _VALUE>
int compareByKey(const MapEntry<_KEY,_VALUE>& left, const MapEntry<_KEY,_VALUE>& right) {
	comparator<_KEY> cmp;
	return cmp(left.key, right.key);
}

template<typename _KEY, typename _VALUE>
int compareByValue(const MapEntry<_KEY,_VALUE>& left, const MapEntry<_KEY,_VALUE>& right) {
	comparator<_VALUE> cmp;
	return cmp(left.value, right.value);
}

template<typename _KEY, typename _VALUE>
class TreeMapIterator;

template<typename _KEY, typename _VALUE>
class TreeMap : public Map<_KEY,_VALUE> {
	friend class TreeMapIterator<_KEY,_VALUE>;
public:
	typedef TreeMapIterator<_KEY,_VALUE> iterator;

	TreeMap() {
		tree = new RedBlackTree<MapEntry<_KEY,_VALUE>>;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}
	~TreeMap() {
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			delete internalIteratorEnd;
		}
		delete tree;
	}

	void clear() {
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		delete tree;
		tree = new RedBlackTree<MapEntry<_KEY,_VALUE>>;
	}

	bool containsKey(const _KEY& key) const {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		return tree->hasNode(mapEntry, &compareByKey);
	}

	bool containsValue(const _VALUE& value) const {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.value = value;
		return tree->hasMatches(mapEntry, &compareByValue);
	}

	const _VALUE& get(const _KEY& key) const {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<_KEY,_VALUE>* result = tree->getNodeValue(mapEntry, &compareByKey);
		return result->value;
	}

	bool isEmpty() const {
		return tree->getSize()==0;
	}

	const std::size_t& size() const {
		return tree->getSize();
	}

	void set(const _KEY& key, const _VALUE& value) {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		mapEntry.value = value;
		tree->insertNode(mapEntry, &compareByKey);
	}

	void removeKey(const _KEY& key) {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		tree->deleteNode(mapEntry, &compareByKey);
	}

	void removeValue(const _VALUE& value) {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.value = value;
		tree->deleteMatches(mapEntry, &compareByValue);
	}

	MapIterator<_KEY,_VALUE>* begin(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(tree);
		return internalIteratorStart;
	}

	MapIterator<_KEY,_VALUE>* end(){
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(tree->getSize());
			return internalIteratorEnd;
		}
	}
private:
	RedBlackTree<MapEntry<_KEY,_VALUE>>* tree;
	MapIterator<_KEY,_VALUE>* internalIteratorStart;
	MapIterator<_KEY,_VALUE>* internalIteratorEnd;
};

template<typename _KEY, typename _VALUE>
class TreeMapIterator : public MapIterator<_KEY,_VALUE> {
	public:
		TreeMapIterator(RedBlackTree<MapEntry<_KEY,_VALUE>>* tree){
			this->tree = tree;
			current_item = tree->min();
			this->offset = 0;
		}

		TreeMapIterator(std::size_t total){
			tree = nullptr;
			current_item = nullptr;
			this->offset = total;
		}

		~TreeMapIterator(){}

		const std::pair<_KEY, _VALUE> operator*(){
			if(current_item==nullptr) throw std::out_of_range("Key not found!");
			return std::make_pair(current_item->data.key, current_item->data.value);
		}

		void operator++(){
			current_item = tree->getNextNode(current_item);
			++this->offset;
		}

	private:
		RedBlackTree<MapEntry<_KEY,_VALUE>>* tree;
		RedBlackTreeNode<MapEntry<_KEY,_VALUE>>* current_item;
};

#endif /* SRC_MAP_TREEMAP_H_ */
