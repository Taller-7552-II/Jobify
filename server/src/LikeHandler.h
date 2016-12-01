#ifndef LIKEHANDLER_H
#define LIKEHANDLER_H

#include "EventHandlerIgnoresAuthentication.h"

//!Clase handler que elimina usuario.
/*!Hereda de EventHandlerIgnoresAuthentication.
*/
class LikeHandler : public EventHandlerIgnoresAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator y los guarda en db y auth.
        */
        LikeHandler(Database *db, TokenAuthenticator *a);
        virtual ~LikeHandler();

    protected:
    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest el username y username 2 y le da like.
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // LIKEHANDLER_H
