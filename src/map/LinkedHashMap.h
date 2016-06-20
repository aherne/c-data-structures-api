/*
 * HashMap.h
 *
 *  Created on: Feb 26, 2016
 *      Author: lucian p
 */

#ifndef LINKEDHASHMAP_H_
#define LINKEDHASHMAP_H_

#include <vector>
#include <algorithm>
#include <utility>
#include "Map.h"
#include "MapEntry.h"
#include "../Hashing.h"
#include "../Comparator.h"
#include "../list/DoublyLinkedListSorter.h"

template<typename _KEY, typename _VALUE>
struct LinkedHashMapEntry {
	std::size_t hash;
	MapEntry<_KEY,_VALUE> data;
	// singly linked list for traversal @ bucket
	LinkedHashMapEntry<_KEY, _VALUE>* nextInBucket;
	// doubly linked list for traversal in insertion order
	LinkedHashMapEntry<_KEY, _VALUE>* previous;
	LinkedHashMapEntry<_KEY, _VALUE>* next;
};

template<typename _KEY, typename _VALUE>
class KeyMapBucketComparator {
public:
	KeyMapBucketComparator(bool (*function)(const _KEY&,const _KEY&)) {
		compareFunction = function;
	}

	bool operator()(LinkedHashMapEntry<_KEY,_VALUE>*& left, LinkedHashMapEntry<_KEY,_VALUE>*& right) const {
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

	bool operator()(LinkedHashMapEntry<_KEY,_VALUE>*& left, LinkedHashMapEntry<_KEY,_VALUE>*& right) const {
		return compareFunction(left->data.key, right->data.key);
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

	LinkedHashMap(){
		count=0;
		bucket_count=8;
		buckets = new LinkedHashMapEntry<_KEY, _VALUE>*[bucket_count]();
		head = nullptr;
		tail = nullptr;
	}

	~LinkedHashMap(){
		emptyBuckets();
		head = nullptr;
		tail = nullptr;
	}

	void clear(){
		emptyBuckets();
		head = nullptr;
		tail = nullptr;

		count=0;
		bucket_count=8;
		buckets = new LinkedHashMapEntry<_KEY, _VALUE>*[bucket_count]();
	}

	bool containsKey(const _KEY& key) const{
		if(count==0) return false;
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);

		LinkedHashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
				return true;
			}
			currentBucket = currentBucket->nextInBucket;
		}
		return false;
	}

	bool containsValue(const _VALUE& value) const{
		if(count==0) return false;
		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashMapEntry<_KEY, _VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				if(valueComparator(currentBucket->data.value, value)==0) {
					return true;
				}
				currentBucket = currentBucket->nextInBucket;
			}
		}
		return false;
	}

	bool isEmpty() const {
		return (count==0?true:false);
	}

	const std::size_t& size() const{
		return count;
	}

	std::vector<_KEY> getKeys(){
		std::vector<_KEY> output;
		if(head!=nullptr) {
			LinkedHashMapEntry<_KEY, _VALUE>* currentBucket = head;
			while(currentBucket!=nullptr) {
				output.push_back(currentBucket->data.key);
				currentBucket = currentBucket->next;
			}
		}
		return output;
	}

	std::vector<_VALUE> getValues(){
		std::vector<_VALUE> output;
		if(head!=nullptr) {
			LinkedHashMapEntry<_KEY, _VALUE>* currentBucket = head;
			while(currentBucket!=nullptr) {
				output.push_back(currentBucket->data.value);
				currentBucket = currentBucket->next;
			}
		}
		return output;
	}

	const _VALUE& get(const _KEY& key) const{
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);

		LinkedHashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
				return currentBucket->data.value;
			}
			currentBucket = currentBucket->nextInBucket;
		}
		throw std::out_of_range("Value not found!");
	}

	void set(const _KEY& key, const _VALUE& value){
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);
		LinkedHashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		if(currentBucket!=nullptr) {
			while(currentBucket!=nullptr) {
				if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
					// update
					currentBucket->data.value = value;
					return;
				}
				if(currentBucket->nextInBucket == nullptr) {
					LinkedHashMapEntry<_KEY, _VALUE>* be = createEntry(hashValue, key,value);
					currentBucket->nextInBucket = be;

					if(tail!=nullptr) {
						tail->next = be;
					}
					tail = be;

					++ count;
					if(count == bucket_count) {
						rehash();
					}

					return;
				} else {
					currentBucket = currentBucket->nextInBucket;
				}
			}
		} else {
			LinkedHashMapEntry<_KEY, _VALUE>* be = createEntry(hashValue, key,value);
			buckets[bucketNumber] = be;

			if(head==nullptr) {
				head = be;
			}
			if(tail!=nullptr) {
				tail->next = be;
			}
			tail = be;

			++ count;
			if(count == bucket_count) {
				rehash();
			}

			return;
		}
	}

	void removeKey(const _KEY& key){
		if(count==0) return;
		std::size_t oldCount = count;
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);
		buckets[bucketNumber] = recursiveDeleteKey(buckets[bucketNumber], key);
		if(oldCount == count) throw std::out_of_range("Key not found!");
	}

	void removeValue(const _VALUE& value) {
		if(count==0) return;
		std::size_t oldCount = count;
		for(std::size_t i=0; i<bucket_count; ++i) {
			buckets[i] = recursiveDeleteValue(buckets[i], value);
		}
		if(oldCount == count) throw std::out_of_range("Value not found!");
	}

	iterator begin() {
		return LinkedHashMapIterator<_KEY,_VALUE>(this);
	}

	iterator end(){
		return LinkedHashMapIterator<_KEY,_VALUE>(count);
	}

	void sortByKey(bool (*comparator) (const _KEY&, const _KEY&)) {
		KeyMapBucketComparator<_KEY,_VALUE> klhmbc(comparator);
		DoublyLinkedListSorter<LinkedHashMapEntry<_KEY, _VALUE>, KeyMapBucketComparator<_KEY,_VALUE>> sort(&head, &tail, klhmbc);
	}
	void sortByValue(bool (*comparator) (const _VALUE&, const _VALUE&)) {
		ValueMapBucketComparator<_KEY,_VALUE> klhmbc(comparator);
		DoublyLinkedListSorter<LinkedHashMapEntry<_KEY, _VALUE>, ValueMapBucketComparator<_KEY,_VALUE>> sort(&head, &tail, klhmbc);
	}

