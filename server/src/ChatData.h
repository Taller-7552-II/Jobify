#ifndef CHATDATA_H
#define CHATDATA_H

#include "DBElement.h"
#include <vector>
#include <string>
#include <algorithm>
#include "leveldb/status.h"

class User;


//!Clase que contiene la informacion del usuario.
/*!Tiene los datos del usuario y se encarga de manejarlos\
Hereda de DBElement.
*/
class ChatData : public DBElement
{
    public:
        friend class User;


        //!Funcion que inicializa la clase.
        /*!Realiza la misma inicializacion que DBElement, pero ademas sus variables particulares
        las inicia en "", 0 o en el caso de couta_max, en 10GB.
        */
        ChatData(Database* db, DatabaseWriteBatch* dbbatch = NULL);
        virtual ~ChatData();

        //!Funcion que establece el username.
        /*!Recibe un string y se lo asigna a username.
        */
        void setUsername(std::string name) { this->username = name; }


        //!Funcion que cambia la lista de notificaciones.
        /*!Recibe como string las nuevas notificaciones y la asigna a la variable.
        */
        void addMensajes(std::string u) { this->mensajes.push_back(u); }
        //!Funcion que devuelve el username.
        std::string getUsername() { return username; }
        //!Funcion que obtiene la metadata del usuario de la base de datos.
        Status DBget();


        //!Funcion que agrega una notificacion en la base de datos
        Status DBaddMensajes(std::string u);
        //!Funcion que devuelve el perfil del usuario
        /*!Devuelve el perfil del usuario en fortato json
        */
        std::string getProfile();

        //!Funcion que crea al usuario en la base de datos.
        /*!Si no existe ya el usuario, lo crea y registra la fecha de inscripcion.
        */
        Status DBcreate();


    protected:

        //!Funcion que establece la key.
        /*!Toma la variable username y la establece como key, luego de agrgarle ".usertoken".
        */
        virtual void _setKey();

        //!Funcion que establece el value.
        /*!Toma las variables join_date,  email y forma un json.
        */
        virtual void _setValue();

        //!Funcion que establece varias variables.
        /*!Toma la variable value y a partir de ella obtiene join_date, email y ultima_ubicacion.
        */
        virtual void _setValueVars();

    private:
        //!Variable string que contiene username.
        std::string username;


        //!Variable para mensajes
        std::vector<std::string> mensajes;
        // agregar lo que haga falta


        //!Funcion que elimina usuario de la base de datos.
        Status DBerase();


};

#endif // CHATDATA_H
