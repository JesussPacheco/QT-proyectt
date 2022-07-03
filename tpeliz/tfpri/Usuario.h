#ifndef USUARIO_H
#define USUARIO_H
#include<string>
#include"PUBLICACIONES.h"
#include"Amigos.h"
#include"Chats.h"
#include "Mensajes.h"
#include "HashT.h"
//#include<QApplication>
//#include<QLabel>
//#include <QString>
//#include "mainwindow.h"
using namespace std;
template <typename T>
class Usuario {
    typedef PUBLICACIONES<Publicacion<string>*, string>postString;
    typedef PUBLICACIONES<Publicacion<string>*, int>postInt;
    typedef Amigos<Usuario<string>*, string>friendString;
    typedef Amigos<Usuario<string>*, int>friendsInt;
    typedef Chats<Mensajes<Mensaje<string>*>*,string>SmsString;
    struct Seguir {
        friendString*name = new friendString([](Usuario<string>*a) { return a->getNombre(); });
        friendString*adress = new friendString([](Usuario<string>*a) { return a->getCorreo(); });
        friendString*date = new friendString([](Usuario<string>*a) { return a->getFecha(); });
        friendsInt *id=new   friendsInt([](Usuario<string>*a) { return a->getID(); });
    };

    struct Post {
                postString*text = new postString([](Publicacion<string>*a) { return a->getTexto(); });
                postInt*id = new postInt([](Publicacion<string>*a) { return a->getId(); });
                HashTable<string, BusquedaPub<Publicacion<string>*>*>iniciaCon;
                HashTable<string, BusquedaPub<Publicacion<string>*>*>terminaCon;

    };
    struct Chat{  //esta en struct opcional para ver si tambien le ponemos una opcion de busqueda:v
         SmsString*sms=new SmsString([](Mensajes<Mensaje<string>*>*a){return a->getName();});
    };

    T nombre;
    T correo;
    T contrasena;
    T fecha;
    T photo;
    int id;
    Post*publi = new Post();
    Seguir *seguidos = new Seguir();
    Seguir *seguidores = new Seguir();
    Chat *chatsitos=new Chat();
//	MainWindow *perfil;
public:
    Usuario(T nombre="", T correo="", T fecha="", T contrasena = "", T p="",int id=0) :
        nombre(nombre), correo(correo), contrasena(contrasena), fecha(fecha), photo(p),id(id) {
    //	perfil = new MainWindow(nullptr, photo, nombre, apellido, fecha);
    }
    T getNombre() { return  nombre; }
    T getCorreo() { return  correo; }
    T getContrasena() { return  contrasena; }
    T getFecha() { return fecha; }
    T getPhoto() { return photo; }
    int getID(){return id;};
    void setNombre(T n) { nombre = n; }
    void setCorreo(T n) { correo = n; }
    void setContrasena(T n) { contrasena = n; }
    void setFecha(T n) { fecha = n; }
    void setPhoto(T n) { photo = n; }
    void addSeguidor(Usuario<string>*x) {
        seguidores->name->add(x);
        seguidores->adress->add(x);
        seguidores->date->add(x);
        seguidores->id->add(x);
    }
    int codeString(string a) {
        int sum = 0;
        for (auto elem : a) {
            sum += elem;
        }
        return sum;
    }
    void addSeguido(Usuario<string>*x) {
        seguidos->name->add(x);
        seguidos->adress->add(x);
        seguidos->date->add(x);
        seguidos->id->add(x);
    }
    void removeFriend(Usuario<string>*x) {
        seguidos->name->remove(x);
        seguidos->adress->remove(x);
        seguidos->date->remove(x);
    }
    void addPost(Publicacion<string>*x) {
        publi->text->add(x);
            publi->id->add(x);
            auto ini = [&](string s) {string result;
            for (auto elem : s) {
                if (elem == ' ')break;
                result += elem;
            }
            return result; };
            auto fini = [&](string s) {string result;
            for (int i = s.size() - 1; true; i--) {
                if (s[i] == ' '||i<1)break;
                result += s[i];
            }
            reverse(result.begin(), result.end());
            return result; };
            string auxini = ini(x->getTexto());
            string auxfini = fini(x->getTexto());
            if (!publi->iniciaCon.count(auxini)) {
                publi->iniciaCon[auxini] = new BusquedaPub<Publicacion<string>*>;
                publi->iniciaCon[auxini]->Add(x);
            }
            else
                publi->iniciaCon[auxini]->Add(x);
            if (!publi->terminaCon.count(auxfini)) {
                publi-> terminaCon[auxfini] = new BusquedaPub<Publicacion<string>*>;
                publi-> terminaCon[auxfini]->Add(x);
            }
            else
                publi->terminaCon[auxfini]->Add(x);
    }
    void removePost(Publicacion<string>*x) {
        publi->text->remove(x);
        publi->posicion->remove(x);
    }
    void addChat(Mensajes<Mensaje<string>*>*x){
        chatsitos->sms->add(x);
    }
    void addSms(Mensaje<string>*x,Usuario<string>*princs,Usuario<string>*a){
    Mensajes<Mensaje<string>*>*recep=chatsitos->sms->find(a->getNombre());
    recep->Add(x);
    Mensajes<Mensaje<string>*>*dev=a->getChats()->sms->find(princs->getNombre());
    dev->Add(x);

    }
    Seguir*getSeguidor() {
        return seguidores;
    }
    Seguir*getSeguido() {
        return seguidos;
    }
    Post*getPost() {
        return publi;
    }
    Chat *getChats(){
        return chatsitos;
    }
    int getlen(){return seguidos->id->getlen();}
    Usuario<string>* getRoot(){
        return seguidos->id->getRoot();
    }

//	MainWindow* getPerfil() { return perfil; }
};

#endif
