/*
 * TreeSet.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef SET_TREESET_H_
#define SET_TREESET_H_

#include "../tree/RedBlackTree.h"
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
		tree = new RedBlackTree<T, compareByValue>;
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
		tree = new RedBlackTree<T, compareByValue>;
	}

	bool contains(const T& value) const {
		return tree->hasNode(value);
	}

	bool isEmpty() const {
		return tree->getSize()==0;
	}

	const std::size_t& size() const {
		return tree->getSize();
	}

	void add(const T& value) {
		tree->insertNode(value);
	}

	void remove(const T& value) {
		tree->deleteNode(value);
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
	RedBlackTree<T, compareByValue>* tree;
	SetIterator<T>* internalIteratorStart;
	SetIterator<T>* internalIteratorEnd;
};

template<typename T>
class TreeSetIterator : public SetIterator<T> {
	public:
		TreeSetIterator(RedBlackTree<T, compareByValue>* tree){
			content = tree;
			current_item = tree->min();
			this->offset = 0;
			this->total = tree->getSize();
		}

		TreeSetIterator(std::size_t total){
			content = nullptr;
			current_item = nullptr;
			this->offset = total;
			this->total = total;
		}

		~TreeSetIterator(){}

		const T& operator*(){
			if(current_item==nullptr) throw std::out_of_range("Key not found!");
			return current_item->data;
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
		RedBlackTree<T, compareByValue>* content;
		RedBlackTreeNode<T>* current_item;
		std::size_t total;
};

#endif /* SET_TREESET_H_ */
