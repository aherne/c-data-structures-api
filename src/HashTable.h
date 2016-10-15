/*
 * HashTable.h
 *
 *  Created on: Aug 20, 2016
 *      Author: aherne
 */

#ifndef SRC_HASHTABLE_H_
#define SRC_HASHTABLE_H_

template<typename VALUE>
struct HashTableEntry {
	std::size_t hash;
	VALUE data;
	HashTableEntry<VALUE>* next;
};

template<typename VALUE, int (*compare)(const VALUE&,const VALUE&), std::size_t (*hashingFunc)(const VALUE&)>
class HashTable {
public:
	HashTable(){
		count=0;
		bucket_count=8;
		buckets = new HashTableEntry<VALUE>*[bucket_count]();
	}

	HashTable(const std::size_t& reservedSize){
		count=0;
		bucket_count=reservedSize;
		buckets = new HashTableEntry<VALUE>*[bucket_count]();
	}

	~HashTable(){
		emptyBuckets();
	}

	void clear(){
		emptyBuckets();

		count=0;
		bucket_count=8;
		buckets = new HashTableEntry<VALUE>*[bucket_count]();
	}

	bool contains(const VALUE& value) const{
		if(count==0) return false;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);

		HashTableEntry<VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && compare(currentBucket->data,value)==0) {
				return true;
			}
			currentBucket = currentBucket->next;
		}
		return false;
	}

	bool contains(const VALUE& value, int (*customCompare)(const VALUE&,const VALUE&)) const{
		if(count==0) return false;
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashTableEntry<VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				if(customCompare(currentBucket->data, value)==0) {
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

	const VALUE* get(const VALUE& value) const {
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);

		HashTableEntry<VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && compare(currentBucket->data,value)==0) {
				return &(currentBucket->data);
			}
			currentBucket = currentBucket->next;
		}
		throw std::out_of_range("Key not found!");
	}

	void set(const VALUE& value){
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);
		HashTableEntry<VALUE>* currentBucket = buckets[bucketNumber];
		if(currentBucket!=nullptr) {
			// there are rows already, so loop until end
			while(currentBucket!=nullptr) {
				if(currentBucket->hash == hashValue && compare(currentBucket->data,value)==0) {
					// update
					currentBucket->data = value;
					return;
				}
				if(currentBucket->next == nullptr) {
					// append to end
					HashTableEntry<VALUE>* be = new HashTableEntry<VALUE>;
					be->hash = hashValue;
					be->data = value;
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
			HashTableEntry<VALUE>* be = new HashTableEntry<VALUE>;
			be->hash = hashValue;
			be->data = value;
			be->next = nullptr;

			buckets[bucketNumber] = be;

			++ count;
			if(count == bucket_count) {
				rehash();
			}
			return;
		}
	}

	void remove(const VALUE& value){
		if(count==0) return;
		std::size_t oldCount = count;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);
		buckets[bucketNumber] = recursiveDelete(buckets[bucketNumber], value, compare);
		if(oldCount == count) throw std::out_of_range("Key not found!");
	}

	void remove(const VALUE& value, int (*customCompare)(const VALUE&,const VALUE&)) {
		if(count==0) return;
		std::size_t oldCount = count;
		for(std::size_t i=0; i<bucket_count; ++i) {
			buckets[i] = recursiveDelete(buckets[i], value, customCompare);
		}
		if(oldCount == count) throw std::out_of_range("Value not found!");
	}

	// iterator stuff
	std::size_t getMinBucket() const {
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashTableEntry<VALUE>* currentBucket = buckets[i];
			if(currentBucket!=nullptr) {
				return i;
			}
		}
		return 0;
	}

	HashTableEntry<VALUE>* getCurrentNode(const std::size_t& bucket_number, const std::size_t& position) const {
		HashTableEntry<VALUE>* currentBucket = buckets[bucket_number];
		std::size_t j = 0;
		while(currentBucket!=nullptr) {
			if(j==position) {
				return currentBucket;
			}
			currentBucket = currentBucket->next;
			++j;
		}
		return nullptr;
	}

	void nextNode(std::size_t& bucket_number, std::size_t& position) {
		std::size_t j = 0;
		for(std::size_t i=bucket_number; i< bucket_count; ++i) {
			HashTableEntry<VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				if(i==bucket_number) {
					if(j>position) {
						++position;
						return;
					}
					++j;
				} else {
					bucket_number = i;
					position = 0;
					return;
				}
				currentBucket = currentBucket->next;
			}
		}
	}
private:

	int getBucketNumber(std::size_t hash) const {
		return hash % bucket_count;
	}

	HashTableEntry<VALUE>* recursiveDelete(HashTableEntry<VALUE>* currentBucket, const VALUE& value, int (*comparator)(const VALUE&,const VALUE&)) {
		if (currentBucket == nullptr)
			return nullptr;

		if (comparator(currentBucket->data, value)==0) {
			HashTableEntry<VALUE>* tempNextP;
			tempNextP = currentBucket->next;
			delete currentBucket;
			-- count;
			return tempNextP;
		}
		currentBucket->next = recursiveDelete(currentBucket->next, value, comparator);
		return currentBucket;
	}

	void emptyBuckets() {
		for(std::size_t i=0; i< bucket_count; ++i) {
			HashTableEntry<VALUE>* head = buckets[i];
			HashTableEntry<VALUE>* del = head;
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

		HashTableEntry<VALUE>** new_buckets = new HashTableEntry<VALUE>*[new_bucket_count]();

		for(std::size_t i=0; i< bucket_count; ++i) {
			HashTableEntry<VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				int bucket_number = currentBucket->hash % new_bucket_count;

	            // advance n *before* moving node to new hash bed
				HashTableEntry<VALUE>* tmp = currentBucket;
	            currentBucket = currentBucket->next;

	            // find the proper collision list pointer.
	            HashTableEntry<VALUE>*& bucket = new_buckets[bucket_number];
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
	HashTableEntry<VALUE> **buckets;
};



#endif /* SRC_HASHTABLE_H_ */
