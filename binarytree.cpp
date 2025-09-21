#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* left;  // hijo izquierdo
    Nodo* right; // hijo derecho
    Nodo(int dato) {
        this->dato = dato;
        this->left = NULL;
        this->right = NULL;
    }
};

// Binary Search Tree (BST) -> Arbol Binario de Busqueda
// Un arbol sin elementos repetidos
class BST {
private:
    Nodo* raiz = NULL;
    Nodo* insertarNodoAux(Nodo* nodo, int x) { // En la primera llamada 'nodo=raiz'
        // Si existe un nodo disponible, inserto 'x'
        if (nodo == NULL)
            return new Nodo(x);
        if (x < nodo->dato)
            nodo->left = insertarNodoAux(nodo->left, x);
        else if (x > nodo->dato)
            nodo->right = insertarNodoAux(nodo->right, x);
        return nodo;
    }
    Nodo* buscarAux(Nodo* nodo, int x) {
        if (nodo == NULL)
            return NULL;  // No se encontro el nodo
        else if (x == nodo->dato)
            return nodo;  // Encontre el nodo
        if (x < nodo->dato)
            return buscarAux(nodo->left, x);
        else
            return buscarAux(nodo->right, x);
    }
    void imprimirEnOrderAux(Nodo* nodo) { // En la primera llamada 'nodo=raiz' ( O(log N))
        if (nodo == NULL)
            return;
        imprimirEnOrderAux(nodo->left);
        cout << nodo->dato << ' ';
        imprimirEnOrderAux(nodo->right);
    }
    void imprimirPreOrderAux(Nodo* nodo) {
        if (nodo == NULL)
            return;
        cout << nodo->dato << ' ';
        imprimirPreOrderAux(nodo->left);
        imprimirPreOrderAux(nodo->right);
    }
    void imprimirPostOrderAux(Nodo* nodo) {
        if (nodo == NULL)
            return;
        imprimirPostOrderAux(nodo->left);
        imprimirPostOrderAux(nodo->right);
        cout << nodo->dato << ' ';
    }
    void eliminar(Nodo* nodo) {
        if (nodo == NULL)
            return;

        eliminar(nodo->left);
        eliminar(nodo->right);
        delete nodo;
    }
    int minimoAux(Nodo* nodo) {
        // Cuando el nodo no tenga hijo izquierdo, significa
        // que no existe otro nodo con un dato menor al actual
        if (nodo->left == NULL)
            return nodo->dato;
        return minimoAux(nodo->left);
    }
    int maximoAux(Nodo* nodo) {
        // Cuando el noodo no tenga hijo derecho, significa
        // que no existe otro nodo con una dato mayor al actual
        if (nodo->right == NULL)
            return nodo->dato;
        return maximoAux(nodo->right);
    }
    Nodo* sucesorAux(Nodo* nodo) {
        // En la primera llamada 'nodo' contiene a 'x'
        if (nodo->right != NULL) // Tiene hijo derecho
            return this->buscar(minimoAux(nodo->right));
        else {
            // Cuando no tiene hijo derecho
            Nodo* ancestro = raiz;
            Nodo* sucesor = NULL;
            while (ancestro != nodo) {
                if (nodo->dato < ancestro->dato) {
                    sucesor = ancestro;
                    ancestro = ancestro->left;
                }
                else
                    ancestro = ancestro->right;
            }
            return sucesor;
        }
    }
public:
    void insertarNodo(int x) {
        raiz = insertarNodoAux(raiz, x);
    }
    void imprimirEnOrder() {
        this->imprimirEnOrderAux(raiz);
        cout << endl;
    }
    void imprimirPreOrder() {
        this->imprimirPreOrderAux(raiz);
        cout << endl;
    }
    void imprimirPostOrder() {
        this->imprimirPostOrderAux(raiz);
        cout << endl;
    }
    ~BST() {
        this->eliminar(raiz);
    }
    Nodo* buscar(int x) {
        return buscarAux(raiz, x);
    }
    int minimo() {
        return minimoAux(raiz);
    }
    int maximo() {
        return maximoAux(raiz);
    }
    Nodo* sucesor(int x) {
        auto nodo_con_x = buscarAux(raiz, x);
        if (nodo_con_x == NULL)
            return NULL;
        return sucesorAux(nodo_con_x);
    }
};
int main() {
    BST arbol;
    arbol.insertarNodo(5);
    arbol.insertarNodo(7);
    arbol.insertarNodo(4);
    arbol.insertarNodo(6);
    arbol.insertarNodo(6);
    arbol.insertarNodo(8);
    arbol.insertarNodo(2);

    cout << "Minimo: " << arbol.minimo() << endl;
    cout << "Maximo: " << arbol.maximo() << endl;

    Nodo* sucesor = arbol.sucesor(5);
    cout << "Sucesor de 5: " << sucesor->dato << endl;

    Nodo* sucesor2 = arbol.sucesor(6);
    cout << "Sucesor de 6: " << sucesor2->dato << endl;
    /*
    auto res = arbol.buscar(8);
    if (res == NULL)
        cout << "No se encontro el dato\n";
    else
        cout << "Se encontro el dato\n";

    cout << "En Orden: ";
    arbol.imprimirEnOrder();
    cout << "Pre Orden: ";
    arbol.imprimirPreOrder();
    cout << "Post Orden: ";
    arbol.imprimirPostOrder();
    */
    /*
    Nodo* raiz = NULL;
    raiz = new Nodo(5); // raiz != NULL
    cout << "raiz: " << raiz->dato << endl;
    raiz->left = new Nodo(4);
    cout << "hijo izquierdo de la raiz: " << raiz->left->dato << endl;
    raiz->right = new Nodo(7);
    raiz->left->left = new Nodo(2);
    */

    return 0;
}
