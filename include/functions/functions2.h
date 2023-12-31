#pragma once
#include <time.h>
#include <random>
#include <stdexcept>

using namespace std;

namespace linked_list {


    
    template <typename T>
    class LinkedList;
    template <typename T>
    class Node {
        friend LinkedList<T>;
        Node<T>* prev_;
        Node<T>* next_;
        T value_;

    public:
        Node();
        Node(Node<T>* prev, Node* next, T const& value);
        Node(Node<T>* prev, Node* next);
        Node(T const& value);
        Node(Node<T> const& other);
        ~Node() = default;       
        T GetValue() const;   
        Node<T>* GetPrev() const;
        Node<T>* GetNext() const;
        void SetPrev(Node <T>*);
        void SetNext(Node <T>*);
    };

    template <typename T>
    Node<T>::Node(T const& value) {
        this->prev_ = nullptr;
        this->next_ = nullptr;
        this->value_ = value;
    }

    template <typename T>
    Node<T>::Node() {
        this->prev_ = nullptr;
        this->next_ = nullptr;
        this->value_ = T(0);
    }

    template <typename T>
    Node<T>::Node(Node<T>* prev, Node* next, T const& value) {
        this->prev_ = prev;
        this->next_ = next;
        this->value_ = value;
    }

    template <typename T>
    Node<T>::Node(Node<T>* prev, Node* next) {
        this->prev_ = prev;
        this->next_ = next;
    }


    template <typename T>
    Node<T>::Node(Node<T> const& other) {
        this->prev_ = other.prev_;
        this->next_ = other.next_;
        this->value_ = other.value_;

    }

    template <typename T>
    T Node<T>::GetValue() const {
        return this->value_;
    }

    template <typename T>
    Node<T>* Node<T>::GetNext() const {
        return this->next_;
    }

    template <typename T>
    Node<T>* Node<T>::GetPrev() const {
        return this->prev_;
    }

    template<typename T>
    void Node<T>::SetPrev(Node<T>* other)
    {
        this->prev_ = other;
    }

