#ifndef PUBLICACION_H
#define PUBLICACION_H
#include"Comentarios.h"
#include <QVBoxLayout>
template <class T, class R = T>
class Publicacion {
    typedef COMENTARIOS<COMENTARIO<string>*, string>commentString;
    typedef COMENTARIOS<COMENTARIO<string>*, int>commentInt;
    struct Coment {
        commentString*text = new commentString([](COMENTARIO<string>*a) { return a->getTexto(); });
        commentInt*posicion = new commentInt([](COMENTARIO<string>*a) { return a->getpos(); });
    };
    T texto;
    T photo;
    int *like;
    int id;
    T fecha;
    int idu;
    QVBoxLayout *todo=new QVBoxLayout();
    Coment*comentarios=new Coment();
public:
    Publicacion(T tx, T ph,int *likes, int pos, T date,int iddu) {
        texto = tx;
        photo = ph;
        this->id = pos;
        like = likes;
        fecha=date;
        idu=iddu;
    }
    Publicacion(QVBoxLayout *A,T tx, T ph,int *likes, int pos, T date){
        texto = tx;
        photo = ph;
        this->id = pos;
        like = likes;
        fecha=date;
        todo=A;

    }

    void setTexto(T a) { texto = a; }
    void setPhoto(T a) { photo = a; }
    void setLike(int a) { like = a; }
    T getTexto() { return texto; }
    T getPhoto() { return photo; }
    T getFecha(){return fecha;}
    int getIdu(){return idu;}
    void setLayout(QVBoxLayout* aa){
        todo=aa;

    }
    QVBoxLayout* getLayout(){return todo;}
    void maslike() { like++; }
    int getLike() { return like; }
    int getId() { return id; }
    void addComment(COMENTARIO<string>*x) {
        comentarios->text->add(x);
        comentarios->text->add(x);
    }
    void removeComment(COMENTARIO<string>*x) {
        comentarios->text->remove(x);
        comentarios->posicion->remove(x);
    }
    Coment* getComent(){
        return comentarios;

    }};
#endif // PUBLICACION_H
