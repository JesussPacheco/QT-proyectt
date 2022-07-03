#ifndef LISTA_H
#define LISTA_H
#include<iostream>
#include<functional>
using namespace std;
template<class T, class R = T>
class BusquedaPub
{
private:
    int len;
    struct Node
    {
        T date;
        Node*next;
        Node*back;
        Node(T date = nullptr, Node*next = nullptr, Node*back = nullptr) :next(next), date(date), back(back) {}
    }*Head, *End, *actual;
public:
    BusquedaPub() {
        Head = nullptr;
        actual = nullptr;
        End = nullptr;
        //	End = nullptr;
        len = 0;
    }
    ~BusquedaPub() {}
    void Add(T date) {
        Node*nuevo = new Node(date);
        if (Head == nullptr) {
            Head = nuevo;
            actual = nuevo;
        }
        else {
            nuevo->next = Head;
            End->next = nuevo;
            nuevo->back = End;
            Head->back = nuevo;
        }
        End = nuevo;
        len++;
    }
    void eliminate() {
        Node*aux = actual;
        aux->back->next = aux->next;
        aux->next->back = aux->back;
        if (actual == Head) {
            actual = aux->next;
            Head = actual->next;
        }
        else if (actual == End) {
            actual = aux->next;
            End = actual->next;
        }

        else actual = aux->next;

        delete aux;
        len--;
        if (len == 0) {
            actual = nullptr;
            Head = nullptr;
            End = nullptr;
        }
    }
    void LoveLambda(function<void(T)>operacion) {
        Node*aux = Head;
        for (int i = 1; i <= len; i++) {
            operacion(aux->date);
            aux = aux->next;
        }

    }
    bool empty() {
        return (Head == nullptr) ? true : false;
    }
    void Next() {
        actual = actual->next;
    }
    void Back() {
        actual = actual->back;
    }
    Node*getHead() {
        return Head;
    }
    Node*getEnd() {
        return End;
    }
    Node*getActual() {
        return actual;
    }
    void Again() {
        actual = Head;
    }
    int size() {
        return len;
    }
};


#endif
