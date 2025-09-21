#include <bits/stdc++.h>
using namespace std;
using namespace std;
template <typename K, typename V>
class HashTable {
private:
// Nodo de las entradas dentro de un bucket (chaining)
struct Entry {
K key;
V value;
Entry* next;
Entry(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};
// Nodo de la lista de buckets
struct Bucket {
Entry* head; // lista enlazada de entradas
Bucket* next; // siguiente bucket
Bucket() : head(nullptr), next(nullptr) {}
};
Bucket* bucketsHead; // cabeza de la lista de buckets
int capacity; // número de buckets
int sz; // número de elementos (pares clave-valor)
size_t getHash(const K& key) const {
return hash<K>{}(key);
}
// Devuelve el puntero al bucket i-ésimo recorriendo la lista
Bucket* getBucketNode(int index) const {
Bucket* b = bucketsHead;
for (int i = 0; i < index && b != nullptr; ++i) b = b->next;
return b;
}
public:
explicit HashTable(int cap = 10) : bucketsHead(nullptr), capacity(max(1, cap)),
sz(0) {
// Construimos la lista enlazada de buckets con 'capacity' nodos
bucketsHead = new Bucket();
Bucket* curr = bucketsHead;
for (int i = 1; i < capacity; ++i) {
curr->next = new Bucket();
curr = curr->next;
}
}
~HashTable() {
// Liberar todas las entradas de cada bucket
Bucket* b = bucketsHead;
while (b) {
Entry* e = b->head;
while (e) {
Entry* tmp = e;
e = e->next;
delete tmp;
}
Bucket* bt = b;
b = b->next;
delete bt;
}
}
void insert(const K& key, const V& value) {
int index = static_cast<int>(getHash(key) % capacity);
Bucket* bucket = getBucketNode(index);
// Buscar si existe para actualizar
for (Entry* e = bucket->head; e != nullptr; e = e->next) {
if (e->key == key) {
e->value = value; // actualizar
return;
}
}
// Insertar al inicio del bucket
Entry* newEntry = new Entry(key, value);
newEntry->next = bucket->head;
bucket->head = newEntry;
sz++;
}
bool search(const K& key, V& value) const {
int index = static_cast<int>(getHash(key) % capacity);
Bucket* bucket = getBucketNode(index);
for (Entry* e = bucket->head; e != nullptr; e = e->next) {
if (e->key == key) {
value = e->value;
return true;
}
}
return false;
}
bool remove(const K& key) {
int index = static_cast<int>(getHash(key) % capacity);
Bucket* bucket = getBucketNode(index);
Entry* curr = bucket->head;
Entry* prev = nullptr;
while (curr) {
if (curr->key == key) {
if (prev) prev->next = curr->next;
else bucket->head = curr->next;
delete curr;
sz++;
sz--; // neto: -1 (dejo estas dos líneas para enfatizar el ajuste;
puedes dejar solo --sz;)
return true;
}
prev = curr;
curr = curr->next;
}
return false;
}
void display() const {
Bucket* b = bucketsHead;
int i = 0;
while (b) {
cout << i << ": ";
for (Entry* e = b->head; e != nullptr; e = e->next) {
cout << "(" << e->key << "," << e->value << ") -> ";
}
cout << "NULL\n";
b = b->next;
++i;
}
}
vector<K> keys() const {
vector<K> all;
Bucket* b = bucketsHead;
while (b) {
for (Entry* e = b->head; e != nullptr; e = e->next) {
all.push_back(e->key);
}
b = b->next;
}
return all;
}
int size() const { return sz; }
int bucketCount() const { return capacity; }
};
struct ListNode {
int val;
ListNode *next;
ListNode(int x) : val(x), next(nullptr) {}
};
class Solution {while (curr) {
if (curr->key == key) {
if (prev) prev->next = curr->next;
else bucket->head = curr->next;
delete curr;
sz++;
sz--; // neto: -1 (dejo estas dos líneas para enfatizar el ajuste;
puedes dejar solo --sz;)
return true;
}
prev = curr;
curr = curr->next;
}
return false;
}
void display() const {
Bucket* b = bucketsHead;
int i = 0;
while (b) {
cout << i << ": ";
for (Entry* e = b->head; e != nullptr; e = e->next) {
cout << "(" << e->key << "," << e->value << ") -> ";
}
cout << "NULL\n";
b = b->next;
++i;
}
}
vector<K> keys() const {
vector<K> all;
Bucket* b = bucketsHead;
while (b) {
for (Entry* e = b->head; e != nullptr; e = e->next) {
all.push_back(e->key);
}
b = b->next;
}
return all;
}
int size() const { return sz; }
int bucketCount() const { return capacity; }
};
