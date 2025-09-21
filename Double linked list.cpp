#include <iostream>
using namespace std;

template <typename T>
struct Node {
T data;
Node<T>* next;
Node<T>* prev;

Node(T d) {
data = d;
next = nullptr;
prev = nullptr;
}
~Node() = default;
};

template <typename T>
class List {
private:
Node<T>* head;
Node<T>* tail;

public:
List() : head(nullptr), tail(nullptr) {}

Node<T>* getHead() {
return head;
}

T front() {
return head->data;
}

T back() {
return tail->data;
}

void pushFront(T value) {
Node<T>* newNode = new Node<T>(value);
newNode->prev = nullptr;
newNode->next = head;
if (head) head->prev = newNode;
head = newNode;
if (!tail) tail = newNode;
}

void pushBack(T value) {
Node<T>* newNode = new Node<T>(value);
newNode->next = nullptr;
newNode->prev = tail;
if (tail) tail->next = newNode;
tail = newNode;
if (!head) head = newNode;
}

void popFront() {
if(!head) return;
if(head == tail) {
delete head;
head = nullptr;
tail = nullptr;
return;
}
Node<T>* temp = head;
head = head->next;
head->prev = nullptr;
delete temp;
}

void popBack() {
if(!tail) return;
if(head == tail) {
delete tail;
tail = nullptr;
head = nullptr;
return;
}
Node<T>* temp = tail;
tail = tail->prev;
tail->next = nullptr;
delete temp;
}

    void insert(int pos, T num) {
        if (!head) {
            head = new Node<T>(num);
            tail = head;
            return;
        }
        Node<T>* nodo = new Node<T>(num);
        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos - 1) {
            temp = temp->next;
        }

        if (pos == 0) {
            nodo->next = head;
            head->prev = nodo;
            head = nodo;
            return;
        }

        if (temp->next == nullptr) {
            temp->next = nodo;
            nodo->prev = temp;
            tail = nodo;
            return;
        }

        nodo->next = temp->next;
        nodo->prev = temp;
        temp->next->prev = nodo;
        temp->next = nodo;
    }

    void remnove(int pos) {

        if (head == nullptr) {
            return;
        }

        Node<T>* temp = head;
        int i = 0;
        while(i++ < pos - 1) {
            temp = temp->next;
        }

        if (temp == head) {
            head = temp->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        }

        else if (temp->next == nullptr) {
            temp->prev->next = nullptr;
        }

        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
    }

T operator[](int pos) {
Node<T>* temp = head;
int i = 0;
@@ -166,8 +230,11 @@

cout << "Tamaño de lista: " << l1.size() << endl;

    cout << "El valor en la posicion 2:" << endl;
    cout << l1[2] << endl;
    cout << "Agregar el 5 en la posicion 4: " <<endl;
    l1.insert(4,5);

    cout << "El valor en la posicion 4:" << endl;
    cout << l1[4] << endl;

l1.reverse();
cout << "Reverse: ---" << endl;
