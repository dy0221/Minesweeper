#ifndef LIST
#define LIST

#include "cell.h"
namespace DLIST {
    class Node
    {
    private:
        Node* prev;
        Node* next;
    public:
        CELL::Cell* data;
        Node(CELL::Cell* val) : data(val), prev(nullptr), next(nullptr) {}
        Node* GetPrev() { return prev; }
        Node* GetNext() { return next; }
        void SetPrev(Node* p) { prev = p; }
        void SetNext(Node* n) { next = n; }
        void Display() const { data->ShowMember(); }
    };

    class DbLinkedList
    {
    private:
        Node* node;
    public:
        DbLinkedList() : node(nullptr) {}
        ~DbLinkedList() {
            while (node != nullptr) {
                Node* temp = node;
                node = node->GetNext();
                delete temp->data; 
                delete temp;       
            }
        }

        int GetSize() {
            int size = 0;
            Node* current = node;
            while (current != nullptr) {
                size++;
                current = current->GetNext();
            }
            return size;
        }

        bool is_empty() {
            return (node == nullptr);
        }

        void AddNode(CELL::Cell* val) {
            Node* new_node = new Node(val);
            if (node == nullptr) {
                node = new_node;
            }
            else {
                Node* current = node;
                while (current->GetNext() != nullptr) {
                    current = current->GetNext();
                }
                current->SetNext(new_node);
                new_node->SetPrev(current);
            }
        }

        void DisplayList() {
            Node* current = node;
            while (current != nullptr) {
                current->Display();
                current = current->GetNext();
                printf("\n");
            }
        }

        CELL::Cell* GetData(int n) {
            Node* current = this->node;
            int count = 1;
            while (current != nullptr && count < n) {
                current = current->GetNext();
                count++;
            }
            if (current == nullptr) {
                return nullptr;
            }
            else {
                return current->data;
            }
        }

        void DeleteData() {
            while (node != nullptr) {
                Node* temp = node;
                node = node->GetNext();
                delete temp->data; 
                delete temp;       
            }
        }
    };
}

#endif