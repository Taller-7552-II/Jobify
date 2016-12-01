#ifndef SENDFRIENDREQUESTHANDLER_H
#define SENDFRIENDREQUESTHANDLER_H

#include "EventHandlerChecksAuthentication.h"

//!Clase handler que envia notificacion de agregar amigo
/*!Hereda de EventHandlerChecksAuthentication.
*/
class SendFriendRequestHandler : public EventHandlerChecksAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator y los guarda en db y auth.
        */
        SendFriendRequestHandler(Database *db, TokenAuthenticator *a);
        virtual ~SendFriendRequestHandler();

    protected:

    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest el username y busca el usuario\
        Luego extrae los datos a modificar y los cambia.
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // USERPOSTNOTIFICATION_H
