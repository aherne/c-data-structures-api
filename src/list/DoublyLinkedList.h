/*
 * DoublyLinkedList.h
 *
 *  Created on: May 3, 2016
 *      Author: aherne
 */

#ifndef LIST_DOUBLYLINKEDLIST_H_
#define LIST_DOUBLYLINKEDLIST_H_

#include "DoublyLinkedListSorter.h"
#include <iostream>

template<typename T>
struct DoublyLinkedListEntry {
	T value;
	DoublyLinkedListEntry* next;
	DoublyLinkedListEntry* previous;
};

template<typename T>
class DoublyLinkedListComparator {
public:
	DoublyLinkedListComparator(bool (*function)(const T&,const T&)) {
		compareFunction = function;
	}

	bool operator()(DoublyLinkedListEntry<T>*& left, DoublyLinkedListEntry<T>*& right) const {
		return compareFunction(left->value, right->value);
	}
private:
	bool (*compareFunction)(const T&,const T&);
};

template<typename T>
class DoublyLinkedListIterator;

template<typename T>
class DoublyLinkedList: public List<T> {
	friend class DoublyLinkedListIterator<T>;
	public:
		typedef DoublyLinkedListIterator<T> iterator;

		DoublyLinkedList() {
			head = nullptr;
			tail = nullptr;
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
			internalIteratorStart = nullptr;
			internalIteratorEnd = nullptr;
		}

		~DoublyLinkedList() {
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
			currentItem = nullptr;
			currentIndex = 0;
			count = 0;
		}

		void addToTop(const T& value) {
			DoublyLinkedListEntry<T>* newNode = new DoublyLinkedListEntry<T>;
			newNode->value = value;
			newNode->next = head;
			newNode->previous = nullptr;
			if(head!=nullptr) {
				head->previous = newNode;
			}
			head = newNode;
			if(tail==nullptr) {
				tail = head;
			}
			// reset internal counter
			currentIndex = 0;
			currentItem = head;
			++ count;
		}

		void addToBottom(const T& value) {
			DoublyLinkedListEntry<T>* element = new DoublyLinkedListEntry<T>;
			element->value = value;
			element->next = nullptr;
			element->previous = tail;
			if(head==nullptr) {
				head = element;
			} else {
				tail->next = element;
			}
			tail = element;
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

			// perform full traversal
			if(index==0) {
				addToTop(value);
			} else if(index==count) {
				addToBottom(value);
			} else {
				traverse(index-1);

				DoublyLinkedListEntry<T>* newNode = new DoublyLinkedListEntry<T>;
				newNode->value = value;
				newNode->previous = currentItem->previous;
				newNode->next = currentItem->next;
				newNode->next->previous = newNode;
				currentItem->next = newNode;

				currentIndex = index;
				currentItem = newNode;
				++ count;
			}
		}

		bool isEmpty() const {
			return count==0;
		}

		const std::size_t& size() const {
			return count;
		}

		bool containsIndex(const size_t& index) const  {
			return (index>=count?false:true);
		}

