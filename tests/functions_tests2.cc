#include <chrono>
#include <iostream>
#include <\AISD2\include\functions\functions2.h>
#include <thread>

using namespace linked_list;
using namespace std;

template <class T>
void PrintList(LinkedList<T> const& list) {
    for (int i = 0; i < list.GetSize(); ++i) {
        cout << list[i].GetValue()<<" ";
    }
    cout << endl ;
}


int main() {
    LinkedList<int> a = LinkedList<int>(3,5);

    PrintList(a);

    Node<int> b = Node<int>(4);
    a.PushTail(b);
    PrintList(a);

    a.PushHead(b);
    PrintList(a);

    a.PopHead();
    PrintList(a);

    a.PopTail();
    PrintList(a);

    LinkedList<int> c = LinkedList<int>(3);
    a.PushTail(c);
    PrintList(a);
    
    ReverseLinkedList(a);
    PrintList(a);



    return 0;
}