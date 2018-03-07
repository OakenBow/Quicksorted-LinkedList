#include <LinkedList.hpp>

#include <cassert>
#include <iostream>
#include <sstream>


using namespace std;
template class LinkedList<int>;

void testConstructor() {
   cout << "Testing constructor...";
   LinkedList<int> ll;
   stringstream    ss;
   ll.display(ss, " ");
   assert(ss.str() == "");
   assert(ll.size() == 0);

   cout << "PASSED. \n" << flush;
}

void testInsert() {
   cout << "Testing insert...";
   LinkedList<int> llInt;
   for (int i = 0; i < 10; i++)
      llInt.insert(i, i);
   assert(llInt.size() == 10);
   cout << "PASSED! \n" << flush;
}

void testDisplay() {
   cout << "Testing display...";
   LinkedList<int> llInt;
   stringstream    ss;
   for (int i = 0; i < 10; i++)
      llInt.insert(i, i);
   llInt.display(ss, " ");

   // Note: display adds a trailing space.
   assert(ss.str() == "0 1 2 3 4 5 6 7 8 9 ");
   cout << "PASSED!\n" << flush;
}

void testGet() {
   cout << "Testing get...";
   LinkedList<int> llInt;
   for (int i = 0; i < 10; i++)
      llInt.insert(i, i);

   assert(llInt.get(5) == 5);
   cout << "PASSED!\n" << flush;
}

int main() {
   testConstructor();
   testInsert();
   testDisplay();
   testGet();
   return 0;
}
