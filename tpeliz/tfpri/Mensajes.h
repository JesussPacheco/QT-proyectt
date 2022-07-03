#ifndef MENSAJES_H
#define MENSAJES_H
#include<functional>
#include"Mensaje.h"
using namespace std;
template<class T,class R=T>
class Mensajes {
    int len;
    string name;
    struct Node
    {
        T date;
        Node*next;

        Node(T date, Node*next = nullptr) :date(date) ,next(next){}
    }*Head,*End;
public:
    Mensajes(string name):name(name) {
        Head = nullptr;
        End = nullptr;
        len = 0;
    }
    void Add(T date) {
        Node*nuevo = new Node(date);
        if (Head== nullptr) {
            Head = nuevo;
        }
        else {
            End->next = nuevo;
        }
        End = nuevo;
        len++;
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
    string getName(){
        return name;
    }

};
#endif // MENSAJES_H