		bool containsValue(const T& value) const {
			DoublyLinkedListEntry<T>* temp = head;
			while(temp!=nullptr) {
				if(valueComparator(temp->value, value)==0) {
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
			} else if(index == (count-1)) {
				deleteTail();
			} else {
				traverse(index);
				deleteCurrentItem();
			}
		}

		void removeValue(const T& value) {
			if(count==0) return;

			std::size_t oldCount = count;
			DoublyLinkedListEntry<T>* temp = head;
			std::size_t position = 0;
			while(temp!=nullptr) {
				if(valueComparator(temp->value, value)==0) {
					if(temp == head) {
						deleteHead();
						temp = head;
					} else if(temp == tail) {
						deleteTail();
						temp = currentItem;
					} else {
						currentIndex = position;
						currentItem = temp;
						deleteCurrentItem();
						temp = currentItem;
					}
				}

				temp = temp->next;
				++ position;
			}

			if(oldCount == count) throw std::out_of_range("Value not found!");
		}

		void sort(bool (*comparator) (const T&, const T&)) {
			// reset internal iterator
			currentIndex = 0;
			currentItem = nullptr;
			// sort
			DoublyLinkedListComparator<T> comparison(comparator);
			DoublyLinkedListSorter<DoublyLinkedListEntry<T>, DoublyLinkedListComparator<T>> dlls(&head, &tail, comparison);
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
		void traverse(const std::size_t& index) const {
			if(index==currentIndex && currentItem!=nullptr) return;

			bool forwardTraversal = true;
			if(currentItem==nullptr) {
				if(index>(count/2)) forwardTraversal = false;
			} else {
				if(index>currentIndex) { // forward
					// calculate if it's closer to tail than current index
					if((count-index)<(index-currentIndex)) forwardTraversal = false;
				} else {				// backward
					// calculate if it's closer to current index than head
					if(index>(currentIndex-index)) forwardTraversal = false;
				}
			}

			if(!forwardTraversal) {
				// backward traversal
				std::size_t i = count-1;
				DoublyLinkedListEntry<T>* temp = tail;
				if(currentItem!=nullptr && index<=currentIndex) {
					i = currentIndex;
					temp = currentItem;
				}
				while(temp!=nullptr) {
					if(i==index) {
						currentIndex = i;
						currentItem = temp;
						return;
					}
					temp = temp->previous;
					--i;
				}
			} else {
				// forward traversal
				std::size_t i = 0;
				DoublyLinkedListEntry<T>* temp = head;
				if(currentItem!=nullptr && index>=currentIndex) {
					i = currentIndex;
					temp = currentItem;
				}
				while(temp!=nullptr) {
					if(i==index) {
						currentIndex = i;
						currentItem = temp;
						return;
					}
					temp = temp->next;
					++i;
				}
			}
		}

		void deleteHead() {
			DoublyLinkedListEntry<T>* temp = head->next;
			if(temp!=nullptr) temp->previous = nullptr;
			delete head;
			head = temp;
			currentIndex = 0;
			currentItem = temp;
			-- count;
			if(count==0) tail = nullptr;
		}

		void deleteTail() {
			DoublyLinkedListEntry<T>* temp = tail->previous;
			if(temp!=nullptr) temp->next = nullptr;
			delete tail;
			tail = temp;
			currentIndex = count-2;
			currentItem = temp;
			-- count;
		}

		void deleteCurrentItem() {
			/* Change next only if node to be deleted is NOT the last node */
			if(currentItem->next != NULL)
				currentItem->next->previous = currentItem->previous;

			/* Change prev only if node to be deleted is NOT the first node */
			if(currentItem->previous != NULL)
				currentItem->previous->next = currentItem->next;

			DoublyLinkedListEntry<T>* newCurrentItem = currentItem->previous;

			delete currentItem;

			-- count;

			-- currentIndex;
			currentItem = newCurrentItem;
		}

		void empty(){
			// delete iterators
			if(internalIteratorStart!=nullptr) {
				delete internalIteratorStart;
				delete internalIteratorEnd;
			}

			// delete entries in DLL
			DoublyLinkedListEntry<T>* temp = head;
			DoublyLinkedListEntry<T>* del = temp;
			while(del != nullptr) {
				temp = temp->next;
				delete del;
				del = temp;
			}
		}

		DoublyLinkedListEntry<T>* head;
		DoublyLinkedListEntry<T>* tail;
		std::size_t count;
		comparator<T> valueComparator;

		// for fast iteration
		mutable std::size_t currentIndex;
		mutable DoublyLinkedListEntry<T>* currentItem;
		ListIterator<T>* internalIteratorStart;
		ListIterator<T>* internalIteratorEnd;
};

template<typename T>
class DoublyLinkedListIterator : public ListIterator<T>{
	public:
		DoublyLinkedListIterator(DoublyLinkedList<T>* list){
			content = list;
			current_item = list->head;
			this->offset = 0;
			this->total = list->count;
		}

		DoublyLinkedListIterator(std::size_t total){
			content = nullptr;
			current_item = nullptr;
			this->offset = total;
			this->total = total;
		}

		~DoublyLinkedListIterator(){}

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
		DoublyLinkedList<T>* content;
		DoublyLinkedListEntry<T>* current_item;
		std::size_t total;
};

#endif /* LIST_DOUBLYLINKEDLIST_H_ */
