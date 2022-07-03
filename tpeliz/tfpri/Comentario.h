#ifndef COMENTARIO_H
#define COMENTARIO_H
#include"RESPUESTAS.h"
#include <QVBoxLayout>
template <class T, class R = T>
class COMENTARIO {
    typedef RESPUESTAS <RESPUESTA<string>*, string>rtaString;
    typedef RESPUESTAS <RESPUESTA<string>*, int>rtaInt;
    struct rta {
        rtaString*text = new rtaString([](RESPUESTA<string>*a) { return a->getTexto(); });
        rtaInt*posicion = new rtaInt([](RESPUESTA<string>*a) { return a->getpos(); });
    };
    rta *respuestas=new rta();
    T texto;
    T photo;
    int like;
    int id;
    T date;
    QVBoxLayout *todo;
public:
    COMENTARIO(T tx, T ph, int pos, T dd) {
        texto = tx;
        photo = ph;
        id = pos;
        like = 0;
        date=dd;
    }
    void setTexto(T a) { texto = a; }
    void setPhoto(T a) { photo = a; }
    void setLike(int a) { like = a; }
    void setTodo(QVBoxLayout *A){todo=A;}
    T getTexto() { return texto; }
    T getPhoto() { return photo; }
    QVBoxLayout * getTodo(){return todo;}
    void maslike() { like++; }
    int getLike() { return like; }
    int getpos() { return id; }
    void addAnswer(RESPUESTA<string>*x) {
        respuestas->text->add(x);
        respuestas->text->add(x);
    }
    void removeAnswer(RESPUESTA<string>*x) {
        respuestas->text->remove(x);
        respuestas->posicion->remove(x);
    }
};
#endif // COMENTARIO_H
