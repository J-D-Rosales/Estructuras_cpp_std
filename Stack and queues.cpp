#include <cstddef>       // std::size_t
#include <initializer_list>
#include <stdexcept>     // std::out_of_range
#include <utility>       // std::move, std::swap, std::forward
#include <iostream>
#include <string>
#include <vector>
// =======================
// Stack (Pila, LIFO)
// =======================
template <typename T>
class Stack {
private:
    struct Node {
        T value;
        Node* next;
        template <typename... Args>
        explicit Node(Node* nx, Args&&... args)
            : value(std::forward<Args>(args)...), next(nx) {}
    };

    Node* head_ = nullptr;
    std::size_t size_ = 0;

    void copy_from(const Stack& other) {
        // Para preservar orden, primero copiamos a un arreglo temporal
        // y luego insertamos en orden inverso.
        if (other.size_ == 0) return;
        // Reservamos nodos en un arreglo dinámico simple
        Node** nodes = new Node*[other.size_];
        std::size_t i = 0;
        for (Node* p = other.head_; p; p = p->next, ++i) {
            nodes[i] = new Node(nullptr, p->value);
        }
        // Reconectar en orden inverso para mantener top igual
        for (std::size_t k = other.size_; k > 0; --k) {
            nodes[k-1]->next = head_;
            head_ = nodes[k-1];
            ++size_;
        }
        delete[] nodes;
    }

public:
    // --------- CTORs / DTOR / Assign ----------
    Stack() = default;

    Stack(std::initializer_list<T> ilist) {
        // El primero de la lista debe quedar al fondo.
        // Insertamos al revés para que el último quede en top.
        for (auto it = ilist.end(); it != ilist.begin();) {
            --it;
            push(*it);
        }
    }

    Stack(const Stack& other) { copy_from(other); }

    Stack(Stack&& other) noexcept
        : head_(other.head_), size_(other.size_) {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    ~Stack() { clear(); }

    Stack& operator=(Stack other) noexcept { // copy-and-swap
        swap(other);
        return *this;
    }

    void swap(Stack& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(size_, other.size_);
    }

    // --------- Observadores ----------
    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }

    // --------- Acceso ----------
    T& top() {
        if (empty()) throw std::out_of_range("Stack::top: empty");
        return head_->value;
    }
    const T& top() const {
        if (empty()) throw std::out_of_range("Stack::top: empty");
        return head_->value;
    }

    // --------- Modificadores ----------
    void clear() noexcept {
        Node* p = head_;
        while (p) {
            Node* nxt = p->next;
            delete p;
            p = nxt;
        }
        head_ = nullptr;
        size_ = 0;
    }

    void push(const T& v) {
        head_ = new Node(head_, v);
        ++size_;
    }
    void push(T&& v) {
        head_ = new Node(head_, std::move(v));
        ++size_;
    }

    template <typename... Args>
    T& emplace(Args&&... args) {
        head_ = new Node(head_, std::forward<Args>(args)...);
        ++size_;
        return head_->value;
    }

    // pop que lanza si está vacía
    void pop() {
        if (empty()) throw std::out_of_range("Stack::pop: empty");
        Node* old = head_;
        head_ = head_->next;
        delete old;
        --size_;
    }

    // Versión segura: devuelve false si estaba vacía, true si sacó y entrega en out
    bool try_pop(T& out) noexcept {
        if (empty()) return false;
        out = std::move(head_->value);
        Node* old = head_;
        head_ = head_->next;
        delete old;
        --size_;
        return true;
    }
};

// --------- free swap ----------
template <typename T>
void swap(Stack<T>& a, Stack<T>& b) noexcept { a.swap(b); }

// =======================
// Queue (Cola, FIFO)
// =======================
template <typename T>
class Queue {
private:
    struct Node {
        T value;
        Node* next;
        template <typename... Args>
        explicit Node(Args&&... args)
            : value(std::forward<Args>(args)...), next(nullptr) {}
    };

    Node* head_ = nullptr; // frente (front)
    Node* tail_ = nullptr; // fondo (back)
    std::size_t size_ = 0;

    void copy_from(const Queue& other) {
        for (Node* p = other.head_; p; p = p->next) {
            push(p->value);
        }
    }

public:
    // --------- CTORs / DTOR / Assign ----------
    Queue() = default;

    Queue(std::initializer_list<T> ilist) {
        for (const auto& v : ilist) push(v);
    }

    Queue(const Queue& other) { copy_from(other); }

    Queue(Queue&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    ~Queue() { clear(); }

    Queue& operator=(Queue other) noexcept { // copy-and-swap
        swap(other);
        return *this;
    }

    void swap(Queue& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    // --------- Observadores ----------
    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }

    // --------- Acceso ----------
    T& front() {
        if (empty()) throw std::out_of_range("Queue::front: empty");
        return head_->value;
    }
    const T& front() const {
        if (empty()) throw std::out_of_range("Queue::front: empty");
        return head_->value;
    }

    T& back() {
        if (empty()) throw std::out_of_range("Queue::back: empty");
        return tail_->value;
    }
    const T& back() const {
        if (empty()) throw std::out_of_range("Queue::back: empty");
        return tail_->value;
    }

    // --------- Modificadores ----------
    void clear() noexcept {
        Node* p = head_;
        while (p) {
            Node* nxt = p->next;
            delete p;
            p = nxt;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    // enqueue
    void push(const T& v) {
        Node* node = new Node(v);
        if (!tail_) head_ = tail_ = node;
        else { tail_->next = node; tail_ = node; }
        ++size_;
    }
    void push(T&& v) {
        Node* node = new Node(std::move(v));
        if (!tail_) head_ = tail_ = node;
        else { tail_->next = node; tail_ = node; }
        ++size_;
    }
    // alias útil
    void enqueue(const T& v) { push(v); }
    void enqueue(T&& v) { push(std::move(v)); }

    template <typename... Args>
    T& emplace(Args&&... args) {
        Node* node = new Node(std::forward<Args>(args)...);
        if (!tail_) head_ = tail_ = node;
        else { tail_->next = node; tail_ = node; }
        ++size_;
        return tail_->value;
    }

    // dequeue que lanza si está vacía
    void pop() {
        if (empty()) throw std::out_of_range("Queue::pop: empty");
        Node* old = head_;
        head_ = head_->next;
        if (!head_) tail_ = nullptr;
        delete old;
        --size_;
    }
    void dequeue() { pop(); } // alias

    // Versión segura: devuelve false si estaba vacía, true si sacó
    bool try_pop(T& out) noexcept {
        if (empty()) return false;
        out = std::move(head_->value);
        Node* old = head_;
        head_ = head_->next;
        if (!head_) tail_ = nullptr;
        delete old;
        --size_;
        return true;
    }
    bool try_dequeue(T& out) noexcept { return try_pop(out); } // alias
};

// --------- free swap ----------
template <typename T>
void swap(Queue<T>& a, Queue<T>& b) noexcept { a.swap(b); }



int main() {
    Stack<int> s;
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);


    s.push(1);
    s.push(2);
    s.push(3);

    for (int i = 0; i < 3; i++) {
        cout << s.top() << endl;
        s.pop();
    }


    return 0;
}


