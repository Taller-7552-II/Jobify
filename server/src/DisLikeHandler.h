#ifndef DISLIKEHANDLER_H
#define DISLIKEHANDLER_H

#include "EventHandlerIgnoresAuthentication.h"

//!Clase handler que elimina usuario.
/*!Hereda de EventHandlerIgnoresAuthentication.
*/
class DisLikeHandler : public EventHandlerIgnoresAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator y los guarda en db y auth.
        */
        DisLikeHandler(Database *db, TokenAuthenticator *a);
        virtual ~DisLikeHandler();

    protected:
    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest el username y elimina el like.
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // DISLIKEHANDLER_H
