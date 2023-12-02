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
    T data;          // данные узла
    Node<T>* prev;   // указатель на предыдущий узел
    Node<T>* next;   // указатель на следующий узел
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;   // указатель на голову списка
    Node<T>* tail;   // указатель на конец списка
public:
    // Конструктор по умолчанию
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Конструктор копирования
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

    // Деструктор
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

    // Оператор присваивания
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) {
            return *this;
        }

        // Очищаем текущий список
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

        // Копируем элементы из другого списка
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