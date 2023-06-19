#ifndef CONTAINER_H
#define CONTAINER_H

#include <cstddef>
#include <iterator>

template <typename T>
class Container {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
    };

public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    private:
        Node* current;

    public:
        explicit Iterator(Node* node) : current(node) {}
        ~Iterator() {}
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp(*this);
            operator++();
            return temp;
        }

        Iterator& operator--() {
            if (current) {
                current = current->prev;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp(*this);
            operator--();
            return temp;
        }

        T& operator*() const {
            return current->data;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !operator==(other);
        }
        void swap(Iterator& a, Iterator& b) {
            std::swap(a,b);
        }
    };

public:
    Container() : head(nullptr), tail(nullptr), size(0) {}

    ~Container() {
        clearList();
    }

    void addElement(const T& element) {
        Node* newNode = new Node(element);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void deleteElement(const T& element) {
        Node* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == element) {
                if (currentNode == head) {
                    head = currentNode->next;
                    if (head) {
                        head->prev = nullptr;
                    }
                }
                else if (currentNode == tail) {
                    tail = currentNode->prev;
                    if (tail) {
                        tail->next = nullptr;
                    }
                }
                else {
                    currentNode->prev->next = currentNode->next;
                    currentNode->next->prev = currentNode->prev;
                }
                delete currentNode;
                size--;
                break;
            }
            currentNode = currentNode->next;
        }
    }

    void clearList() {
        Node* currentNode = head;
        while (currentNode != nullptr) {
            Node* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    Iterator find_element(const T& element) {
        Node* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == element) {
                return Iterator(currentNode);
            }
            currentNode = currentNode->next;
        }
        return Iterator(nullptr);
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(tail->next);
    }

    bool empty() const {
        return size == 0;
    }

    std::size_t getSize() const {
        return size;
    }

private:
    Node* head;
    Node* tail;
    std::size_t size;
};

#endif // CONTAINER_H