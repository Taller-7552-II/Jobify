#ifndef TOPRANKGETHANDLER_H
#define TOPRANKGETHANDLER_H

#include "EventHandlerIgnoresAuthentication.h"

//!Clase handler que obtiene un usuario.
/*!Hereda de EventHandlerChecksAuthentication.
*/
class TopRankGetHandler : public EventHandlerIgnoresAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator al divino boton pero queda poco tiempo
        */
        TopRankGetHandler(Database *db, TokenAuthenticator *a);
        virtual ~TopRankGetHandler();

    protected:
    private:
        //!Funcion que maneja httprequests.
        /*!Devuelve el top de los likes
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // TOPRANKGETHANDLER_H
