#pragma once
#include <iostream>
#include <string>
#include <functional>

template<typename T>
class LinkedList{

    struct Node{

        T data;
        Node* next;
        Node(const T& entity) : data(entity), next(nullptr) {}
    };

    Node* head;

    public:

        // default constructor
        LinkedList() : head(nullptr) {}

        // copy constructor
        LinkedList(const LinkedList& LinkedList_to_copy) : head(nullptr){

            Node* current = LinkedList_to_copy.head;
            while(current != nullptr){

                this->add(current->data);
                current = current->next;
            }
        }

        // move constructor
        LinkedList(LinkedList&& other) noexcept : head(other.head) { other.head = nullptr; }

        // assignment operator overload for copying
        LinkedList& operator=(const LinkedList& LinkedList_to_copy){

            if(this == &LinkedList_to_copy) return this;
            clear();

            Node* current = LinkedList_to_copy.head;

            while(current != nullptr){

                add(current->data);
                current = current->next;
            }

            return *this;
        }

        // assignment operator overload for moving
        LinkedList& operator=(LinkedList&& other) noexcept{

            if(this == &other) return *this;
            this->clear();
            this->head = other.head;
            other.head = nullptr;
            return *this;
        }


        ~LinkedList() {

            clear();
        }

        void add(const T& element);
        T* find(std::function<bool(const T&)> predicate);
        void remove(std::function<bool(const T&)> predicate);
        void clear();
};

template <typename T>
void LinkedList<T>::clear(){

    Node* current = head;
    while(current != nullptr){

        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

template <typename T>
void LinkedList<T>::add(const T& element){ // append

    if(head == nullptr){

        head = new Node(element);
        return;
    }
    Node* current_node = head;
    while(current_node->next != nullptr){

        current_node = current_node->next;
    }
    current_node->next = new Node(element);
    return;
}

template <typename T>
T* LinkedList<T>::find(std::function<bool(const T&)> predicate){

    Node* current_node = head;
    while(current_node != nullptr){

        if(predicate(current_node->data)){
            return &current_node->data;
        }
        current_node = current_node->next;
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::remove(std::function<bool(const T&)> predicate){

    Node* current_node = head;
    Node * previous_node = nullptr;

    while(current_node != nullptr){

        if(predicate(current_node->data)){

            if(current_node == head) head = head->next;
            else previous_node->next = current_node->next;
            delete current_node;
            return;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }
}
