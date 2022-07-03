#ifndef COMENTARIOS_H
#define COMENTARIOS_H
#include<iostream>
//#include"Persona.h"
#include<functional>
//#include<QApplication>
#include<algorithm>
#include"Comentario.h"
using namespace std;
template <typename T, typename R = T>
class COMENTARIOS {
protected:
    struct Node {
        T date; Node* left; Node* right; int height;
        Node(T date) : date(date), left(nullptr), right(nullptr), height(0) {}
    };
    Node*NONE = nullptr;
      T nn=nullptr;
    typedef function<R(T)>      lbdKey;
    typedef function<void(T)>   lbdProc;
    Node*   root;
    Node*actual;
    int     len;
    lbdKey  key;

public:
    COMENTARIOS(lbdKey key = [](T a) {return a; }) : key(key), root(nullptr), len(0) {
        actual = root;
    }
    ~COMENTARIOS() { destroy(root); }

    int     height() { return height(root); }
    int     size() { return len; }
    void    clear() { destroy(root); len = 0; }

    void    add(T date) { add(root, date); }
    void    inOrder(lbdProc proc) { inOrder(root, proc); }
    T find(R attr) {
        Node*& node = find(root, attr);
        return node == nullptr ? nn : node->date;
    }
    bool empty() {
        return len == 0 ? true : false;
    }
    Node*getActual() {
        return actual;
    }
    void remove(T attr) {
        Node*& node = find(root, key(attr));
        if (node == nullptr) return;
        if (node->left == nullptr) {
            Node* aux = node;
            node = node->right;
            delete aux;
        }
        else {
            Node*& cand = greatest(node->left);
            node->date = cand->date;
            Node* aux = cand;
            cand = cand->left;
            delete aux;
        }
    }
    void eliminate() {
        Node*& node = actual;
        if (node == nullptr) return;
        if (node->left == nullptr) {
            Node* aux = node;
            node = node->right;
            delete aux;
        }
        else {
            Node*& cand = greatest(node->left);
            node->date = cand->date;
            Node* aux = cand;
            cand = cand->left;
            delete aux;
        }
    }
    void Next() {

    }
    void Back() {

    }
    void Again() {
        actual = menor(root);
    }
private:
    void destroy(Node*& node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            node = nullptr;
        }
    }
    int height(Node* node) {
        return node == nullptr ? -1 : node->height;
    }
    void add(Node*& node, T date) {
        if (node == nullptr) {
            node = new Node(date);
            ++len;
        }
        else {
            if (key(date) < key(node->date)) {
                add(node->left, date);
            }
            else {
                add(node->right, date);
            }
            balance(node); /* :O */
        }
    }
    Node*& greater(Node*& node) {
        return node->right != nullptr ? node : greater(node->right);
    }
    Node*& menor(Node*& node) {
        return node->left != nullptr ? node : greater(node->left);
    }

    void inOrder(Node* node, lbdProc proc) {
        if (node != nullptr) {
            inOrder(node->left, proc);
            proc(node->date);
            inOrder(node->right, proc);
        }
    }
    Node*& find(Node*& node, R attr) {
        if (node == nullptr) {
            return dummynull;
        }
        else if (attr == key(node->date)) {
            return node;
        }
        else if (attr < key(node->date)) {
            return find(node->left, attr);
        }
        else {
            return find(node->right, attr);
        }
    }

    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
    }
    void rotateLeft(Node*& node) { // X = node, Y = node->right
        Node* aux = node->right;
        node->right = aux->left;
        updateHeight(node);
        aux->left = node;
        updateHeight(aux);
        node = aux;
    }
    void rotateRight(Node*& node) { // Y = node, X = node->left
        Node* aux = node->left;
        node->left = aux->right;
        updateHeight(node);
        aux->right = node;
        updateHeight(aux);
        node = aux;
    }
    void balance(Node*& node) {
        int hl = height(node->left);
        int hr = height(node->right);

        if (hr - hl < -1) {
            hl = height(node->left->left);
            hr = height(node->left->right);
            if (hr > hl) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        }
        else if (hr - hl > 1) {
            hl = height(node->right->left);
            hr = height(node->right->right);
            if (hl > hr) {
                rotateRight(node->right);
            }
            rotateLeft(node);
        }
        else {
            updateHeight(node);
        }
    }
    Node*& greatest(Node*& node) {
        return node->right == nullptr ? node : greatest(node->right);
    }


    Node* dummynull = nullptr;
};
#endif
