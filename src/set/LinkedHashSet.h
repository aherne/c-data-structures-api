/*
 * HashSet.h
 *
 *  Created on: Mar 4, 2016
 *      Author: lucian
 */

#ifndef SRC_LINKEDHASHSET_H_
#define SRC_LINKEDHASHSET_H_

#include <vector>
#include <algorithm>
#include "Set.h"
#include "../Hashing.h"
#include "../Comparator.h"
#include "../list/DoublyLinkedListSorter.h"

template<typename T>
struct LinkedHashSetEntry {
	std::size_t hash;
	T value;
	// singly linked list for traversal @ bucket
	LinkedHashSetEntry<T>* nextInBucket;
	// doubly linked list for traversal in insertion order
	LinkedHashSetEntry<T>* previous;
	LinkedHashSetEntry<T>* next;
};

template<typename T>
class SetBucketComparator {
	public:
		SetBucketComparator(bool (*function)(const T&,const T&)) {
			compare = function;
		}
		int operator()(LinkedHashSetEntry<long int>* const& left, LinkedHashSetEntry<long int>* const& right) const {
			return compare(left->value, right->value);
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
		count=0;
		bucket_count=8;
		buckets = new LinkedHashSetEntry<T>*[bucket_count]();
		head = nullptr;
		tail = nullptr;
	}

	~LinkedHashSet(){
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
		buckets = new LinkedHashSetEntry<T>*[bucket_count]();
	}

	bool contains(const T& value) const {
		if(count==0) return false;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);

		LinkedHashSetEntry<T>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && valueComparator(currentBucket->value,value)==0) {
				return true;
			}
			currentBucket = currentBucket->nextInBucket;
		}
		return false;
	}

	bool isEmpty() const{
		return (count==0?true:false);
	}

	const std::size_t& size() const{
		return count;
	}

	std::vector<T> getValues(){
		std::vector<T> output;
		if(head!=nullptr) {
			LinkedHashSetEntry<T>* currentBucket = head;
			while(currentBucket!=nullptr) {
				output.push_back(currentBucket->value);
				currentBucket = currentBucket->next;
			}
		}
		return output;
	}

	void add(const T& value){
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);
		LinkedHashSetEntry<T>* currentBucket = buckets[bucketNumber];
		if(currentBucket!=nullptr) {
			// there are rows already, so loop until end
			while(currentBucket!=nullptr) {
				if(currentBucket->hash == hashValue && valueComparator(currentBucket->value, value)==0) {
					return; // value already exists
				}
				if(currentBucket->nextInBucket == nullptr) {
					LinkedHashSetEntry<T>* be = createEntry(hashValue, value);
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
			LinkedHashSetEntry<T>* be = createEntry(hashValue, value);
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

	LinkedHashSetEntry<T>* createEntry(std::size_t hashValue, const T& value) {
		LinkedHashSetEntry<T>* be = new LinkedHashSetEntry<T>;
		be->hash = hashValue;
		be->value = value;
		be->nextInBucket = nullptr;
		be->next = nullptr;
		be->previous = tail;
		return be;
	}

	void remove(const T& value) {
		if(count==0) return;
		std::size_t oldCount = count;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);
		buckets[bucketNumber] = recursiveDelete(buckets[bucketNumber], value);
		if(oldCount == count) throw std::out_of_range("Key not found!");
	}

	iterator begin() {
		return iterator(this);
	}

	iterator end(){
		return iterator(count);
	}

	void sort(bool (*comparator) (const T&, const T&)) {
		SetBucketComparator<T> lhsc(comparator);
		DoublyLinkedListSorter<LinkedHashSetEntry<T>, SetBucketComparator<T>> sort(&head, &tail, lhsc);
	}
private:

	int getBucketNumber(std::size_t hash) const {
		return hash % bucket_count;
	}

	void deleteFromDoublyLinkedList(LinkedHashSetEntry<T>*& currentBucket) {
		if(currentBucket == head) {
			head = head->next;		// one step forward
		} else if(currentBucket == tail) {
			tail = tail->previous;	// one step backward
			tail->next = nullptr;
		} else {
			currentBucket->previous->next = currentBucket->next;
		}
	}

	LinkedHashSetEntry<T>* recursiveDelete(LinkedHashSetEntry<T>* currentBucket, const T& value) {
		if (currentBucket == nullptr)
			return nullptr;

		if (valueComparator(currentBucket->value, value)==0) {
			deleteFromDoublyLinkedList(currentBucket);
			LinkedHashSetEntry<T>* tempNextP;
			tempNextP = currentBucket->nextInBucket;
			delete currentBucket;
			-- count;
			return tempNextP;
		}
		currentBucket->nextInBucket = recursiveDelete(currentBucket->nextInBucket, value);
		return currentBucket;
	}

	void emptyBuckets() {
		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashSetEntry<T>* head = buckets[i];
			LinkedHashSetEntry<T>* del = head;
			while(del != nullptr) {
				head = head->nextInBucket;
				delete del;
				del = head;
			}
		}
		delete[] buckets;
	}

	void rehash() {
		std::size_t new_bucket_count = bucket_count*2 + 1;

		LinkedHashSetEntry<T>** new_buckets = new LinkedHashSetEntry<T>*[new_bucket_count]();

		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashSetEntry<T>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				int bucket_number = currentBucket->hash % new_bucket_count;

	            // advance n *before* moving node to new hash bed
				LinkedHashSetEntry<T>* tmp = currentBucket;
	            currentBucket = currentBucket->nextInBucket;

	            // find the proper collision list pointer.
	            LinkedHashSetEntry<T>*& bucket = new_buckets[bucket_number];
	            tmp->nextInBucket = bucket;
	            bucket = tmp;
			}
		}

		delete [] buckets;
		buckets = new_buckets;
		bucket_count = new_bucket_count;
	}

	std::size_t count;

	std::size_t bucket_count;
	LinkedHashSetEntry<T> **buckets;
	hash<T> hashingFunc;

	comparator<T> valueComparator;

	// parameters needed by doubly linked list
	LinkedHashSetEntry<T>* head;
	LinkedHashSetEntry<T>* tail;
};

template<typename T>
class LinkedHashSetIterator {
	public:
		LinkedHashSetIterator(){
			current_item = nullptr;
			offset = 0;
		}

		LinkedHashSetIterator(LinkedHashSet<T>* map){
			current_item = map->head;
			offset = 0;
		}

		LinkedHashSetIterator(std::size_t total){
			current_item = nullptr;
			offset = total;
		}

		~LinkedHashSetIterator(){}

		const T operator*(){
			return current_item->value;
		}

		bool operator!=(const LinkedHashSetIterator<T>& it) const {
			return offset!=it.offset;
		}

		LinkedHashSetIterator<T>& operator++(){
			if(current_item!=nullptr) {
				current_item = current_item->next;
			}
			++offset;
			return *this;
		}

	private:
		LinkedHashSetEntry<T>* current_item;
		std::size_t offset;
};

#endif /* SRC_LINKEDHASHSET_H_ */
