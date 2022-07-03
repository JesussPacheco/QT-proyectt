#ifndef MENSAJE_H
#define MENSAJE_H
template<class T,class R=T>
class Mensaje{
    T sms;
    T date;
    T id;

public:
    Mensaje(T sms=" ",T date=" ",T id=""):sms(sms),date(date),id(id){

    }
    T getSms(){return sms;}
    T getDate(){return date;}
    T getID(){return id;}

};
#endif // MENSAJE_H
