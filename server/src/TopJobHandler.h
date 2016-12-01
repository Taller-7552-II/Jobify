#ifndef TOPJOBHANDLER_H
#define TOPJOBHANDLER_H

#include "EventHandlerIgnoresAuthentication.h"

//!Clase handler que obtiene un usuario.
/*!Hereda de EventHandlerChecksAuthentication.
*/
class TopJobHandler : public EventHandlerIgnoresAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator al divino boton pero queda poco tiempo
        */
        TopJobHandler(Database *db, TokenAuthenticator *a);
        virtual ~TopJobHandler();

    protected:
    private:
        //!Funcion que maneja httprequests.
        /*!Devuelve el top de los likes
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // TOPJOBHANDLER_H
