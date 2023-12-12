#include <chrono>
#include <iostream>
#include <\AISD2\include\functions\functions2.h>
#include <thread>

using namespace linked_list;
using namespace std;

int GetWolframState(int rule, int code) { return (rule >> code) & 0b00000001; }

template <class T>
int GetCode(Node<T>* elem) {
    int res = 0;
    res += int(elem->GetNext()->GetValue() * pow(2, 0));
    res += int(elem->GetValue() * pow(2, 1));
    res += int(elem->GetPrev()->GetValue() * pow(2, 2));
    return res;
}

template <class T>
void PrintList(LinkedList<T> const& list) {
    for (int i = 0; i < list.GetSize(); ++i) {
        cout << list[i].GetValue()<<" ";
    }
    cout << endl ;
}

template <class T>
LinkedList<T> GetNextState(LinkedList<T> const& list, int rule) {
    LinkedList<T> res;
    Node<T>* ptr = list.GetHead();
    for (int i = 0; i < list.GetSize(); ++i) {
        int value = GetCode(ptr);
        value = GetWolframState(rule, value);
        Node<T> elem(value);
        res.PushTail(elem);
        ptr = ptr->GetNext();
    }
    return res;
}

int GetSize() {

    int size = 0;
    while (true) {
        cout << "Enter a size of linked-list. Values will be generated randomly."
            << endl
            << "Size: ";

        cin >> size;
        if (size < 3) {

            cout << "ERROR. To calculate a Wolfram code size of list must be at "
                "least 3. "
                << endl;
            ;
        }
        else
            break;
    }
    return size;
}

int GetWolframCode() {
    int code = 0;
    while (true) {
        cout << "Enter a Wolfram code"
            << endl
            << "Code: ";

        cin >> code;
        if (code > 255 || code < 0) {
            cout << "ERROR. Wolfram code must be between 0 and 255" << endl;
            ;
        }
        else
            break;
    }
    return code;
}

int GetCount() {
    int count = 0;
    while (true) {
        cout << "Enter a count of calculated lists" << endl << "Count: ";

        cin >> count;
        if (count < 1) {
            cout << "ERROR. To calculate a Wolfram code size of list must be at "
                "least 1. ";
        }
        else
            break;
    }
    return count;
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
    a.PushHead(c);
    PrintList(a);

    return 0;
}