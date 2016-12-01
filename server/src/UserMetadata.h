#ifndef USERMETADATA_H
#define USERMETADATA_H

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
class UserMetadata : public DBElement
{
    public:
        friend class User;


        //!Funcion que inicializa la clase.
        /*!Realiza la misma inicializacion que DBElement, pero ademas sus variables particulares
        las inicia en "", 0 o en el caso de couta_max, en 10GB.
        */
        UserMetadata(Database* db, DatabaseWriteBatch* dbbatch = NULL);
        virtual ~UserMetadata();

        //!Funcion que establece el username.
        /*!Recibe un string y se lo asigna a username.
        */
        void setUsername(std::string name) { this->username = name; }


        //!Funcion que establece la fecha de inscripcion.
        /*!Recibe un string y lo establece como la fecha.
        */
        void setJoinDate(std::string date) { this->join_date = date; }

        //!Funcion que cambia el resume por uno nuevo.
        /*!Recibe como string el nuevo resume y lo asigna a la variable.
        */
        void changeResume(std::string n_email) { this->resume = n_email; }

        //!Funcion que cambia el mail por uno nuevo.
        /*!Recibe como string el nuevo mail y lo asigna a la variable.
        */
        void changeEmail(std::string n_email) { this->email = n_email; }

        std::string getEmail() { return this->email; }

        //!Funcion que cambia la ultima ubicacion del usuario.
        /*!Recibe como string la nueva ubicacion y la asigna a la variable.
        */
        void changeUltimaUbicacion(std::string u) { this->ultima_ubicacion = u; }

        //!Funcion que cambia la lista de job
        /*!Recibe como string el nuevo job y la asigna a la variable.
        */
        void changeJobList(std::string u) { this->jobList = u; }

        //!Funcion que cambia la lista de skill
        /*!Recibe como string el nuevo skill y la asigna a la variable.
        */
        void changeSkillList(std::string u) { this->skillList = u; }


        //!Funcion que cambia la lista de notificaciones.
        /*!Recibe como string las nuevas notificaciones y la asigna a la variable.
        */
        void addNotificacion(std::string u) { this->notificaciones.push_back(u); }

        //!Funcion que borra una notificacion
        /*!Recibe como string cual borrar.
        */
        void removeNotification(std::string u);

        //!Funcion que cambia la lista de contactos
        /*!Recibe como string la lista de contactos y la asigna a la a la ultima .
        */
        void addFriend(std::string u) { this->friendList.push_back(u); }

        //!Funcion que cambia la lista de Likes
        /*!Recibe como string la lista de Likes y la asigna a la a la ultima .
        */
        void addLike(std::string u) { this->likeList.push_back(u); }

        //!Funcion que borra un Like
        /*!Recibe como string el nombre del Like
        */
        void removeLike(std::string u);

        //!Funcion que borra un contacto
        /*!Recibe como string el nombre del contacto
        */
        void removeFriend(std::string u);

        //!Funcion que cambia el nombre del usuario
        /*!Recibe el nombre y cambia su variable asociada
        */
        void changeName(std::string n) {this->name = n;}

         //!Funcion que cambia la foto del usuario del usuario
        /*!Recibe la foto encriptada y cambia su variable asociada
        */
        void changePic(std::string p) {this->picture = p;}

        std::string getUltimaUbicacion() { return this->ultima_ubicacion; }


        //!Funcion que devuelve la fecha de inscripcion.
        std::string getJoinDate() { return join_date; }

        //!Funcion que devuelve el username.
        std::string getUsername() { return username; }

        //!Funcion que devuelve el username.
        std::vector<std::string>*  getLikeList() { return &likeList; }

        //!Funcion que obtiene la metadata del usuario de la base de datos.
        Status DBget();

        //!Funcion que cambia la foto de perfil
        Status DBchange_profile_pic(std::string picture);

        //!Funcion que cambia el nombre que aparece en perfil
        Status DBchange_name(std::string name);

        //!Funcion que cambia la ultima ubicacion
        Status DBchange_last_place(std::string place);

        //!Funcion que cambia mail en la base de datos.
        Status DBchange_email(std::string n_email);

        //!Funcion que cambia resume en la base de datos.
        Status DBchange_resume(std::string n_email);
        //!Funcion que cambia skill list en la base de datos.
        Status DBchange_skill_list(std::string n_email);

        //!Funcion que cambia job list en la base de datos.
        Status DBchange_job_list(std::string n_email);

        //!Funcion que agrega una notificacion en la base de datos
        Status DBaddNotification(std::string u);

        //!Funcion que borra una notificacion en la base de datos
        Status DBremoveNotification(std::string u);

        //!Funcion que agrega un amigo en la base de datos
        Status DBaddFriend(std::string u, bool cyclic = false);

        //!Funcion que borra un amigo en la base de datos
        Status DBremoveFriend(std::string u);

        //!Funcion que agrega un Like en la base de datos
        Status DBaddLike(std::string u);

        //!Funcion que borra un Like en la base de datos
        Status DBremoveLike(std::string u);
        //!Variable string que contiene jobList.
        std::string jobList;

        //!Variable string que contiene skillList.
        std::string skillList;
        //!Funcion que devuelve el perfil del usuario
        /*!Devuelve el perfil del usuario en fortato json
        */
        std::string getProfile();

        //!Variable para la lista de Likes
        std::vector<std::string> likeList;
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

        //!Variable string que contiene resume.
        std::string resume;

        //!Variable con la fecha de inscripcion.
        /*!Contiene la fecha en que el usuario creo su cuenta.
        */
        std::string join_date;

        //!Variable con el mail del usuario.
        std::string email;

        //!Variable con nombre del usuario
        std::string name;

        //!Variable con foto del usuario encriptada en base64
        std::string picture;

        //!Variable con la ultima ubicacion del usuario.
        std::string ultima_ubicacion;

        //!Variable para la lista de amigos
        std::vector<std::string> friendList;


        //!Variable para notificaciones
        std::vector<std::string> notificaciones;
        // agregar lo que haga falta


        //!Funcion que elimina usuario de la base de datos.
        Status DBerase();

        //!Funcion que crea al usuario en la base de datos.
        /*!Si no existe ya el usuario, lo crea y registra la fecha de inscripcion.
        */
        Status DBcreate();

        //!Funcion que cambia ultima ubicacion en la base de datos.
        Status DBchange_ultima_ubicacion(std::string u);
};

#endif // USERMETADATA_H
