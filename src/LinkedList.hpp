#pragma once
#include <ctype.h>

#include <functional>
#include <thread>  // We gon' thread this sort to kingdom come

// Research for implementing quicksearch:

// "choosing the middle index of the partition or (especially for longer
// partitions) choosing the median of the first, middle and last element of the
// partition for the pivot (as recommended by Sedgewick).[18] This
// "median-of-three" rule counters the case of sorted (or reverse-sorted) input,
// and gives a better estimate of the optimal pivot (the true median) than
// selecting any single element, when no information about the ordering of the
// input is known."

// Keeping all defintions in here for now because C++ is stupid about templates
// and translation units.
template <typename T>  // Because typedefs suck for this.
class LinkedList {
  public:
   using EleType = T;
   using ElePtr  = EleType *;
   using Index   = unsigned;
   LinkedList() {
      first = nullptr;
   }
   // LinkedList(init list) TODO
   ~LinkedList() {
      empty();  // Deletes all nodes AND sets first to nullptr anyway.
   }

   // Although exposing doOnNode would break encapsulation, it's still a pretty
   // nice function to have exposed, so expose it for data ops only.
   inline void doOn(Index index, std::function<void(EleType &)> func) {
      doOnNode(index, [&](Node *node) { func(node->data); });
   }

   const EleType &get(Index index) {
      EleType *node;
      doOn(index, [&](EleType &ele) { node = &ele; });
      return *node;
   }
   void set(Index index, EleType newEle) {
      doOn(index, [&](EleType &ele) { ele = newEle; });
   }

   Index size() const {
      return first->getChainLength(0);
   }

   void insert(EleType newEle, Index index) {
      if (first != nullptr)
         doOnNode(index - 1, [&](Node *node) {
            // Operating on the node before where we insert at,
            // so the newNode's next is the node directly after the position's
            // predeccessor.
            Node *newNode = new Node{newEle, node->next};
            node->next    = newNode;  // And finally re-link the chain.
         });
      else {
         first = new Node{newEle, nullptr};
      }
   }
   void insertSorted(T newEle) {
      // Wish we could still use doOn here, but we'll need
      // a good ol' for loop.
   }

   void erase(Index index) {
      if (index > 0)
         doOnNode(index - 1, [](Node *node) {
            Node *oldNode = node->next;
            // Remove from the middle of the chain
            node->next = node->next->next;

            // Now that it's safely outside the chain. delete it
            delete oldNode;
         });
      else {
         delete first;
         first = nullptr;  // As always, pesky VS.
      }
   }
   inline void empty() {
      if (first) {
         first->chainDelete();
         first = nullptr;  // Because VS is still stupid, apparently.
      }
   }

   // The real moneymaker.
   void quickSort() {
      unsigned length = size();
      // TODO: TODO: Actually learn the QS algorithm.
      // My understanding of the algorithm:
      // 1. Break the array into 2 partitions (+pivot), 1 full of elements
      //    greater than the pivot and 1 less than.
      // 2. Call this algorithm on each of those partitions until left with a
      //    base case.
   }

   void display(std::ostream &out, std::string delim = " ") {
      Node *ptr = first;
      while (ptr) {
         out << ptr->data << delim;
         ptr = ptr->next;
      }
   }

  private:
   struct Node {
      EleType data;
      Node *  next;

      // Goes to the end of the list, tells that one to delete itself,
      // Then goes back down the chain to the first node, deleting all along the
      // way. (Including first).
      void chainDelete() {
         if (next != nullptr)
            next->chainDelete();
         delete this;
      }
      // Goes all the way to the end of the chain, adding 1 for each link
      // Implemented like this for QS.
      unsigned getChainLength(unsigned curLength) {
         if (next)
            return 1 + next->getChainLength(curLength);
         else
            return 1;
      }
   };

   // firstLink => The beginning of "our" array, since this may be called from
   // other threads and we don't want multiple threads accessing the same stuff.
   // lastLink => Index (relative to firstLink) of the last link we use.
   //
   // Pseudocode for the general QS algorithm from here:
   // https://www.geeksforgeeks.org/quick-sort/
   static void realQuickSort(Node *nodeList[], Index last) {
      if (nodeList[0]->data < nodeList[last]->data) {
         Index pivot = partition(nodeList, last);
         realQuickSort(nodeList, pivot - 1);
         realQuickSort(nodeList + (pivot + 1), last);
      }
   }

   static Index partition(Node *nodeList[], Index last) {
      Node *pivotNode = nodeList[last];

      Index i, j = 0;
      while (j <= last - 1) {
      }
   }

   void rebuildLinks(Node *nodeList[], unsigned numLinks) {
   }

   // Since we have to do the same traversal each time in all the other funcs,
   // why not just make a more abstract function?
   // TODO: Inline and take the memory hit or leave as is and take an invoke
   // hit?
   void doOnNode(Index index, std::function<void(Node *)> func) {
      Node *ptr = first;
      Index cur = 0;
      while (ptr != nullptr && cur != index) {
         ptr = ptr->next;
         cur++;
      }
      // cur == index AND ptr is now the element we want to operate on, so...
      func(ptr);
   }

   Node *first;  ///< First link in the chain.
};
