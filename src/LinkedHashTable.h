/*
 * LinkedLinkedHashTable.h
 *
 *  Created on: Aug 20, 2016
 *      Author: aherne
 */

#ifndef SRC_LINKEDHASHTABLE_H_
#define SRC_LINKEDHASHTABLE_H_


template<typename VALUE>
struct LinkedHashTableEntry {
	std::size_t hash;
	VALUE data;
	// singly linked list for traversal @ bucket
	LinkedHashTableEntry<VALUE>* nextInBucket;
	// doubly linked list for traversal in insertion order
	LinkedHashTableEntry<VALUE>* previous;
	LinkedHashTableEntry<VALUE>* next;
};

template<typename VALUE>
class LinkedHashTable {
public:
	LinkedHashTable(){
		count=0;
		bucket_count=8;
		buckets = new LinkedHashTableEntry<VALUE>*[bucket_count]();
		head = nullptr;
		tail = nullptr;
	}

	~LinkedHashTable(){
		emptyBuckets();
	}

	void clear(){
		emptyBuckets();

		head = nullptr;
		tail = nullptr;
		count=0;
		bucket_count=8;
		buckets = new LinkedHashTableEntry<VALUE>*[bucket_count]();
	}

	bool contains(const VALUE& value, int (*compare)(const VALUE&,const VALUE&), std::size_t (*hashingFunc)(const VALUE&)) const{
		if(count==0) return false;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);

		LinkedHashTableEntry<VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && compare(currentBucket->data,value)==0) {
				return true;
			}
			currentBucket = currentBucket->nextInBucket;
		}
		return false;
	}

	bool contains(const VALUE& value, int (*compare)(const VALUE&,const VALUE&)) const{
		if(count==0) return false;
		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashTableEntry<VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				if(compare(currentBucket->data, value)==0) {
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

	const std::size_t& size() const {
		return count;
	}

	const VALUE* get(const VALUE& value, int (*compare)(const VALUE&,const VALUE&), std::size_t (*hashingFunc)(const VALUE&)) const {
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);

		LinkedHashTableEntry<VALUE>* currentBucket = buckets[bucketNumber];
		while(currentBucket!=nullptr) {
			if(currentBucket->hash == hashValue && compare(currentBucket->data,value)==0) {
				return &(currentBucket->data);
			}
			currentBucket = currentBucket->nextInBucket;
		}
		throw std::out_of_range("Key not found!");
	}

	// FIXME
	void set(const VALUE& value, int (*compare)(const VALUE&,const VALUE&), std::size_t (*hashingFunc)(const VALUE&)){
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);
		LinkedHashTableEntry<VALUE>* currentBucket = buckets[bucketNumber];
		if(currentBucket!=nullptr) {
			while(currentBucket!=nullptr) {
				if(currentBucket->hash == hashValue && compare(currentBucket->data,value)==0) {
					// update
					currentBucket->data = value;
					return;
				}
				if(currentBucket->nextInBucket == nullptr) {
					LinkedHashTableEntry<VALUE>* be = createEntry(hashValue, value);
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
			LinkedHashTableEntry<VALUE>* be = createEntry(hashValue, value);
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

	void remove(const VALUE& value, int (*compare)(const VALUE&,const VALUE&), std::size_t (*hashingFunc)(const VALUE&)){
		if(count==0) return;
		std::size_t oldCount = count;
		std::size_t hashValue = hashingFunc(value);
		int bucketNumber = getBucketNumber(hashValue);
		buckets[bucketNumber] = recursiveDelete(buckets[bucketNumber], value, compare);
		if(oldCount == count) throw std::out_of_range("Key not found!");
	}

	void remove(const VALUE& value, int (*compare)(const VALUE&,const VALUE&)) {
		if(count==0) return;
		std::size_t oldCount = count;
		for(std::size_t i=0; i<bucket_count; ++i) {
			buckets[i] = recursiveDelete(buckets[i], value, compare);
		}
		if(oldCount == count) throw std::out_of_range("Value not found!");
	}

	// iterator & sort stuff
	LinkedHashTableEntry<VALUE>*& getHead() {
		return head;
	}

	LinkedHashTableEntry<VALUE>*& getTail() {
		return tail;
	}
private:

	LinkedHashTableEntry<VALUE>* createEntry(std::size_t hashValue, const VALUE& value) {
		LinkedHashTableEntry<VALUE>* be = new LinkedHashTableEntry<VALUE>;
		be->hash = hashValue;
		be->data = value;
		be->nextInBucket = nullptr;
		be->next = nullptr;
		be->previous = tail;
		return be;
	}

	int getBucketNumber(std::size_t hash) const {
		return hash % bucket_count;
	}

	LinkedHashTableEntry<VALUE>* recursiveDelete(LinkedHashTableEntry<VALUE>* currentBucket, const VALUE& value, int (*compare)(const VALUE&,const VALUE&)) {
		if (currentBucket == nullptr)
			return nullptr;

		if (compare(currentBucket->data, value)==0) {
			deleteFromDoublyLinkedList(currentBucket);
			LinkedHashTableEntry<VALUE>* tempNextP;
			tempNextP = currentBucket->nextInBucket;
			delete currentBucket;
			-- count;
			return tempNextP;
		}
		currentBucket->nextInBucket = recursiveDelete(currentBucket->nextInBucket, value, compare);
		return currentBucket;
	}

	void deleteFromDoublyLinkedList(LinkedHashTableEntry<VALUE>*& currentBucket) {
		if(currentBucket == head) {
			head = head->next;		// one step forward
		} else if(currentBucket == tail) {
			tail = tail->previous;	// one step backward
			tail->next = nullptr;
		} else {
			currentBucket->previous->next = currentBucket->next;
		}
	}

	void emptyBuckets() {
		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashTableEntry<VALUE>* head = buckets[i];
			LinkedHashTableEntry<VALUE>* del = head;
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

		LinkedHashTableEntry<VALUE>** new_buckets = new LinkedHashTableEntry<VALUE>*[new_bucket_count]();

		for(std::size_t i=0; i< bucket_count; ++i) {
			LinkedHashTableEntry<VALUE>* currentBucket = buckets[i];
			while(currentBucket!=nullptr) {
				int bucket_number = currentBucket->hash % new_bucket_count;

	            // advance n *before* moving node to new hash bed
				LinkedHashTableEntry<VALUE>* tmp = currentBucket;
	            currentBucket = currentBucket->nextInBucket;

	            // find the proper collision list pointer.
	            LinkedHashTableEntry<VALUE>*& bucket = new_buckets[bucket_number];
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
	LinkedHashTableEntry<VALUE> **buckets;

	// parameters needed by doubly linked list
	LinkedHashTableEntry<VALUE>* head;
	LinkedHashTableEntry<VALUE>* tail;
};



#endif /* SRC_LINKEDHASHTABLE_H_ */
