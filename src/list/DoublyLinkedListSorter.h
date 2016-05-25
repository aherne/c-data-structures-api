/*
 * Sorter.h
 *
 *  Created on: May 14, 2016
 *      Author: aherne
 */

#ifndef DOUBLYLINKEDLISTSORTER_H_
#define DOUBLYLINKEDLISTSORTER_H_

/**
 * Algorithm: Merge Sort
 * Source: http://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
 */
template<typename _NODE, typename _COMPARATOR>
class DoublyLinkedListSorter {
public:
	DoublyLinkedListSorter(_NODE** headRef, _COMPARATOR& comparator) {
		sort(headRef, comparator);
	}

	DoublyLinkedListSorter(_NODE** headRef, _NODE** tailRef, _COMPARATOR& comparator) {
		sort(headRef, comparator);
		*tailRef = getTail(*headRef);
	}
private:
	void sort(_NODE** headRef, _COMPARATOR& comparator) {
		_NODE* head = *headRef;

		/* Base case -- length 0 or 1 */
		if ((head == nullptr) || (head->next == nullptr)){
			return;
		}

	    _NODE* second = split(head);

	    // Recur for left and right halves
	    sort(&head, comparator);
	    sort(&second, comparator);

	    // Merge the two sorted halves
	    *headRef = merge(head,second,comparator);
	}

	// Split a doubly linked list (DLL) into 2 DLLs of half sizes
	_NODE* split(_NODE* head) {
	    _NODE* fast = head;
	    _NODE* slow = head;
	    while (fast->next && fast->next->next) {
	        fast = fast->next->next;
	        slow = slow->next;
	    }
	    _NODE* temp = slow->next;
	    slow->next = nullptr;
	    return temp;
	}

	// Function to merge two linked lists
	_NODE* merge(_NODE*& first, _NODE*& second, _COMPARATOR& comparator) {
	    // If first linked list is empty
	    if (!first)
	        return second;

	    // If second linked list is empty
	    if (!second)
	        return first;

	    // Pick the smaller value
	    if (comparator(first, second)==true) {
	        first->next = merge(first->next,second,comparator);
	        first->next->previous = first;
	        first->previous = nullptr;
	        return first;
	    } else {
	        second->next = merge(first,second->next,comparator);
	        second->next->previous = second;
	        second->previous = nullptr;
	        return second;
	    }
	}

	_NODE* getTail(_NODE* head) {
		_NODE* tmp = head;
		while(tmp!=nullptr) {
			if(tmp->next==nullptr) {
				return tmp;
			}
			tmp = tmp->next;
		}
		return nullptr;
	}
};
#endif /* DOUBLYLINKEDLISTSORTER_H_ */
