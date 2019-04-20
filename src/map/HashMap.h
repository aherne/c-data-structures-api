/*
 * HashMap.h
 *
 *  Created on: Mar 17, 2016
 *      Author: lucian
 */

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include "../HashTable.h"
#include "Map.h"
#include "../Comparator.h"
#include "../Hashing.h"

template<typename KEY, typename VALUE>
class HashMapIterator;

template<typename KEY, typename VALUE, int (*compareByKey)(const KEY&, const KEY&)=comparator<KEY>, std::size_t (*hash)(const KEY&)=hash<KEY>, int (*compareByValue)(const VALUE&, const VALUE&) = comparator<VALUE>>
class HashMap : public Map<KEY,VALUE> {
	friend class HashMapIterator<KEY,VALUE>;
public:
	typedef HashMapIterator<KEY,VALUE> iterator;

	HashMap(){
		hashTable = new HashTable<MapEntry<KEY,VALUE>>(compareMapKey<KEY, VALUE, compareByKey>, hashMapKey<KEY, VALUE, hash>);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	HashMap(const std::size_t& reservedSize){
		hashTable = new HashTable<MapEntry<KEY,VALUE>>(compareMapKey<KEY, VALUE, compareByKey>, hashMapKey<KEY, VALUE, hash>, reservedSize);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	HashMap(const HashMap<KEY, VALUE, compareByKey, hash, compareByValue>& other) = delete;

	~HashMap(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			delete internalIteratorEnd;
		}
		delete hashTable;
	}

	const VALUE& operator[](const KEY& key) const {
		MapEntry<KEY,VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<KEY,VALUE>* result = hashTable->get(mapEntry);
		return result->value;
	}

	void clear(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		delete hashTable;

		hashTable = new HashTable<MapEntry<KEY,VALUE>>(compareMapKey<KEY, VALUE, compareByKey>, hashMapKey<KEY, VALUE, hash>);
	}

	bool containsKey(const KEY& key) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<KEY,VALUE> mapEntry;
		mapEntry.key = key;
		return hashTable->contains(mapEntry);
	}

	bool containsValue(const VALUE& value) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<KEY,VALUE> mapEntry;
		mapEntry.value = value;
		return hashTable->contains(mapEntry, compareMapValue<KEY, VALUE, compareByValue>);
	}

	bool isEmpty() const {
		return hashTable->isEmpty();
	}

	const std::size_t& size() const {
		return hashTable->size();
	}

	const VALUE& get(const KEY& key) const {
		MapEntry<KEY,VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<KEY,VALUE>* result = hashTable->get(mapEntry);
		return result->value;
	}

	void set(const KEY& key, const VALUE& value){
		MapEntry<KEY,VALUE> mapEntry;
		mapEntry.key = key;
		mapEntry.value = value;
		hashTable->set(mapEntry);
	}

	void removeKey(const KEY& key){
		if(hashTable->isEmpty()) return;
		MapEntry<KEY,VALUE> mapEntry;
		mapEntry.key = key;
		hashTable->remove(mapEntry);
	}

	void removeValue(const VALUE& value) {
		if(hashTable->isEmpty()) return;
		MapEntry<KEY,VALUE> mapEntry;
		mapEntry.value = value;
		hashTable->remove(mapEntry, compareMapValue<KEY, VALUE, compareByValue>);
	}

	MapIterator<KEY,VALUE>* begin(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(hashTable);
		return internalIteratorStart;
	}

	MapIterator<KEY,VALUE>* end(){
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(hashTable->size());
			return internalIteratorEnd;
		}
	}

private:
	HashTable<MapEntry<KEY,VALUE>>* hashTable;
	MapIterator<KEY,VALUE>* internalIteratorStart;
	MapIterator<KEY,VALUE>* internalIteratorEnd;
};

template<typename KEY, typename VALUE>
class HashMapIterator : public MapIterator<KEY,VALUE> {
	public:
		HashMapIterator(HashTable<MapEntry<KEY,VALUE>>* hashTable){
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

		const std::pair<KEY, VALUE> operator*(){
			HashTableEntry<MapEntry<KEY, VALUE>>* currentBucket = content->getCurrentNode(current_bucket, current_position);
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
		HashTable<MapEntry<KEY,VALUE>>* content;

		std::size_t current_bucket;
		std::size_t current_position;
		std::size_t total;
};


#endif /* SRC_HASHMAP_H_ */
