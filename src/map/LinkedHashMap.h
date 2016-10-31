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

template<typename _KEY, typename _VALUE, int (*compare)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&), std::size_t (*hash)(const MapEntry<_KEY,_VALUE>&)>
class LinkedHashMapIterator;

template<typename _KEY, typename _VALUE, int (*compare)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&) = compareByKey, std::size_t (*hash)(const MapEntry<_KEY,_VALUE>&) = hashByKey>
class LinkedHashMap : public Map<_KEY,_VALUE> {
	friend class LinkedHashMapIterator<_KEY,_VALUE,compare,hash>;
public:
	typedef LinkedHashMapIterator<_KEY,_VALUE,compare,hash> iterator;

	LinkedHashMap(const std::size_t& reservedSize){
		hashTable = new LinkedHashTable<MapEntry<_KEY,_VALUE>, compare, hash>(reservedSize);
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	LinkedHashMap(){
		hashTable = new LinkedHashTable<MapEntry<_KEY,_VALUE>, compare, hash>;
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

	const _VALUE& operator[](const _KEY& key) const {
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		const MapEntry<_KEY,_VALUE>* result = hashTable->get(mapEntry);
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

		hashTable = new LinkedHashTable<MapEntry<_KEY,_VALUE>, compare, hash>;
	}

	bool containsKey(const _KEY& key) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.key = key;
		return hashTable->contains(mapEntry);
	}

	bool containsValue(const _VALUE& value, int (*valueComparator)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)=compareByValue) const{
		if(hashTable->isEmpty()) return false;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.value = value;
		return hashTable->contains(mapEntry, valueComparator);
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

	void removeValue(const _VALUE& value, int (*valueComparator)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)=compareByValue) {
		if(hashTable->isEmpty()) return;
		MapEntry<_KEY,_VALUE> mapEntry;
		mapEntry.value = value;
		hashTable->remove(mapEntry, valueComparator);
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
	LinkedHashTable<MapEntry<_KEY,_VALUE>, compare, hash>* hashTable;
	MapIterator<_KEY,_VALUE>* internalIteratorStart;
	MapIterator<_KEY,_VALUE>* internalIteratorEnd;
};

template<typename _KEY, typename _VALUE, int (*compare)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&), std::size_t (*hash)(const MapEntry<_KEY,_VALUE>&)>
class LinkedHashMapIterator : public MapIterator<_KEY,_VALUE> {
	public:
		LinkedHashMapIterator(LinkedHashTable<MapEntry<_KEY,_VALUE>, compare, hash>* map){
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

		const std::pair<_KEY, _VALUE> operator*(){
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
		LinkedHashTable<MapEntry<_KEY,_VALUE>, compare, hash>* content;
		LinkedHashTableEntry<MapEntry<_KEY,_VALUE>>* current_item;
		std::size_t total;
};

#endif /* HASHMAP_H_ */
