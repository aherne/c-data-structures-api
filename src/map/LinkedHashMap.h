/*
 * HashMap.h
 *
 *  Created on: Feb 26, 2016
 *      Author: lucian p
 */

#ifndef LINKEDHASHMAP_H_
#define LINKEDHASHMAP_H_

#include <algorithm>
#include <utility>
#include "../LinkedHashTable.h"
#include "MapEntry.h"
#include "Map.h"
#include "../list/DoublyLinkedListSorter.h"


template<typename _KEY, typename _VALUE>
class KeyMapBucketComparator {
public:
	KeyMapBucketComparator(bool (*function)(const _KEY&,const _KEY&)) {
		compareFunction = function;
	}

	bool operator()(LinkedHashTableEntry<MapEntry<_KEY, _VALUE>>*& left, LinkedHashTableEntry<MapEntry<_KEY, _VALUE>>*& right) const {
		return compareFunction(left->data.key, right->data.key);
	}
private:
	bool (*compareFunction)(const _KEY&,const _KEY&);
};

template<typename _KEY, typename _VALUE>
class ValueMapBucketComparator {
public:
	ValueMapBucketComparator(bool (*function)(const _VALUE&,const _VALUE&)) {
		compareFunction = function;
	}

	bool operator()(LinkedHashTableEntry<MapEntry<_KEY, _VALUE>>*& left, LinkedHashTableEntry<MapEntry<_KEY, _VALUE>>*& right) const {
		return compareFunction(left->data.value, right->data.value);
	}
private:
	bool (*compareFunction)(const _VALUE&,const _VALUE&);
};

template<typename _KEY, typename _VALUE>
class LinkedHashMapIterator;

template<typename _KEY, typename _VALUE>
class LinkedHashMap : public Map<_KEY,_VALUE> {
	friend class LinkedHashMapIterator<_KEY,_VALUE>;
public:
	typedef LinkedHashMapIterator<_KEY,_VALUE> iterator;

	LinkedHashMap(const std::size_t& reservedSize){
		hashTable = new LinkedHashTable<MapEntry<_KEY,_VALUE>>(reservedSize);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	LinkedHashMap(){
		hashTable = new LinkedHashTable<MapEntry<_KEY,_VALUE>>;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	~LinkedHashMap(){
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

		hashTable = new LinkedHashTable<MapEntry<_KEY,_VALUE>>;
	}

	bool containsKey(const _KEY& key) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		return hashTable->contains(mapEntry, &compareByKey, &hasher);
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
		const MapEntry<_KEY,_VALUE>* result = hashTable->get(mapEntry, &compareByKey, &hasher);
		return result->value;
	}

	void set(const _KEY& key, const _VALUE& value){
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		mapEntry.value = value;
		hashTable->set(mapEntry, &compareByKey, &hasher);
	}

	void removeKey(const _KEY& key){
		if(hashTable->isEmpty()) return;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		hashTable->remove(mapEntry, &compareByKey, &hasher);
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

	void sortByKey(bool (*comparator) (const _KEY&, const _KEY&)) {
		KeyMapBucketComparator<_KEY,_VALUE> klhmbc(comparator);
		DoublyLinkedListSorter<LinkedHashTableEntry<MapEntry<_KEY, _VALUE>>, KeyMapBucketComparator<_KEY,_VALUE>> sort(&(hashTable->getHead()), &(hashTable->getTail()), klhmbc);
	}
	void sortByValue(bool (*comparator) (const _VALUE&, const _VALUE&)) {
		ValueMapBucketComparator<_KEY,_VALUE> klhmbc(comparator);
		DoublyLinkedListSorter<LinkedHashTableEntry<MapEntry<_KEY, _VALUE>>, ValueMapBucketComparator<_KEY,_VALUE>> sort(&(hashTable->getHead()), &(hashTable->getTail()), klhmbc);
	}

private:
	LinkedHashTable<MapEntry<_KEY,_VALUE>>* hashTable;
	MapIterator<_KEY,_VALUE>* internalIteratorStart;
	MapIterator<_KEY,_VALUE>* internalIteratorEnd;
};

template<typename _KEY, typename _VALUE>
class LinkedHashMapIterator : public MapIterator<_KEY,_VALUE> {
	public:
		LinkedHashMapIterator(LinkedHashTable<MapEntry<_KEY,_VALUE>>* map){
			current_item = map->getHead();
			this->offset = 0;
		}

		LinkedHashMapIterator(std::size_t total){
			current_item = nullptr;
			this->offset = total;
		}

		~LinkedHashMapIterator(){}

		const std::pair<_KEY, _VALUE> operator*(){
			if(current_item==nullptr) throw std::out_of_range("Key not found!");
			return std::make_pair(current_item->data.key, current_item->data.value);
		}

		void operator++(){
			if(current_item!=nullptr) {
				current_item = current_item->next;
			}
			++this->offset;
		}

	private:
		LinkedHashTableEntry<MapEntry<_KEY,_VALUE>>* current_item;
};

#endif /* HASHMAP_H_ */
