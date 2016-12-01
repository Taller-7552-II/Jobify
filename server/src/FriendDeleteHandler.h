#ifndef FRIENDDELETEHANDLER_H
#define FRIENDDELETEHANDLER_H

#include "EventHandlerChecksAuthentication.h"

//!Clase handler que elimina usuario.
/*!Hereda de EventHandlerChecksAuthentication.
*/
class FriendDeleteHandler : public EventHandlerChecksAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator y los guarda en db y auth.
        */
        FriendDeleteHandler(Database *db, TokenAuthenticator *a);
        virtual ~FriendDeleteHandler();

    protected:
    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest el username y elimina el amigo.
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // FRIENDDELETEHANDLER_H
