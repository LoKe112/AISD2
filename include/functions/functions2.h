#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <random>
#include <exception>
#include <filesystem>

using namespace std;

template <typename T>
struct Node {
    T data;          // ������ ����
    Node<T>* prev;   // ��������� �� ���������� ����
    Node<T>* next;   // ��������� �� ��������� ����
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;   // ��������� �� ������ ������
    Node<T>* tail;   // ��������� �� ����� ������
public:
    // ����������� �� ���������
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ����������� �����������
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
        if (other.head == nullptr) {
            return;
        }

        Node<T>* otherCurrent = other.head;
        Node<T>* newCurrent = new Node<T>();
        newCurrent->data = otherCurrent->data;
        newCurrent->prev = nullptr;
        head = newCurrent;

        otherCurrent = otherCurrent->next;

        while (otherCurrent != other.head) {
            Node<T>* newNode = new Node<T>();
            newNode->data = otherCurrent->data;
            newNode->prev = newCurrent;
            newCurrent->next = newNode;

            newCurrent = newNode;
            otherCurrent = otherCurrent->next;
        }

        newCurrent->next = head;
        head->prev = newCurrent;
        tail = newCurrent;
    }

    // ����������
    ~DoublyLinkedList() {
        if (head == nullptr) {
            return;
        }

        Node<T>* current = head->next;
        while (current != head) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }

        delete head;
    }

    // �������� ������������
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) {
            return *this;
        }

        // ������� ������� ������
        if (head != nullptr) {
            Node<T>* current = head->next;
            while (current != head) {
                Node<T>* next = current->next;
                delete current;
                current = next;
            }

            delete head;
        }

        head = nullptr;
        tail = nullptr;

        // �������� �������� �� ������� ������
        if (other.head == nullptr) {
            return *this;
        }

        Node<T>* otherCurrent = other.head;
        Node<T>* newCurrent = new Node<T>();
        newCurrent->data = otherCurrent->data;
        newCurrent->prev = nullptr;
        head = newCurrent;

        otherCurrent = otherCurrent->next;

        while (otherCurrent != other.head) {
            Node<T>* newNode = new Node<T>();
            newNode->data = otherCurrent->data;
            newNode->prev = newCurrent;
            newCurrent->next = newNode;

            newCurrent = newNode;
            otherCurrent = otherCurrent->next;
        }

        newCurrent->next = head;
        head->prev = newCurrent;
        tail = newCurrent;

        return *this;
    }
};