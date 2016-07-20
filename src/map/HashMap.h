/*
 * HashMap.h
 *
 *  Created on: Mar 17, 2016
 *      Author: lucian
 */

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include <utility>
#include "Map.h"
#include "../Hashing.h"
#include "../Comparator.h"

#include "MapEntry.h"

template<typename _KEY, typename _VALUE>
struct HashMapEntry {
	std::size_t hash;
	MapEntry<_KEY,_VALUE> data;
	HashMapEntry<_KEY, _VALUE>* next;
};

template<typename _KEY, typename _VALUE>
class HashMapIterator;


template<typename _KEY, typename _VALUE>
class HashMap : public Map<_KEY,_VALUE> {
	friend class HashMapIterator<_KEY,_VALUE>;
public:
	typedef HashMapIterator<_KEY,_VALUE> iterator;

	HashMap(){
		count=0;
		bucket_count=8;
		buckets = new HashMapEntry<_KEY, _VALUE>*[bucket_count]();
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	~HashMap(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			delete internalIteratorEnd;
		}
		emptyBuckets();
	}

	void clear(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		emptyBuckets();

		count=0;
		bucket_count=8;
		buckets = new HashMapEntry<_KEY, _VALUE>*[bucket_count]();
	}

	bool containsKey(const _KEY& key) const{
		if(count==0) return false;
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);

		HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
				return true;
			}
			currentBucket = currentBucket->next;
		}
		return false;
	}

	bool containsValue(const _VALUE& value) const{
		if(count==0) return false;
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				if(valueComparator(currentBucket->data.value, value)==0) {
					return true;
				}
				currentBucket = currentBucket->next;
			}
		}
		return false;
	}

	bool isEmpty() const {
		return (count==0?true:false);
	}

	const std::size_t& size() const {
		return count;
	}

	const _VALUE& get(const _KEY& key) const {
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);

		HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
				return currentBucket->data.value;
			}
			currentBucket = currentBucket->next;
		}
		throw std::out_of_range("Key not found!");
	}

	void set(const _KEY& key, const _VALUE& value){
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);
		HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		if(currentBucket!=nullptr) {
			// there are rows already, so loop until end
			while(currentBucket!=nullptr) {
				if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
					// update
					currentBucket->data.value = value;
					return;
				}
				if(currentBucket->next == nullptr) {
					// append to end
					HashMapEntry<_KEY, _VALUE>* be = new HashMapEntry<_KEY, _VALUE>;
					be->hash = hashValue;
					be->data.key = key;
					be->data.value = value;
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
			HashMapEntry<_KEY, _VALUE>* be = new HashMapEntry<_KEY, _VALUE>;
			be->hash = hashValue;
			be->data.key = key;
			be->data.value = value;
			be->next = nullptr;

			buckets[bucketNumber] = be;

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

	MapIterator<_KEY,_VALUE>* begin(){
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(this);
		return internalIteratorStart;
	}

	MapIterator<_KEY,_VALUE>* end(){
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(count);
			return internalIteratorEnd;
		}
	}

private:
	MapIterator<_KEY,_VALUE>* internalIteratorStart;
	MapIterator<_KEY,_VALUE>* internalIteratorEnd;

	int getBucketNumber(std::size_t hash) const {
		return hash % bucket_count;
	}

	HashMapEntry<_KEY, _VALUE>* recursiveDeleteKey(HashMapEntry<_KEY, _VALUE>* currentBucket, const _KEY& key) {
		if (currentBucket == nullptr)
			return nullptr;

		if (keyComparator(currentBucket->data.key, key)==0) {
			HashMapEntry<_KEY, _VALUE>* tempNextP;
			tempNextP = currentBucket->next;
			delete currentBucket;
			-- count;
			return tempNextP;
		}
		currentBucket->next = recursiveDeleteKey(currentBucket->next, key);
		return currentBucket;
	}

	HashMapEntry<_KEY, _VALUE>* recursiveDeleteValue(HashMapEntry<_KEY, _VALUE> *currP, const _VALUE& value) {
		if (currP == nullptr)
			return nullptr;

		if (valueComparator(currP->data.value,value)==0) {
			HashMapEntry<_KEY, _VALUE>* tempNextP;
			tempNextP = currP->next;
			delete currP;
			-- count;
			return tempNextP;
		}
		currP->next = recursiveDeleteValue(currP->next, value);
		return currP;
	}

	void emptyBuckets() {
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashMapEntry<_KEY, _VALUE>* head = buckets[i];
			HashMapEntry<_KEY, _VALUE>* del = head;
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

		HashMapEntry<_KEY, _VALUE>** new_buckets = new HashMapEntry<_KEY, _VALUE>*[new_bucket_count]();

		for(std::size_t i=0; i< bucket_count; ++i) {
			HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				int bucket_number = currentBucket->hash % new_bucket_count;

	            // advance n *before* moving node to new hash bed
				HashMapEntry<_KEY, _VALUE>* tmp = currentBucket;
	            currentBucket = currentBucket->next;

	            // find the proper collision list pointer.
	            HashMapEntry<_KEY, _VALUE>*& bucket = new_buckets[bucket_number];
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
	HashMapEntry<_KEY, _VALUE> **buckets;

	hash<_KEY> hashingFunc;
	comparator<_KEY> keyComparator;
	comparator<_VALUE> valueComparator;
};

template<typename _KEY, typename _VALUE>
class HashMapIterator : public MapIterator<_KEY,_VALUE> {
	public:
		HashMapIterator(HashMap<_KEY, _VALUE>* map){
			content = map;
			current_bucket = 0;
			current_position = 0;
			this->offset = 0;
			for(std::size_t i=current_bucket; i< content->bucket_count; ++i) {
				HashMapEntry<_KEY, _VALUE>* currentBucket = content->buckets[i];
				if(currentBucket!=nullptr) {
					current_bucket = i;
					return;
				}
			}
		}

		HashMapIterator(std::size_t total){
			content = nullptr;
			current_bucket = 0;
			current_position = 0;
			this->offset = total;
		}

		~HashMapIterator() {}

		const std::pair<_KEY, _VALUE> operator*(){
			HashMapEntry<_KEY, _VALUE>* currentBucket = content->buckets[current_bucket];
			std::size_t j = 0;
			while(currentBucket!=nullptr) {
				if(j==current_position) {
					return std::make_pair(currentBucket->data.key, currentBucket->data.value);
				}
				currentBucket = currentBucket->next;
				++j;
			}
			throw std::out_of_range("Element not found!");
		}

		void operator++() {
			std::size_t j = 0;
			for(std::size_t i=current_bucket; i< content->bucket_count; ++i) {
				HashMapEntry<_KEY, _VALUE>* currentBucket = content->buckets[i];
				while(currentBucket!=nullptr) {
					if(i==current_bucket) {
						if(j>current_position) {
							++current_position;
							++this->offset;
							return;
						}
						++j;
					} else {
						current_bucket = i;
						current_position = 0;
						++this->offset;
						return;
					}
					currentBucket = currentBucket->next;
				}
			}
			// if this step is reached, then iterator reached end
			++this->offset;
			return;
		}

	private:
		HashMap<_KEY, _VALUE>* content;

		std::size_t current_bucket;
		std::size_t current_position;
};


#endif /* SRC_HASHMAP_H_ */
