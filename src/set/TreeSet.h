/*
 * TreeSet.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef SET_TREESET_H_
#define SET_TREESET_H_

#include "../RedBlackTree.h"
#include "Set.h"
#include "../Hashing.h"
#include "../Comparator.h"

template<typename T>
class TreeSetIterator;

template<typename T>
class TreeSet : public Set<T> {
	friend class TreeSetIterator<T>;
public:
	typedef TreeSetIterator<T> iterator;

	TreeSet() {
		tree = new RedBlackTree<T>;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}
	~TreeSet() {
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
		tree = new RedBlackTree<T>;
	}

	bool contains(const T& value) const {
		return tree->hasNode(value, &compareValue);
	}

	bool isEmpty() const {
		return tree->getSize()==0;
	}

	const std::size_t& size() const {
		return tree->getSize();
	}

	void add(const T& value) {
		tree->insertNode(value, &compareValue);
	}

	void remove(const T& value) {
		tree->deleteNode(value, &compareValue);
	}

	SetIterator<T>* begin(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(tree);
		return internalIteratorStart;
	}

	SetIterator<T>* end(){
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(tree->getSize());
			return internalIteratorEnd;
		}
	}
private:
	RedBlackTree<T>* tree;
	SetIterator<T>* internalIteratorStart;
	SetIterator<T>* internalIteratorEnd;
};

template<typename T>
class TreeSetIterator : public SetIterator<T> {
	public:
		TreeSetIterator(RedBlackTree<T>* tree){
			this->tree = tree;
			current_item = tree->min();
			this->offset = 0;
		}

		TreeSetIterator(std::size_t total){
			tree = nullptr;
			current_item = nullptr;
			this->offset = total;
		}

		~TreeSetIterator(){}

		const T& operator*(){
			if(current_item==nullptr) throw std::out_of_range("Key not found!");
			return current_item->data;
		}

		void operator++(){
			current_item = tree->getNextNode(current_item);
			++this->offset;
		}

	private:
		RedBlackTree<T>* tree;
		RedBlackTreeNode<T>* current_item;
};

#endif /* SET_TREESET_H_ */
