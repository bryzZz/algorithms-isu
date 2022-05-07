#include <iostream>
#include <algorithm>
#include <numeric>
#include <memory>
 
class Node{
public:
    int data;
    std::shared_ptr<Node> next;
    // Node* next;

    Node(): data(0){
        next = nullptr;
    }
    Node(int data): data(data) {
        next = nullptr;
    }
    Node(int array[], int n) {
        std::shared_ptr<Node> node(this);
        // Node *node = this;
        node->data = array[0];
        for(int i=1; i<n; i++) {
            node->next = std::shared_ptr<Node>(new Node(array[i]));
            node = node->next;
        }
    }
    Node(std::initializer_list<int> list) {
        if (list.size() != 0) {
            // Node* node = this;
            std::shared_ptr<Node> node(this);
            auto it = list.begin();
            node->data = *it;
            ++it;
            for (; it != list.end(); ++it) {
                node->next = std::shared_ptr<Node>(new Node(*it));
                // node->next = new Node(*it);
                node = node->next;
            }
        }
    }
    ~Node() {
        std::cout << "delete Node(" << data << ")" << std::endl;
    }
    
    void display() {
        // display(this);
        std::shared_ptr<Node> node(this);
        while(node->next != nullptr){
            std::cout << node->next << std::endl;
            std::cout << node->data << " -> ";
            node = node->next;
        }
        std::cout << std::endl;
    }

    void del(int value) {
        if(this->next->data == value){
            this->next = this->next->next;
            this->next->next = nullptr;
        }else {
            this->next->del(value);
        }
    }

// private:
//     void display(std::shared_ptr<Node> p) {
//         std::cout << p->data << " -> " << std::flush;
//         if (p->next != nullptr) {
//             display(p->next);
//         }
//     }
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
};

int main() {
    std::shared_ptr<Node> head1(new Node(10));
    std::shared_ptr<Node> head2(new Node(15));
    std::shared_ptr<Node> tail(new Node(20));
    // Node* head1 = new Node(10);
    // Node* head2 = new Node(15);
    // Node* tail = new Node(20);
    head1->next = tail;
    head2->next = tail;
    // head1->del(20);
    head1->display();
    // head2->del(20);
    // head2->display();
    // LinkedList list = {3, 5, 7, 10, 15, 8, 12, 20};
    // list.display();

    return 0;
}