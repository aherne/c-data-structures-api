/*
 * LinkedListSorter.h
 *
 *  Created on: May 8, 2016
 *      Author: aherne
 */

#ifndef LIST_LINKEDLISTSORTER_H_
#define LIST_LINKEDLISTSORTER_H_


/**
 * Algorithm: Merge Sort
 * Source: http://www.geeksforgeeks.org/merge-sort-for-linked-list/
 */
template<typename _NODE, typename _COMPARATOR>
class LinkedListSorter {
public:
	LinkedListSorter(_NODE** headRef, _NODE** tailRef, _COMPARATOR& comparator) {
		sort(headRef, comparator);
		*tailRef = getTail(*headRef);
	}
private:
	void sort(_NODE** headRef, _COMPARATOR& comparator) {
		_NODE* head = *headRef;
		_NODE* a;
		_NODE* b;

		/* Base case -- length 0 or 1 */
		if ((head == nullptr) || (head->next == nullptr)){
			return;
		}

		/* Split head into 'a' and 'b' sublists */
		split(head, &a, &b);

		/* Recursively sort the sublists */
		sort(&a, comparator);
		sort(&b, comparator);

		/* answer = merge the two sorted lists together */
		*headRef = merge(a, b, comparator);
	}

	_NODE* merge(_NODE*& a, _NODE*& b, _COMPARATOR& comparator) {
		_NODE* result = nullptr;

		/* Base cases */
		if (a == nullptr)
			 return(b);
		else if (b==nullptr)
			 return(a);

		/* Pick either a or b, and recur */
		if (comparator(a, b)==true) {
			 result = a;
			 result->next = merge(a->next, b, comparator);
		} else {
			 result = b;
			 result->next = merge(a, b->next, comparator);
		}
		return(result);
	}

	void split(_NODE*& source, _NODE** frontRef, _NODE** backRef) {
		_NODE* fast;
		_NODE* slow;
		if (source==nullptr || source->next==nullptr){
			/* length < 2 cases */
			*frontRef = source;
			*backRef = nullptr;
		} else {
			slow = source;
			fast = source->next;

			/* Advance 'fast' two nodes, and advance 'slow' one node */
			while (fast != nullptr) {
				fast = fast->next;
				if (fast != nullptr) {
					slow = slow->next;
					fast = fast->next;
				}
			}

			/* 'slow' is before the midpoint in the list, so split it in two at that point. */
			*frontRef = source;
			*backRef = slow->next;
			slow->next = nullptr;
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



#endif /* LIST_LINKEDLISTSORTER_H_ */
