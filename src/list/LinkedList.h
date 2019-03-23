/*
 * LinkedList.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_LINKEDLIST_H_
#define LIST_LINKEDLIST_H_

template<typename T>
struct LinkedListEntry {
	T value;
	LinkedListEntry* next;
};

template<typename T>
class LinkedListComparator {
public:
	LinkedListComparator(bool (*function)(const T&,const T&)) {
		compareFunction = function;
	}

	bool operator()(LinkedListEntry<T>*& left, LinkedListEntry<T>*& right) const {
		return compareFunction(left->value, right->value);
	}
private:
	bool (*compareFunction)(const T&,const T&);
};

#include "List.h"
#include <stdexcept>
#include "LinkedListSorter.h"
#include "../Comparator.h"

template<typename T>
class LinkedListIterator;

template<typename T, int (*comparator)(const T&, const T&)=comparator<T>>
class LinkedList: public List<T> {
	friend class LinkedListIterator<T>;
	public:
		typedef LinkedListIterator<T> iterator;

		LinkedList() {
			head = nullptr;
			tail = nullptr;
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
			internalIteratorStart = nullptr;
			internalIteratorEnd = nullptr;
		}

		~LinkedList() {
			empty();
		}

		const T& operator[](const size_t& index) const {
			traverse(index);

			return currentItem->value;
		}

		void clear() {
			empty();

			internalIteratorStart = nullptr;
			internalIteratorEnd = nullptr;
			head = nullptr;
			tail = nullptr;
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
		}

		void addToTop(const T& value) {
			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;

			// add element
			LinkedListEntry<T>* element = new LinkedListEntry<T>;
			element->value = value;
			element->next = head;
			head = element;
			if(tail==nullptr) tail = head;

			// increment counter
			++ count;
		}

		void addToBottom(const T& value) {
			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;

			// add element
			LinkedListEntry<T>* newNode = new LinkedListEntry<T>;
			newNode->value = value;
			newNode->next = nullptr;
			if(count==0) {
				head = newNode;
				tail = head;
			} else {
				tail->next = newNode;
				tail = newNode;
			}

			// increment counter
			++ count;
		}

		const T& get(const size_t& index) const {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			traverse(index);

			return currentItem->value;
		}

		void set(const size_t& index, const T& value) {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			traverse(index);

			currentItem->value = value;
		}

		void emplace(const size_t& index, const T& value) {
			if(index>count) throw std::out_of_range("Index cannot exceed list length!");

			if(index==0) {
				addToTop(value);

				currentIndex = 0;
				currentItem = head;
			} else if(index==count) {
				addToBottom(value);

				currentIndex = index;
				currentItem = tail;
			} else {
				std::size_t i = 0;
				LinkedListEntry<T>* temp = head;
				if(currentItem!=nullptr && index>currentIndex) {
					i = currentIndex;
					temp = currentItem;
				}
				while(temp!=nullptr) {
					if((i+1)==index) {
						LinkedListEntry<T>* newNode = new LinkedListEntry<T>;
						newNode->value = value;
						newNode->next = temp->next;

						temp->next = newNode;

						currentIndex = index;
						currentItem = newNode;

						++ count;
						return;
					}
					temp = temp->next;
					++i;
				}
			}
		}

		bool isEmpty() const {
			return count==0;
		}

		const std::size_t& size() const {
			return count;
		}

		bool containsIndex(const size_t& index) const {
			return (index>=count?false:true);
		}

		bool containsValue(const T& value) const {
			LinkedListEntry<T>* temp = head;
			while(temp!=nullptr) {
				if(comparator(temp->value, value)==0) {
					return true;
				}
				temp = temp->next;
			}
			return false;
		}

		void removeIndex(const size_t& index) {
			if(index>=count) throw std::out_of_range("Index must already exist!");

			if(index==0) {
				deleteHead();
			} else {
				traverse(index-1);
				deleteNextItem();
			}
		}

		void removeValue(const T& value) {
			if(count==0) return;

			std::size_t oldCount = count;
			LinkedListEntry<T>* temp = head;
			std::size_t position = 0;
			while(temp!=nullptr) {
				if(temp == head) {
					if(comparator(temp->value, value)==0) {
						deleteHead();
						temp = head;
					}
				} else {
					if(temp->next!=nullptr) {
						if(comparator(temp->next->value, value)==0) {
							currentIndex = position;
							currentItem = temp;
							deleteNextItem();
							temp = currentItem;
						}
					}
				}


				temp = temp->next;
				++ position;
			}

			if(oldCount == count) throw std::out_of_range("Value not found!");
		}

		void sort(bool (*compare) (const T&, const T&)) {
			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;
			// sort
			LinkedListComparator<T> comparison(compare);
			LinkedListSorter<LinkedListEntry<T>, LinkedListComparator<T>> dlls(&head, &tail, comparison);
		}

		ListIterator<T>* begin() {
			if(internalIteratorStart!=nullptr) {
				delete internalIteratorStart;
				internalIteratorStart = nullptr;
				delete internalIteratorEnd;
				internalIteratorEnd = nullptr;
			}
			internalIteratorStart = new iterator(this);
			return internalIteratorStart;
		}

		ListIterator<T>* end() {
			if(internalIteratorEnd!=nullptr){
				return internalIteratorEnd;
			} else {
				internalIteratorEnd = new iterator(count);
				return internalIteratorEnd;
			}
		}
	private:

		void deleteHead() {
			LinkedListEntry<T>* temp = head->next;
			delete head;
			head = temp;
			if(temp==nullptr) tail = nullptr;
			currentIndex = 0;
			currentItem = temp;
			-- count;
		}

		void deleteNextItem() {
			LinkedListEntry<T>* nextItem = currentItem->next;
			currentItem->next = nextItem->next;

			if(nextItem==tail) tail = currentItem;

			delete nextItem;

			-- count;
		}

		void traverse(const size_t& index) const {
			std::size_t i = 0;
			LinkedListEntry<T>* temp = head;
			if(currentItem!=nullptr && index>=currentIndex) {
				i = currentIndex;
				temp = currentItem;
			}
			while(temp!=nullptr) {
				if(i==index) {
					currentIndex = index;
					currentItem = temp;
					return;
				}
				temp = temp->next;
				++i;
			}
		}

		void empty(){
			// delete iterators
			if(internalIteratorStart!=nullptr) {
				delete internalIteratorStart;
				delete internalIteratorEnd;
			}

			// delete entries in LL
			LinkedListEntry<T>* temp = head;
			LinkedListEntry<T>* del = temp;
			while(del != nullptr) {
				temp = temp->next;
				delete del;
				del = temp;
			}
		}

		LinkedListEntry<T>* head;
		LinkedListEntry<T>* tail;
		std::size_t count;

		// for fast get/set iteration
		mutable std::size_t currentIndex;
		mutable LinkedListEntry<T>* currentItem;
		ListIterator<T>* internalIteratorStart;
		ListIterator<T>* internalIteratorEnd;
};

template<typename T>
class LinkedListIterator : public ListIterator<T>{
	public:
		LinkedListIterator(LinkedList<T>* list){
			content = list;
			current_item = list->head;
			this->offset = 0;
			this->total = list->count;
		}

		LinkedListIterator(std::size_t total){
			content = nullptr;
			current_item = nullptr;
			this->offset = total;
			this->total = total;
		}

		~LinkedListIterator(){}

		const T& operator*(){
			return current_item->value;
		}

		void operator++(){
			if(content->count!=this->total) {
				this->offset = this->total;
			} else {
				if(current_item!=nullptr) {
					current_item = current_item->next;
				}
				++this->offset;
			}
		}

	private:
		LinkedList<T>* content;
		LinkedListEntry<T>* current_item;
		std::size_t total;
};


#endif /* LIST_LINKEDLIST_H_ */
