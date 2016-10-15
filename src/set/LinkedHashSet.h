/*
 * HashSet.h
 *
 *  Created on: Mar 4, 2016
 *      Author: lucian
 */

#ifndef SRC_LINKEDHASHSET_H_
#define SRC_LINKEDHASHSET_H_

#include "../LinkedHashTable.h"
#include <algorithm>
#include "Set.h"
#include "../Hashing.h"
#include "../Comparator.h"
#include "../list/DoublyLinkedListSorter.h"


template<typename T>
class SetBucketComparator {
	public:
		SetBucketComparator(bool (*function)(const T&,const T&)) {
			compare = function;
		}
		int operator()(LinkedHashTableEntry<T>*& left, LinkedHashTableEntry<T>*& right) const {
			return compare(left->data, right->data);
		}
	private:
		bool (*compare)(const T&,const T&);
};

template<typename T>
class LinkedHashSetIterator;

template<typename T>
class LinkedHashSet : public Set<T> {
	friend class LinkedHashSetIterator<T>;
public:
	typedef LinkedHashSetIterator<T> iterator;

	LinkedHashSet(){
		hashTable = new LinkedHashTable<T>;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	LinkedHashSet(const std::size_t& reservedSize){
		hashTable = new LinkedHashTable<T>(reservedSize);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	~LinkedHashSet(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			delete internalIteratorEnd;
		}
		delete hashTable;
	}

	void clear(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		delete hashTable;

		hashTable = new LinkedHashTable<T>;
	}

	bool contains(const T& value) const {
		return hashTable->contains(value, &compareValue, &hashValue);
	}

	bool isEmpty() const{
		return hashTable->isEmpty();
	}

	const std::size_t& size() const{
		return hashTable->size();
	}

	void add(const T& value){
		hashTable->set(value, &compareValue, &hashValue);
	}

	void remove(const T& value){
		hashTable->remove(value, &compareValue, &hashValue);
	}

	SetIterator<T>* begin() {
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(hashTable);
		return internalIteratorStart;
	}

	SetIterator<T>* end() {
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(hashTable->size());
			return internalIteratorEnd;
		}
	}

	void sort(bool (*comparator) (const T&, const T&)) {
		SetBucketComparator<T> lhsc(comparator);
		DoublyLinkedListSorter<LinkedHashTableEntry<T>, SetBucketComparator<T>> sort(&hashTable->getHead(), &hashTable->getTail(), lhsc);
	}
private:
	LinkedHashTable<T>* hashTable;
	SetIterator<T>* internalIteratorStart;
	SetIterator<T>* internalIteratorEnd;
};

template<typename T>
class LinkedHashSetIterator : public SetIterator<T> {
	public:
		LinkedHashSetIterator(LinkedHashTable<T>* set){
			content = set;
			current_item = set->getHead();
			this->offset = 0;
			this->total = set->size();
		}

		LinkedHashSetIterator(std::size_t total){
			content = nullptr;
			current_item = nullptr;
			this->offset = total;
			this->total = total;
		}

		~LinkedHashSetIterator(){}

		const T& operator*(){
			if(current_item==nullptr) throw std::out_of_range("Key not found!");
			return current_item->data;
		}

		void operator++(){
			if(content->size()!=this->total) {
				this->offset = this->total;
			} else {
				if(current_item!=nullptr) {
					current_item = current_item->next;
				}
				++this->offset;
			}
		}

	private:
		LinkedHashTable<T>* content;
		LinkedHashTableEntry<T>* current_item;
		std::size_t total;
};

#endif /* SRC_LINKEDHASHSET_H_ */
