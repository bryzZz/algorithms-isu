#include <iostream>
#include <algorithm>
#include <numeric>
#include <memory>
 
class Node{
public:
    int data;
    Node* next;

    Node(): data(0){
        next = nullptr;
    }

    Node(int data): data(data) {
        next = nullptr;
    }

    Node(int array[], int n) {
        Node *node = this;
        node->data = array[0];
        for(int i=1; i<n; i++) {
            node->next = new Node(array[i]);
            node = node->next;
        }
    }

    Node(std::initializer_list<int> list) {
        if (list.size() != 0) {
            Node* node = this;
            auto it = list.begin();
            node->data = *it;
            ++it;
            for (; it != list.end(); ++it) {
                node->next = new Node(*it);
                node = node->next;
            }
        }
    }

    int count() {
        int c = 0;
        Node* node = this;
        while (node) {
            c++;
            node = node->next;
        }
        return c;
    }

    int sum() {
        int c = 0;
        Node* node = this;
        while (node) {
            c += node->data;
            node = node->next;
        }
        return c;
    }

    int max() {
        Node* node = this;
        int c = node->data; // INT32_MIN
        while (node) {
            if (node->data > c) {
                c = node->data;
            }
            node = node->next;
        }
        return c;
    }

    int rmax(){
        return rmax(this);
    }

    void display() {
        display(this);
        std::cout << std::endl;
    }

private:

    int rmax(Node *p) {
        int max = 0;
        if (p == nullptr) {
            return INT32_MIN;
        }
        max = rmax(p->next);
        if (max > p->data) {
            return max;
        }
        return p->data;
    }

    void display(Node* p) {
        std::cout << p->data << " -> " << std::flush;
        if (p->next != nullptr) {
            display(p->next);
        }
    }

};

class LinkedList {
private:
    Node *first;

public:
    LinkedList() {
        first = nullptr;
    }

    LinkedList(std::initializer_list<int> list) {
        first = new Node(list);
    }

    void display() {
        first->display();
    }

    Node* get_first() {
        return first;
    }

    class Iterator {
    public:
        Iterator(): current(nullptr) {};
        Iterator(const Node *node): current(node) {};

        int operator*() {
            // std::cout << "call *operator" << std::endl;
            return current->data;
        }
        Iterator &operator++() {
            // std::cout << "call ++operator" << std::endl;
            if (current != nullptr) {
                previous = current;
                current = current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            // std::cout << "call ++(int) operator" << std::endl;
            Iterator temp = *this;
            ++*this;
        }    

        bool operator!=(const Iterator &other) {
            // std::cout << "call !=operator" << std::endl;
            return this->current != other.current;
        }
    private:
        const Node *previous = nullptr;
        const Node *current = nullptr;
    };

    Iterator begin() const noexcept{
        return Iterator(first);
    }

    Iterator end() const noexcept {
        return Iterator();
    }
};

int main() {
    int A[] = {3, 5, 7, 10, 15, 8, 12, 20};
    Node *head = new Node(A, 8);
    head->display();

    Node other = {3, 5, 7, 10, 15, 8, 12, 20};
    other.display();

    std::cout << other.max() << std::endl;

    LinkedList list = {3, 5, 7, 10, 15, 8, 12, 20};
    list.display();
    for (auto value: list) {
        std::cout << value << std::endl;
    }
    int sum = 0;
    std::for_each(list.begin(), list.end(), [&] (int n) {
        sum += n;
    });
    std::cout << sum << std::endl;
    int accum = std::accumulate(list.begin(), list.end(), 0);
    std::cout << accum << std::endl;
    return 0;
}