/*
 * HashSet.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef SET_HASHSET_H_
#define SET_HASHSET_H_

#include "../HashTable.h"
#include "Set.h"
#include "../Hashing.h"
#include "../Comparator.h"

template<typename T>
class HashSetIterator;

template<typename T>
class HashSet : public Set<T> {
	friend class HashSetIterator<T>;
public:
	typedef HashSetIterator<T> iterator;

	HashSet(){
		hashTable = new HashTable<T>;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}
	HashSet(const std::size_t& reservedSize){
		hashTable = new HashTable<T>(reservedSize);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	~HashSet(){
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

		hashTable = new HashTable<T>;
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
private:
	HashTable<T>* hashTable;
	SetIterator<T>* internalIteratorStart;
	SetIterator<T>* internalIteratorEnd;
};


template<typename T>
class HashSetIterator : public SetIterator<T> {
	public:
		HashSetIterator(HashTable<T>* hashTable){
			content = hashTable;
			current_bucket = hashTable->getMinBucket();
			current_position = 0;
			this->offset = 0;
		}

		HashSetIterator(std::size_t total){
			content = nullptr;
			current_bucket = 0;
			current_position = 0;
			this->offset = total;
		}

		~HashSetIterator() {}

		const T& operator*(){
			HashTableEntry<T>* currentBucket = content->getCurrentNode(current_bucket, current_position);
			if(currentBucket==nullptr) throw std::out_of_range("Key not found!");
			return currentBucket->data;
		}

		void operator++() {
			content->nextNode(current_bucket, current_position);
			++this->offset;
			return;
		}

	private:
		HashTable<T>* content;

		std::size_t current_bucket;
		std::size_t current_position;
};


#endif /* SET_HASHSET_H_ */