    template<typename T>
    void Node<T>::SetNext(Node<T>* other)
    {
        this->next_ = other;
    }

template <typename T>
class LinkedList {
    Node<T>* head_;
    int size_;

public:
    int GetSize() const;
    LinkedList();
    LinkedList(int size, T const& value);
    LinkedList(int size);  
    LinkedList(LinkedList<T> const& other);
    void Swap(LinkedList<T>& other);
    LinkedList<T>& operator=(LinkedList<T> const& other);
    ~LinkedList();
    void PushTail(Node<T> const& node);
    void PushTail(LinkedList<T> const& other);
    void PushHead(Node<T> const& node);
    void PushHead(LinkedList<T> const& other);
    void PopHead();
    void PopTail();
    void DeleteNode(T const& value);
    Node<T>& operator[](int index);
    Node<T> operator[](int index) const;
    Node<T>* GetHead() const;
    void SetHead(Node<T>* other);
};

template <typename T>
LinkedList<T>::LinkedList() {
    this->size_ = 0;
    this->head_ = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(int size, T const& value) {
    if (size <= 0) {
        throw std::runtime_error("Size can't be equal or less 0");
    }
    this->size_ = size;
    this->head_ = new Node<T>(value);
    Node<T>* ptr = this->head_;
    for (int i = 0; i < this->size_ - 1; ++i) {
        ptr->next_ = new Node<T>(value);
        ptr->next_->prev_ = ptr;
        ptr = ptr->next_;
    }
    ptr->next_ = this->head_;
    this->head_->prev_ = ptr;
}

template <typename T>
LinkedList<T>::LinkedList(int size) {
    if (size <= 0) {
        throw std::runtime_error("Size can't be equal or less 0");
    }
    this->size_ = size;
    this->head_ = new Node<T>;
    Node<T>* ptr = this->head_;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < this->size_ - 1; ++i) {
        ptr->value_ = rand() % 10;
        ptr->next_ = new Node<T>;
        ptr->next_->prev_ = ptr;
        ptr = ptr->next_;
    }
    ptr->value_ = rand() % 10;
    ptr->next_ = this->head_;
    this->head_->prev_ = ptr;
}
template <typename T>
LinkedList<T>::LinkedList(LinkedList const& other) {
    if (other.size_ == 0) {
        this->head_ = nullptr;
        this->size_ = 0;
    }
    else {
        this->size_ = other.size_;
        Node<T>* other_ptr = other.head_;
        this->head_ = new Node<T>(other_ptr->value_);
        Node<T>* ptr = this->head_;
        while (other.head_->prev_ != other_ptr) {
            ptr->next_ = new Node<T>(other_ptr->next_->value_);
            ptr->next_->prev_ = ptr;
            other_ptr = other_ptr->next_;
            ptr = ptr->next_;
        }
        ptr->next_ = this->head_;
        this->head_->prev_ = ptr;
    }
}

template <typename T>
void LinkedList<T>::Swap(LinkedList<T>& other) {
    std::swap(this->head_, other.head_);
    std::swap(this->size_, other.size_);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> const& other) {
    LinkedList<T> temp(other);
    this->Swap(temp);
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    if (this->head_ != nullptr) {
        Node<T>* ptr = this->head_;
        for (int i = 1; i < this->size_; ++i) {
            ptr = ptr->next_;
            delete ptr->prev_;
        }
        delete ptr;
    }
}

template <class T>
void LinkedList<T>::PushTail(Node<T> const& node) {
    if (this->head_ == nullptr) {
        this->head_ = new Node<T>(node.value_);
        this->head_->next_ = this->head_;
        this->head_->prev_ = this->head_;
    }
    else {
        this->head_->prev_->next_ = new Node<T>(node.value_);
        this->head_->prev_->next_->prev_ = this->head_->prev_;
        this->head_->prev_ = this->head_->prev_->next_;
        this->head_->prev_->next_ = this->head_;
    }
    this->size_++;
}

template <class T>
void LinkedList<T>::PushHead(Node<T> const& node) {
    this->PushTail(node);
    this->head_ = this->head_->prev_;
}

template <class T>
void LinkedList<T>::PopTail() {
    if (this->head_ == nullptr) {
        throw std::runtime_error("List is empty");
    }
    else if (this->size_ == 1) {
        delete this->head_;
        this->head_ = nullptr;
    }
    else {
        Node<T>* ptr = this->head_->prev_;
        this->head_->prev_ = ptr->prev_;
        ptr->prev_->next_ = this->head_;
        delete ptr;
    }
    this->size_--;
}

template <class T>
void LinkedList<T>::PopHead() {
    if (this->size_ != 0)
        this->head_ = this->head_->next_;
    this->PopTail();
}

template <class T>
void LinkedList<T>::PushTail(LinkedList<T> const& other) {
    if (this->size_ == 0) {
        *this = LinkedList(other);
    }
    else if (other.size_) {
        Node<T>* past = this->head_->prev_;
        Node<T>* ptr = past;
        Node<T>* other_ptr = other.head_;
        for (int i = 0; i < other.size_; ++i) {
            ptr->next_ = new Node<T>(other_ptr->value_);
            ptr->next_->prev_ = ptr;
            other_ptr = other_ptr->next_;
            ptr = ptr->next_;
        }
        ptr->next_ = this->head_;
        this->head_->prev_ = ptr;
        this->size_ += other.size_;
    }
}

template <class T>
void LinkedList<T>::PushHead(LinkedList<T> const& other) {
    Node<T>* past = this->head_->prev_;
    this->PushTail(other);
    this->head_ = past->next_;
}

template <class T>
void LinkedList<T>::DeleteNode(T const& value) {
    Node<T>* ptr = this->head_;
    for (int i = 0; i < size_; ++i) {
        if (ptr->value_ == value) {
            ptr->prev_->next_ = ptr->next_;
            ptr->next_->prev_ = ptr->prev_;
            Node<T>* next = ptr->next_;
            delete ptr;
            this->size_--;
            ptr = next;
        }
        else
            ptr = ptr->next_;
    }
}
template <class T>
Node<T>& LinkedList<T>::operator[](int index) {
    if (index >= this->size_ || index < 0) {
        throw std::runtime_error("Index is invalid");
    }
    Node<T>* ptr = this->head_;
    for (int i = 0; i < index; ++i) {
        ptr = ptr->next_;
    }
    return *ptr;
}

template <class T>
Node<T> LinkedList<T>::operator[](int index) const {
    if (index >= this->size_ || index < 0) {
        throw std::runtime_error("Index is invalid");
    }
    Node<T>* ptr = this->head_;
    for (int i = 0; i < index; ++i) {
        ptr = ptr->next_;
    }
    return *ptr;
}

template <class T>
int LinkedList<T>::GetSize() const {
    return this->size_;
}

template <class T>
Node<T>* LinkedList<T>::GetHead() const {
    return this->head_;
}

template <class T>
void LinkedList<T>::SetHead(Node<T>* other) {
    this->head_ = other;
}

template <class T>
void ReverseLinkedList(LinkedList<T>& list) {
    Node<T>* ptr = list.GetHead();
    for (int i=0; i < list.GetSize(); i++) {
        Node<T>* temp = ptr->GetPrev();
        ptr->SetPrev(ptr->GetNext());
        ptr->SetNext(temp);
        ptr = ptr->GetPrev();
    }
    list.SetHead(ptr->GetNext());
}
}


