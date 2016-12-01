#ifndef RESPONDFRIENDREQUESTHANDLER_H
#define RESPONDFRIENDREQUESTHANDLER_H

#include "EventHandlerChecksAuthentication.h"

//!Clase handler que responde notificacion de agregar amigo
/*!Hereda de EventHandlerChecksAuthentication.
*/
class RespondFriendRequestHandler : public EventHandlerChecksAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator y los guarda en db y auth.
        */
        RespondFriendRequestHandler(Database *db, TokenAuthenticator *a);
        virtual ~RespondFriendRequestHandler();

    protected:

    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest el username y busca el usuario\
        Luego extrae los datos a modificar y los cambia.
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // RESPONDFRIENDREQUESTHANDLER_H
