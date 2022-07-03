#ifndef HASHT_H
#define HASHT_H
#include <iostream>
#include <vector>
#include <iomanip> //setw() \t
#include <functional>
#include "Lista.h"
using namespace std;
template <typename KEY, typename VAL>
class HashTable {
    //InformaciÃ³n de entrada
    struct DATA {
        KEY key;
        VAL* val;
        DATA() {}
        DATA(KEY key, VAL* val = new VAL) : key(key), val(val) {}
    };

    vector<int> primos;
    //atributos
    vector<DATA*> tabla;
    int capacidad;
    float factor_carga;
    int c_limite;

    function<int(KEY)> codificar; // parte de funcion_hash

public:
        HashTable(int capacidad = 23, float factor_carga = 0.75) {
        GenerarPrimos(capacidad * 2);
        this->codificar = codificar;
        this->capacidad = sgtPrimo(capacidad);
        this->factor_carga = factor_carga;
        this->c_limite = 0;
        //INICIALIZAR EL ESPACIO DE LA TABLA
        for (int i = 0; i < capacidad; i++) {
            tabla.push_back(NULL);
        }
    }

    VAL& operator [](KEY key) {
        if (c_limite >= (int)(factor_carga*capacidad)) resize(this->capacidad * 2);
        int indice = funcion_hash(key);

        if (tabla[indice] == NULL) {
            tabla[indice] = new DATA(key);
            c_limite++;
        }
        return *tabla[indice]->val;
    }
    bool count(KEY x) {
        int indice = funcion_hash(x);
        if (tabla[indice] != NULL) {
            return true;
        }
        else return false;

    }

    int codeString(string a) {
        int sum = 0;
        for (auto elem : a) {
            sum += elem;
        }
        return sum;
    }
    //Criba de erastostenes
    void GenerarPrimos(int n) {
        primos.clear();
        bool* nroPrimos = new bool[n + 1];
        //iniciar datos
        for (int i = 0; i < n; i++) {
            nroPrimos[i] = true;
        }
        //ComprobaciÃ³n multiplos
        for (int i = 2; i*i <= n; i++) {
            for (int j = i * 2; j <= n; j += i) {
                nroPrimos[j] = false;
            }
        }
        for (int i = 2; i <= n; i++) {
            if (nroPrimos[i]) primos.push_back(i);
        }
    }

    int sgtPrimo(int n) {
        for (int primo : primos) {
            if (primo >= n) {
                return primo;
            }
        }
        return -1; //Nunca va a pasar
    }

    void resize(int new_capacidad) {
        vector<DATA*> new_tabla;
        GenerarPrimos(new_capacidad * 2);

        this->capacidad = sgtPrimo(new_capacidad);
        this->c_limite = 0;

        for (int i = 0; i < capacidad; i++) {
            new_tabla.push_back(NULL);
        }

        vector<DATA*> old_tabla = tabla;
        tabla = new_tabla;

        for (int i = 0; i < old_tabla.size(); i++) {
            if (old_tabla[i] != nullptr) {
                int indice = funcion_hash(old_tabla[i]->key);
                if (tabla[indice] == NULL) {
                    tabla[indice] = new DATA(old_tabla[i]->key, old_tabla[i]->val);
                    c_limite++;
                }
            }
        }

    }

    int funcion_hash(KEY key) {
        int codigo = codeString(key);
        auto hash = [=](int i) {return (codigo + i * i) % capacidad; };
        for (int i = 0; true; i++) {
            int indice = hash(i);
            if (indice < 0)indice = indice*-1;
            if (tabla[indice] == NULL || key == tabla[indice]->key) {

                return indice;
            }
        }
    }
};
#endif // HASHT_H
