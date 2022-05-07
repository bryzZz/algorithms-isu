#include <iostream>
#include <memory>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data): data(data){
        next = nullptr;
    }
    ~Node() {
        std::cout << "destroyed node with value " << data << std::endl;
    }
};

template<class T>
class SmartPointer {
    T *ptr;
    
    public:
        explicit SmartPointer(T* p = nullptr) {ptr = p;}
    
        ~SmartPointer() {delete(ptr);}
        T& operator*() {return *ptr;}
        T* operator->() {return ptr;}
};

void func() {
    SmartPointer<Node> node(new Node(10));
}

int main() {
    // {
    //     Node *node = new Node(12);

    //     unique_ptr<Node> uptr(new Node(10));

    //     uptr = make_unique<Node>(12);
        
    //     cout << uptr->data << endl;
    // }

    // shared_ptr<Node> sptr2(new Node(2));

    {
        // cout << "shared ptr" << endl;

        // shared_ptr<Node> sptr(new Node(13));

        // cout << sptr.use_count() << endl;

        // shared_ptr<Node> sptr2 = sptr;

        // cout << sptr.use_count() << endl;
    }

    weak_ptr<Node> wptr;
    {
        shared_ptr<Node> sptr(new Node(10));

        wptr = sptr;

        cout << wptr.lock()->data << endl;
    }

    cout << boolalpha << wptr.expired() << endl;

    // SmartPointer<Node> ptr(new Node(1));

    // cout << (*ptr).data << endl;
    // cout << ptr->data << endl;

    // SmartPointer<int> i(new int(2));

    // cout << *i << endl;

    // while (true) {
    //     func();
    // }

    // cout << "end of program" << endl;
    return 0;
}