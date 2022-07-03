#ifndef RESPUESTA_H
#define RESPUESTA_H
template <class T, class R = T>
class RESPUESTA {
    T texto;
    T photo;
    int like;
    int pos;
public:
    RESPUESTA(T tx, T ph, int pos) {
        texto = tx;
        photo = ph;
        this->pos = pos;
        like = 0;
    }
    void setTexto(T a) { texto = a; }
    void setPhoto(T a) { photo = a; }
    void setLike(int a) { like = a; }
    T getTexto() { return texto; }
    T getPhoto() { return photo; }
    void maslike() { like++; }
    int getLike() { return like; }
    int getpos() { return pos; }

};
#endif // RESPUESTA_H
