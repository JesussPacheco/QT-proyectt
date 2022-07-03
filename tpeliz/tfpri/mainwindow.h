#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"Usuarios.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
QT_BEGIN_NAMESPACE
#include<QListWidgetItem>
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum Ventanas{login,registro,principal,amigos};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    typedef Usuarios<Usuario<string>*, string> UsuariosString;
    typedef Usuarios<Usuario<string>*, int> UsuariosInt;
    struct Users {
        UsuariosString*name = new   UsuariosString([](Usuario<string>*a) { return a->getNombre(); });
        UsuariosString*adress = new UsuariosString([](Usuario<string>*a) { return a->getCorreo(); });
        UsuariosString*date = new   UsuariosString([](Usuario<string>*a) { return a->getFecha(); });
        UsuariosInt*id = new   UsuariosInt([](Usuario<string>*a) { return a->getID(); });
    };
    struct Post {
        PUBLICACIONES<Publicacion<string>*, string>*text = new PUBLICACIONES<Publicacion<string>*, string>([](Publicacion<string>*a) { return a->getTexto(); });
        PUBLICACIONES<Publicacion<string>*, int>*id = new PUBLICACIONES<Publicacion<string>*, int>([](Publicacion<string>*a) { return a->getId(); });
        HashTable<string, BusquedaPub<Publicacion<string>*>*>iniciaCon;
        HashTable<string, BusquedaPub<Publicacion<string>*>*>terminaCon;

    };
        Usuario<string>*usaux;
         Usuario<string>*auxAmix;//mostrar amigo actual
     int len=1;
   Users*ususarios=new Users;
   QString auxfoto="";
   Post *totalposts = new Post;
   QString auxfotoRegistro;
   QVBoxLayout *lay=new QVBoxLayout(this);
   QVBoxLayout *laySeguido=new QVBoxLayout;
   QWidget *conten=new QWidget();
   int can=0;
private slots:
//void on_btnRegistrarse_clicked();
   void CargarData();
void Registrarse();
void VentanaRegistro();
void VentanaLogin();
void VentanaPrincipal();
void CargarFollowers();
void MostrarListaSeguidos(string opc,Usuario<string>*userr,QListWidget*&lista);
void MostrarListaSeguidores(string opc,Usuario<string>*userr,QListWidget*&lista);
void on_btnRCargarImg_released();
void on_btnLngresar_clicked();
void on_btnCerrar_clicked();
QVBoxLayout* Publicacioonlayout(QString usuario,QString fechaa, QString userf,QString txt,QString ph,int *likes,Publicacion<string>* nn);
void on_CboxOrden_currentIndexChanged(const QString &arg1);
QVBoxLayout* Comentariolayout(QString usuario,QString fechaa,QString txt);
void CargarPublicaciones();
void on_CboxOrden_2_currentIndexChanged(const QString &arg1);
void CargarComentarios();
void on_btnPublicar_clicked();
//void CrearPublicacion(QString text,QString usuario,string ff,string fecha);
void on_btnImgPubl_clicked();
void VentanaAmigo();
void on_listSeguidos_itemDoubleClicked(QListWidgetItem *item);

void on_listSeguidores_itemDoubleClicked(QListWidgetItem *item);
void AgregarMensaje();
void MostrarChat();
void Buscar(QString opc,QString abuscar);
void on_btnGO_released();
private:
    Ui::MainWindow *ui;
public slots:

};

#endif // MAINWINDOW_H