private:
	LinkedHashMapEntry<_KEY, _VALUE>* createEntry(std::size_t hashValue, const _KEY& key, const _VALUE& value) {
		LinkedHashMapEntry<_KEY, _VALUE>* be = new LinkedHashMapEntry<_KEY, _VALUE>;
		be->hash = hashValue;
		be->data.key = key;
		be->data.value = value;
		be->nextInBucket = nullptr;
		be->next = nullptr;
		be->previous = tail;
		return be;
	}

	int getBucketNumber(std::size_t hash) const {
		return hash % bucket_count;
	}

	void deleteFromDoublyLinkedList(LinkedHashMapEntry<_KEY, _VALUE>*& currentBucket) {
		if(currentBucket == head) {
			head = head->next;		// one step forward
		} else if(currentBucket == tail) {
			tail = tail->previous;	// one step backward
			tail->next = nullptr;
		} else {
			currentBucket->previous->next = currentBucket->next;
		}
	}

	LinkedHashMapEntry<_KEY, _VALUE>* recursiveDeleteKey(LinkedHashMapEntry<_KEY, _VALUE>* currentBucket, const _KEY& key) {
		if (currentBucket == nullptr)
			return nullptr;

		if (keyComparator(currentBucket->data.key, key)==0) {
			deleteFromDoublyLinkedList(currentBucket);
			LinkedHashMapEntry<_KEY, _VALUE>* tempNextP;
			tempNextP = currentBucket->nextInBucket;
			delete currentBucket;
			-- count;
			return tempNextP;
		}
		currentBucket->nextInBucket = recursiveDeleteKey(currentBucket->nextInBucket, key);
		return currentBucket;
	}

	LinkedHashMapEntry<_KEY, _VALUE>* recursiveDeleteValue(LinkedHashMapEntry<_KEY, _VALUE>* currentBucket, const _VALUE& value) {
		if (currentBucket == nullptr)
			return nullptr;

		if (valueComparator(currentBucket->data.value,value)==0) {
			deleteFromDoublyLinkedList(currentBucket);
			LinkedHashMapEntry<_KEY, _VALUE>* tempNextP;
			tempNextP = currentBucket->nextInBucket;
			delete currentBucket;
			-- count;
			return tempNextP;
		}
		currentBucket->nextInBucket = recursiveDeleteValue(currentBucket->nextInBucket, value);
		return currentBucket;
	}

	void emptyBuckets(){
		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashMapEntry<_KEY, _VALUE>* head = buckets[i];
			LinkedHashMapEntry<_KEY, _VALUE>* del = head;
			while(del != nullptr) {
				head = head->nextInBucket;
				delete del;
				del = head;
			}
		}
		delete[] buckets;
	}

	void rehash(){
		std::size_t new_bucket_count = bucket_count*2 + 1;

		LinkedHashMapEntry<_KEY, _VALUE>** new_buckets = new LinkedHashMapEntry<_KEY, _VALUE>*[new_bucket_count]();

		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashMapEntry<_KEY, _VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				int bucket_number = currentBucket->hash % new_bucket_count;

	            // advance n *before* moving node to new hash bed
				LinkedHashMapEntry<_KEY, _VALUE>* tmp = currentBucket;
	            currentBucket = currentBucket->nextInBucket;

	            // find the proper collision list pointer.
	            LinkedHashMapEntry<_KEY, _VALUE>*& bucket = new_buckets[bucket_number];
	            tmp->nextInBucket = bucket;
	            bucket = tmp;
			}
		}

		delete [] buckets;
		buckets = new_buckets;
		bucket_count = new_bucket_count;
	}

	std::size_t count;

	// parameters needed by hash map
	std::size_t bucket_count;
	LinkedHashMapEntry<_KEY, _VALUE>** buckets;
	hash<_KEY> hashingFunc;

	// comparators
	comparator<_KEY> keyComparator;
	comparator<_VALUE> valueComparator;

	// parameters needed by doubly linked list
	LinkedHashMapEntry<_KEY, _VALUE>* head;
	LinkedHashMapEntry<_KEY, _VALUE>* tail;
};

template<typename _KEY, typename _VALUE>
class LinkedHashMapIterator {
	public:
		LinkedHashMapIterator(){
			current_item = nullptr;
			offset = 0;
		}

		LinkedHashMapIterator(LinkedHashMap<_KEY, _VALUE>* map){
			current_item = map->head;
			offset = 0;
		}

		LinkedHashMapIterator(std::size_t total){
			current_item = nullptr;
			offset = total;
		}

		~LinkedHashMapIterator(){}

		const std::pair<_KEY, _VALUE> operator*(){
			return std::make_pair(current_item->data.key, current_item->data.value);
		}

		bool operator!=(const LinkedHashMapIterator<_KEY,_VALUE>& it) const {
			return offset!=it.offset;
		}

		LinkedHashMapIterator<_KEY,_VALUE>& operator++(){
			if(current_item!=nullptr) {
				current_item = current_item->next;
			}
			++offset;
			return *this;
		}

	private:
		LinkedHashMapEntry<_KEY, _VALUE>* current_item;
		std::size_t offset;
};

#endif /* HASHMAP_H_ */
