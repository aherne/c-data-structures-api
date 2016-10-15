/*
 * HashMap.h
 *
 *  Created on: Mar 17, 2016
 *      Author: lucian
 */

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include "../HashTable.h"
#include "MapEntry.h"
#include "Map.h"

template<typename _KEY, typename _VALUE>
class HashMapIterator;

template<typename _KEY, typename _VALUE>
class HashMap : public Map<_KEY,_VALUE> {
	friend class HashMapIterator<_KEY,_VALUE>;
public:
	typedef HashMapIterator<_KEY,_VALUE> iterator;

	HashMap(){
		hashTable = new HashTable<MapEntry<_KEY,_VALUE>,compareByKey, hashByKey>;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	HashMap(const std::size_t& reservedSize){
		hashTable = new HashTable<MapEntry<_KEY,_VALUE>,compareByKey, hashByKey>(reservedSize);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	~HashMap(){
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

		hashTable = new HashTable<MapEntry<_KEY,_VALUE>,compareByKey, hashByKey>;
	}

	bool containsKey(const _KEY& key) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		return hashTable->contains(mapEntry);
	}

	bool containsValue(const _VALUE& value) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.value = value;
		return hashTable->contains(mapEntry, &compareByValue);
	}

	bool isEmpty() const {
		return hashTable->isEmpty();
	}

	const std::size_t& size() const {
		return hashTable->size();
	}

	const _VALUE& get(const _KEY& key) const {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<_KEY,_VALUE>* result = hashTable->get(mapEntry);
		return result->value;
	}

	void set(const _KEY& key, const _VALUE& value){
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		mapEntry.value = value;
		hashTable->set(mapEntry);
	}

	void removeKey(const _KEY& key){
		if(hashTable->isEmpty()) return;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		hashTable->remove(mapEntry);
	}

	void removeValue(const _VALUE& value) {
		if(hashTable->isEmpty()) return;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.value = value;
		hashTable->remove(mapEntry, &compareByValue);
	}

	MapIterator<_KEY,_VALUE>* begin(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(hashTable);
		return internalIteratorStart;
	}

	MapIterator<_KEY,_VALUE>* end(){
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(hashTable->size());
			return internalIteratorEnd;
		}
	}

private:
	HashTable<MapEntry<_KEY,_VALUE>,compareByKey, hashByKey>* hashTable;
	MapIterator<_KEY,_VALUE>* internalIteratorStart;
	MapIterator<_KEY,_VALUE>* internalIteratorEnd;
};

template<typename _KEY, typename _VALUE>
class HashMapIterator : public MapIterator<_KEY,_VALUE> {
	public:
		HashMapIterator(HashTable<MapEntry<_KEY,_VALUE>,compareByKey, hashByKey>* hashTable){
			content = hashTable;
			current_bucket = hashTable->getMinBucket();
			current_position = 0;
			this->offset = 0;
			this->total = hashTable->size();
		}

		HashMapIterator(std::size_t total){
			content = nullptr;
			current_bucket = 0;
			current_position = 0;
			this->offset = total;
			this->total = total;
		}

		~HashMapIterator() {}

		const std::pair<_KEY, _VALUE> operator*(){
			HashTableEntry<MapEntry<_KEY, _VALUE>>* currentBucket = content->getCurrentNode(current_bucket, current_position);
			if(currentBucket==nullptr) throw std::out_of_range("Key not found!");
			return std::make_pair(currentBucket->data.key, currentBucket->data.value);
		}

		void operator++() {
			if(content->size()!=this->total) {
				this->offset = this->total;
			} else {
				content->nextNode(current_bucket, current_position);
				++this->offset;
			}
		}

	private:
		HashTable<MapEntry<_KEY,_VALUE>, compareByKey, hashByKey>* content;

		std::size_t current_bucket;
		std::size_t current_position;
		std::size_t total;
};


#endif /* SRC_HASHMAP_H_ */
