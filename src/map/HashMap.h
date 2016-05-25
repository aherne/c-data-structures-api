/*
 * HashMap.h
 *
 *  Created on: Mar 17, 2016
 *      Author: lucian
 */

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include <vector>
#include <utility>
#include "Map.h"
#include "HashMapEntry.h"
#include "../Hashing.h"
#include "../Comparator.h"

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
	}

	~HashMap(){
		emptyBuckets();
	}

	HashMapIterator<_KEY,_VALUE> begin(){
		 return iterator(this);
	}

	HashMapIterator<_KEY,_VALUE> end(){
		return iterator(this, count );
	}

	void clear(){
		emptyBuckets();

		count=0;
		bucket_count=8;
		buckets = new HashMapEntry<_KEY, _VALUE>*[bucket_count]();
	}

	bool containsKey(const _KEY& key){
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

	bool containsValue(const _VALUE& value) {
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

	bool isEmpty() {
		return (count==0?true:false);
	}

	std::size_t size() {
		return count;
	}
	std::vector<_KEY> getKeys() {
		std::vector<_KEY> output;
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				output.push_back(currentBucket->data.key);
				currentBucket = currentBucket->next;
			}
		}
		return output;
	}
	std::vector<_VALUE> getValues(){
		std::vector<_VALUE> output;
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				output.push_back(currentBucket->data.value);
				currentBucket = currentBucket->next;
			}
		}
		return output;
	}

	_VALUE& get(const _KEY& key) {
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);

		HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
				return currentBucket->data.value;
			}
			currentBucket = currentBucket->next;
		}
		throw std::out_of_range("Value not found!");
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
		std::size_t hashValue = hashingFunc(key);
		int bucketNumber = getBucketNumber(hashValue);
		HashMapEntry<_KEY, _VALUE>* currentBucket = buckets[bucketNumber];
		HashMapEntry<_KEY, _VALUE>* previousBucket = nullptr;
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && keyComparator(currentBucket->data.key,key)==0) {
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

	void removeValue(const _VALUE& value) {
		if(count==0) return;
		std::size_t oldCount = count;
		for(std::size_t i=0; i<bucket_count; ++i) {
			buckets[i] = recursiveDeleteValue(buckets[i], value);
		}
		if(oldCount == count) throw std::out_of_range("Value not found!");
	}

private:
	int getBucketNumber(std::size_t hash) {
		return hash % bucket_count;
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
class HashMapIterator {
	public:
		HashMapIterator(){
			content = nullptr;
			current_bucket = 0;
			current_position = 0;
			offset = 0;
		}

		HashMapIterator(HashMap<_KEY, _VALUE>* map){
			content = map;
			current_bucket = 0;
			current_position = 0;
			offset = 0;
			for(std::size_t i=current_bucket; i< content->bucket_count; ++i) {
				HashMapEntry<_KEY, _VALUE>* currentBucket = content->buckets[i];
				if(currentBucket!=nullptr) {
					current_bucket = i;
					return;
				}
			}
		}

		HashMapIterator(HashMap<_KEY, _VALUE>* map, std::size_t total){
			content = map;
			current_bucket = 0;
			current_position = 0;
			offset = total;
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

		bool operator!=(const HashMapIterator<_KEY,_VALUE>& it) {
			return offset!=it.offset;
		}

		void operator++() {
			std::size_t j = 0;
			for(std::size_t i=current_bucket; i< content->bucket_count; ++i) {
				HashMapEntry<_KEY, _VALUE>* currentBucket = content->buckets[i];
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
		HashMap<_KEY, _VALUE>* content;

		std::size_t current_bucket;
		std::size_t current_position;
};


#endif /* SRC_HASHMAP_H_ */
