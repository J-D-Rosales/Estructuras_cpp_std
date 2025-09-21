#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T d) {
        data = d;
        next = nullptr;
    }

    ~Node() = default;
};

template <typename T = int>
class List {
private:
    Node<T>* head;

public:
    List() : head(nullptr) {}

    Node<T>* getHead() {
        return head;
    }

    T front() {
        return head->data;
    }

    T back() {
        Node<T>* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    void pushFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    void pushBack(T value) {
        Node<T>* node = new Node<T>(value);
        if(!head) {
            head = node;
            return;
        }
        Node<T>* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
        node->next = nullptr;
    }

    void popFront() {
        if(!head) return;
        if(head->next == nullptr) {
            delete head;
            head = nullptr;
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    void popBack() {
        Node<T>* temp = head;
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        while(temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    T operator[](int pos) {
        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        Node<T>* temp = head;
        int i = 0;
        while(temp != nullptr) {
            i++;
            temp = temp->next;
        }
        return i;
    }

    void clear() {
        while(head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    Node<T>* merge(Node<T>* a, Node<T>* b) {
        if(!a) return b;
        if(!b) return a;
        if(a->data <= b->data) {
            a->next = merge(a->next, b);
            return a;
        } else {
            b->next = merge(a, b->next);
            return b;
        }
    }

    Node<T>* mergeSort(Node<T>* current) {
        if (!current || !current->next) return current;
        Node<T>* slow = current;
        Node<T>* fast = current->next;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node<T>* mid = slow->next;
        slow->next = nullptr;
        Node<T>* left = mergeSort(current);
        Node<T>* right = mergeSort(mid);
        return merge(left, right);
    }

    void sort() {
        head = mergeSort(head);
    }

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;
        while(curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    void insert(int pos, T num) {
        Node<T>* nodo = new Node<T>(num);
        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos - 1) {
            temp = temp->next;
        }
        nodo->next = temp->next;
        temp->next = nodo;
    }

    ~List() { clear(); }

    template<typename T_>
    friend ostream& operator<<(ostream& os, const List<T_> &l);
};


template<typename T>
ostream& operator<<(ostream &os, const List<T> &l) {
    Node<T>* temp = l.head;
    while (temp != nullptr) {
        os << temp->data << " ";
        temp = temp->next;
    }
    return os;
}

int main () {
    List<int> l1;
    l1.pushFront(30);
    l1.pushBack(50);
    l1.pushFront(20);
    l1.pushFront(10);
    l1.pushBack(40);

    cout << "-------------" << endl;

    cout << l1 << "\n";
    cout << "Ordered: ---" << endl;
    l1.sort();
    cout << l1 << "\n";

    cout << "Tamaño de lista: " << l1.size() << endl;

    cout << "El valor en la posicion 2:" << endl;
    cout << l1[2] << endl;

    l1.reverse();
    cout << "Reverse: ---" << endl;
    cout << l1 << "\n";

    return 0;
}
