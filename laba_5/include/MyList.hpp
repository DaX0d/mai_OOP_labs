#pragma once

#include <memory>
#include <iterator>
#include <concepts>
#include <memory_resource>


template<class T>
class MyList {
private:
    struct Node {
        T data;
        Node* next{nullptr};

        template<typename... Args>
        explicit Node(Args&&... args):
            data(std::forward<Args>(args)...), next(nullptr) {}
    };

    using allocator_type = std::pmr::polymorphic_allocator<Node>;

    Node* head{nullptr};
    std::size_t size_{0};
    allocator_type allocator;

public:
    class Iterator {
    private:
        Node* current;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* node = nullptr): current(node) {}

        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const { 
            return current == other.current; 
        }
        
        bool operator!=(const Iterator& other) const { 
            return current != other.current; 
        }
    };

    explicit MyList(std::pmr::memory_resource* mr = nullptr) 
        : allocator(mr) {}

    ~MyList() { clear(); }

    void push_front(const T& value) {
        Node* new_node = allocator.allocate(1);
        std::allocator_traits<decltype(allocator)>::construct(
            allocator, new_node, value);
        new_node->next = head;
        head = new_node;
        ++size_;
    }

    template<typename... Args>
    void emplace_front(Args&&... args) {
        Node* new_node = allocator.allocate(1);
        std::allocator_traits<decltype(allocator)>::construct(
            allocator, new_node, std::forward<Args>(args)...);
        new_node->next = head;
        head = new_node;
        ++size_;
    }

    void pop_front() {
        if (head) {
            Node* to_delete = head;
            head = head->next;
            std::allocator_traits<decltype(allocator)>::destroy(
                allocator, to_delete);
            allocator.deallocate(to_delete, 1);
            --size_;
        }
    }

    void clear() {
        while (head) {
            pop_front();
        }
    }

    bool empty() const { return head == nullptr; }
    std::size_t size() const { return size_; }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};
