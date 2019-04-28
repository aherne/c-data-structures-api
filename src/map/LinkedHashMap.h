/*
 * HashMap.h
 *
 *  Created on: Feb 26, 2016
 *      Author: lucian p
 */

#ifndef LINKEDHASHMAP_H_
#define LINKEDHASHMAP_H_

#include <stdexcept>
#include <algorithm>
#include <utility>
#include "../utilities/LinkedHashTable.h"
#include "Map.h"
#include "../list/DoublyLinkedListSorter.h"
#include "../Comparator.h"
#include "../Hashing.h"


template<typename KEY, typename VALUE>
class KeyMapBucketComparator {
public:
	KeyMapBucketComparator(bool (*function)(const KEY&, const KEY&)) {
		compareFunction = function;
	}

	bool operator()(LinkedHashTableEntry<MapEntry<KEY, VALUE>>*& left, LinkedHashTableEntry<MapEntry<KEY, VALUE>>*& right) const {
		return compareFunction(left->data.key, right->data.key);
	}
private:
	bool (*compareFunction)(const KEY&, const KEY&);
};

template<typename KEY, typename VALUE>
class ValueMapBucketComparator {
public:
	ValueMapBucketComparator(bool (*function)(const VALUE&, const VALUE&)) {
		compareFunction = function;
	}

	bool operator()(LinkedHashTableEntry<MapEntry<KEY, VALUE>>*& left, LinkedHashTableEntry<MapEntry<KEY, VALUE>>*& right) const {
		return compareFunction(left->data.value, right->data.value);
	}
private:
	bool (*compareFunction)(const VALUE&, const VALUE&);
};

template<typename KEY, typename VALUE>
class LinkedHashMapIterator;

template<typename KEY, typename VALUE, int (*compareByKey)(const KEY&, const KEY&) = comparator<KEY>, std::size_t (*hash)(const KEY&) = hash<KEY>, int (*compareByValue)(const VALUE&, const VALUE&) = comparator<VALUE>>
class LinkedHashMap : public Map<KEY, VALUE> {
	friend class LinkedHashMapIterator<KEY, VALUE>;
public:
	typedef LinkedHashMapIterator<KEY, VALUE> iterator;

	LinkedHashMap(const std::size_t& reservedSize){
		hashTable = new LinkedHashTable<MapEntry<KEY, VALUE>>(compareMapKey<KEY, VALUE, compareByKey>, hashMapKey<KEY, VALUE, hash>, reservedSize);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	LinkedHashMap(){
		hashTable = new LinkedHashTable<MapEntry<KEY, VALUE>>(compareMapKey<KEY, VALUE, compareByKey>, hashMapKey<KEY, VALUE, hash>);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	LinkedHashMap(const LinkedHashMap<KEY, VALUE, compareByKey, hash, compareByValue>& other) = delete;

	~LinkedHashMap(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			delete internalIteratorEnd;
		}
		delete hashTable;
	}

	const VALUE& operator[](const KEY& key) const {
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<KEY, VALUE>* result = hashTable->get(mapEntry);
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

		hashTable = new LinkedHashTable<MapEntry<KEY, VALUE>>(compareMapKey<KEY, VALUE, compareByKey>, hashMapKey<KEY, VALUE, hash>);
	}

	bool containsKey(const KEY& key) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		return hashTable->contains(mapEntry);
	}

	bool containsValue(const VALUE& value) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<KEY, VALUE> mapEntry;
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
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<KEY, VALUE>* result = hashTable->get(mapEntry);
		return result->value;
	}

	void set(const KEY& key, const VALUE& value){
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		mapEntry.value = value;
		hashTable->set(mapEntry);
	}

	void removeKey(const KEY& key){
		if(hashTable->isEmpty()) return;
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.key = key;
		hashTable->remove(mapEntry);
	}

	void removeValue(const VALUE& value) {
		if(hashTable->isEmpty()) return;
		MapEntry<KEY, VALUE> mapEntry;
		mapEntry.value = value;
		hashTable->remove(mapEntry, compareMapValue<KEY, VALUE, compareByValue>);
	}

	MapIterator<KEY, VALUE>* begin(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(hashTable);
		return internalIteratorStart;
	}

	MapIterator<KEY, VALUE>* end(){
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(hashTable->size());
			return internalIteratorEnd;
		}
	}

	void sortByKey(bool (*comparator) (const KEY&, const KEY&)) {
		KeyMapBucketComparator<KEY, VALUE> klhmbc(comparator);
		DoublyLinkedListSorter<LinkedHashTableEntry<MapEntry<KEY, VALUE>>, KeyMapBucketComparator<KEY, VALUE>> sort(&(hashTable->getHead()), &(hashTable->getTail()), klhmbc);
	}
	void sortByValue(bool (*comparator) (const VALUE&, const VALUE&)) {
		ValueMapBucketComparator<KEY, VALUE> klhmbc(comparator);
		DoublyLinkedListSorter<LinkedHashTableEntry<MapEntry<KEY, VALUE>>, ValueMapBucketComparator<KEY, VALUE>> sort(&(hashTable->getHead()), &(hashTable->getTail()), klhmbc);
	}

private:
	LinkedHashTable<MapEntry<KEY, VALUE>>* hashTable;
	MapIterator<KEY, VALUE>* internalIteratorStart;
	MapIterator<KEY, VALUE>* internalIteratorEnd;
};

template<typename KEY, typename VALUE>
class LinkedHashMapIterator : public MapIterator<KEY, VALUE> {
	public:
		LinkedHashMapIterator(LinkedHashTable<MapEntry<KEY, VALUE>>* map){
			content = map;
			current_item = map->getHead();
			this->offset = 0;
			this->total = map->size();
		}

		LinkedHashMapIterator(std::size_t total){
			content = nullptr;
			current_item = nullptr;
			this->offset = total;
			this->total = total;
		}

		~LinkedHashMapIterator(){}

		const std::pair<KEY, VALUE> operator*(){
			if(current_item==nullptr) throw std::out_of_range("Key not found!");
			return std::make_pair(current_item->data.key, current_item->data.value);
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
		LinkedHashTable<MapEntry<KEY, VALUE>>* content;
		LinkedHashTableEntry<MapEntry<KEY, VALUE>>* current_item;
		std::size_t total;
};

#endif /* HASHMAP_H_ */
