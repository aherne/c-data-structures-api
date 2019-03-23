/*
 * TreeMap.h
 *
 *  Created on: Aug 14, 2016
 *      Author: aherne
 */

#ifndef SRC_MAP_TREEMAP_H_
#define SRC_MAP_TREEMAP_H_

#include "../tree/RedBlackTree.h"
#include "Map.h"
#include "../Comparator.h"

template<typename KEY, typename VALUE>
class TreeMapIterator;

template<typename KEY, typename VALUE, int (*compareByKey)(const KEY&, const KEY&), int (*compareByValue)(const VALUE&, const VALUE&) = comparator<VALUE>>
class TreeMap : public Map<KEY, VALUE> {
	friend class TreeMapIterator<KEY, VALUE>;
public:
	typedef TreeMapIterator<KEY, VALUE> iterator;

	TreeMap() {
		tree = new RedBlackTree<MapEntry<KEY, VALUE>>(compareMapKey<KEY, VALUE, compareByKey>);
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

	const VALUE& operator[](const KEY& key) const {
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<KEY, VALUE>* result = tree->getNodeValue(mapEntry);
		return result->value;
	}

	void clear() {
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		delete tree;
		tree = new RedBlackTree<MapEntry<KEY, VALUE>>(compareMapKey<KEY, VALUE, compareByKey>);
	}

	bool containsKey(const KEY& key) const {
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		return tree->hasNode(mapEntry);
	}

	bool containsValue(const VALUE& value) const {
		if(tree->getSize()==0) return false;
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.value = value;
		return tree->hasMatches(mapEntry, compareMapValue<KEY, VALUE, compareByValue>);
	}

	const VALUE& get(const KEY& key) const {
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<KEY, VALUE>* result = tree->getNodeValue(mapEntry);
		return result->value;
	}

	bool isEmpty() const {
		return tree->getSize()==0;
	}

	const std::size_t& size() const {
		return tree->getSize();
	}

	void set(const KEY& key, const VALUE& value) {
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		mapEntry.value = value;
		tree->insertNode(mapEntry);
	}

	void removeKey(const KEY& key) {
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		tree->deleteNode(mapEntry);
	}

	void removeValue(const VALUE& value) {
		if(tree->getSize()==0) return;
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.value = value;
		tree->deleteMatches(mapEntry, compareMapValue<KEY, VALUE, compareByValue>);
	}

	MapIterator<KEY, VALUE>* begin(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(tree);
		return internalIteratorStart;
	}

	MapIterator<KEY, VALUE>* end(){
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(tree->getSize());
			return internalIteratorEnd;
		}
	}
private:
	RedBlackTree<MapEntry<KEY, VALUE>>* tree;
	MapIterator<KEY, VALUE>* internalIteratorStart;
	MapIterator<KEY, VALUE>* internalIteratorEnd;
};

template<typename KEY, typename VALUE>
class TreeMapIterator : public MapIterator<KEY, VALUE> {
	public:
		TreeMapIterator(RedBlackTree<MapEntry<KEY, VALUE>>* tree){
			this->content = tree;
			current_item = tree->min();
			this->offset = 0;
			this->total = tree->getSize();
		}

		TreeMapIterator(std::size_t total){
			content = nullptr;
			current_item = nullptr;
			this->offset = total;
			this->total = total;
		}

		~TreeMapIterator(){}

		const std::pair<KEY, VALUE> operator*(){
			if(current_item==nullptr) throw std::out_of_range("Key not found!");
			return std::make_pair(current_item->data.key, current_item->data.value);
		}

		void operator++(){
			if(content->getSize()!=this->total) {
				this->offset = this->total;
			} else {
				current_item = content->getNextNode(current_item);
				++this->offset;
			}
		}

	private:
		RedBlackTree<MapEntry<KEY, VALUE>>* content;
		RedBlackTreeNode<MapEntry<KEY, VALUE>>* current_item;
		std::size_t total;
};

#endif /* SRC_MAP_TREEMAP_H_ */
