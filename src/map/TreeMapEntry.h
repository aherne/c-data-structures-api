/*
 * TreeMapEntry.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef MAP_TREEMAPENTRY_H_
#define MAP_TREEMAPENTRY_H_
  // Red-black tree class, designed for use in implementing STL
  // associative containers (set, multiset, map, and multimap). The
  // insertion and deletion algorithms are based on those in Cormen,
  // Leiserson, and Rivest, Introduction to Algorithms (MIT Press,
  // 1990), except that
  //
  // (1) the header cell is maintained with links not only to the root
  // but also to the leftmost node of the tree, to enable constant
  // time begin(), and to the rightmost node of the tree, to enable
  // linear time performance when used with the generic set algorithms
  // (set_union, etc.)
  //
  // (2) when a node being deleted has two children its successor node
  // is relinked into its place, rather than copied, so that the only
  // iterators invalidated are those referring to the deleted node.

#include "MapEntry.h"

template <typename _KEY, typename _VALUE>
struct TreeMapEntry {
	MapEntry<_KEY,_VALUE> data;
	enum color {red, black};
	TreeMapEntry<_KEY, _VALUE>* parent;
	TreeMapEntry<_KEY, _VALUE>* left;
	TreeMapEntry<_KEY, _VALUE>* right;
};

#endif /* MAP_TREEMAPENTRY_H_ */
