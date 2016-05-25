/*
 * HashSet.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef SET_HASHSET_H_
#define SET_HASHSET_H_

#include <vector>
#include "Set.h"
#include "HashSetEntry.h"
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
		count=0;
		bucket_count=8;
		buckets = new HashSetEntry<T>*[bucket_count]();
	}

	~HashSet(){
		emptyBuckets();
	}

	void clear(){
		emptyBuckets();

		count=0;
		bucket_count=8;
		buckets = new HashSetEntry<T>*[bucket_count]();
	}

	bool contains(const T& value) {
		if(count==0) return false;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);

		HashSetEntry<T>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && valueComparator(currentBucket->value,value)==0) {
				return true;
			}
			currentBucket = currentBucket->next;
		}
		return false;
	}

	bool isEmpty(){
		return (count==0?true:false);
	}

	std::size_t size(){
		return count;
	}

	std::vector<T> getValues(){
		std::vector<T> output;
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashSetEntry<T>* currentBucket = buckets[i];
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
		HashSetEntry<T>* currentBucket = buckets[bucketNumber];
		if(currentBucket!=nullptr) {
			// there are rows already, so loop until end
			while(currentBucket!=nullptr) {
				if(currentBucket->hash == hashValue && valueComparator(currentBucket->value, value)==0) {
					return; // value already exists
				}
				if(currentBucket->next == nullptr) {
					// append to end
					HashSetEntry<T>* be = new HashSetEntry<T>;
					be->hash = hashValue;
					be->value = value;
					be->next = nullptr;

					currentBucket->next = be;
					++ count;
					if(count == bucket_count) {
						rehash();
					}
					return;
				} else {
					currentBucket = currentBucket->next;
				}
			}
		} else {
			HashSetEntry<T>* be = new HashSetEntry<T>;
			be->hash = hashValue;
			be->value = value;
			be->next = nullptr;

			buckets[bucketNumber] = be;

			++ count;
			if(count == bucket_count) {
				rehash();
			}
			return;
		}
	}

	void remove(const T& value){
		if(count==0) return;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);
		HashSetEntry<T>* currentBucket = buckets[bucketNumber];
		HashSetEntry<T>* previousBucket = nullptr;
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && valueComparator(currentBucket->value,value)==0) {
				if(previousBucket!=nullptr) {
					previousBucket->next = currentBucket->next;
				} else {
					previousBucket = currentBucket->next;
				}
				delete currentBucket;
				buckets[bucketNumber] = previousBucket;
				--count;
				return;
			}
			previousBucket = currentBucket;
			currentBucket = currentBucket->next;
		}
		throw std::out_of_range("Key not found!");
	}

	HashSetIterator<T> begin() {
		return iterator(this);
	}

	HashSetIterator<T> end() {
		return iterator(this, count );
	}
private:
	int getBucketNumber(std::size_t hash) {
		return hash % bucket_count;
	}

	void emptyBuckets(){
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashSetEntry<T>* head = buckets[i];
			HashSetEntry<T>* del = head;
			while(del != nullptr) {
				head = head->next;
				delete del;
				del = head;
			}
		}
		delete[] buckets;
	}

	void rehash(){
		std::size_t new_bucket_count = bucket_count*2 + 1;

		HashSetEntry<T>** new_buckets = new HashSetEntry<T>*[new_bucket_count]();

		for(std::size_t i=0; i< bucket_count; ++i) {
			HashSetEntry<T>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				int bucket_number = currentBucket->hash % new_bucket_count;

	            // advance n *before* moving node to new hash bed
				HashSetEntry<T>* tmp = currentBucket;
	            currentBucket = currentBucket->next;

	            // find the proper collision list pointer.
	            HashSetEntry<T>*& bucket = new_buckets[bucket_number];
	            tmp->next = bucket;
	            bucket = tmp;
			}
		}

		delete [] buckets;
		buckets = new_buckets;
		bucket_count = new_bucket_count;
	}

	std::size_t count;
	std::size_t bucket_count;
	HashSetEntry<T> **buckets;

	hash<T> hashingFunc;
	comparator<T> valueComparator;
};


template<typename T>
class HashSetIterator {
	public:
		HashSetIterator(){
			content = nullptr;
			current_bucket = 0;
			current_position = 0;
			offset = 0;
		}

		HashSetIterator(HashSet<T>* set){
			content = set;
			current_bucket = 0;
			current_position = 0;
			offset = 0;
			for(std::size_t i=current_bucket; i< content->bucket_count; ++i) {
				HashSetEntry<T>* currentBucket = content->buckets[i];
				if(currentBucket!=nullptr) {
					current_bucket = i;
					return;
				}
			}
		}

		HashSetIterator(HashSet<T>* set, std::size_t total){
			content = set;
			current_bucket = 0;
			current_position = 0;
			offset = total;
		}

		~HashSetIterator() {}

		const T operator*() {
			HashSetEntry<T>* currentBucket = content->buckets[current_bucket];
			std::size_t j = 0;
			while(currentBucket!=nullptr) {
				if(j==current_position) {
					return currentBucket->value;
				}
				currentBucket = currentBucket->next;
				++j;
			}
			throw std::out_of_range("Element not found!");
		}

		bool operator!=(const HashSetIterator<T>& it) {
			return offset!=it.offset;
		}

		void operator++(){
			std::size_t j = 0;
			for(std::size_t i=current_bucket; i< content->bucket_count; ++i) {
				HashSetEntry<T>* currentBucket = content->buckets[i];
				while(currentBucket!=nullptr) {
					if(i==current_bucket) {
						if(j>current_position) {
							++current_position;
							++offset;
							return;
						}
						++j;
					} else {
						current_bucket = i;
						current_position = 0;
						++offset;
						return;
					}
					currentBucket = currentBucket->next;
				}
			}
			// if this step is reached, then iterator reached end
			++offset;
			return;
		}

		std::size_t offset;
	private:
		HashSet<T>* content;

		std::size_t current_bucket;
		std::size_t current_position;
};


#endif /* SET_HASHSET_H_ */
