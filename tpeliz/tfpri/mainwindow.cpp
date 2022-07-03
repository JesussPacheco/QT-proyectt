#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include<QString>
#include <QDate>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <QTextStream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "Usuario.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    laySeguido->setAlignment(Qt::AlignTop);
    CargarData();
    QPixmap logocam(":/Imagenes/camara.png");
    ui->btnImgPubl->setIconSize(QSize(45,45));
    ui->btnImgPubl->setIcon(logocam);
    QPixmap perfill(":/Imagenes/perfillogo.png");
    ui->btnMiPerfil->setIconSize(QSize(55,55));
    ui->btnMiPerfil->setIcon(perfill);
    connect(ui->btnLNuevacuenta,SIGNAL(released()),this,SLOT(VentanaRegistro()));
    connect(ui->btnRRegistrarse,SIGNAL(released()),this,SLOT(Registrarse()));
    connect(ui->btnMiPerfil,SIGNAL(released()),this,SLOT(VentanaPrincipal()));
    connect(ui->btnEnviarSms,SIGNAL(released()),this,SLOT(AgregarMensaje()));
    connect(ui->refresh,SIGNAL(released()),this,SLOT(Refrescar()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Registrarse(){
        QString nom=ui->tbxRNombre->text();
        QString correo=ui->tbxRCorreo->text();
        QString contrase=ui->tbxRContra->text();
        string fecha="";
        fecha+= (ui->boxRDia->text()).toLocal8Bit().constData(); fecha+="/";
        fecha+= (ui->boxRMes->text()).toLocal8Bit().constData();fecha+="/";
        fecha+= (ui->boxRA->text()).toLocal8Bit().constData();
        QString auxFecha=QString::fromUtf8(fecha.c_str());;
        Usuario<string>*new_user=new Usuario<string>(nom.toStdString(), correo.toStdString(), fecha, contrase.toStdString() , auxfotoRegistro.toStdString(),len);
        len++;
        ususarios->adress->add(new_user);
        ususarios->name->add(new_user);
        ususarios->id->add(new_user);
        ususarios->date->add(new_user);
        VentanaLogin();

}
void MainWindow::VentanaRegistro(){
     ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::VentanaLogin(){
      ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::VentanaPrincipal(){
     QString opcion=ui->CboxOrden->currentText();
     QString opcion2=ui->CboxOrden_2->currentText();
     MostrarListaSeguidores(opcion2.toStdString(),usaux,ui->listSeguidores);
     MostrarListaSeguidos(opcion.toStdString(),usaux,ui->listSeguidos);
    ui->stackedWidget->setCurrentIndex(2);
    }
void MainWindow::VentanaAmigo(){
ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_btnRCargarImg_released()
{
    QString filename;
       filename=QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
       if(QString::compare(filename,QString())!=0){
           QImage image;
           bool valid=image.load(filename);
           if(valid){
               image=image.scaledToWidth(ui->label->width(),Qt::SmoothTransformation);
               ui->label->setPixmap(QPixmap::fromImage(image));
               auxfotoRegistro=filename;
           }
       }


}
void MainWindow::CargarData(){
    QString direccionArch= QDir::currentPath()+"/users.txt";// ***********************carga los usuarios
    string ss=direccionArch.toStdString();

        ifstream file(ss);
        int id;
        string idd,email,name,date;
      while (getline(file, idd, '\t')) {
          QString iidd=QString::fromUtf8(idd.c_str());
           id=iidd.split(" ")[0].toInt();
            getline(file, email, '\t');
            file >> name; file.get();
            getline(file, date);
          Usuario<string>* aux=new Usuario<string>(name,email,date,"",":/Imagenes/userdesc.jpg",id);
           ususarios->id->add(aux);
           ususarios->date->add(aux);
           ususarios->name->add(aux);
           ususarios->adress->add(aux);
        }
        file.close();
        CargarFollowers();
        CargarPublicaciones();
        CargarComentarios();
}
void MainWindow::CargarFollowers(){
    QString direccionArch= QDir::currentPath()+"/followers.txt";// ***********************carga los seguidos y seguidores
    string ss=direccionArch.toStdString();
    ifstream file(ss);
    int id,idf;
    string idd,iddf;
    file.ignore();
    while (file>>idd) {
        file.get();
        getline(file,iddf);
        QString iidd=QString::fromUtf8(idd.c_str());
        id=iidd.split(" ")[0].toInt();
         QString iiddf=QString::fromUtf8(iddf.c_str());
         idf=iiddf.split(" ")[0].toInt();
        Usuario<string>* usaux=ususarios->id->find(id);
        Usuario<string>* seguido=ususarios->id->find(idf);
        usaux->addSeguido(seguido);
        Mensajes<Mensaje<string>*>*chataux=new  Mensajes<Mensaje<string>*>(seguido->getNombre()) ;
        usaux->addChat(chataux);
        seguido->addSeguidor(usaux);
        Mensajes<Mensaje<string>*>*chataux2=new  Mensajes<Mensaje<string>*>(usaux->getNombre()) ;
        seguido->addChat(chataux2);
    }
     file.close();
}
void MainWindow::CargarPublicaciones(){
    QString direccionArch= QDir::currentPath()+"/publications.txt";// ***********************carga las publicaciones
    string ss=direccionArch.toStdString();

        ifstream file(ss);
        int id,likes,idu;
        string idd,texto,iddus,likees,date,aux;
      while (getline(file, idd, '\t')) {
          QString auxqstring=idd.c_str();
          getline(file, iddus, '\t');
          QString auxqstring1=iddus.c_str();
          idu=auxqstring1.split(" ")[0].toInt();

          getline(file, texto, '\t');
          QString auxqstring2=texto.c_str();
          getline(file, aux, '\t');
          file >> date; file.get();
          QString auxqstring3=date.c_str();
          getline(file, likees);
          QString auxqstring4=likees.c_str();
        if(ususarios->id->find(idu)!=nullptr){
            Usuario<string>* auxx=ususarios->id->find(idu);
                    QString a=""; int *likess=new int(auxqstring4.split(" ")[0].toInt());
                     Publicacion<string>* postaux=new Publicacion<string>(texto,"",likess,auxqstring.split(" ")[0].toInt(),date,idu);
                     QVBoxLayout *llayout(Publicacioonlayout(auxx->getNombre().c_str(),auxqstring3,auxx->getPhoto().c_str(),auxqstring2,a,likess,postaux));
                    postaux->setLayout(llayout);
                    auxx->addPost(postaux);
                          totalposts->id->add(postaux);
                          totalposts->text->add(postaux);
                          ///insert hash
                          auto ini = [&](string s) {string result;
                              for (auto elem : s) {
                                  if (elem == ' ')break;
                                  result += elem;
                              }
                              return result; };
                              auto fini = [&](string s) {string result;
                              for (int i = s.size() - 1; true; i--) {
                                  if (s[i] == ' ')break;
                                  result += s[i];
                              }
                              reverse(result.begin(), result.end());
                              return result; };

                              string auxini = ini(texto);
                                 string auxfini = fini(texto);

                                      if (!totalposts->iniciaCon.count(auxini)) {
                                          totalposts->iniciaCon[auxini] = new BusquedaPub<Publicacion<string>*>;
                                          totalposts->iniciaCon[auxini]->Add(postaux);
                                      }
                                      else
                                          totalposts->iniciaCon[auxini]->Add(postaux);
                                      if (!totalposts->terminaCon.count(auxfini)) {
                                         totalposts-> terminaCon[auxfini] = new BusquedaPub<Publicacion<string>*>;
                                         totalposts-> terminaCon[auxfini]->Add(postaux);
                                      }
                                      else
                                         totalposts->terminaCon[auxfini]->Add(postaux);
                         }//T tx, T ph,int likes, int pos, T date
                         }
                       file.close();
                 }

void MainWindow::CargarComentarios(){
    QString direccionArch= QDir::currentPath()+"/comment.txt";// ***********************carga las publicaciones
    string ss=direccionArch.toStdString();

        ifstream file(ss);
        int id,likes,idpu;
        string idd,texto,iddpu,likees,date,aux;
      while (getline(file, idd, '\t')) {
          QString auxqstring=idd.c_str();
          getline(file, iddpu, '\t');
          QString auxqstring1=iddpu.c_str();
          idpu=auxqstring1.split(" ")[0].toInt();
          file >> date; file.get();
          QString auxqstring3=date.c_str();
          getline(file, texto);
          QString auxqstring2=texto.c_str();

        if(totalposts->id->find(idpu)!=nullptr){

         Publicacion<string>* auxx=totalposts->id->find(idpu);
         Usuario <string>* usuarioo=ususarios->id->find(auxx->getIdu());
         QString a="";
         COMENTARIO<string>* postaux=new COMENTARIO<string>(texto,"",idpu,date);
         QVBoxLayout *llayout(Comentariolayout(usuarioo->getNombre().c_str(),auxqstring3,texto.c_str()));
         postaux->setTodo(llayout);
         auxx->addComment(postaux);
      //   auxx->getComent()->posicion->inOrder([&](COMENTARIO<string>*a){
         auxx->getLayout()->addLayout(llayout);
                  //   });

        }//T tx, T ph,int likes, int pos, T date
        }
      file.close();
}
QVBoxLayout* MainWindow::Comentariolayout(QString usuario,QString fechaa,QString txt){
    QLabel *space=new QLabel();
    space->setMaximumWidth(100);
    space->setWordWrap(true);

    QVBoxLayout *todo=new QVBoxLayout;
    todo->setAlignment(Qt::AlignTop);
    QPixmap photoo(":/Imagenes/userdesc.jpg");
      QLabel *lblf=new QLabel();
     lblf->setPixmap(photoo.scaled(30,30,Qt::KeepAspectRatio));
      lblf->setMaximumWidth(50);
      QLabel *llnom=new QLabel(usuario);
      llnom->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
      llnom->setWordWrap(true);
        // llnom->setStyleSheet("Text-align:left");
      QLabel *llfech=new QLabel(fechaa);
      llfech->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
      llfech->setWordWrap(true);
      llfech->setAlignment(Qt::AlignRight);

      QHBoxLayout *perfil = new QHBoxLayout;
      perfil->addWidget(space);
      perfil->addWidget(lblf);
      perfil->addWidget(llnom);
      perfil->addWidget(llfech);

      QLabel *ll=new QLabel(txt);
      ll->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
      ll->setWordWrap(true);

      QHBoxLayout *textoo = new QHBoxLayout;
      textoo->addWidget(space);
      textoo->addWidget(ll);

      todo->addLayout(perfil);
      todo->setSpacing(10);
      todo->addLayout(textoo);
      return todo;
}

QVBoxLayout* MainWindow::Publicacioonlayout(QString usuario,QString fechaa, QString userf,QString txt,QString ph,int *likes,Publicacion<string> *publ){
int *llike=likes; Publicacion <string>* pntr=publ;
    string fecha;
    QVBoxLayout *todo=new QVBoxLayout;
    todo->setAlignment(Qt::AlignTop);
  QPixmap photoo(userf);
    QLabel *lblf=new QLabel();
   lblf->setPixmap(photoo.scaled(30,30,Qt::KeepAspectRatio));
    lblf->setMaximumWidth(50);

    QLabel *llnom=new QLabel(usuario);
    llnom->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    llnom->setWordWrap(true);
      // llnom->setStyleSheet("Text-align:left");
    QLabel *llfech=new QLabel(fechaa);
    llfech->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    llfech->setWordWrap(true);
    llfech->setAlignment(Qt::AlignRight);

    QHBoxLayout *perfil = new QHBoxLayout;
    perfil->addWidget(lblf);
    perfil->addWidget(llnom);
    perfil->addWidget(llfech);

    QLabel *ll=new QLabel(txt);
    ll->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    ll->setWordWrap(true);

    QString like=to_string(*likes).c_str();
    QPushButton *btnLike = new QPushButton("â™¥ "+like);
   QPushButton *btnComent = new QPushButton("Comentar");
    QPushButton *btnShare = new QPushButton("Compartir");

    QHBoxLayout *botones = new QHBoxLayout;
    botones->addWidget(btnLike);
    botones->addWidget(btnComent);
    botones->addWidget(btnShare);
    botones->setSpacing(20);

    todo->addLayout(perfil);
    todo->addWidget(ll);
    if(ph!=""){
        QLabel *llp=new QLabel();
        QPixmap aux(ph);
        llp->setPixmap(aux.scaled(300,300,Qt::KeepAspectRatio));
        llp->setAlignment(Qt::AlignCenter);
        todo->addWidget(llp);
    }
    todo->setSpacing(10);
    todo->addLayout(botones);
    connect(btnLike, &QPushButton::clicked,[=](){
        (*llike)++;
        QString likke=to_string(*llike).c_str();
        btnLike->setText("â™¥ "+likke);});

    connect(btnShare, &QPushButton::clicked,[=](){
        usaux->addPost(publ);
     /*   if(usaux->getPost()->id->size()!=0){
            usaux->getPost()->id->inOrder([&](Publicacion<string>*a){

                 lay->addLayout(a->getLayout());

            });
        }*/
    } );
    return todo;
}

void MainWindow::MostrarListaSeguidos(string opc,Usuario<string>*userr,QListWidget*&lista){
    if(userr->getSeguido()->name->size()!=0){
        ui->listSeguidos->clear();
        if(opc=="NOMBRE"){
           userr->getSeguido()->name->inOrder([&](Usuario<string>*a) {
            QString nombre = a->getNombre().c_str();
            QString adress =(a->getCorreo().c_str());
            QString date=(a->getFecha().c_str());
       lista->addItem(nombre + "\t" +adress+"\t"+date);
        });
        }
        else if(opc=="CORREO"){
           userr->getSeguido()->adress->inOrder([&](Usuario<string>*a) {
            QString nombre = a->getNombre().c_str();
            QString adress =(a->getCorreo().c_str());
            QString date=(a->getFecha().c_str());
            lista->addItem(adress+ "\t" +nombre +"\t"+date);
        });
        }
        else{
            userr->getSeguido()->date->inOrder([&](Usuario<string>*a) {
            QString nombre = a->getNombre().c_str();
            QString adress =(a->getCorreo().c_str());
            QString date=(a->getFecha().c_str());
            lista->addItem(date+ "\t" +nombre +"\t"+adress);
        });
        }
        }

}
void MainWindow::MostrarListaSeguidores(string opc,Usuario<string>*userr,QListWidget*&lista){
    if(userr->getSeguidor()->name->size()!=0){
        lista->clear();
        if(opc=="NOMBRE"){
           userr->getSeguidor()->name->inOrder([&](Usuario<string>*a) {
            QString nombre = a->getNombre().c_str();
            QString adress =(a->getCorreo().c_str());
            QString date=(a->getFecha().c_str());
            lista->addItem(nombre + "\t" +adress+"\t"+date);
        });
        }
        else if(opc=="CORREO"){
           userr->getSeguidor()->adress->inOrder([&](Usuario<string>*a) {
            QString nombre = a->getNombre().c_str();
            QString adress =(a->getCorreo().c_str());
            QString date=(a->getFecha().c_str());
            lista->addItem(adress+ "\t" +nombre +"\t"+date);
        });
        }
        else{
            userr->getSeguidor()->date->inOrder([&](Usuario<string>*a) {
            QString nombre = a->getNombre().c_str();
            QString adress =(a->getCorreo().c_str());
            QString date=(a->getFecha().c_str());
            lista->addItem(date+ "\t" +nombre +"\t"+adress);
        });
        }
        }

}
void MainWindow::on_btnLngresar_clicked(){
    if(ui->tbxLcorreo->text()!=""){
        string aux=ui->tbxLcorreo->text().toStdString();
        if(ususarios->adress->find(aux)!=nullptr){
         usaux=ususarios->adress->find(aux);
         ui->lblEmail->setText(to_string(usaux->getlen()).c_str());
            ui->lblNombrePerfil->setText(QString::fromUtf8(usaux->getNombre().c_str()));
            ui->tbxEmailPerfil->setText(QString::fromUtf8(usaux->getCorreo().c_str()));
            ui->tbxFechaCrea->setText(QString::fromUtf8(usaux->getFecha().c_str()));
            QPixmap photo(QString::fromUtf8(usaux->getPhoto().c_str()));
            ui->lblFotoperfil->setPixmap(photo.scaled(190,190,Qt::KeepAspectRatio));
            //***********************************************************************************cargar seguidores
            // add a la list seguidos
             VentanaPrincipal();
             MostrarListaSeguidos("NOMBRE",usaux,ui->listSeguidos);
             MostrarListaSeguidores("NOMBRE",usaux,ui->listSeguidores);
             //cargar publicaciones

          //QWidget *variable = ui->scrollArea->widget();
          //if(variable){variable->deleteLater();}

             //QVBoxLayout * lay = new QVBoxLayout();
            lay->setAlignment(Qt::AlignTop);

             if(usaux->getPost()->id->size()!=0){
                 usaux->getPost()->id->inOrder([&](Publicacion<string>*a){
                     QString date=a->getFecha().c_str();
                     QString txt=a->getTexto().c_str();
                     ui->listPubli->addItem(date+"\n"+txt);
                      a->getComent()->posicion->inOrder([&](COMENTARIO<string>*b){
                          QString datecomm=b->getTexto().c_str();
                          QString likcomm=to_string(b->getLike()).c_str();
                           ui->listPubli->addItem("\n"+datecomm+" "+likcomm+"\n");
                 });
                 });
             }
            // ui->scrollAreaWidgetContents->setLayout(lay);

            QWidget *areaVisible= new QWidget();
            areaVisible->setLayout(lay);
          // ui->scrollArea->setLayout(lay);

         //ui->scrollArea->setWidget(areaVisible);
        }else QMessageBox::information(this,tr("Advertencia"),tr("ContraseÃ±a o correo electrÃ³nico incorrecto"));

    }
}

void MainWindow::on_btnCerrar_clicked()
{

    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnPublicar_clicked()//******crea nueva publicacion
{
    QString anho=to_string(QDate::currentDate().year()).c_str();
        QString mes=to_string(QDate::currentDate().month()).c_str();
        QString dia=to_string(QDate::currentDate().day()).c_str();
        QString fecha=anho+"-"+mes+"-"+dia;
  //           ui->scrollAreaWidgetContents->setLayout(lay);
             int *likess=new int(0);
       Publicacion <string>* x=new Publicacion <string>(ui->textEdit->toPlainText().toStdString(),auxfoto.toStdString(),likess,totalposts->id->size()+1,fecha.toStdString(),usaux->getID());
      QVBoxLayout* Wid= Publicacioonlayout(usaux->getNombre().c_str(),fecha,usaux->getPhoto().c_str(),ui->textEdit->toPlainText(),auxfoto,likess,x);
      x->setLayout(Wid);
     lay->addLayout(Wid);

    //ui->scrollAreaWidgetContents->setLayout(lay);
    usaux->addPost(x);
    totalposts->id->add(x);
   // totalposts->text->add(x);
    auxfoto="";
    ui->textEdit->setText("");ui->lblLcorreo->setText(usaux->getCorreo().c_str());
    on_btnLngresar_clicked();
}

void MainWindow::on_btnImgPubl_clicked()
{
    QString filename;
       filename=QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
       if(QString::compare(filename,QString())!=0){
           QImage image;
           bool valid=image.load(filename);
           if(valid){
               image=image.scaledToWidth(ui->label->width(),Qt::SmoothTransformation);
               ui->label->setPixmap(QPixmap::fromImage(image));
               auxfoto=filename;
           }
       }
}

void MainWindow::on_listSeguidos_itemDoubleClicked(QListWidgetItem *item)
{
    istringstream iss( ui->listSeguidos->currentItem()->text().toStdString());
    string busc;
    iss>>busc;
    QString opcion=ui->CboxOrden->currentText();
    if(opcion=="NOMBRE")auxAmix=usaux->getSeguido()->name->find(busc);
    else if(opcion=="CORREO")auxAmix=usaux->getSeguido()->adress->find(busc);
    else auxAmix=usaux->getSeguido()->date->find(busc);
    QPixmap photo(QString::fromUtf8(auxAmix->getPhoto().c_str()));
    ui->lblamixPhoto->setPixmap(photo.scaled(190,190,Qt::KeepAspectRatio));
    VentanaAmigo();
    ui->lblAmixNombre->setText(QString::fromUtf8(auxAmix->getNombre().c_str()));
    MostrarListaSeguidos("NOMBRE",auxAmix,ui->amixSeguidos);
    MostrarListaSeguidores("NOMBRE",auxAmix,ui->AmixSeguidores);
   // ui->scrollAreaWidgetContents_2->setLayout(laySeguido);
    if(auxAmix->getPost()->id->size()!=0){
        auxAmix->getPost()->id->inOrder([&](Publicacion<string>*a){
              laySeguido->addItem(a->getLayout());
        });
    }
    ui->scrollAreaWidgetContents_2->setLayout(laySeguido);
}

void MainWindow::on_listSeguidores_itemDoubleClicked(QListWidgetItem *item)
{
    istringstream iss( ui->listSeguidores->currentItem()->text().toStdString());
    string busc;
    iss>>busc;
    QString opcion=ui->CboxOrden_2->currentText();
    if(opcion=="NOMBRE")auxAmix=usaux->getSeguidor()->name->find(busc);
    else if(opcion=="CORREO")auxAmix=usaux->getSeguidor()->adress->find(busc);
    else auxAmix=usaux->getSeguidor()->date->find(busc);
    QPixmap photo(QString::fromUtf8(auxAmix->getPhoto().c_str()));
    ui->lblamixPhoto->setPixmap(photo.scaled(190,190,Qt::KeepAspectRatio));
    VentanaAmigo();
    ui->lblAmixNombre->setText(QString::fromUtf8(auxAmix->getNombre().c_str()));
    MostrarListaSeguidos("NOMBRE",auxAmix,ui->amixSeguidos);
    MostrarListaSeguidores("NOMBRE",auxAmix,ui->AmixSeguidores);
    if(auxAmix->getPost()->id->size()!=0){
        auxAmix->getPost()->id->inOrder([&](Publicacion<string>*a){
              laySeguido->addItem(a->getLayout());
        });
    }
    ui->scrollAreaWidgetContents_2->setLayout(laySeguido);
}
void MainWindow::AgregarMensaje(){
    string sms=ui->lineEditSms->text().toStdString();
    Mensaje<string>*new_sms=new Mensaje<string>(sms);
   usaux->addSms(new_sms,usaux,auxAmix);
   MostrarChat();
}
void MainWindow::MostrarChat(){
    Mensajes<Mensaje<string>*>*aux=usaux->getChats()->sms->find(auxAmix->getNombre());
      ui->textEditMensajes->clear();
    aux->LoveLambda([&](Mensaje<string>*a){

        QString auxsms= a->getSms().c_str();
        ui->textEditMensajes->append(auxsms+"\n");
            });
    }


void MainWindow::on_CboxOrden_currentIndexChanged(const QString &arg1)
{
    QString opcion=ui->CboxOrden->currentText();
    MostrarListaSeguidos(opcion.toStdString(),usaux,ui->listSeguidos);
}

void MainWindow::on_CboxOrden_2_currentIndexChanged(const QString &arg1)
{
    QString opcion=ui->CboxOrden_2->currentText();
    MostrarListaSeguidores(opcion.toStdString(),usaux,ui->listSeguidores);
}

void MainWindow::Buscar(QString opc,QString abuscar){
    ui->listPubli->clear();
    if (opc == "Inicia") {
        cout<<"entro"<<endl;
              if (totalposts->iniciaCon.count(abuscar.toStdString())) {
                  totalposts->iniciaCon[abuscar.toStdString()]->LoveLambda([&](Publicacion<string> *a) {
                      QString date=a->getFecha().c_str();
                      QString txt=a->getTexto().c_str();
                      ui->listPubli->addItem(date+"\n"+txt);
                       a->getComent()->posicion->inOrder([&](COMENTARIO<string>*b){
                           QString datecomm=b->getTexto().c_str();
                           QString likcomm=to_string(b->getLike()).c_str();
                            ui->listPubli->addItem("\n"+datecomm+" "+likcomm+"\n");
                  });
                  });
              }

              else {
                  cout << "no existe\n";
                  //un mensaje de no existe ese elemento que inicie asi :v
              }
          }

          else if (opc == "Termina") {
        cout<<"SI ENTRA"<<endl;
              if (totalposts->terminaCon.count(abuscar.toStdString())){
                  totalposts->terminaCon[abuscar.toStdString()]->LoveLambda([&](Publicacion<string> *a) {
                      QString date=a->getFecha().c_str();
                      QString txt=a->getTexto().c_str();
                      ui->listPubli->addItem(date+"\n"+txt);
                       a->getComent()->posicion->inOrder([&](COMENTARIO<string>*b){
                           QString datecomm=b->getTexto().c_str();
                           QString likcomm=to_string(b->getLike()).c_str();
                            ui->listPubli->addItem("\n"+datecomm+" "+likcomm+"\n");
                  });
                  });}
              else {
                  cout << "no exisste\n";
                  //mensaje no hay p
              }
          }
          else if (opc == "Igual") {
              Publicacion<string> *auxigual = totalposts->text->find(abuscar.toStdString());
              if (auxigual == nullptr) {
                  QString date=auxigual->getFecha().c_str();
                  QString txt=auxigual->getTexto().c_str();
                  ui->listPubli->addItem(date+"\n"+txt);
                   auxigual->getComent()->posicion->inOrder([&](COMENTARIO<string>*b){
                       QString datecomm=b->getTexto().c_str();
                       QString likcomm=to_string(b->getLike()).c_str();
                        ui->listPubli->addItem("\n"+datecomm+" "+likcomm+"\n");
                   });
              }
              else {
                  cout << auxigual->getTexto();
                  //lo que quieras con auxigual(que se muestre p :'v)
              }
          }
          else if (opc=="Esta") {
              bool salida = false;
             totalposts->id->inOrder([&](Publicacion<string> *a) {
                  istringstream iss(a->getTexto());
                  string s;
                  while (iss >> s) {
                      if (s== abuscar.toStdString()) {
                          salida = true;
                            totalposts->id->inOrder([&](Publicacion<string> *a) {
                              QString date=a->getFecha().c_str();
                              QString txt=a->getTexto().c_str();
                              ui->listPubli->addItem(date+"\n"+txt);
                               a->getComent()->posicion->inOrder([&](COMENTARIO<string>*b){
                                   QString datecomm=b->getTexto().c_str();
                                   QString likcomm=to_string(b->getLike()).c_str();
                                    ui->listPubli->addItem("\n"+datecomm+" "+likcomm+"\n");
                          });
                          });}
                          break;
                      }
                  ; });
              if (!salida) {
                  //mensaje de no se encontro ellemento;
                  cout << "no se encontro" << endl;
              }
          }
          else if (opc=="NoEsta") {
            totalposts->id->inOrder([&](Publicacion<string> *a) {
                  bool ver = false;//para ver si existe o no un elme
                  istringstream iss(a->getTexto());
                  string s;
                  while (iss >> s) {
                      if (s == abuscar.toStdString()) {
                          ver = true;
                          break;
                      }
                  }
                  if (!ver) {
                      totalposts->id->inOrder([&](Publicacion<string> *a) {
                        QString date=a->getFecha().c_str();
                        QString txt=a->getTexto().c_str();
                        ui->listPubli->addItem(date+"\n"+txt);
                         a->getComent()->posicion->inOrder([&](COMENTARIO<string>*b){
                             QString datecomm=b->getTexto().c_str();
                             QString likcomm=to_string(b->getLike()).c_str();
                              ui->listPubli->addItem("\n"+datecomm+" "+likcomm+"\n");
                    });
                    });
                  }
                  ; });
          }

}

void MainWindow::on_btnGO_released()
{
    Buscar(ui->cboxordenpub->currentText(),ui->leditp->text());
}
