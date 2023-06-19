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

    struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node;
        using pointer = Node*;
        using reference = T&;

        Iterator(Container::Iterator& o) : m_ptr(o.m_ptr) {}
        Iterator(Container::Iterator&& o) noexcept : m_ptr(std::move(o.m_ptr))
        {
            o.m_ptr = nullptr;
        }
        Iterator(pointer ptr) : m_ptr(ptr) {}
        ~Iterator() {}

        reference operator*() const { return m_ptr->data; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { if (m_ptr) { m_ptr = m_ptr->next; } return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { if (m_ptr) { m_ptr = m_ptr->prev; } return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };


        // copy assignment
        Iterator& operator=(const Container::Iterator& other)
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            *m_ptr = *other;
            return *this;
        }

        // move assignment
        Iterator& operator=(Iterator&& other) noexcept
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            m_ptr = std::move(other.m_ptr);
            other.m_ptr = nullptr;

            return *this;
        }

        void swap(Iterator& other) {
            std::swap(*m_ptr, *other);
        }

    private:
        pointer m_ptr;
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